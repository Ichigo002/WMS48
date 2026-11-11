#ifndef FONT_MANAGER_H
#define FONT_MANAGER_H

#include "graphics/fonts/Font.h"
#include "graphics/fonts/DefaultFont.h"

#define FONT_DEFAULT "default"
#define FONT_MONO "monospace"
#define FONT_LOVELY "fell-in-love-natalia"

class FontManager
{
public:
    FontManager();
    ~FontManager();

    Font& getFont(String name);
private:
    DefaultFont font_d;
};


#endif