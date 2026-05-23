#line 1 "C:\\Users\\RobinMadar\\OneDrive - Krakul OÜ\\Documents\\Projects\\DDox\\Dox.cpp"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include "Dox.h"
#include <stdarg.h>
#include <stdio.h>

int roll = 0;
int initiative = 0;
int current_hp = player.hp;
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
    tft.fillScreen(BG);
    drawCalcMenu();
    break;

  case MENU_HP:
    tft.fillScreen(BG);
    drawHPMenu();
    break;

  case MENU_INIT:
    tft.fillScreen(BG);
    drawInitMenu();
    break;

  }
}

// Handle menu selection based on the current menu state and selected item
void selectOption() {

  switch(menuState) {

    case MENU_MAIN:
      if (selected == 0) navPush(MENU_NEWCHAR);
      else if (selected == 1) navPush(MENU_LOADCHAR);
      break;

    case MENU_NEWCHAR:
      // In progress
      break;

    case MENU_LOADCHAR:
      if (selected < CharacterCount) {
        player = *CharacterList[selected];
        current_hp = player.hp;
        navPush(MENU_CHARACTER);
        sel = 0;
      }
      break;

    case MENU_CHARACTER:
      if (sel == 0) navPush(MENU_HP);
      else if (sel == 1) navPush(MENU_INIT);
      else navPush(MENU_CALC);
      break;

  }
}

// Draw the main menu with the selected item highlighted
void drawMainMenu() {
  Txt("Welcome to the", 20, 30);
  Txt(" D o s s i e r", 20, 60);
  tft.drawBitmap(200, 20, Dos, 100, 100, ICON);

  if (selected == 0) SelTxt("New Character", 20, 180, 160);
  else Txt("New Character", 20, 180);

  if (selected == 1) SelTxt("Load Character", 20, 210, 180);
  else Txt("Load Character", 20, 210);
}

// Draw the "New Character" menu
void drawNewCharMenu() {
  Txt("New Character", 20, 30);
}

// Draw the "Load Character" menu
void drawLoadMenu() {
  Txt("Load Character", 20, 30);

  // List characters
  for (uint8_t i = 0; i < CharacterCount; i++){
    uint8_t y = 90 + i * 30;
    
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
  SelTxt(player.name, 20, 20, 180);

  TxtF(40, 60, "Level: %d", player.lvl);
  TxtF(85, 80, "%d", current_hp + player.tempHp);
  TxtF(40, 80, "HP:   /%d", player.hp);
  TxtF(190, 60, "AC: %d", player.ac);
  TxtF(190, 80, "Init: %d", initiative);

  TxtF(40, 120, "STR: %d", player.str);
  TxtF(40, 150, "DEX: %d", player.dex);
  TxtF(40, 180, "CON: %d", player.con);
  
  TxtF(190, 120, "INT: %d", player.intel);
  TxtF(190, 150, "WIS: %d", player.wis);
  TxtF(190, 180, "CHA: %d", player.cha);

  if (sel == 0) {
    tft.fillCircle(20, 87, 4, TXT);
    Txt("Calculator", 20, 210);
  } else if (sel == 1) {
    tft.fillCircle(180, 87, 4, TXT);
    Txt("Calculator", 20, 210);
  } else {
    SelTxt("Calculator", 20, 210, 140);
  }
}

void drawCalcMenu() {
  Txt("Calculator", 20, 30);

  // Roll field — highlighted when selected == 0
  if (selected == 0)
    SelTxt("Roll", 20, 80, 70);
  else
    Txt("Roll", 20, 80);
  TxtF(160, 80, "%d", roll);

  // Damage breakdown (read-only)
  TxtF(20, 130, "Prof: %d", player.proficiency);

  // ExtraDmg field — highlighted when selected == 1
  if (selected == 1)
    SelTxt("ExtraDmg:", 20, 160, 120);
  else
    Txt("ExtraDmg:", 20, 160);
  TxtF(160, 160, "%d", player.weaponDamage);

  TxtF(20, 200, "Total: %d", player.proficiency + player.weaponDamage + roll);
}

void HandleSerial() {
  while (Serial.available()) {
    char c = Serial.read();

    if (menuState == MENU_CALC) {
      if (c == '1') {
        if (selected == 0) roll++;
        else if (selected == 1) player.weaponDamage++;
        lastSelected = ~selected;
      }
      else if (c == '0') {
        if (selected == 0) roll--;
        else if (selected == 1) player.weaponDamage--;
        lastSelected = ~selected;
      }
      else if (c == 'e') selected = (selected + 1) % 2;
      else if (c == 'q') menuState = navPop();
    }
    else if (menuState == MENU_CHARACTER) {
      if (c == '1') {
        sel = (sel + 1) % 3;
        lastSelected = ~selected;
      }
      else if (c == '0') {
        sel = (sel + 2) % 3;
        lastSelected = ~selected;
      }
      else if (c == 'e') selectOption();
      else if (c == 'q') menuState = navPop();
    }
    else if (menuState == MENU_HP) {
      if (c == '1') {
        if (selected == 0 && current_hp < player.hp) { current_hp++; lastSelected = ~selected; }
        else if (selected == 1) { player.tempHp++; lastSelected = ~selected; }
      }
      else if (c == '0') {
        if (selected == 0) { current_hp--; lastSelected = ~selected; }
        else if (selected == 1 && player.tempHp > 0) { player.tempHp--; lastSelected = ~selected; }
      }
      else if (c == 'e') selected = (selected + 1) % 2;
      else if (c == 'q') menuState = navPop();
    }
    else if (menuState == MENU_INIT) {
      if (c == '1') { initiative++; lastSelected = ~selected; }
      else if (c == '0') { initiative--; lastSelected = ~selected; }
      else if (c == 'q') menuState = navPop();
    }
    else {
      uint8_t maxItems = (menuState == MENU_LOADCHAR) ? CharacterCount : 2;
      if (c == '0') {
        selected = (selected + 1) % maxItems;
      }
      else if (c == '1') {
        selected = (selected + maxItems - 1) % maxItems;
      }
      else if (c == 'e') {
        selectOption();
      }
      else if (c == 'q') {
        menuState = navPop();
      }
    }
  }
}

void drawHPMenu() {
  SelTxt(player.name, 20, 20, 180);
  Txt("Hit Points", 20, 60);
  if (selected == 0) tft.fillCircle(20, 115, 4, TXT);
  else if (selected == 1) tft.fillCircle(20, 145, 4, TXT);
  Txt("HP:", 40, 107);
  TxtF(110, 107, "%d / %d", current_hp, player.hp);
  Txt("Temp:", 40, 137);
  TxtF(110, 137, "%d", player.tempHp);
}

void drawInitMenu() {
  SelTxt(player.name, 20, 20, 180);
  Txt("Initiative", 20, 60);
  tft.fillCircle(20, 115, 4, TXT);
  Txt("INT:", 40, 107);
  TxtF(110, 107, "%d", initiative);
}

void navPush(MenuState next) {
  if (navDepth < 4) navStack[navDepth++] = menuState;
  menuState = next;
  selected = 0;
}

MenuState navPop() {
  selected = 0;
  if (navDepth > 0) return navStack[--navDepth];
  return MENU_MAIN;
}

void TxtF(uint16_t x, uint16_t y, const char *fmt, ...) {

  char buffer[48];

  va_list args;
  va_start(args, fmt);
  vsnprintf(buffer, sizeof(buffer), fmt, args);
  va_end(args);

  Txt(buffer, x, y);
}