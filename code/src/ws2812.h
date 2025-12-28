
#ifndef WS28128B_H
#define WS28128B_H

#include <cstddef>
#include <cstdint>

#include <ch32v00x.h>

struct GPIOPin {
    GPIO_TypeDef *gpio;
    uint32_t mask;

    GPIOPin(GPIO_TypeDef *gpio, int offset) : gpio(gpio),
                                              mask(uint32_t(1) << offset) {}

    inline bool get() const {
        return gpio->INDR & mask;
    }
    inline void set() {
        gpio->BSHR = mask;
    }
    inline void clear() {
        gpio->BSHR = mask << 16;
    }
};

struct Color { uint8_t r, g, b; };

class WS2812 {
    Color *_data;
    size_t _size;
    GPIOPin _pin;

public:
    WS2812(Color *data, size_t size, GPIOPin pin) :
        _data(data), _size(size), _pin(pin) {}
    template<size_t N>
    WS2812(Color (&data)[N], GPIOPin pin) :
        WS2812(data, N, pin) {}

    Color *data() const { return _data; }
    size_t size() const { return _size; }

    void output();

private:
    void outputBit(bool value);
};

#endif
