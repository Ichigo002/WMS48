#ifndef DEFAULT_FONT_H
#define DEFAULT_FONT_H

#include "graphics/fonts/Font.h"
#include <Arduino.h>




class DefaultFont : public Font
{
public:
    DefaultFont();
    ~DefaultFont();

private:

    const uint8_t bitmap[5] = {0x74, 0x63, 0xf8, 0xc6, 0x20};
    const Glyph glyphs[1] = {{5, 5, 7, 0, -7}};

    const int bitmap_length = 5; // length of bitmap table
    const int glyphs_length = 1; // length of glyphs table

    const int spacing = 1;
};


#endif