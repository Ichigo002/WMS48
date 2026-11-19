#ifndef FONT_MANAGER_H
#define FONT_MANAGER_H

#include "graphics/fonts/Font.h"
#include "graphics/fonts/NataliaFont.h"
#include "graphics/fonts/MonospaceFont.h"

class FontManager
{
public:
    FontManager();
    ~FontManager();

    Font& getFont(String name);
private:
    NataliaFont f1;
    MonospaceFont f2;
};


#endif