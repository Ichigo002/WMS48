#include "Display.h"

Display *Display::instance = nullptr;

#define COL_CLK_HIGH() (GPIO.out_w1ts = (1UL << 25))
#define COL_CLK_LOW() (GPIO.out_w1tc = (1UL << 25))

#define COL_LATCH_HIGH() (GPIO.out_w1ts = (1UL << 27))
#define COL_LATCH_LOW() (GPIO.out_w1tc = (1UL << 27))

#define COL_DATA_HIGH() (GPIO.out1_w1ts.val = (1UL << (33 - 32)))
#define COL_DATA_LOW() (GPIO.out1_w1tc.val = (1UL << (33 - 32)))

#define COL_OE_HIGH() (GPIO.out1_w1ts.val = (1UL << (32 - 32)))
#define COL_OE_LOW() (GPIO.out1_w1tc.val = (1UL << (32 - 32)))

#define ROW_CLK_HIGH() (GPIO.out_w1ts = (1UL << 2))
#define ROW_CLK_LOW() (GPIO.out_w1tc = (1UL << 2))

#define ROW_LATCH_HIGH() (GPIO.out_w1ts = (1UL << 5))
#define ROW_LATCH_LOW() (GPIO.out_w1tc = (1UL << 5))

#define ROW_DATA_HIGH() (GPIO.out_w1ts = (1UL << 18))
#define ROW_DATA_LOW() (GPIO.out_w1tc = (1UL << 18))

#define ROW_OE_HIGH() (GPIO.out_w1ts = (1UL << 17))
#define ROW_OE_LOW() (GPIO.out_w1tc = (1UL << 17))

Display::Display()
{
    current_row = 0;
}

Display::~Display()
{
}

void Display::setup(uint8_t refresh_freq_hz)
{
    setNewRefreshRate(refresh_freq_hz);
    setBrightness(1);
    instance = this;

    timer = timerBegin(0, 8, true);

    timerAttachInterrupt(timer, &Display::refreshISR, true);
    timerAlarmWrite(timer, ticks_per_row_refresh, true);
    timerWrite(timer, 0);
    timerAlarmEnable(timer);

    pinMode(config::display::columns_clk, OUTPUT);
    pinMode(config::display::columns_data, OUTPUT);
    pinMode(config::display::columns_latch, OUTPUT);
    pinMode(config::display::columns_oe, OUTPUT);

    pinMode(config::display::rows_clk, OUTPUT);
    pinMode(config::display::rows_data, OUTPUT);
    pinMode(config::display::rows_latch, OUTPUT);
    pinMode(config::display::rows_oe, OUTPUT);

    ROW_OE_HIGH();

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
    if (value > 31)
        value = 31;
    abstract_buffer[x][y] = value;
}

void Display::setNewRefreshRate(uint8_t refresh_freq_hz)
{
    double frame_period_ms = 1000.0 / refresh_freq_hz;
    double smallest_bitplane_row_refresh_us =
        frame_period_ms * 1000.0 / 31.0 / 32.0;

    ticks_per_row_refresh = smallest_bitplane_row_refresh_us / 0.1;
}

void Display::setBrightness(float _brightness)
{
    if(_brightness < 0) _brightness = 0;
    if(_brightness > 1.0f) _brightness = 1.0f;

    modified_ticks_per_row = ticks_per_row_refresh * _brightness;

    if(modified_ticks_per_row < 20)
    {
        modified_ticks_per_row = 20;
    }
}

float Display::getBrightness()
{
    return (float)modified_ticks_per_row / (float)ticks_per_row_refresh;
}

void Display::buildBitPlanes()
{
    if (build_bitplane_ready)
        return;

    int m, which_buff;

    for (byte i = 0; i < 5; i++) // each bitplanes loop
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
    if (build_bitplane_ready)
    {
        build_bitplane_ready = false;
        swapBitplaneBuffer();
    }
}

void IRAM_ATTR Display::refresh_row(int row)
{
    ROW_LATCH_LOW();
    ROW_CLK_LOW();

    for (byte i = 0; i < 4; i++)
    {
        buff_rows[i] = 0;
    }

    int pr = map_y[row]; // physical row
    int which_buff = (pr - (pr % 8)) / 8;
    buff_rows[which_buff] = buff_rows[which_buff] | (1 << (pr % 8));

    for (size_t i = 0; i < 4; i++)
    {

        for (uint8_t j = 0; j < 8; j++)
        {
            if (buff_rows[i] & (1 << j))
            {
                ROW_DATA_LOW();
            }
            else
            {
                ROW_DATA_HIGH();
            }

            // Tiny inline toggle for the clock
            ROW_CLK_HIGH();
            ROW_CLK_LOW();
        }
    }

    ROW_LATCH_HIGH();
    ROW_LATCH_LOW();

    ROW_OE_LOW();
    COL_OE_LOW();
}

void IRAM_ATTR Display::refresh_cols(int current_row, int current_bitplane)
{
    COL_OE_HIGH();
    ROW_OE_HIGH();

    COL_LATCH_LOW();
    COL_CLK_LOW();

    uint8_t t;

    for (byte i = 0; i < 6; i++)
    {
        t = ptr_ready_bitplane[current_bitplane][current_row][i];

        /* 0 - turned off, 1 - turned on*/

        for (uint8_t i = 0; i < 8; i++)
        {
            if (t & (1 << i))
            {
                COL_DATA_HIGH();
            }
            else
            {
                COL_DATA_LOW();
            }

            COL_CLK_HIGH();
            COL_CLK_LOW();
        }
    }

    COL_LATCH_HIGH();
    COL_LATCH_LOW();
}

void IRAM_ATTR Display::refreshISR()
{
    instance->refresh_cols(instance->current_row, instance->current_bitplane);

    instance->refresh_row(instance->current_row);

    instance->current_row++;

    if (instance->current_row >= 32)
    {
        instance->current_row = 0;
        instance->current_bitplane++;
        if (instance->current_bitplane > 4)
        {
            instance->current_bitplane = 0;
            instance->iram_refresh_finished();
        }
    }

    int next_alarm_ticks = instance->modified_ticks_per_row * (1 << instance->current_bitplane);

    timerAlarmWrite(instance->timer, next_alarm_ticks, true);
}