#line 1 "C:\\Users\\RobinMadar\\OneDrive - Krakul OÜ\\Documents\\Projects\\DDox\\CLAUDE.md"
# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

DDox is an Arduino/ESP32-C6 application providing a TFT touchscreen D&D character dossier — HP tracking, initiative rolling, stat display, and a damage calculator.

## Build & Upload

This project uses the Arduino IDE (not CMake or Make). Build artifacts go to `./build/`.

- **Board:** `esp32:esp32:esp32c6`
- **Port:** COM16
- **Upload speed:** 921600 baud
- **Flash:** 4M, QIO mode, 80MHz

To build and upload: open `DDox.ino` in Arduino IDE, select the ESP32-C6 board, and click Upload. There are no automated tests — testing is done manually via the TFT display and serial monitor (115200 baud).

## Hardware

SPI ILI9341 TFT display (320×240):

| Signal   | Pin |
|----------|-----|
| TFT_CLK  | 18  |
| TFT_MISO | 15  |
| TFT_MOSI | 19  |
| TFT_DC   | 22  |
| TFT_CS   | 20  |
| TFT_RST  | 21  |

Libraries: `Adafruit_ILI9341`, `Adafruit_GFX`

## Architecture

**Entry point:** `DDox.ino` — initializes SPI/TFT, runs `setup()`/`loop()`, and delegates all rendering and input to `Dox.cpp`.

**UI layer:** `Dox.cpp` / `Dox.h` — contains all menu state logic, drawing functions, and serial input handling. Menu states: `MENU_MAIN`, `MENU_NEWCHAR`, `MENU_LOADCHAR`, `MENU_CHARACTER`, `MENU_CALC`.

**Character data:** `src/characters/characters.cpp` / `.h` — defines the `Character` struct (name, D&D stats, HP, AC, etc.) and predefined character instances.

**Bitmap assets:** `src/bmp/` — raw pixel arrays for icons and portraits, declared in `bmp.h`.

## Serial Interface (for manual testing)

Navigation menus (`MENU_MAIN`, `MENU_LOADCHAR`, `MENU_CHARACTER`):
- `0` / `1` — move selection
- `e` — confirm/enter
- `q` — go back

Calculator menu (`MENU_CALC`):
- `1` / `0` — increment/decrement current field
- `e` — cycle to next field (Initiative → HP → Roll)
- `q` — return to character menu

## Color Palette

Defined in `Dox.cpp`:
- Background: `0x49C4`
- Text: `0x2104`
- Icons: `0x7A86`
