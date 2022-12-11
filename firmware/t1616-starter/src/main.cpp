#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define PIN_LED PIN_PB4 // 5
#define PIN_RGB PIN_PA7

uint8_t seq = 0;

Adafruit_NeoPixel pixels(1, PIN_RGB, NEO_GRB + NEO_KHZ800);

void setup() {

  pinMode(PIN_LED, OUTPUT);

  delay(1000);
  Serial.begin(115200);
  Serial.printf("Started at %d MHz\n", F_CPU);

  pixels.begin();
}

void loop() {
  seq++;

  Serial.print('.');

  digitalWrite(PIN_LED, seq % 2);

  pixels.clear();
  if (seq % 2 == 0)
    pixels.setPixelColor(0, pixels.Color((0xff - seq) % 0xff, seq % 0xff, seq % 0x7f + (0xff - seq) % 0x7f));
  pixels.show();

  delay(250);
}