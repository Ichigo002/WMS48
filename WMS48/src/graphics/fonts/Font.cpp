#include "Font.h"

int Font::getTextWidth(const String &txt, int font_size) const
{
    int l = 0;
    for (size_t i = 0; i < txt.length(); i++)
    {
        l += getGlyphByChar(txt[i]).xAdvance * font_size;

        if (i < txt.length() - 1)
            l += spacing * font_size;
    }
    return l;
}

const Glyph &Font::getGlyphByChar(char c) const
{
    if(c >= glyphs_length)
        return glyphs[0]; // X NULL GLYPH

    return glyphs[0]; // change it later to c - 0x20
}
