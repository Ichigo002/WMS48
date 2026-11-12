#ifndef FONT_H
#define FONT_H

#include <Arduino.h>

struct Glyph
{
    uint16_t byteAddr; // tells which byte in bitmap starts a glyph
    uint8_t w, h; // width and height of glyph
    int8_t yOffset; // offset from cursor/baseline to top-left of bitmap
};


class Font
{
public:
    Font(int bitmap_leng, int glyphs_leng, int spacing_, int max_Yoffset, String name) 
        : bitmap_length(bitmap_leng), glyphs_length(glyphs_leng), spacing(spacing_), max_Yoffset(max_Yoffset), name(name)
        {};
    virtual ~Font() = default;

    int getTextWidth(const String& txt, int font_size = 1) const;
    int getTextHeight(const String& txt, int font_size = 1) const;
    // returns positive integer of top height above baseline
    int getTextTopOffset(const String& txt, int font_size = 1) const;
    // returns positive integer of height below baseline
    int getTextBottomOffset(const String& txt, int font_size = 1) const;

    const Glyph& getGlyphByCharIndex(int char_index) const;
    
    const uint8_t getByte(int n) const;

    const int spacing;
    const int max_Yoffset; // max y offest over baseline, IT IS NEGATIVE: -7 example
    const String name;

private:
    virtual const Glyph& _getGlyph(int g) const = 0;
    virtual const uint8_t& _getByte(int i) const = 0;

    const int bitmap_length; // length of bitmap table
    const int glyphs_length; // length of glyphs table
    const int ascii_glyphs_length = 95; // when ascii ends in glyph table 
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
                w = 5;
                h = 7;
                xOffset = 0;

    const int bitmap_length = 5; // length of bitmap table
    const int glyphs_length = 1; // length of glyphs table



*/