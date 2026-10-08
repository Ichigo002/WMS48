#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "Display.h"
#include "Font.h"

#include <string>
#include <math.h>

using std::string;

// brig - brightness
class Graphics
{
public:
    Graphics(Display& _display);
    ~Graphics();

    void clear();
    void drawPixel(uint8_t x, uint8_t y, uint8_t brig);
    void drawLine(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t brig = 32);
    void drawRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t brig = 32);
    void drawFilledRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t brig = 32);
    void drawCircle(uint8_t x, uint8_t y, uint8_t r, uint8_t brig = 32);
   // void drawQuarterOfCircle(uint8_t x, uint8_t y, uint8_t r, uint8_t )

    void drawCharacter(uint8_t x, uint8_t y, char ascii, const Font& font, int font_size = 1, uint8_t brig = 32);
    void drawText(uint8_t x, uint8_t y, string text, const Font& font, int font_size = 1, uint8_t brig = 32, int spacing = 1);

    double getDistanceBetween(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
private:

    void drawSymmetricCircle(uint8_t x, uint8_t y,uint8_t cx, uint8_t cy, uint8_t r, uint8_t brig);

    void drawLineLow(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t brig);
    void drawLineHigh(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t brig);
    Display& display;
};

#endif