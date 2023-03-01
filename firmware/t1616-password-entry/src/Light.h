#pragma once

#include <tinyNeoPixel.h>
#include "Tone.h"

#define PIN_RGB PIN_PA7
#define LED_COUNT 1

class Light
{
private:
    tinyNeoPixel *pixels = new tinyNeoPixel(LED_COUNT, PIN_RGB, NEO_GRB + NEO_KHZ800);
    Tone *tone;

    uint32_t seq_starts = 0;
    uint32_t seq_ends = 0;
    uint8_t seq_max = 0;
    uint8_t seq = 0;
    uint32_t seq_color = 0;

    void setColor(uint32_t color);
    void flash(uint32_t color, uint8_t count, uint32_t delay_ms);

public:
    Light(Tone *tone) : tone(tone)
    {
        pixels->begin();
    };

    void lock();
    void denied();
    void unlock();

    void loop();
};

void Light::setColor(uint32_t color)
{
    pixels->clear();
    if (color != 0)
        for (uint8_t i = 0; i < LED_COUNT; i++)
            pixels->setPixelColor(i, color);
    pixels->show();
}

void Light::flash(uint32_t color, uint8_t count, uint32_t delay_ms)
{
    seq = 0;
    seq_max = count * 2 - 1;
    seq_starts = millis();
    seq_ends = seq_starts + delay_ms;
    seq_color = color;
    pinMode(PIN_RGB, OUTPUT);
    setColor(color);
}

void Light::lock()
{
    auto blue = pixels->Color(0, 0, 0xff);
    flash(blue, 1, 500);
}

void Light::denied()
{
    tone->beep(500, 500);
    auto red = pixels->Color(0xff, 0, 0);
    flash(red, 5, 200);
}

void Light::unlock()
{
    tone->beep(500, 150, true);
    auto green = pixels->Color(0, 0xff, 0);
    flash(green, 3, 250);
}

void Light::loop()
{
    if (seq <= seq_max)
    {
        if (millis() > seq_ends)
        {
            uint32_t color = (seq % 2 == 0) ? seq_color : pixels->Color(0, 0, 0);
            setColor(color);
            seq++;
            uint32_t delay_ms = seq_ends - seq_starts;
            seq_starts = seq_ends;
            seq_ends += delay_ms;
        }
    }
}