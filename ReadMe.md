## Project Overview

DDox is a D&D character dossier project — HP tracking, initiative rolling, stat display, and a damage calculator.<br>
Uses ESP32-C6 and Arduino.

Libraries: `Adafruit_ILI9341`, `Adafruit_GFX`

## Pinout

SPI ILI9341 TFT display (320×240):

| Signal   | Pin |
|----------|-----|
| TFT_CLK  | 18  |
| TFT_MISO | 15  |
| TFT_MOSI | 19  |
| TFT_DC   | 22  |
| TFT_CS   | 20  |
| TFT_RST  | 21  |

## System

Serial:<br>
- `0` / `1` — move selection
- `e` — confirm/enter
- `q` — go back

Encoder:<br>
- `CW` / `CCW` — move selection
- `SEL` — confirm/enter
- `BUT1` — go back

## Color Palette

Defined in `Dox.cpp`:
- Background: `0x49C4`
- Text: `0x2104`
- Icons: `0x7A86`