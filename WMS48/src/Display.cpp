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

    uint32_t T_us = 1000000UL / (refresh_freq_hz * 32); // 1/8 of resresh time for one bitplane

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

    digitalWrite(config::display::rows_oe, HIGH);

    buildBitPlanes();
}

void Display::update()
{
    buildBitPlanes();
}

void Display::setPixelRaw(u_int x, u_int y, uint8_t value)
{
    if (x >= 48 || y >= 32)
        return;
    abstract_buffer[x][y] = value;
}

void Display::buildBitPlanes()
{
    if(build_bitplane_ready)
        return;

    int m, which_buff;

    for (byte i = 0; i < 8; i++) // each bitplanes loop
    {
        for (byte j = 0; j < 32; j++) // each row loop
        {
            for (byte g = 0; g < 6; g++)
            {
                ptr_rebuild_bitplane[i][j][g] = 0;
            }
            
            for (byte l = 0; l < 48; l++) // each column loop
            {
                
                if (abstract_buffer[l][j] & (1 << (i)))
                {
                    m = map_x[l];
                    which_buff = (m - (m % 8)) / 8;

                    ptr_rebuild_bitplane[i][j][which_buff] =
                        ptr_rebuild_bitplane[i][j][which_buff] | (1 << (m % 8));

                }
            }
        }
    }
    build_bitplane_ready = true;

}

void IRAM_ATTR Display::swapBitplaneBuffer()
{
    if (ptr_ready_bitplane == bitplanes_A)
    {
        ptr_ready_bitplane = bitplanes_B;
        ptr_rebuild_bitplane = bitplanes_A;
    }
    else
    {
        ptr_ready_bitplane = bitplanes_A;
        ptr_rebuild_bitplane = bitplanes_B;
    }
}

void IRAM_ATTR Display::iram_refresh_finished()
{
    if(build_bitplane_ready)
    {
        build_bitplane_ready = false;
        swapBitplaneBuffer();
    }
}

void IRAM_ATTR Display::refresh_row(int row)
{
    digitalWrite(config::display::rows_latch, LOW);
    digitalWrite(config::display::rows_clk, LOW);

    for (byte i = 0; i < 4; i++)
    {
        buff_rows[i] = 0;
    }

    int pr = map_y[row]; // physical row
    int which_buff = (pr - (pr % 8)) / 8;
    buff_rows[which_buff] = buff_rows[which_buff] | (1 << (pr % 8));

    for (size_t i = 0; i < 4; i++)
    {
        shiftOut(
            config::display::rows_data,
            config::display::rows_clk,
            LSBFIRST,
            ~buff_rows[i]);
    }

    digitalWrite(config::display::rows_latch, HIGH);

    digitalWrite(config::display::rows_latch, LOW);
    digitalWrite(config::display::rows_oe, LOW);
    digitalWrite(config::display::columns_oe, LOW);
}

void IRAM_ATTR Display::refresh_cols(int current_row, int current_bitplane)
{
    digitalWrite(config::display::rows_oe, HIGH);
    digitalWrite(config::display::columns_oe, HIGH);

    digitalWrite(config::display::columns_latch, LOW);
    digitalWrite(config::display::columns_clk, LOW);

    for (byte i = 0; i < 6; i++)
    {
        uint8_t t = ptr_ready_bitplane[current_bitplane][current_row][i];

        /* 0 - turned off, 1 - turned on*/
        shiftOut(
            config::display::columns_data,
            config::display::columns_clk,
            LSBFIRST,
            t);
    }

    digitalWrite(config::display::columns_latch, HIGH);
    digitalWrite(config::display::columns_latch, LOW);
}

void IRAM_ATTR Display::refreshISR()
{
    instance->last_time = micros();
    instance->refresh_cols(instance->current_row, instance->current_bitplane);
    instance->refresh_row(instance->current_row);

    instance->current_row++;
    if (instance->current_row >= 32)
    {
        instance->current_row = 0;
        instance->current_bitplane++;
        if (instance->current_bitplane >= 8)
        {
            instance->current_bitplane = 0;
            instance->iram_refresh_finished();
        }
    }

    instance->refresh_time = micros() - instance->last_time;

}