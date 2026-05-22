#line 1 "C:\\Work\\Arduino\\DDox\\src\\characters\\characters.cpp"
#include "characters.h"

Character player;

const Character Kyle = {
  "Ketamine Kyle",
  16, 16, 18, 13, 14, 12,
  4, 2, 2,
  16, 30,
  38, 0
};

const Character Temp = {
  "Temp",
  0, 0, 0, 0, 0, 0,
  0, 0, 0,
  0, 0,
  0, 0
};

const Character* CharacterList[] = {
    &Kyle, 
    &Temp 
};

const uint8_t CharacterCount = sizeof(CharacterList) / sizeof(CharacterList[0]);