#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include "config.cpp"


class Display
{
public:
    Display();
    ~Display();

    void setup();
    void refresh();

    void setPixel(int x, int y, uint8_t value);
protected:
    void refresh_rows();
    void refresh_cols(int current_row);

protected:
    uint8_t buffer[48][32]; // [x][y]
    /*
        00000000 00000000 00000000 00000000 00000000 00000000  0
        00000000 00000000 00000000 00000000 00000000 00000000  .
        .                                                      .
        .                                                      .
        .                                                      32
        0 . . .                                              48
    */

private:
    short int current_hc595;
    short int refresh_row_counter;
};



#endif
