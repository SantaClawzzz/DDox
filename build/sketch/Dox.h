#line 1 "C:\\Users\\RobinMadar\\OneDrive - Krakul OÜ\\Documents\\Projects\\DDox\\Dox.h"
#ifndef DOX_H
#define DOX_H

#include <Arduino.h>
#include <Adafruit_ILI9341.h>
#include "src/bmp/bmp.h"
#include "src/characters/characters.h"

// For ESP32-C6
#define TFT_CLK 18
#define TFT_MISO 15
#define TFT_MOSI 19
#define TFT_DC 22
#define TFT_CS 20
#define TFT_RST 21

// Color palette
#define BG   0x49C4
#define TXT  0x2104
#define ICON 0x7A86

// TFT instance
extern Adafruit_ILI9341 tft;

// Menu Enum
enum MenuState {
  MENU_MAIN,
  MENU_NEWCHAR,
  MENU_LOADCHAR,
  MENU_CHARACTER,
  MENU_CALC,
  MENU_HP,
  MENU_INIT
};

extern MenuState menuState;
extern MenuState navStack[];
extern uint8_t navDepth;
extern uint8_t selected;
extern uint8_t lastSelected;

// Function prototypes
void navPush(MenuState next);
MenuState navPop();
void Txt(const char *txt, uint16_t x, uint16_t y);
void SelTxt(const char *txt, uint16_t x, uint16_t y, uint8_t w);
void drawMainMenu();
void HandleSerial();
void selectOption();
void drawMenu();
void drawNewCharMenu();
void drawLoadMenu();
void drawCharacterMenu();
void drawCalcMenu();
void drawHPMenu();
void drawInitMenu();
void TxtF(uint16_t x, uint16_t y, const char *fmt, ...);

#endif