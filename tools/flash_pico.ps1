<#
.SYNOPSIS
    Flash firmware to MindReset Pico (ESP32-S3) via esptool.py.
.DESCRIPTION
    Flashes Read_Pico.bin (0x10000) and resets the active OTA slot by flashing
    ota_data_initial.bin (0xd10000). Optionally performs a full flash including
    bootloader and partition table with -FullFlash.
.EXAMPLE
    .\tools\flash_pico.ps1
    .\tools\flash_pico.ps1 -Port COM24
    .\tools\flash_pico.ps1 -Port COM24 -FullFlash
#>
param(
    [string]$Port,
    [string]$Baud = "460800",
    [switch]$FullFlash
)

$ErrorActionPreference = "Stop"
$repo = Split-Path -Parent (Split-Path -Parent $MyInvocation.MyCommand.Path)
$buildDir = Join-Path $repo "build\boards\pico\build"

$appBin = Join-Path $buildDir "Read_Pico.bin"
$otaDataBin = Join-Path $buildDir "ota_data_initial.bin"
$bootloaderBin = Join-Path $buildDir "bootloader\bootloader.bin"
$partitionBin = Join-Path $buildDir "partition_table\partition-table.bin"

if (-not (Test-Path $appBin)) {
    throw "Read_Pico.bin not found at $appBin. Please build the firmware first."
}
if (-not (Test-Path $otaDataBin)) {
    throw "ota_data_initial.bin not found at $otaDataBin. Please build the firmware first."
}

# Auto-activate ESP-IDF profile if esptool is not already in PATH
if (-not (Get-Command "esptool.py" -ErrorAction SilentlyContinue) -and -not (Get-Command "esptool" -ErrorAction SilentlyContinue)) {
    $profile = "C:\Espressif\tools\Microsoft.v6.1.PowerShell_profile.ps1"
    if (Test-Path $profile) {
        Write-Host "Activating ESP-IDF environment from $profile..." -ForegroundColor Cyan
        . $profile
    } else {
        throw "esptool not found in PATH and default profile $profile does not exist. Please run inside ESP-IDF PowerShell."
    }
}

$portArgs = @()
if ($Port) {
    $portArgs = @("-p", $Port)
}
$baudArgs = @("-b", $Baud)

if ($FullFlash) {
    Write-Host "Flashing full image (bootloader + partition table + app + otadata)..." -ForegroundColor Green
    esptool.py @portArgs @baudArgs write_flash `
        0x0 $bootloaderBin `
        0x8000 $partitionBin `
        0x10000 $appBin `
        0xd10000 $otaDataBin
} else {
    Write-Host "Flashing app + resetting active OTA slot to ota_0..." -ForegroundColor Green
    esptool.py @portArgs @baudArgs write_flash `
        0x10000 $appBin `
        0xd10000 $otaDataBin
}

if ($LASTEXITCODE -eq 0) {
    Write-Host "`nFlash completed successfully! Device should reboot into ota_0." -ForegroundColor Green
} else {
    Write-Host "`nFlash failed with exit code $LASTEXITCODE" -ForegroundColor Red
}

