
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

class RainbowGenerator {
    Color &_output;
    uint16_t _counter;
    uint16_t _step;
    uint8_t _saturation;
    uint8_t _value;

public:
    RainbowGenerator(Color &output, uint16_t step,
                     uint8_t saturation, uint8_t value) :
        _output(output), _counter(0), _step(step),
        _saturation(saturation), _value(value) {}

    void step() {
        _output = FineHSV(_counter, _saturation, _value);
        _counter += _step;
        _counter %= FineHSV::MAX_HUE;
    }
};

#define PIN_LED_NOW   PD3
#define PIN_LED_2SLOW PD4
#define PIN_LED_0     PD5
#define PIN_LED_1     PD6

#define PIN_RGB_FRONT PC6
#define PIN_RGB_BACK  PC7

#define PIN_BUTTON    PD0

const int PINS[] = { PIN_LED_NOW, PIN_LED_0, PIN_LED_1, PIN_LED_2SLOW };

volatile unsigned counter = 0;

Color colors_front[2] = {};
WS2812 output_front(colors_front, { GPIOC, 6 });

RainbowGenerator rainbow[] = {
    { colors_front[0], FineHSV::MAX_HUE / 8 / 10, 255, 8 },
    { colors_front[1], FineHSV::MAX_HUE / 8 / 7, 255, 8 }
};

void resetCounter() {
    counter = 0;
}

void setup() {
    for (int pin : PINS) pinMode(pin, OUTPUT);
    pinMode(PIN_RGB_FRONT, OUTPUT);
    pinMode(PIN_BUTTON, INPUT_PULLUP);
    // The CH32V003 framework does not use the normal Arduino API. :(
    attachInterrupt(digitalPinToInterrupt(PIN_BUTTON), GPIO_Mode_IPU,
                    resetCounter, EXTI_Mode_Interrupt, EXTI_Trigger_Falling);
}

void loop() {
    unsigned curCounter = counter;
    if (curCounter < 8 * 5) {
        digitalWrite(PINS[curCounter & 3], !(curCounter >> 2 & 1));
        counter = curCounter + 1;
    }
    for (auto &r : rainbow) r.step();
    output_front.output();
    delay(125);
}
