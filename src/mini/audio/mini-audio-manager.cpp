#include "mini-audio-manager.h"
#include "drivers/Es8311Wire.h"
#include "mini/storage/logger.h"
#include "mini/MiniConfig.h"
#include "mini/neopixel/NeoPixel.h"

#include <Wire.h>
#include <FS.h>
#include <SD_MMC.h>

#include "driver/i2s.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

// ---------------------------------------------------------------------------
// Pin / config expectations (add these to MiniConfig.h if not already there,
// values taken from the LCDWIKI manufacturer datasheet):
//
//   AUDIO_I2C_SDA      GPIO_NUM_16   (shared with touch + extended I2C)
//   AUDIO_I2C_SCL      GPIO_NUM_15   (shared with touch + extended I2C)
//   AUDIO_I2S_MCLK     GPIO_NUM_4
//   AUDIO_I2S_BCK      GPIO_NUM_5
//   AUDIO_I2S_DOUT     GPIO_NUM_8    (matches manufacturer's proven demo
//                                     NOT the raw datasheet label, which
//                                     describes pins from the codec's point
//                                     of view rather than the ESP32's)
//   AUDIO_I2S_WS       GPIO_NUM_7
//   AUDIO_AMP_ENABLE   GPIO_NUM_1
//
// Note: datasheet lists GPIO8 as "I2S bus bit input data signal" (DIN) --
// not used here since Mini has no mic input.
// ---------------------------------------------------------------------------

namespace
{
    constexpr size_t   kMaxPathLen        = 96;
    constexpr size_t   kStreamChunkBytes  = 1024;
    constexpr uint32_t kDefaultSampleRate = 44100;
    constexpr int       kDefaultVolume    = 70;

    struct PlayRequest
    {
        char path[kMaxPathLen];
    };

    Es8311Codec codec;
    constexpr i2s_port_t kI2SPort = I2S_NUM_0;
    bool i2sInstalled = false;

    bool     codecReady  = false;
    uint32_t currentRate = 0;

    QueueHandle_t playQueue  = nullptr;
    TaskHandle_t  taskHandle = nullptr;

    volatile bool playing       = false;
    volatile bool stopRequested = false;

    // Minimal WAV header reader. Only cares about the fmt and data chunks,
    // and only supports 16-bit PCM (mono or stereo) -- covers every
    // boot/notification/alarm asset actually shipping on Mini.
    struct WavInfo
    {
        uint32_t sampleRate;
        uint16_t numChannels;
        uint16_t bitsPerSample;
        uint32_t dataSize;
    };

    bool parseWavHeader(File& file, WavInfo& info)
    {
        uint8_t header[12];
        if (file.read(header, 12) != 12) return false;
        if (memcmp(header, "RIFF", 4) != 0 || memcmp(header + 8, "WAVE", 4) != 0)
        {
            Logger::info("Audio", "Not a valid WAV file");
            return false;
        }

        bool haveFmt = false;
        bool haveData = false;

        while (file.available() >= 8)
        {
            uint8_t chunkHeader[8];
            if (file.read(chunkHeader, 8) != 8) break;

            char chunkId[5] = {0};
            memcpy(chunkId, chunkHeader, 4);
            uint32_t chunkSize = chunkHeader[4] | (chunkHeader[5] << 8) |
                                (chunkHeader[6] << 16) | (chunkHeader[7] << 24);

            if (memcmp(chunkId, "fmt ", 4) == 0)
            {
                uint8_t fmt[16];
                if (chunkSize < 16 || file.read(fmt, 16) != 16) return false;

                uint16_t audioFormat = fmt[0] | (fmt[1] << 8);
                info.numChannels     = fmt[2] | (fmt[3] << 8);
                info.sampleRate      = fmt[4] | (fmt[5] << 8) | (fmt[6] << 16) | (fmt[7] << 24);
                info.bitsPerSample   = fmt[14] | (fmt[15] << 8);

                if (chunkSize > 16) file.seek(file.position() + (chunkSize - 16));

                if (audioFormat != 1 /* PCM */ || info.bitsPerSample != 16)
                {
                    Logger::info("Audio", "Only 16-bit PCM WAV is supported");
                    return false;
                }
                haveFmt = true;
            }
            else if (memcmp(chunkId, "data", 4) == 0)
            {
                info.dataSize = chunkSize;
                haveData = true;
                break; // file is now positioned right at PCM data
            }
            else
            {
                file.seek(file.position() + chunkSize); // skip LIST, fact, etc
            }
        }

        return haveFmt && haveData;
    }
}

