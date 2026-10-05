#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include "config.cpp"

class Display
{
public:
    Display();
    ~Display();

    void setup(uint8_t refresh_freq_hz);

    void update();
    
    void setPixelRaw(u_int x, u_int y, uint8_t value);

    volatile double refresh_time, last_time;

protected:
    void buildBitPlanes();

    void IRAM_ATTR fastShiftOut(uint8_t val);

    void IRAM_ATTR swapBitplaneBuffer();

    void IRAM_ATTR iram_refresh_finished();

    void IRAM_ATTR refresh_row(int row);
    void IRAM_ATTR refresh_cols(int current_row, int current_bitplane);

    hw_timer_t *timer = NULL;
    static Display *instance;

    volatile bool refresh_finished = false;
    volatile char current_row = 0;
    volatile char current_bitplane = 0;

    static void IRAM_ATTR refreshISR();

protected:
    volatile bool build_bitplane_ready = false;
    uint8_t buff_rows[4];

    volatile uint8_t (*ptr_rebuild_bitplane)[32][6] = bitplanes_A;
    volatile uint8_t (*ptr_ready_bitplane)[32][6] = bitplanes_B;

    volatile uint8_t bitplanes_A[8][32][6]; // 8 bitplanes, [bitplane][rows][columns raw byte]
    volatile uint8_t bitplanes_B[8][32][6]; // 8 bitplanes, [bitplane][rows][columns raw byte]

    uint8_t abstract_buffer[48][32]; // [x][y]
    /*
        00000000 00000000 00000000 00000000 00000000 00000000  0
        00000000 00000000 00000000 00000000 00000000 00000000  .
        .                                                      .
        .                                                      .
        .                                                      32
        0 . . .                                              48
    */

private:
    // map abstract coordinates x to physical pins on display
    int map_x[48] =
        {
            0, 2, 4, 6, 8, 10, 12, 14,
            16, 18, 20, 22, 24, 26, 28, 30,
            32, 34, 36, 38, 40, 42, 44, 46,
            23, 21, 19, 17, 15, 13, 11, 9,
            7, 5, 3, 1, 47, 45, 43, 41,
            39, 37, 35, 33, 31, 29, 27, 25};

    int map_y[32] =
        {
            24, 25, 26, 27, 28, 29, 30, 31,
            16, 17, 18, 19, 20, 21, 22, 23,
            8, 9, 10, 11, 12, 13, 14, 15,
            0, 1, 2, 3, 4, 5, 6, 7};
};

#endif
