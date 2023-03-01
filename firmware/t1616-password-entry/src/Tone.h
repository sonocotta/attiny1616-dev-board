#pragma once

#include <Arduino.h>

#define PIN_BUZZER PIN_PC2
#define NO_TONE         \
    noTone(PIN_BUZZER); \
    digitalWrite(PIN_BUZZER, HIGH);

class Tone
{
private:
    uint32_t beep_start = 0;
    uint32_t beep_end = 0;
    uint32_t beep_freq = 0;
    bool beeping = false;
    bool isHappy = false;

public:
    Tone()
    {
        digitalWrite(PIN_BUZZER, HIGH);
    };

    void beep(uint32_t how_long, uint32_t freq, bool happy = false);
    void happyBeep(uint32_t how_long, uint32_t freq);
    void loop();
};

void Tone::beep(uint32_t how_long, uint32_t freq, bool happy)
{
    beep_start = millis();
    beep_end = beep_start + how_long;
    beep_freq = freq;
    tone(PIN_BUZZER, beep_freq);
    isHappy = happy;
    beeping = true;
}

void Tone::loop()
{
    if (beeping)
    {
        if (isHappy)
        {
            tone(PIN_BUZZER, beep_freq + (millis() - beep_start));
        }

        if (millis() > beep_end)
        {
            NO_TONE;
            beeping = false;
        }
    }
}