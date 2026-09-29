#include "Display.h"

Display *Display::instance = nullptr;

Display::Display()
{
    current_row = 0;
}

Display::~Display()
{
}

void Display::setup(uint8_t refresh_freq_hz)
{
    instance = this;

    uint32_t T_us = 1000000UL / (refresh_freq_hz * 32);

    timer = timerBegin(0, 80, true);
    timerAttachInterrupt(timer, &Display::refreshISR, true);
    timerAlarmWrite(timer, T_us, true);
    timerAlarmEnable(timer);

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


void Display::setPixelRaw(u_int x, u_int y, uint8_t value)
{
    if(x >=48 || y >= 32)
        return;
    buffer[x][y] = value;
}

void IRAM_ATTR Display::refresh_row(int row)
{
    digitalWrite(config::display::rows_latch, LOW);
    digitalWrite(config::display::rows_clk, LOW);

    int physical_row = map_y[row];


    // do zmiany i przeprogramowania:
    int current_hc595 = ((8 - row % 8) + row) / 8;
    int tmp_buff = 0;

    for (size_t i = 0; i < 4; i++)
    {
        tmp_buff = 255;
        //if (current_hc595 == i)
        //    tmp_buff = (1 << (row % 8));

        shiftOut(
            config::display::rows_data,
            config::display::rows_clk,
            LSBFIRST,
            ~tmp_buff);
    }

    digitalWrite(config::display::rows_latch, HIGH);

    digitalWrite(config::display::rows_latch, LOW);
}

void IRAM_ATTR Display::refresh_cols(int current_row)
{
    digitalWrite(config::display::columns_oe, LOW);
    digitalWrite(config::display::columns_latch, LOW);
    digitalWrite(config::display::columns_clk, LOW);

    for (char i = 0; i < 6; i++) // clear buffor before next refresh
    {
        buff[i] = 0;
    }

    for (byte j = 0; j < 48; j++)
    {
        if (buffer[j][current_row] != 0) // TEMPORARY
        {
            int m = map_x[j];
            int which_buff = (m - (m % 8)) / 8;
            buff[which_buff] = buff[which_buff] | (1 << (m % 8));   
        }
    }

    for (byte i = 0; i < 6; i++)
    {
        /* 0 - turned off, 1 - turned on*/
        shiftOut(
            config::display::columns_data,
            config::display::columns_clk,
            LSBFIRST,
            buff[i]);
    }

    digitalWrite(config::display::columns_latch, HIGH);
    digitalWrite(config::display::columns_latch, LOW);
}

void IRAM_ATTR Display::refreshISR()
{
    instance->refresh_cols(instance->current_row);
    instance->refresh_row(instance->current_row);

    instance->current_row++;
    if (instance->current_row > 32)
        instance->current_row = 0;
}
