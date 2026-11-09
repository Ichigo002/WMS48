#ifndef FONT_H
#define FONT_H

#include <Arduino.h>

struct Glyph
{
    uint8_t byteAddr; // tells which byte in bitmap starts a glyph
    uint8_t xAdvance; // tells how much move cursor after drawing
    uint8_t w, h; // width and height of glyph
    int8_t xOffset, yOffset; // offset from cursor/baseline to top-left of bitmap
};


class Font
{
public:
    Font(int bitmap_leng, int glyphs_leng, int spacing_) 
        : bitmap_length(bitmap_leng), glyphs_length(glyphs_leng), spacing(spacing_)
        {};
    virtual ~Font() = default;

    int getTextWidth(const String& txt, int font_size = 1) const;
    virtual const Glyph& getGlyph(char c) const = 0;
    virtual const uint8_t& getByte(int i) const = 0;


    const int bitmap_length; // length of bitmap table
    const int glyphs_length; // length of glyphs table
    const int spacing;
};

#endif

/*

Generator font input:

A
01110
10001
10001
11111
10001
10001
10001__________________ baseline;y=0


generator font output:

    RAW BITMAP:
    01110100|01100011|11111000|11000110|00100000

    const uint8_t bitmap[4] = {0x74, 0x63, 0xf8, 0xc6, 0x20};
    const Glyph glyphs[1] = {{0, 5, 5, 7, 0, -7}};

    {5, 5, 7, 0, -7} =>
                byteAddr = 0;
                xAdvance = 5;
                w = 5;
                h = 7;
                xOffset = 0;
                yOffset = -7;

    const int bitmap_length = 5; // length of bitmap table
    const int glyphs_length = 1; // length of glyphs table



*/