#include <Arduino.h>
#line 1 "C:\\Work\\Arduino\\DDox\\DDox.ino"

/***************************************************
  SPI TFT screen for ESP32-C6
  Based on Adafruit_ILI9341 library

  Made for a DnD type dossier project.
  Created by Robin Madar, March 2026.
 ****************************************************/

#include <Adafruit_ILI9341.h>
#include "Dox.h"
#include "src/characters/characters.h"

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

MenuState menuState = MENU_MAIN;
MenuState lastMenuState = MENU_LOADCHAR;

uint8_t selected = 0;
uint8_t lastSelected = 255;

void setup() {

  // Serial
  Serial.begin(115200);

  // TFT init
  SPI.begin(TFT_CLK, TFT_MISO, TFT_MOSI, TFT_CS);
  tft.begin(40000000);
  
  tft.setRotation(1);
  tft.fillScreen(BG);
  tft.setTextColor(TXT, BG);
  tft.setTextSize(2);
  // TFT init end
  
  //TFT image tests
  //tft.drawRGBBitmap(0, 0, Liz, 320, 240);
  //tft.drawBitmap(0, 0, LP, 320, 240, BLACK);
}

void loop(void) {

  // For serial input
  HandleSerial();

  // Menu section
  if (menuState != lastMenuState || selected != lastSelected) {

    drawMenu();

    lastSelected = selected;
    lastMenuState = menuState;
  }
}

