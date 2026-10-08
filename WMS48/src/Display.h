#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include "config.cpp"

/*
frame rate = 60Hz
frame period = 1/60 = 16.67 ms
average ISR period: 16.67 / 5 bitplanes = 3.33ms

timer divider: 8
total clock esp32: 80MHz
80 / 8 = 10MHz
1 tick = 0.1us

16.67 / 31 = 0.53 ms = 530us
HOWEVER we need to refresh all 32 rows too,
530us / 32 = 17,6 us per row

ticks per sohrtest isr period = 17,6us/0.1us = 176 ticks


*/

/*
 Software interface dealing with hardware.
 It is Display controller.
 It allows simply to control every led on display

 ABSTRAT MAP OF PIXEL

    00000000 00000000 00000000 00000000 00000000 00000000  0
    00000000 00000000 00000000 00000000 00000000 00000000  .
    .                                                      .
    .                                                      .
    .                                                      31
    0 . . .                                              47

*/
class Display
{
public:
    Display();
    ~Display();

    // call it in thesetup function of program
    void setup(uint8_t refresh_freq_hz);

    // call it in the main loop of program
    void update();

    // Turn on pixel (x,y)
    // value - value between 0-31 sets brightness of individual pixel independently
    void setPixelRaw(u_int x, u_int y, uint8_t value);

    // Clears abstract buffer
    void clear();

    // changes refresh rate. do not require restarting display
    void setNewRefreshRate(uint8_t refresh_freq_hz);

    // 0 - dark, 1 - bright
    void setBrightness(float _brightness);
    float getBrightness();

private:
    void buildBitPlanes();

    // swaps bitplanes buffers A->B, B->A
    void IRAM_ATTR swapBitplaneBuffer();

    // checks if bitplane building process is finished before swap to avoid ghosting
    void IRAM_ATTR iram_refresh_finished();

    void IRAM_ATTR refresh_row(int row);
    void IRAM_ATTR refresh_cols(int current_row, int current_bitplane);

    // CRITICAL TIMER used for refreshing.
    hw_timer_t *timer = NULL;

    static Display *instance;

    volatile bool refresh_finished = false;
    volatile bool build_bitplane_ready = false;

    volatile char current_row = 0;
    volatile char current_bitplane = 0;

    // Begginning of refresh is here :P
    static void IRAM_ATTR refreshISR();

    // ticks_per_row_refresh multiplied by total brightness level of display.
    volatile int modified_ticks_per_row;
    // raw base of shortest period for refreshing a row
    int ticks_per_row_refresh;

    uint8_t buff_rows[4];

    // pointers to 2 buffers
    volatile uint8_t (*ptr_rebuild_bitplane)[32][6] = bitplanes_A;
    volatile uint8_t (*ptr_ready_bitplane)[32][6] = bitplanes_B;

    volatile uint8_t bitplanes_A[5][32][6]; // 5 bitplanes, [bitplane][rows][columns raw byte]
    volatile uint8_t bitplanes_B[5][32][6]; // 5 bitplanes, [bitplane][rows][columns raw byte]

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
    // map abstract coordinates x & y to physical pins on display
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
