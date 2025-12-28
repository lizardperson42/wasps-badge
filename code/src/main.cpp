
#include <Arduino.h>

#include "ws2812.h"

struct FineHSV {
    uint16_t hue;
    uint8_t saturation;
    uint8_t value;

    static constexpr uint16_t MAX_HUE = 256 * 6;

    FineHSV(uint16_t hue, uint8_t saturation, uint8_t value) :
        hue(hue), saturation(saturation), value(value) {}

    operator Color() const {
        // <https://en.wikipedia.org/wiki/HSL_and_HSV#HSV_to_RGB>
        int chroma = value * saturation / 255;
        int complement = hue % (2 * 256);
        if (complement >= 256) complement = 512 - complement;
        complement = complement * chroma / 256;

        int r, g, b;
        if (hue < 256) {
            r = chroma    ; g = complement; b = 0         ;
        } else if (hue < 256 * 2) {
            r = complement; g = chroma    ; b = 0         ;
        } else if (hue < 256 * 3) {
            r = 0         ; g = chroma    ; b = complement;
        } else if (hue < 256 * 4) {
            r = 0         ; g = complement; b = chroma    ;
        } else if (hue < 256 * 5) {
            r = complement; g = 0         ; b = chroma    ;
        } else {
            r = chroma    ; g = 0         ; b = complement;
        }

        int whiten = value - chroma;
        return Color{ uint8_t(r + whiten),
                      uint8_t(g + whiten),
                      uint8_t(b + whiten) };
    }
};

#define PIN_LED_NOW   PD3
#define PIN_LED_2SLOW PD4
#define PIN_LED_0     PD5
#define PIN_LED_1     PD6

#define PIN_RGB_FRONT PC6
#define PIN_RGB_BACK  PC7

const int PINS[] = { PIN_LED_NOW, PIN_LED_0, PIN_LED_1, PIN_LED_2SLOW };

unsigned counter = {};
unsigned rainbowCounter = 0;

Color colors_front[2] = {};
Color colors_back[3] = {};
WS2812 output_front(colors_front, { GPIOC, 6 });
WS2812 output_back(colors_back, { GPIOC, 7 });

void setup() {
    counter = 0;
    rainbowCounter = 0;
    for (int pin : PINS) pinMode(pin, OUTPUT);
    pinMode(PIN_RGB_FRONT, OUTPUT);
    pinMode(PIN_RGB_BACK, OUTPUT);
    colors_back[0] = { 8, 0, 0 };
    colors_back[1] = { 0, 8, 0 };
    colors_back[2] = { 0, 0, 8 };
}

void loop() {
    counter = (counter + 1) & 7;
    digitalWrite(PINS[counter & 3], counter >> 2 & 1);
    colors_front[0] = FineHSV(rainbowCounter, 255, 8);
    colors_front[1] = FineHSV((rainbowCounter + FineHSV::MAX_HUE / 2) %
                                  FineHSV::MAX_HUE,
                              255, 8);
    output_front.output();
    output_back.output();
    rainbowCounter = (rainbowCounter + FineHSV::MAX_HUE / 10 / 8) %
                         FineHSV::MAX_HUE;
    delay(125);
}