bool AudioManager::begin(bool initializeI2CBus)
{
    Serial.println("[Audio] Initializing audio manager...");
    Logger::info("Audio", "Starting Audio Init");

    if (initializeI2CBus)
    {
        Wire.begin(AUDIO_I2C_SDA, AUDIO_I2C_SCL);
        Logger::info("Audio", "Initialized shared I2C bus (audio ran first)");
    }
    else
    {
        Logger::info("Audio", "Assuming I2C bus already initialized by touch");
    }

    pinMode(AUDIO_AMP_ENABLE, OUTPUT);
    digitalWrite(AUDIO_AMP_ENABLE, LOW);

    i2s_config_t i2sConfig = {};
    i2sConfig.mode                 = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX);
    i2sConfig.sample_rate          = kDefaultSampleRate;
    i2sConfig.bits_per_sample      = I2S_BITS_PER_SAMPLE_16BIT;
    i2sConfig.channel_format       = I2S_CHANNEL_FMT_RIGHT_LEFT;
    i2sConfig.communication_format = I2S_COMM_FORMAT_STAND_I2S;
    i2sConfig.intr_alloc_flags     = ESP_INTR_FLAG_LEVEL1;
    i2sConfig.dma_buf_count        = 6;
    i2sConfig.dma_buf_len          = 256;
    i2sConfig.use_apll             = false;
    i2sConfig.tx_desc_auto_clear   = true;
    i2sConfig.mclk_multiple        = I2S_MCLK_MULTIPLE_256; // matches ES8311's expected MCLK/rate ratio

    if (i2s_driver_install(kI2SPort, &i2sConfig, 0, nullptr) != ESP_OK)
    {
        Serial.println("[Audio] i2s_driver_install failed");
        Logger::info("Audio", "i2s_driver_install failed");
        ledSetState(LedState::ERROR);
        return false;
    }

    i2s_pin_config_t pinConfig = {};
    pinConfig.mck_io_num   = AUDIO_I2S_MCLK;
    pinConfig.bck_io_num   = AUDIO_I2S_BCK;
    pinConfig.ws_io_num    = AUDIO_I2S_WS;
    pinConfig.data_out_num = AUDIO_I2S_DOUT;
    pinConfig.data_in_num  = I2S_PIN_NO_CHANGE; // no mic on Mini

    if (i2s_set_pin(kI2SPort, &pinConfig) != ESP_OK)
    {
        Serial.println("[Audio] i2s_set_pin failed");
        Logger::info("Audio", "i2s_set_pin failed");
        ledSetState(LedState::ERROR);
        return false;
    }

    i2sInstalled = true;

    if (!configureCodecForRate(kDefaultSampleRate))
    {
        Serial.println("[Audio] Codec init failed");
        Logger::info("Audio", "ES8311 codec init failed");
        ledSetState(LedState::ERROR);
        return false;
    }

    codec.volumeSet(kDefaultVolume);
    codecReady = true;

    playQueue = xQueueCreate(4, sizeof(PlayRequest));
    if (playQueue == nullptr)
    {
        Serial.println("[Audio] Failed to create play queue");
        Logger::info("Audio", "Play queue creation failed");
        return false;
    }

    BaseType_t taskResult = xTaskCreatePinnedToCore(
        audioTask,
        "audioTask",
        8192,
        nullptr,
        5,
        &taskHandle,
        1
    );

    if (taskResult != pdPASS)
    {
        Serial.println("[Audio] Failed to create audio task");
        Logger::info("Audio", "Audio task creation failed");
        return false;
    }

    Serial.println("[Audio] Audio manager ready");
    Logger::info("Audio", "Audio init successful");
    return true;
}

bool AudioManager::configureCodecForRate(uint32_t sampleRate)
{
    if (!i2sInstalled)
        return false;

    if (i2s_set_clk(kI2SPort, sampleRate, I2S_BITS_PER_SAMPLE_16BIT, I2S_CHANNEL_STEREO) != ESP_OK)
    {
        Logger::info("Audio", "i2s_set_clk failed");
        return false;
    }

    // ES8311 needs MCLK = sampleRate * 256 to match a row in its coefficient
    // table -- this is the exact combo the manufacturer reference used.
    Es8311ClockConfig clkCfg = {
        .mclk_inverted      = false,
        .sclk_inverted      = false,
        .mclk_from_mclk_pin = true,
        .mclk_frequency     = (int)(sampleRate * 256),
        .sample_frequency   = (int)sampleRate,
    };

    if (!codec.init(ES8311_ADDR_CE_LOW, clkCfg, Es8311Resolution::Res16, Es8311Resolution::Res16))
    {
        Logger::info("Audio", "ES8311 init failed for this sample rate");
        return false;
    }

    codec.microphoneConfig(false); // no mic on Mini
    currentRate = sampleRate;
    return true;
}

bool AudioManager::play(const char* path)
{
    if (!codecReady || playQueue == nullptr)
        return false;

    PlayRequest req = {};
    strncpy(req.path, path, kMaxPathLen - 1);

    if (playing)
        stopRequested = true;

    return xQueueSend(playQueue, &req, pdMS_TO_TICKS(100)) == pdPASS;
}

void AudioManager::stop()
{
    stopRequested = true;
}

void AudioManager::setVolume(int volume)
{
    if (!codecReady) return;
    codec.volumeSet(volume);
}

void AudioManager::mute(bool enable)
{
    if (!codecReady) return;
    codec.voiceMute(enable);
}

bool AudioManager::isPlaying()
{
    return playing;
}

bool AudioManager::playFileInternal(const char* path)
{
    File file = SD_MMC.open(path);
    if (!file)
    {
        Logger::info("Audio", "Failed to open audio file");
        return false;
    }

    WavInfo info{};
    if (!parseWavHeader(file, info))
    {
        file.close();
        return false;
    }

    if (info.sampleRate != currentRate)
    {
        if (!configureCodecForRate(info.sampleRate))
        {
            Logger::info("Audio", "Failed to reconfigure codec for file's sample rate");
            file.close();
            return false;
        }
    }

    uint8_t buffer[kStreamChunkBytes];
    uint32_t remaining = info.dataSize;

    playing = true;
    stopRequested = false;

    while (remaining > 0 && !stopRequested)
    {
        size_t toRead = min((uint32_t)kStreamChunkBytes, remaining);
        size_t bytesRead = file.read(buffer, toRead);
        if (bytesRead == 0) break;

        size_t bytesWritten = 0;
        i2s_write(kI2SPort, buffer, bytesRead, &bytesWritten, portMAX_DELAY);

        remaining -= bytesRead;
    }

    file.close();
    playing = false;
    return true;
}

void AudioManager::audioTask(void* param)
{
    PlayRequest req;
    for (;;)
    {
        if (xQueueReceive(playQueue, &req, portMAX_DELAY) == pdPASS)
        {
            playFileInternal(req.path);
        }
    }
}