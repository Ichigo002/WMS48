#include "Font.h"

int Font::getTextWidth(const String &txt, int font_size) const
{
    int l = 0;
    for (size_t i = 0; i < txt.length(); i++)
    {
        l += getGlyph(txt[i]).w * font_size;

        l += spacing * font_size;
    }
    return l;
}

int Font::getTextHeight(const String &txt, int font_size) const
{
    int h_above = 0;
    int h_below = 0;
    const Glyph *g;
    for (size_t i = 0; i < txt.length(); i++)
    {
        g =  &getGlyph(txt[i]);

        if(g->yOffset + g->h > h_below)
            h_below = g->yOffset + g->h;
        if(g->yOffset < h_above)
            h_above = g->yOffset;
    }
    Serial.println(h_below);
    
    return ((-h_above) + h_below) * font_size + 1;
}

const Glyph &Font::getGlyph(char c) const
{
    if ((c - 0x20) >= glyphs_length)
            return _getGlyph(1); // X NULL GLYPH

    return _getGlyph(c - 0x20); // change it later to c - 0x20
}
