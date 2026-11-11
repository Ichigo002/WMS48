#include "FontManager.h"

FontManager::FontManager()
{
}

FontManager::~FontManager()
{
}

Font &FontManager::getFont(String name)
{
    if(name == FONT_MONO)
        return font_d;
    if(name == FONT_LOVELY)
        return font_d;

    return font_d; // FONT_dEFAULT
}
