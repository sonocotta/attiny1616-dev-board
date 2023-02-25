#pragma once

#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include "SafeState.h"
#include "Icons.h"
#include "Light.h"
#include "Tone.h"

#define PIN_LENGTH 4

#define DELAY_LOCK 800
#define DELAY_UNLOCK 800
#define DELAY_MISMATCH 800
#define DELAY_DENIED 1600
#define DELAY_WELCOME 500
#define DELAY_UNLOCKED 1000
#define DELAY_STEPS 8

#define KEY_BEEP_MS 50
#define IDLE_TIMEOUT 8000

enum State
{
    WELCOME_1,
    WELCOME_2,

    CHECK_LOCKED,
    SAFE_LOCKED,
    SAFE_LOCKED_INPUTKEY,
    SAFE_LOCKED_VALIDATE,
    SAFE_LOCKED_DOUNLOCK,
    SAFE_LOCKED_DENIED,
    SAFE_UNLOCKED,
    SAFE_UNLOCKED_ASKKEY,
    SAFE_UNLOCKED_INPUTKEY,
    SAFE_UNLOCKED_REPEATKEY,
    SAFE_UNLOCKED_MATCH,
    SAFE_UNLOCKED_MISMATCH,
    SAFE_UNLOCKED_DOLOCK,

    WAIT_SCREEN_START,
    WAIT_SCREEN_PROGRESS,
    WAIT_SCREEN_NONBLOCKING,
    INPUT_PIN,
};

class UI
{
private:
    LiquidCrystal_I2C *lcd;
    Keypad *keypad;
    SafeState *safeState;
    Light *light;
    Tone *tone;

    State state = WELCOME_1;
    void setState(State _state)
    {
        // Serial.printf("State) { %d -> %d\n", state, _state);
        state = _state;
    };

    uint32_t idle_since = 0;

    // Nonblocking wait
    uint32_t wait_from = 0;
    uint32_t wait_till = 0;
    uint8_t wait_step = 0;
    State state_after_break;
    void wait(uint32_t how_long, State state_after, bool showProgress = true);

    // Nonblocking pin reading
    char key[PIN_LENGTH + 1] = {0};
    char pin[PIN_LENGTH + 1] = {0};
    uint8_t pin_keys;
    State state_after_pin;
    void askpin(State state_after);

protected:
    void showWaitScreen(int delayMillis);

public:
    UI(LiquidCrystal_I2C *lcd, Keypad *keypad, SafeState *safeState, Light *light, Tone *tone)
        : lcd(lcd), keypad(keypad), safeState(safeState), light(light), tone(tone)
    {
        idle_since = millis();
    };

    void loop();
};

