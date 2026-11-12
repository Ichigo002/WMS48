#include "Font.h"
#include "PolishDiacriticalsDecoder.h"

int Font::getTextWidth(const String &txt, int font_size) const
{
    std::vector<int>& idxs = decodeTextToCharIndex(txt);

    int l = 0;
    for (size_t i = 0; i < idxs.size(); i++)
    {
        l += getGlyphByCharIndex(idxs[i]).w * font_size;

        l += spacing * font_size;
    }
    return l;
}

int Font::getTextHeight(const String &txt, int font_size) const
{
    int h_above = 0;
    int h_below = 0;
    std::vector<int>& idxs = decodeTextToCharIndex(txt);
    const Glyph *g;
    for (size_t i = 0; i < idxs.size(); i++)
    {
        g = &getGlyphByCharIndex(idxs[i]);
        // Serial.printf("%c yOff=%d h=%d top=%d bottom=%d\n",
        //   txt[i], g->yOffset, g->h, g->yOffset, g->yOffset + g->h);

        if (g->yOffset + g->h > h_below)
            h_below = g->yOffset + g->h;

        if (g->yOffset < h_above)
            h_above = g->yOffset;
    }

    return ((-h_above) + h_below) * font_size;
}

int Font::getTextTopOffset(const String &txt, int font_size) const
{
    int top = 0;
    std::vector<int>& idxs = decodeTextToCharIndex(txt);

    const Glyph *g;
    for (size_t i = 0; i < idxs.size(); i++)
    {
        g = &getGlyphByCharIndex(idxs[i]);
        if (g->yOffset < top)
            top = g->yOffset;
    }

    return -top * font_size;
}

int Font::getTextBottomOffset(const String &txt, int font_size) const
{
    int bot = 0;
    std::vector<int>& idxs = decodeTextToCharIndex(txt);
    const Glyph *g;
    for (size_t i = 0; i < idxs.size(); i++)
    {
        g = &getGlyphByCharIndex(idxs[i]);
        if (g->yOffset + g->h > bot)
            bot = g->yOffset + g->h;
    }

    return bot * font_size;
}

const Glyph &Font::getGlyphByCharIndex(int char_index) const
{
    
    if (char_index > 0)
    {
        if ((char_index - 0x20) >= 0 && (char_index - 0x20) < ascii_glyphs_length)
            return _getGlyph(char_index - 0x20); // return correct ascii

        return _getGlyph('X' - 0x20); // X Bad GLYPH INDEX
    }

    char_index *= -1;

    if (char_index + ascii_glyphs_length >= glyphs_length)
        return _getGlyph('R' - 0x20); // R Bad GLYPH INDEX

    return _getGlyph(char_index + ascii_glyphs_length); // return correct polish case
}

uint8_t Font::getByte(int n) const
{
    // if(n < 0 || n >= bitmap_length);
    //     return 0;
    return _getByte(n);
}
