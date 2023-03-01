/**
   Arduino Electronic Safe

   Copyright (C) 2020, Uri Shaked.
   Released under the MIT License.
*/

#pragma once

#include <LiquidCrystal_I2C.h>

// Our custom icon numbers
#define ICON_LOCKED_CHAR (byte)0
#define ICON_UNLOCKED_CHAR (byte)1

// This is a standard icon on the LCD1602 character set
#define ICON_RIGHT_ARROW (byte)126

const byte iconLocked[8] PROGMEM = {
    0b01110,
    0b10001,
    0b10001,
    0b11111,
    0b11011,
    0b11011,
    0b11111,
};

const byte iconUnlocked[8] PROGMEM = {
    0b01110,
    0b10000,
    0b10000,
    0b11111,
    0b11011,
    0b11011,
    0b11111,
};

class Icons
{

public:
   Icons(LiquidCrystal_I2C &lcd)
   {
      byte icon[8];
      memcpy_P(icon, iconLocked, sizeof(icon));
      lcd.createChar(ICON_LOCKED_CHAR, icon);
      memcpy_P(icon, iconUnlocked, sizeof(icon));
      lcd.createChar(ICON_UNLOCKED_CHAR, icon);
   }
};
