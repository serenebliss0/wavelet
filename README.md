
<p align="center">
  <a href="https://github.com/serenebliss0/wavelet">
    <img
      width="139"
      height="48"
      alt="Wavelet Logo"
      src="https://github.com/user-attachments/assets/ed79e45b-1031-42fb-a0aa-3ef0ca24f411"
    />
  </a>
</p>


<p align="center">
  <b>A modular, open-source smart speaker framework built on the ESP32 platform.</b>
</p>

<p align="center">
  <img src="https://img.shields.io/badge/PlatformIO-Core-orange?style=for-the-badge&logo=platformio">
  <img src="https://img.shields.io/badge/Framework-Arduino_ESP32-blue?style=for-the-badge&logo=espressif">
  <img src="https://img.shields.io/badge/UI-LVGL_v8.4-green?style=for-the-badge">
  <img src="https://img.shields.io/badge/License-MIT-yellow?style=for-the-badge">
</p>

---

## Overview

**Wavelet** is a unified embedded software platform for a family of modular smart speakers. Built on Espressif hardware, the project uses a single scalable codebase configured via compile-time environment flags in PlatformIO. 

The system transitions away from legacy web-based dashboards toward an ecosystem focused on local embedded UI rendering (LVGL), low-energy provisioning, and companion app controls.

---

## The Wavelet Family

The platform scales across three distinct hardware tiers to balance power consumption, interface complexity, and performance:

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
