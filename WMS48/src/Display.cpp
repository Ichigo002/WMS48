#include "Display.h"

Display::Display()
{
}

Display::~Display()
{
}

void Display::setup()
{
    pinMode(config::display::columns_clk, OUTPUT);
    pinMode(config::display::columns_data, OUTPUT);
    pinMode(config::display::columns_latch, OUTPUT);
    pinMode(config::display::columns_oe, OUTPUT);

    pinMode(config::display::rows_clk, OUTPUT);
    pinMode(config::display::rows_data, OUTPUT);
    pinMode(config::display::rows_latch, OUTPUT);
    pinMode(config::display::rows_oe, OUTPUT);

    digitalWrite(config::display::rows_oe, LOW);
}

void Display::refresh()
{
}

void Display::setPixel(int x, int y, uint8_t value)
{
}

void Display::refresh_rows()
{
    digitalWrite(config::display::rows_latch, LOW);
    digitalWrite(config::display::rows_clk, LOW);

    for (size_t i = 0; i < 4; i++)
    {
        int temp_counter;
        if (current_hc595 == i)
            temp_counter = (1 << refresh_row_counter);
        else
            temp_counter = 0;

        shiftOut(
            config::display::rows_data,
            config::display::rows_clk,
            MSBFIRST,
            ~temp_counter);
    }

    refresh_row_counter++;
    if (refresh_row_counter >= 8)
    {
        refresh_row_counter = 0;
        current_hc595 += 1;
        if (current_hc595 >= 4)
        {
            current_hc595 = 0;
        }
    }

    digitalWrite(config::display::rows_latch, HIGH);

    digitalWrite(config::display::rows_latch, LOW);
}

void Display::refresh_cols()
{
    digitalWrite(config::display::columns_oe, LOW);
    digitalWrite(config::display::columns_latch, LOW);
    digitalWrite(config::display::columns_clk, LOW);

    for (byte i = 0; i < 6; i++)
    {
        /* 0 - turned off, 1 - turned on*/
        shiftOut(
            config::display::columns_data,
            config::display::columns_clk,
            MSBFIRST,
            0
        );
    }

    digitalWrite(config::display::columns_latch, HIGH);
    digitalWrite(config::display::columns_latch, LOW);
}
