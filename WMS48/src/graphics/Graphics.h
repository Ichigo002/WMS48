#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "Display.h"
#include "graphics/fonts/Font.h"

#include <string>
#include <math.h>

using std::string;

// brig - brightness
class Graphics
{
public:
    Graphics(Display& _display, const Font& ebmedded_font);
    ~Graphics();

    void setFont(const Font& f);

    void clear();
    void drawPixel(int x, int y, uint8_t brig);
    void drawLine(int x0, int y0, int x1, int y1, uint8_t brig = 32);
    void drawRect(int x, int y, uint8_t w, uint8_t h, uint8_t brig = 32);
    void drawFilledRect(int x, int y, int w, int h, uint8_t brig = 32);
    void drawCircle(int x0, int y0, int r, uint8_t brig = 32);

    void drawCharacter(int x, int y, char ascii, const Font& font, int font_size = 1, uint8_t brig = 32);
    void drawCharacter(int x, int y, char ascii, int font_size = 1, uint8_t brig = 32);


    void drawText(int x, int y, String text, const Font& font, int font_size = 1, uint8_t brig = 32);
    void drawText(int x, int y, String text, int font_size = 1, uint8_t brig = 32);


private:

    void drawSymmetricCircle(int x0, int y0, int dx, int dy, uint8_t brig);

    void drawLineLow(int x0, int y0, int x1, int y1, uint8_t brig);
    void drawLineHigh(int x0, int y0, int x1, int y1, uint8_t brig);
    Display& display;

    const Font* embeddedFont;
};

#endif