void UI::loop()
{
    static bool newCodeNeeded;

    if (state == WELCOME_1)
    {
        lcd->setCursor(4, 0);
        lcd->print("Welcome!");
        wait(DELAY_WELCOME, WELCOME_2, false);
    }

    else if (state == WELCOME_2)
    {
        lcd->setCursor(0, 2);
        String message = "Tiny1616 Safe";
        for (byte i = 0; i < message.length(); i++)
        {
            lcd->print(message[i]);
            delay(50);
        }
        wait(DELAY_WELCOME, CHECK_LOCKED, false);
    }

    else if (state == CHECK_LOCKED)
    {
        setState(safeState->locked() ? SAFE_LOCKED : SAFE_UNLOCKED);
    }

    else if (state == SAFE_LOCKED)
    {
        lcd->clear();
        lcd->setCursor(0, 0);
        lcd->write(ICON_LOCKED_CHAR);
        lcd->print(" Safe Locked! ");
        lcd->write(ICON_LOCKED_CHAR);
        setState(SAFE_LOCKED_INPUTKEY);
    }

    else if (state == SAFE_UNLOCKED)
    {
        lcd->clear();

        lcd->setCursor(0, 0);
        lcd->write(ICON_UNLOCKED_CHAR);
        lcd->setCursor(2, 0);
        lcd->print(" # to lock");
        lcd->setCursor(15, 0);
        lcd->write(ICON_UNLOCKED_CHAR);

        newCodeNeeded = true;

        if (safeState->hasCode())
        {
            lcd->setCursor(0, 1);
            lcd->print("  A = new code");
            newCodeNeeded = false;
        }

        setState(SAFE_UNLOCKED_ASKKEY);
    }

    else if (state == SAFE_LOCKED_INPUTKEY)
    {
        askpin(SAFE_LOCKED_VALIDATE);
    }

    else if (state == SAFE_LOCKED_VALIDATE)
    {
        bool unlockedSuccessfully = safeState->unlock(String(pin));
        wait(DELAY_UNLOCK, unlockedSuccessfully ? SAFE_LOCKED_DOUNLOCK : SAFE_LOCKED_DENIED);
    }

    else if (state == SAFE_LOCKED_DOUNLOCK)
    {
        light->unlock();
        lcd->clear();
        lcd->setCursor(0, 0);
        lcd->write(ICON_UNLOCKED_CHAR);
        lcd->setCursor(4, 0);
        lcd->print("Unlocked!");
        lcd->setCursor(15, 0);
        lcd->write(ICON_UNLOCKED_CHAR);
        wait(DELAY_UNLOCKED, SAFE_UNLOCKED, false);
    }

    else if (state == SAFE_LOCKED_DENIED)
    {
        lcd->clear();
        lcd->setCursor(0, 0);
        lcd->print("Access Denied!");
        light->denied();
        wait(DELAY_DENIED, SAFE_LOCKED);
    }

    else if (state == SAFE_UNLOCKED_INPUTKEY)
    {
        lcd->clear();
        lcd->setCursor(0, 0);
        lcd->print("Enter new code) {");
        askpin(SAFE_UNLOCKED_REPEATKEY);
    }

    else if (state == SAFE_UNLOCKED_REPEATKEY)
    {
        strcpy(key, pin);
        lcd->clear();
        lcd->setCursor(0, 0);
        lcd->print("Confirm new code");
        askpin(SAFE_UNLOCKED_MATCH);
    }

    else if (state == SAFE_UNLOCKED_MATCH)
    {
        if (strcmp(key, pin) == 0)
        {
            safeState->setCode(String(pin));
            setState(SAFE_UNLOCKED_DOLOCK);
        }
        else
        {
            lcd->clear();
            lcd->setCursor(1, 0);
            lcd->print("Code mismatch");
            lcd->setCursor(0, 1);
            lcd->print("Safe not locked!");
            wait(DELAY_MISMATCH, SAFE_UNLOCKED);
        }
    }

    else if (state == SAFE_UNLOCKED_DOLOCK)
    {
        lcd->clear();
        lcd->setCursor(5, 0);
        lcd->write(ICON_UNLOCKED_CHAR);
        lcd->print(" ");
        lcd->write(ICON_RIGHT_ARROW);
        lcd->print(" ");
        lcd->write(ICON_LOCKED_CHAR);

        light->lock();
        safeState->lock();
        wait(DELAY_LOCK, CHECK_LOCKED);
    }

    else if (state == WAIT_SCREEN_PROGRESS)
    {
        uint32_t total = wait_till - wait_from;
        uint32_t passed = millis() - wait_from;
        uint32_t wait_step_ms = total / DELAY_STEPS;
        if (passed > wait_step * wait_step_ms)
        {
            wait_step++;
            lcd->print("#");
        }

        if (millis() > wait_till)
            setState(state_after_break);
    }

    else if (state == WAIT_SCREEN_NONBLOCKING)
    {
        if (millis() > wait_till)
            setState(state_after_break);
    }

    else if (state == INPUT_PIN)
    {
        {
            char key = keypad->getKey();
            if (key != NO_KEY)
                idle_since = millis();

            if (key >= '0' && key <= '9')
            {
                tone->beep(KEY_BEEP_MS, 2000);
                lcd->print('*');
                pin[pin_keys] = key;
                pin_keys++;
            }

            if (pin_keys >= PIN_LENGTH)
                setState(state_after_pin);
        }
    }

    else if (state == SAFE_UNLOCKED_ASKKEY)
    {
        auto key = keypad->getKey();
        if (key != NO_KEY)
            idle_since = millis();

        if (key == 'A' || key == '#')
        {
            tone->beep(KEY_BEEP_MS, 2000);
            if (key == 'A' || newCodeNeeded)
                setState(SAFE_UNLOCKED_INPUTKEY);
            else
                setState(SAFE_UNLOCKED_DOLOCK);
        }
    }

    lcd->setBacklight(idle_since + IDLE_TIMEOUT > millis());
}

void UI::wait(uint32_t how_long, State state_after, bool showProgress)
{
    wait_step = 0;
    wait_from = millis();
    wait_till = wait_from + how_long;
    state_after_break = state_after;
    if (showProgress)
    {
        lcd->setCursor(0, 1);
        lcd->print("   [         ]  ");
        lcd->setCursor(4, 1);
        setState(WAIT_SCREEN_PROGRESS);
    }
    else
    {
        setState(WAIT_SCREEN_NONBLOCKING);
    }
};

void UI::askpin(State state_after)
{
    // todo: 4 symbols only?
    lcd->setCursor(5, 1);
    lcd->print("[____]");
    lcd->setCursor(6, 1);

    pin_keys = 0;
    state_after_pin = state_after;
    setState(INPUT_PIN);
}