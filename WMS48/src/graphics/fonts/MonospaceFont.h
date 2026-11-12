#ifndef MONOSPACE_FONT_H
#define MONOSPACE_FONT_H

#include "graphics/fonts/Font.h"
#include <Arduino.h>

class MonospaceFont : public Font
{
public:
    MonospaceFont() : Font(396, 95, 1, -7, "default") {};
    ~MonospaceFont() override = default;

    virtual const Glyph &_getGlyph(int g) const override
    {
        if(g < 0 || g > glyphs_length)
        {
            g = 1;
        }
        return glyphs[g];
    }

    virtual const uint8_t &getByte(int i) const override
    {
        return bitmap[i];
    }

private:
    const Glyph glyphs[95] = {

    };
    const uint8_t bitmap[396] = {

    };
};

#endif