#line 1 "C:\\Users\\RobinMadar\\OneDrive - Krakul OÜ\\Documents\\Projects\\DDox\\src\\characters\\characters.h"
#ifndef CHARACTER_H
#define CHARACTER_H

#include <Arduino.h>

struct Character {

  char name[16];

  uint8_t str;
  uint8_t dex;
  uint8_t con;
  uint8_t intel;
  uint8_t wis;
  uint8_t cha;

  uint8_t lvl;
  uint8_t proficiency;
  uint8_t weaponDamage;

  uint8_t ac;
  uint8_t speed;

  int16_t hp;
  int16_t tempHp;

};

extern Character player;

extern const Character Kyle;
extern const Character Temp;

extern const Character* CharacterList[];
extern const uint8_t CharacterCount;

#endif