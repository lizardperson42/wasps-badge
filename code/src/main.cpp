
#include <Arduino.h>

#define PIN_LED_NOW   PD3
#define PIN_LED_2SLOW PD4
#define PIN_LED_0     PD5
#define PIN_LED_1     PD6

#define PIN_RGB_FRONT PC6
#define PIN_RGB_BACK  PC7

const int PINS[] = { PIN_LED_NOW, PIN_LED_0, PIN_LED_1, PIN_LED_2SLOW };

unsigned counter = {};

void setup() {
    counter = 0;
    for (int pin : PINS) pinMode(pin, OUTPUT);
}

void loop() {
    counter = (counter + 1) & 7;
    digitalWrite(PINS[counter & 3], counter >> 2 & 1);
    delay(125);
}
