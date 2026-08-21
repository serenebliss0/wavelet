
<p align="center">
  <img  src="https://github.com/user-attachments/assets/ed79e45b-1031-42fb-a0aa-3ef0ca24f411" width="40%">
</p>

<p align="center">
  <b>A modular, open-source smart speaker platform built around the ESP32 ecosystem.</b>
</p>

<p align="center">
  <img src="https://img.shields.io/badge/PlatformIO-Core-orange?style=for-the-badge&logo=platformio">
  <img src="https://img.shields.io/badge/Framework-Arduino_ESP32-blue?style=for-the-badge&logo=espressif">
  <img src="https://img.shields.io/badge/UI-LVGL_v8.4-green?style=for-the-badge">
  <img src="https://img.shields.io/badge/License-MIT-yellow?style=for-the-badge">
</p>

---

## Overview

Wavelet is a family of ESP32-based smart speakers built from a single shared codebase.

Each model targets a different use case, from a compact BLE-enabled desktop speaker to a future high-power smart speaker, while sharing the same firmware architecture through PlatformIO environments and compile-time feature flags.

The project is currently undergoing a major rewrite focused on modular firmware, modern embedded UI with LVGL and EEZ Studio, BLE onboarding, and a Flutter companion application.

---

## The Wavelet Family

| Model | Target | Current Status |
| ------ | ------ | -------------- |
| **Wavelet Mini** | ESP32-S3 | Active development |
| **Wavelet Regular** | ESP32-WROOM-32 | Being migrated to the new architecture |
| **Wavelet Max** | ESP32-S3 | Planned |

### Wavelet Mini

The Mini is the current focus of development and serves as the foundation for the rest of the Wavelet ecosystem.

It features:

- ESP32-S3
- LVGL + EEZ Studio interface
- QR-code BLE onboarding
- Wi-Fi provisioning
- Spotify API integration
- Battery monitoring
- RTC support
- Touchscreen interface

Unlike previous versions, the Mini no longer supports Bluetooth Classic audio. Instead, it focuses on becoming a connected smart speaker controlled through the companion app.

---

### Wavelet Regular

The Regular is the original portable stereo speaker.

The firmware is currently being migrated to the new modular architecture after much of the original implementation was replaced during Mini development.

Planned features include:

- Stereo audio
- Physical controls
- Battery operation
- Companion app support
- Shared UI framework with the Mini

---

### Wavelet Max

The Max is the planned flagship model.

It is intended to become a wall-powered smart speaker with significantly more processing power and expanded connectivity.

Development has not yet started as the required hardware is still being acquired.

---

## Project Status

| Feature | Mini | Regular | Max |
| :-- | :--: | :--: | :--: |
| BLE Onboarding | ✓ | Planned | Planned |
| LVGL + EEZ Studio | ✓ | Planned | Planned |
| Companion App Pairing | ✓ | Planned | Planned |
| Wi-Fi Provisioning | ✓ | N/A | Planned |
| Physical Buttons | In Progress | In Progress | Planned |
| Battery Monitoring | In Progress | Untested | N/A |
| Spotify API | In Progress | Planned | Planned |
| Bluetooth Audio | N/A | Broken (rewrite in progress) | N/A |
| OTA Updates | Planned | Planned | Planned |
| Clock Faces | Planned | Planned | Planned |

---

## Gallery

### Wavelet Mini UI
<p align="center">
  <img width="30%" alt="boot screen" src="https://github.com/user-attachments/assets/25db4aef-0ce7-4a9a-a229-9b8a0905d9f4" />
  <img width="30%" alt="QR Setup page" src="https://github.com/user-attachments/assets/b6c6f377-4a82-4b27-9e4d-9c225221fe4f" />
  <img width="30%" alt="Onboarding Tutorial: Swipe down" src="https://github.com/user-attachments/assets/28eacc10-51db-4452-9a65-d3c1d1361b0d" />

</p>

---

## Repository Structure

```text
esp32-smart-speaker/
├── assets/
├── data/
├── esp32-smart-speaker-schema/
├── include/
├── lib/
├── src/
│   ├── audio/
│   ├── ble/
│   ├── core/
│   ├── input/
│   ├── mini/
│   ├── screens/
│   ├── spotify_controller/
│   ├── storage/
│   ├── web/
│   ├── wifi/
│   └── main.cpp
├── spk-sounds/
├── test/
├── wavelet_app/          Flutter companion app (Git submodule)
├── webpage_iterations/
└── platformio.ini
```

---

## Getting Started

Clone the repository together with the companion app submodule.

```bash
git clone --recursive https://github.com/serenebliss0/wavelet.git
```

If you've already cloned the repository:

```bash
git submodule update --init --recursive
```

Install PlatformIO if needed.

```bash
pip install platformio
```

Build the desired firmware:

```bash
pio run -e mini
```

or

```bash
pio run -e regular
```

or

```bash
pio run -e max
```

Upload to your board:

```bash
pio run -t upload -e mini
```

---

## Roadmap

### Wavelet Mini

- [x] QR BLE onboarding
- [x] LVGL integration
- [x] EEZ Studio integration
- [ ] Companion app pairing
- [ ] Wi-Fi provisioning
- [ ] Clock faces
- [ ] Spotify interface
- [ ] Battery management
- [ ] Settings pages

