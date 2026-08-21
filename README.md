
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
| LVGL + EEZ Studio | ✓ | N/A | N/A |
| Companion App Pairing | ✓ | Planned | Planned |
| Wi-Fi Provisioning | ✓ | N/A | Planned |
| Physical Buttons | In Progress | In Progress | Planned |
| Battery Monitoring | In Progress | Untested | N/A |
| Spotify API | In Progress | N/A | Planned |
| Bluetooth Audio | N/A | Broken (rewrite in progress) | N/A |
| OTA Updates | Planned | Planned | Planned |
| Clock Faces | Planned | N/A | N/A |

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
- [x] Companion app pairing
- [x] Wi-Fi provisioning
- [ ] Clock faces
- [ ] Spotify interface
- [ ] Battery management
- [ ] Settings pages

### Wavelet Regular

- [ ] Restore Bluetooth audio
- [ ] Migrate to new architecture
- [ ] Companion app support

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


---
