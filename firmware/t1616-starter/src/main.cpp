#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define PIN_LED PIN_PB4 // 5
#define PIN_RGB PIN_PA7
#define PIN_BTN PIN_PA0

uint8_t seq = 0;

Adafruit_NeoPixel pixels(1, PIN_RGB, NEO_GRB + NEO_KHZ800);

void setup() {

  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_BTN, INPUT);

  delay(1000);
  Serial.begin(115200);
  Serial.printf("Started at %d MHz\n", F_CPU);

  pixels.begin();
}

uint8_t btn_state = HIGH;

void loop() {
  seq++;

  Serial.print('.');

  if (btn_state != digitalRead(PIN_BTN)) {
    btn_state = !btn_state;
    Serial.print("Button state is ");
    Serial.println(btn_state);
  }

  digitalWrite(PIN_LED, seq % 2);

  pixels.clear();
  if (seq % 2 == 0)
    pixels.setPixelColor(0, pixels.Color((0xff - seq) % 0xff, seq % 0xff, seq % 0x7f + (0xff - seq) % 0x7f));
  pixels.show();

  delay(500);
}