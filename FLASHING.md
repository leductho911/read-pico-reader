# Firmware Flashing Guide

This document explains how to flash firmware to your **MindReset RDP-G01-W (Pico)** e-paper device (ESP32-S3) via USB, and how the dual OTA boot slot mechanism works.

---

## 1. Quick Flashing Commands

### Option A: Using the Flashing Script (Recommended)

In PowerShell:
```powershell
# Automatically flashes Read_Pico.bin and resets boot slot to ota_0
.\tools\flash_pico.ps1

# Or specify COM port explicitly:
.\tools\flash_pico.ps1 -Port COM24

# Full flash (bootloader + partition table + app + otadata):
.\tools\flash_pico.ps1 -Port COM24 -FullFlash
```

---

### Option B: Using `esptool` Directly

Open your ESP-IDF PowerShell environment (or any terminal with `esptool` in PATH):
```powershell
& "C:\Espressif\tools\Microsoft.v6.1.PowerShell_profile.ps1"
```

Then run:

#### Standard Update (App + OTA Data Reset)
```powershell
esptool -p COM24 -b 460800 write_flash 0x10000 "build/boards/pico/build/Read_Pico.bin" 0xd10000 "build/boards/pico/build/ota_data_initial.bin"
```
*(Note: If using older esptool versions, `esptool.py` or `python -m esptool` also works).*

> **IMPORTANT**:
> Always include `0xd10000 "build/boards/pico/build/ota_data_initial.bin"` when flashing `0x10000`!
> See [Why 0xd10000 (otadata) is Required](#why-0xd10000-otadata-is-required) below.

#### Full Flash (Clean Install)
```powershell
esptool -p COM24 -b 460800 write_flash `
    0x0 "build/boards/pico/build/bootloader/bootloader.bin" `
    0x8000 "build/boards/pico/build/partition_table/partition-table.bin" `
    0x10000 "build/boards/pico/build/Read_Pico.bin" `
    0xd10000 "build/boards/pico/build/ota_data_initial.bin"
```

---

## 2. Why `0xd10000` (`otadata`) is Required

The device partition table defines **two app slots** for Over-The-Air (OTA) updates:

| Name | Type | Offset | Size | Description |
| :--- | :--- | :--- | :--- | :--- |
| `ota_0` | App | `0x00010000` | 4 MB | Primary app slot |
| `ota_1` | App | `0x00910000` | 4 MB | Secondary app slot |
| `otadata` | Data | `0x00d10000` | 8 KB | Boot selector (tracks active slot) |

- When an OTA or web flash update is performed, the system writes the new firmware to the inactive slot and updates `otadata` at `0xd10000` to point to that slot.
- If the device was previously running from `ota_1` (`0x910000`), flashing **only** `0x10000` overwrites `ota_0`, but the ESP32 bootloader still reads `otadata` and **boots the old firmware in `ota_1`**!
- Flashing `ota_data_initial.bin` to `0xd10000` resets `otadata` so the bootloader is forced to boot from `ota_0` (`0x10000`).

---

## 3. How to Build Before Flashing

If you make code changes and need to rebuild:

```powershell
# 1. Update UI translation catalog (if you edited strings or locales)
python tools/gen_ui_locale.py

# 2. Build Pico firmware (auto-detects ESP-IDF v6.1 on Windows)
python tools/build_firmware.py --board pico
```

> **Tip**: `build_firmware.py` automatically detects your ESP-IDF installation (`C:\esp\v6.1\esp-idf`), tools (`C:\Espressif\tools`), and virtualenv Python. You can run it directly in a normal PowerShell terminal without manually activating the ESP-IDF profile.
>
> If you have multiple SDK versions installed, you can explicitly specify the paths:
> ```powershell
> python tools/build_firmware.py --board pico --idf-pico C:\esp\v6.1\esp-idf --tools C:\Espressif\tools
> ```

Built binary files will be located in:
`build/boards/pico/build/`
- `Read_Pico.bin`
- `ota_data_initial.bin`
- `bootloader/bootloader.bin`
- `partition_table/partition-table.bin`

Packaged USB/web distributions are generated in:
`build/boards/packages/pico/`

---

## 4. How to Verify the Flashed Firmware

### Method 1: On-Device Settings UI
1. Turn on the device and go to **Settings (设置)**.
2. Tap **System Upgrade (系统升级)**:
   - Under **Current Version (当前版本)**, check the reported version and build timestamp (e.g. `0.3.3-rc106`).
3. Check UI languages & translations:
   - Go to **Language (语言)** in Settings, and choose **English** or **Tiếng Việt**.
   - Verify UI texts are correctly displayed in the selected language.

### Method 2: Serial Monitor
In your ESP-IDF PowerShell window:
```powershell
idf.py -p COM24 monitor
```
Press the Reset button on the device (or run `esptool run`). The boot log will show:
```text
I (...) boot: Loaded app from partition at offset 0x10000
I (...) esp_image: App version: 0.3.3-rc106
```
*(Press `Ctrl + ]` to exit the monitor).*

---

## 5. Board Partition & Offset Reference

| Board | Chip | Bootloader | Partition Table | App (ota_0) | otadata |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **Pico (RDP-G01-W)** | ESP32-S3 | `0x0` | `0x8000` | `0x10000` | `0xd10000` |
| **Metalio S31** | ESP32-S31 | `0x2000` | `0x8000` | `0x10000` | `0xd000` |

