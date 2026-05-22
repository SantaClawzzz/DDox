#line 1 "C:\\Work\\Arduino\\DDox\\Dox.cpp"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include "Dox.h"
#include <stdarg.h>
#include <stdio.h>

int roll = 0;
int initiative = 0;
uint8_t sel = 0;

// --- FUNCTIONS ---

// Txt is the standard text drawing function
void Txt (const char *txt, uint16_t x, uint16_t y) {
  tft.setCursor(x, y);
  tft.setTextColor(TXT);
  tft.println(txt);
}

// SelTxt is used to highlight the selected menu item
void SelTxt(const char *txt, uint16_t x, uint16_t y, uint8_t w) {
  tft.fillRoundRect(x - 6, y - 5, w, 25, 4, ICON);  // highlight bar
  tft.setCursor(x, y);
  tft.setTextColor(BG, ICON);
  tft.println(txt);
}

// Draw the appropriate menu based on the current menu state and selected item
void drawMenu() {
  // Menustate switch case statement
  switch (menuState) {

  case MENU_MAIN:
    tft.fillScreen(BG); // Main menu
    drawMainMenu();
    break;

  case MENU_NEWCHAR:
    tft.fillScreen(BG); // New character menu
    drawNewCharMenu();
    break;

  case MENU_LOADCHAR:
    tft.fillScreen(BG); // Load character menu
    drawLoadMenu();
    break;

  case MENU_CHARACTER:
    tft.fillScreen(BG); // Character details menu
    drawCharacterMenu();
    break;
  
  case MENU_CALC:
    tft.fillScreen(BG); // Calculator menu
    drawCalcMenu();
    break;

  }
}

// Handle menu selection based on the current menu state and selected item
void selectOption() {

  switch(menuState) {

    case MENU_MAIN:
      if (selected == 0) {
        menuState = MENU_NEWCHAR;
        selected = 0;
      }
      else if (selected == 1) {
        menuState = MENU_LOADCHAR;
        selected = 0;
      }
      break;

    case MENU_NEWCHAR:
      // In progress
      break;

    case MENU_LOADCHAR:
      if (selected < CharacterCount) {
        player = *CharacterList[selected];
        lastMenuState = menuState;
        menuState = MENU_CHARACTER;
        selected = 0;
      }
      break;

    case MENU_CHARACTER:
      if (sel == 2) {
        lastMenuState = menuState;
        menuState = MENU_CALC;
        selected = 0;
        sel = 0;
      }
      break;

  }
}

// Draw the main menu with the selected item highlighted
void drawMainMenu() {
  Txt("Welcome to the", 20, 30);
  Txt(" D o s s i e r", 20, 60);
  tft.drawBitmap(200, 20, Dos, 100, 100, ICON);

  // Selectable options
  if (selected == 0)
    SelTxt("New Character", 20, 180, 160);
  else {
    tft.fillRoundRect(10, 175, 170, 26, 4, BG);
    Txt("New Character", 20, 180);
  }
  if (selected == 1)
    SelTxt("Load Character", 20, 210, 180);
  else {
    tft.fillRoundRect(10, 205, 190, 26, 4, BG);
    Txt("Load Character", 20, 210);
  }
}

// Draw the "New Character" menu
void drawNewCharMenu() {
  Txt("New Character", 20, 30);
}

// Draw the "Load Character" menu
void drawLoadMenu() {

  // New menu
  if (lastMenuState != MENU_LOADCHAR){
    Txt("Load Character", 20, 30);
  }

  // List characters
  for (uint8_t i = 0; i < CharacterCount; i++){
    uint8_t y = 90 + i * 30;

    // Outer dot
    tft.drawCircle(35, y, 7, ICON);
    
    // Options
    if (i == selected) 
      tft.fillCircle(35, y, 4, TXT);  // Highlight the selected character
    else
      tft.fillCircle(35, y, 4, BG);    // "erase" the highlight

    Txt(CharacterList[i]->name, 50, y - 5);
  }
}

void drawCharacterMenu(){

  // Display character info (player was already set in selectOption())
  Txt(player.name, 20, 30);

  TxtF(200, 20, "Level: %d", player.lvl);
  TxtF(200, 40, "HP:    / %d", player.hp);
  TxtF(200, 60, "AC: %d", player.ac);
  TxtF(200, 80, "Initiative: %d", init);

  TxtF(20, 100, "STR: %d", player.str);
  TxtF(20, 130, "DEX: %d", player.dex);
  TxtF(20, 160, "CON: %d", player.con);
  
  TxtF(150, 100, "INT: %d", player.intel);
  TxtF(150, 130, "WIS: %d", player.wis);
  TxtF(150, 160, "CHA: %d", player.cha);

  if (selected == 0) sel = (sel + 1) % 3;
  else if (selected == 1) sel = (sel + 2) % 3;  // +2 mod 3 = -1 mod 3

  // Cursor indicators
  if (sel == 0)
    tft.fillCircle(185, 45, 4, TXT);
  else if (sel == 1)
    tft.fillCircle(185, 85, 4, TXT);

  if (sel == 2)
    SelTxt("Calculator", 20, 210, 140);
  else
    Txt("Calculator", 20, 210);
}

void drawCalcMenu() {
  Txt("Calculator", 20, 30);

  // Initiative field — highlighted when selected == 0
  if (selected == 0)
    SelTxt("Initiative", 20, 80, 135);
  else
    Txt("Initiative", 20, 80);
  TxtF(160, 80, "%d", init);

  // HP field — highlighted when selected == 1
  if (selected == 1)
    SelTxt("HP", 20, 110, 50);
  else
    Txt("HP", 20, 110);
  TxtF(160, 110, "%d", player.hp);

  // Roll field — highlighted when selected == 2
  if (selected == 2)
    SelTxt("Roll", 20, 140, 70);
  else
    Txt("Roll", 20, 140);
  TxtF(160, 140, "%d", roll);

  // Damage total (read-only)
  TxtF(20, 190, "Prof: %d  Wpn: %d", player.proficiency, player.weaponDamage);
  TxtF(20, 210, "Total: %d", player.proficiency + player.weaponDamage + roll);
}

void HandleSerial() {
  while (Serial.available()) {
    char c = Serial.read();

    if (menuState == MENU_CALC) {
      // In MENU_CALC: '1' increases, '0' decreases the selected field; 'e' cycles fields
      if (c == '1') {
        if (selected == 0) init++;
        else if (selected == 1) player.hp++;
        else if (selected == 2) roll++;
        lastSelected = ~selected;  // force redraw
      }
      else if (c == '0') {
        if (selected == 0) init--;
        else if (selected == 1) player.hp--;
        else if (selected == 2) roll--;
        lastSelected = ~selected;  // force redraw
      }
      else if (c == 'e') {
        selected = (selected + 1) % 3;
      }
      else if (c == 'q') {
        menuState = lastMenuState;
        selected = 0;
      }
    }
    else {
      if (c == '0') {
        selected = 0;
      }
      else if (c == '1') {
        selected = 1;
      }
      else if (c == 'e') {
        selectOption();
      }
      else if (c == 'q') {
        menuState = lastMenuState;
        selected = 0;
      }
    }
  }
}

void TxtF(uint16_t x, uint16_t y, const char *fmt, ...) {

  char buffer[48];

  va_list args;
  va_start(args, fmt);
  vsnprintf(buffer, sizeof(buffer), fmt, args);
  va_end(args);

  Txt(buffer, x, y);
}