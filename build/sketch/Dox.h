#line 1 "C:\\Work\\Arduino\\DDox\\Dox.h"
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
  MENU_CALC
};

extern MenuState menuState;
extern MenuState lastMenuState;
extern uint8_t selected;
extern uint8_t lastSelected;
extern uint8_t sel;
extern int roll;
extern int init;

// Function prototypes
void DelTxt(const char *txt, uint16_t x, uint16_t y);
void Txt(const char *txt, uint16_t x, uint16_t y);
void InvTxt(const char *txt, uint16_t x, uint16_t y);
void SelTxt(const char *txt, uint16_t x, uint16_t y, uint8_t w);
void drawMainMenu();
void HandleSerial();
void selectOption();
void drawMenu();
void drawNewCharMenu();
void drawLoadMenu();
void drawCharacterMenu();
void drawCalcMenu();
void TxtF(uint16_t x, uint16_t y, const char *fmt, ...);

#endif