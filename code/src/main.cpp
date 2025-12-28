
#include <Arduino.h>

#define PIN_LED_NOW   PD3
#define PIN_LED_2SLOW PD4
#define PIN_LED_0     PD5
#define PIN_LED_1     PD6

#define PIN_RGB_FRONT PC6
#define PIN_RGB_BACK  PC7

void setup() {
    counter = 0;
    pinMode(PIN_LED_NOW, OUTPUT);
}

void loop() {
    digitalWrite(PIN_LED_NOW, 1);
    delay(500);
    digitalWrite(PIN_LED_NOW, 0);
    delay(500);
}
