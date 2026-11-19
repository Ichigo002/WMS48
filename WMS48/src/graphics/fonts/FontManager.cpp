#include "FontManager.h"

FontManager::FontManager()
{
}

FontManager::~FontManager()
{
}

Font &FontManager::getFont(String name)
{
    if(name == FONT_MONOSPACE)
        return f2;

    return f1; // FONT_dEFAULT
}
