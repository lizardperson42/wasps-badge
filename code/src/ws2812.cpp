
#include "ws2812.h"

#include <initializer_list>

#include <Arduino.h>

void WS2812::output() {
    for (Color *p = _data, *e = _data + _size; p < e; p++) {
        for (uint8_t value : { p->g, p->r, p->b }) {
            for (int bitIndex = 7; bitIndex >= 0; bitIndex--) {
                outputBit(value >> bitIndex & 1);
            }
        }
    }
}

void WS2812::outputBit(bool value) {
    if (value) {
        _pin.set();
        asm volatile ( "nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n"
                       "nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n" );
        _pin.clear();
        asm volatile ( "nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n" );
    } else {
        _pin.set();
        asm volatile ( "nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n" );
        _pin.clear();
        asm volatile ( "nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n"
                       "nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n" );
    }
}

void WS2812::finishOutput() {
    delayMicroseconds(60);
}
