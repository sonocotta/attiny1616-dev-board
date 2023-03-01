#include <Wire.h>

/* Display */
#include <LiquidCrystal_I2C.h>

#define PIN_LCD_EN 2
#define PIN_LCD_RW 1
#define PIN_LCD_RES 0
#define PIN_LCD_LED 3
#define PIN_LCD_D4 4
#define PIN_LCD_D5 5
#define PIN_LCD_D6 6
#define PIN_LCD_D7 7

#define LCD_I2C_ADDR 0x3f

LiquidCrystal_I2C _lcd(
    LCD_I2C_ADDR, PIN_LCD_EN, PIN_LCD_RW, PIN_LCD_RES,
    PIN_LCD_D4, PIN_LCD_D5, PIN_LCD_D6, PIN_LCD_D7,
    PIN_LCD_LED, POSITIVE);

/* Keypad setup */
#include <Keypad.h>

const byte KEYPAD_ROWS = 4;
const byte KEYPAD_COLS = 4;
byte rowPins[KEYPAD_ROWS] = {PIN_PC1, PIN_PC0, PIN_PB0, PIN_PB1};
byte colPins[KEYPAD_COLS] = {PIN_PB2, PIN_PB3, PIN_PB4, PIN_PB5};
char keys[KEYPAD_ROWS][KEYPAD_COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};

Keypad _keypad = Keypad(makeKeymap(keys), rowPins, colPins, KEYPAD_ROWS, KEYPAD_COLS);

/* SafeState stores the secret code in EEPROM */
#include "SafeState.h"
SafeState _safeState;

#include "Tone.h"
Tone _tone;

#include "Light.h"
Light _light(&_tone);

#include "Icons.h"
Icons _icons(&_lcd);

#include "UI.h"
UI _ui(&_lcd, &_keypad, &_safeState, &_light, &_tone);

void setup()
{
    #ifdef DEBUG
    Serial.begin(115200);
    Serial.println("Started");
    #endif
    Wire.swap();

    _lcd.begin(16, 2);

    /* Make sure the physical lock is sync with the EEPROM state */
    if (_safeState.locked())
        _light.lock();
    else
        _light.unlock();
}

void loop()
{
    _ui.loop();
    _tone.loop();
    _light.loop();
    delay(50);
}
