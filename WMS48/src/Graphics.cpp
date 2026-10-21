#include "Graphics.h"
#include "config.h"

#define ABS(a) (((a) < 0) ? -(a) : (a))

Graphics::Graphics(Display &_display) : display(_display)
{
}

Graphics::~Graphics()
{
}

int Graphics::getTextWidth(const String &txt, const Font &f, const int font_size, const int spacing)
{
    return txt.length() * font_size * (f.getCharacterWidth() + spacing) - font_size * spacing;
}

void Graphics::clear()
{
    display.clear();
}

void Graphics::drawPixel(int x, int y, uint8_t brig)
{
    display.setPixelRaw(x, y, brig);
}

void Graphics::drawLine(int x0, int y0, int x1, int y1, uint8_t brig)
{
    if (ABS(y1 - y0) < ABS(x1 - x0))
    {
        if (x0 > x1)
            drawLineLow(x1, y1, x0, y0, brig);
        else
            drawLineLow(x0, y0, x1, y1, brig);
    }
    else
    {
        if (y0 > y1)
            drawLineHigh(x1, y1, x0, y0, brig);
        else
            drawLineHigh(x0, y0, x1, y1, brig);
    }
}

void Graphics::drawRect(int x, int y, uint8_t w, uint8_t h, uint8_t brig)
{
    w--;
    h--;

    for (int _x = x; _x < x + w; _x++)
    {
        drawPixel(_x, y, brig);
    }

    for (int _x = x; _x < x + w; _x++)
    {
        drawPixel(_x, y + h, brig);
    }

    for (int _y = y; _y < y + h; _y++)
    {
        drawPixel(x, _y, brig);
    }

    for (int _y = y; _y <= y + h; _y++)
    {
        drawPixel(x + w, _y, brig);
    }
}

void Graphics::drawFilledRect(int x, int y, int w, int h, uint8_t brig)
{ 
    if(brig > MAX_BRIGHTNESS)
    {
        brig = MAX_BRIGHTNESS;
    }

    if(x < 0) {
        w += x;
        x = 0;
    }
    if(y < 0) {
        h += y;
        y = 0;
    }
    if(x >= WIDTH || y >= HEIGHT) {
        return;
    }

    for (int i = x; i < x + w; i++)
    {
        for (int j = y; j < y + h; j++)
        {
            //display.__graphic_unsafe_setPixelRaw(i, j, brig);
            display.setPixelRaw(i,j,brig);
        }
    }
}

void Graphics::drawCircle(int x0, int y0, int r, uint8_t brig)
{
    int dx = r;
    int dy = 0;
    int t1 = r / 16;

    while (dx >= dy)
    {
        drawSymmetricCircle(x0, y0, dx, dy, brig);

        dy++;
        t1 += dy;
        int t2 = t1 - dx;
        if (t2 >= 0)
        {
            t1 = t2;
            dx--;
        }
    }
}

void Graphics::drawCharacter(int x, int y, char ascii, const Font &font, int font_size, uint8_t brig)
{
    if (ascii == ' ')
    {
        return;
    }

    const uint8_t *ch = font.getCharacter(ascii);

    for (size_t iy = 0; iy < font.getCharacterHeight(); iy++)
    {
        for (size_t ix = 0; ix < font.getCharacterWidth(); ix++)
        {
            if (ch[iy] & (1 << (font.getCharacterWidth() - ix - 1)))
            {
                //Serial.println(font_size);
                for (size_t sx = 0; sx < font_size; sx++)
                {
                    for (size_t sy = 0; sy < font_size; sy++)
                    {
                        drawPixel(x + sx + font_size * ix, y + sy + font_size * iy, brig);

                        //Serial.printf("x: %d, y: %d", x + sx + font_size * ix, y + sy + font_size * iy);
                    }
                }
            }
        }
    }
}

void Graphics::drawText(int x, int y, String text, const Font &font, int font_size, uint8_t brig, int spacing)
{
    for (size_t i = 0; i < text.length(); i++)
    {
        int tx = x + i * font_size * (font.getCharacterWidth() + spacing);
        // if(tx > 48)
        // {
        //     return;
        // }

        drawCharacter(tx, y, text[i], font, font_size, brig);
    }
}

void Graphics::drawSymmetricCircle(int x0, int y0, int dx, int dy, uint8_t brig)
{
    drawPixel(x0 + dx, y0 + dy, brig);
    drawPixel(x0 - dx, y0 + dy, brig);
    drawPixel(x0 + dx, y0 - dy, brig);
    drawPixel(x0 - dx, y0 - dy, brig);

    drawPixel(x0 + dy, y0 + dx, brig);
    drawPixel(x0 - dy, y0 + dx, brig);
    drawPixel(x0 + dy, y0 - dx, brig);
    drawPixel(x0 - dy, y0 - dx, brig);
}

void Graphics::drawLineLow(int x0, int y0, int x1, int y1, uint8_t brig)
{
    int dx = x1 - x0;
    int dy = y1 - y0;

    int yi = 1;

    if (dy < 0)
    {
        yi = -1;
        dy = -dy;
    }

    int D = 2 * dy - dx;
    int y = y0;

    for (int x = x0; x <= x1; x++)
    {
        drawPixel(x, y, brig);
        if (D > 0)
        {
            y += yi;
            D = D + (2 * (dy - dx));
        }
        else
        {
            D = D + 2 * dy;
        }
    }
}

void Graphics::drawLineHigh(int x0, int y0, int x1, int y1, uint8_t brig)
{
    int dx = x1 - x0;
    int dy = y1 - y0;

    int xi = 1;

    if (dx < 0)
    {
        xi = -1;
        dx = -dx;
    }

    int D = 2 * dx - dy;
    int x = x0;

    for (int y = y0; y <= y1; y++)
    {
        drawPixel(x, y, brig);
        if (D > 0)
        {
            x += xi;
            D = D + (2 * (dx - dy));
        }
        else
        {
            D = D + 2 * dx;
        }
    }
}
