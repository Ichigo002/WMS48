#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "Display.h"
#include "Font.h"

#include <string>

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

    void drawText(uint8_t x, uint8_t y, string text, const Font& font, uint8_t brig = 32);

private:

    void drawLineLow(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t brig);
    void drawLineHigh(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t brig);
    Display& display;
};

#endif