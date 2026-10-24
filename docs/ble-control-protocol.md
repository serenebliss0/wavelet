# Wavelet BLE control protocol v1

The same primary service is used by every model:

- Service: `4fafc201-1fb5-459e-8fcc-c5c9c331914b`
- Device info (read): `beb5483e-36e1-4688-b7f5-ea07361b26a8`
- Command (write): `beb5483e-36e1-4688-b7f5-ea07361b26a9`
- Status (read/notify): `beb5483e-36e1-4688-b7f5-ea07361b26ac`
- Device name (write): `beb5483e-36e1-4688-b7f5-ea07361b26ad`

The device-info value is JSON with `protocolVersion`, `model`, and `capabilities`. The app should use capabilities to hide controls the connected model does not support.

## Commands

Write these UTF-8 strings to the command characteristic:

| Command | Behavior |
| --- | --- |
| `GET_STATUS` | Status notification with current model, Wi-Fi/RSSI where available, battery percentage on Mini, and playing state on Mini |
| `PLAY_PAUSE` | Toggle playback on Mini Spotify or Regular Bluetooth audio |
| `SET_VOLUME:<0-100>` | Set volume |
| `SET_THEME:DARK` / `SET_THEME:LIGHT` | Mini display theme |
| `SET_REPEAT:OFF` / `TRACK` / `CONTEXT` | Mini Spotify repeat mode |
| `SET_SHUFFLE:ON` / `OFF` | Mini Spotify shuffle |
| `SYNC_TIME:<UTC Unix seconds>` | Set device clock from the phone |
| `FACTORY_RESET` | Rejected; confirmation is required |
| `FACTORY_RESET:CONFIRM` | Clear Wavelet preferences and restart |

Mini-only Spotify refresh-token characteristic: `beb5483e-36e1-4688-b7f5-ea07361b26ae` (write the token, then reboot). Spotify client ID and client secret remain firmware configuration. Existing setup characteristics and `SET_WIFI` / `SETUP_COMPLETE` continue to work.

## Current model support

| Capability | Mini | Regular |
| --- | --- | --- |
| Play/pause, volume | Yes | Yes |
| Theme, Spotify repeat/shuffle/token | Yes | Not supported |
| Phone time, battery, Wi-Fi RSSI | Yes | Not supported |
| Factory reset | Yes | Yes |

Credentials are currently written over the BLE characteristic without an application-level pairing flow. Use a trusted nearby client while provisioning; authenticated BLE pairing should be added before production credential setup.
