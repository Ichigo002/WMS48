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
       // Serial.printf("%c yOff=%d h=%d top=%d bottom=%d\n",
        //   txt[i], g->yOffset, g->h, g->yOffset, g->yOffset + g->h);

        if(g->yOffset + g->h > h_below)
            h_below = g->yOffset + g->h;
            
        if(g->yOffset < h_above)
            h_above = g->yOffset;
    }
    
    return ((-h_above) + h_below) * font_size;
}

int Font::getTextTopOffset(const String &txt, int font_size) const
{
    int top = 0;
    const Glyph *g;
    for (size_t i = 0; i < txt.length(); i++)
    {
        g =  &getGlyph(txt[i]);
        if(g->yOffset < top)
            top = g->yOffset;
    }
    
    return -top * font_size;
}

int Font::getTextBottomOffset(const String &txt, int font_size) const
{
    int bot = 0;
    const Glyph *g;
    for (size_t i = 0; i < txt.length(); i++)
    {
        g =  &getGlyph(txt[i]);
        if(g->yOffset + g->h > bot)
            bot = g->yOffset + g->h;
    }
    
    return bot * font_size;
}

void Font::convertStringToGlyphIndexTable(const String &txt, int *glyph_index_tab, int &size)
{
    for (size_t i = 0; i < txt.length(); i++)
    {
        if((unsigned char)txt[i] <= 127)
        {
            Serial.printf("char: %i", (int)txt[i]);
        }
        else
        {
            Serial.printf("utf: %#x, %#x", txt[i], txt[i+1]);
            i++;
        }
    }
    
}

const Glyph &Font::getGlyph(char c) const
{
    if ((c - 0x20) >= glyphs_length)
            return _getGlyph('X' - 0x20); // X NULL GLYPH

    return _getGlyph(c - 0x20);
}
