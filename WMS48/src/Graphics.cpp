#include "Graphics.h"

#define ABS(a) (((a) < 0) ? -(a) : (a))

Graphics::Graphics(Display &_display) : display(_display)
{
}

Graphics::~Graphics()
{
}

void Graphics::clear()
{
    display.clear();
}

void Graphics::drawPixel(uint8_t x, uint8_t y, uint8_t brig)
{
    display.setPixelRaw(x, y, brig);
}

void Graphics::drawLine(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t brig)
{
    if(ABS(y1-y0) < ABS(x1-x0))
    {
        if(x0 > x1)
            drawLineLow(x1, y1, x0, y0,brig);
        else
            drawLineLow(x0, y0, x1, y1, brig);
    }
    else
    {
        if(y0 > y1)
            drawLineHigh(x1, y1, x0, y0, brig);
        else
            drawLineHigh(x0, y0, x1, y1, brig);
    }
}

void Graphics::drawRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t brig)
{
    w--;
    h--;

    for (int _x = x; _x < x+w; _x++)
    {
        drawPixel(_x, y, brig);
    }

    for (int _x = x; _x < x+w; _x++)
    {
        drawPixel(_x, y+h, brig);
    }

    for (int _y = y; _y < y+h; _y++)
    {
        drawPixel(x, _y, brig);
    }

    for (int _y = y; _y <= y+h; _y++)
    {
        drawPixel(x+w, _y, brig);
    }

    
}

void Graphics::drawLineLow(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t brig)
{
    int dx = x1 - x0;
    int dy = y1 - y0;

    int yi = 1;

    if(dy < 0)
    {
        yi = -1;
        dy = -dy;
    }

    int D = 2*dy - dx;
    int y = y0;

    for (int x = x0; x < x1; x++)
    {
        drawPixel(x, y, brig);
        if(D > 0)
        {
            y += yi;
            D = D + (2*(dy - dx));
        }
        else
        {
            D = D + 2*dy;
        }
    }
}

void Graphics::drawLineHigh(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t brig)
{
    int dx = x1 - x0;
    int dy = y1 - y0;

    int xi = 1;

    if(dx < 0)
    {
        xi = -1;
        dx = -dx;
    }

    int D = 2*dx - dy;
    int x = x0;

    for (int y = y0; y < y1; y++)
    {
        drawPixel(x, y, brig);
        if(D > 0)
        {
            x += xi;
            D = D + (2*(dx - dy));
        }
        else
        {
            D = D + 2*dx;
        }
    }
}
