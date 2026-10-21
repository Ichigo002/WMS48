#ifndef CLOCK_ANIMATOR_H
#define CLOCK_ANIMATOR_H

#include "Graphics.h"
#include "UnixTimestampFuncs.h"
#include "TextAnimator.h"

enum ClockMode {
    DIGITAL_HH_MM = 0,
    DIGITAL_HH_MM_SS = 1,
    ANALOG_ = 2,
};

struct ClockSettings {
    ClockMode mode = ClockMode::DIGITAL_HH_MM_SS;
    int start_pos_x = 0;
    int start_pos_y = 0;
    bool hidden = false;
    bool blinking_colon = true;
};

class ClockAnimator
{
public:
    ClockAnimator(/* args */);
    ~ClockAnimator();

    ClockSettings settings;
    _TextParameters text_settings;

    void update(float deltaTime);
    void draw(Graphics& g);

private:
    void drawColon(int x, int y, Graphics& g);

private:
    ClockSettings* s;
    _TextParameters* t;

    time_t raw_time;
    struct tm* time_info;

    String str_hh, str_mm, str_ss; 

};


#endif