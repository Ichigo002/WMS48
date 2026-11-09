#ifndef DEFAULT_FONT_H
#define DEFAULT_FONT_H

#include "graphics/fonts/Font.h"
#include <Arduino.h>

class DefaultFont : public Font
{
public:
    DefaultFont() : Font(5, 1, 1) {};
    ~DefaultFont() override = default;

    virtual const Glyph &getGlyph(char c) const override
    {
        if (c >= glyphs_length)
            return glyphs[0]; // X NULL GLYPH

        return glyphs[0]; // change it later to c - 0x20
    }

    virtual const uint8_t& getByte(int i) const override {
        return bitmap[i];
    }


    const Glyph glyphs[1] = {{0, 5, 5, 7, 0, -7}};
private:
    const uint8_t bitmap[5] = {0x74, 0x63, 0xf8, 0xc6, 0x20};
};

#endif