### Wavelet Regular

- [ ] Restore Bluetooth audio
- [ ] Migrate to new architecture
- [ ] Companion app support
- [ ] Shared UI framework

### Wavelet Max

- [ ] Hardware prototype
- [ ] Firmware foundation
- [ ] Network services
- [ ] OTA updates
- [ ] Smart home integration

---

## Companion Application

Wavelet includes a Flutter companion application used for:

- Onboarding
- BLE pairing
- Wi-Fi setup
- Device management
- Future firmware updates

The app lives in its own repository and is included here as a Git submodule.

**Repository:** https://github.com/serenebliss0/wavelet-app

---

## Built With

- C++
- Arduino Framework
- PlatformIO
- LVGL 8.4
- EEZ Studio
- NimBLE
- ArduinoJson
- Flutter
- Dart

---

## Contributing

Contributions, suggestions and bug reports are always welcome.

If you have ideas or improvements, feel free to open an issue or submit a pull request.

---

## License

MIT License

---

Made with ❤️ by **Semire Ajayi**

## Figma Designs

### Wavelet Mini
* **Target:** ESP32-S3 (2.8" Capacitive Touch LCD Module, 8MB OPI PSRAM, 16MB Flash)
* **Power:** 5V USB Type-C or Single-cell Li-Ion (Onboard Charging IC)
* **Audio:** Onboard Speaker Interface (Mono Local Playback / Notifications)
* **Focus:** Active development baseline. Features BLE QR-code onboarding, localized LVGL graphical rendering, and companion app interaction over Bluetooth Low Energy.

### Wavelet Regular
* **Target:** ESP32-WROOM-32 (Standard DevKit V1)
* **Power:** Portable 18650 Battery Array with TP4056 Protection
* **Audio:** Dual MAX98357A I2S DACs driving a 2.0 Stereo Array
* **Focus:** Traditional untethered Bluetooth audio endpoint. Currently undergoing firmware restructuring to align with the new modular architecture.

### Wavelet Max
* **Target:** ESP32-S3-DevKitC-1
* **Power:** 12V–24V DC High-Power Wall Adapter with Buck Regulation
* **Audio:** MAX98357A I2S Pre-amp feeding a TPA3116D2 Class-D 2.1 Amplifier (6.5" Subwoofer + Satellites)
* **Focus:** Flagship wall-powered ecosystem node focused on smart-home connectivity, advanced DSP processing, and cloud services.

---

## Gallery

### Wavelet Mini UI
<p align="center">
  <img width="30%" alt="boot screen" src="https://github.com/user-attachments/assets/25db4aef-0ce7-4a9a-a229-9b8a0905d9f4" />
  <img width="30%" alt="QR Setup page" src="https://github.com/user-attachments/assets/b6c6f377-4a82-4b27-9e4d-9c225221fe4f" />
  <img width="30%" alt="Onboarding Tutorial: Swipe down" src="https://github.com/user-attachments/assets/28eacc10-51db-4452-9a65-d3c1d1361b0d" />

</p>

---

## Project Status

| Feature | Wavelet Mini | Wavelet Regular | Wavelet Max |
| :--- | :---: | :---: | :---: |
| **BLE QR Onboarding** | Completed | In Progress | Planned |
| **LVGL / EEZ UI Engine** | Completed | Planned | Planned |
| **Companion App Link** | In Progress | In Progress | Planned |
| **Physical Controls** | In Progress | In Progress | Planned |
| **Battery Fuel Gauge** | In Progress | Completed | N/A |
| **Spotify API Integration** | In Progress | Planned | Planned |
| **Classic Bluetooth Audio** | N/A (BLE Only) | In Progress | N/A |
| **Wi-Fi Provisioning** | In Progress | N/A | Planned |
| **OTA Updates** | Planned | Planned | Planned |

---



## Repository Structure

```text
esp32-smart-speaker/
├── assets/                       Display graphics and branding assets
├── data/                         Embedded filesystem assets (LVGL image resources)
├── esp32-smart-speaker-schema/   KiCad hardware schematics and PCB designs
├── include/                      Shared core headers and global pin configurations
├── lib/                          Local project dependencies and external drivers
├── src/                          Firmware source code
│   ├── audio/                    I2S audio pipeline and playback drivers
│   ├── battery/                  ADC fuel gauge monitoring
│   ├── ble/                      NimBLE stack and custom GATT services
│   ├── core/                     System orchestration and event loops
│   ├── display/                  LVGL configuration and display drivers
│   ├── input/                    Potentiometer and tactile button handlers
│   ├── mini/                     Wavelet Mini specific entry points and QR setup
│   ├── neopixel/                 Status LED ring controllers
│   ├── rtc_manager/              Real-Time Clock state management
│   ├── screens/                  EEZ Studio / LVGL auto-generated UI code
│   ├── spotify_controller/       Spotify Web API client handlers
│   ├── storage/                  Non-Volatile Storage (NVS) preferences
│   ├── wifi/                     Async network managers
│   └── main.cpp                  Primary setup and execution loop
├── wavelet_app/                  Flutter companion application (Git Submodule)
└── platformio.ini                PlatformIO environment and target definitions
