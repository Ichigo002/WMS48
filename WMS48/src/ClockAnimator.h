#ifndef CLOCK_ANIMATOR_H
#define CLOCK_ANIMATOR_H

#include "Graphics.h"
#include "UnixTimestampFuncs.h"
#include "TextAnimator.h"
#include <math.h>

#define ANALOG_CENTER_X WIDTH / 2
#define ANALOG_CENTER_Y HEIGHT / 2
#define ANALOG_RADIUS 15

enum ClockMode {
    DIGITAL_HH_MM = 0,
    DIGITAL_HH_MM_SS = 1,
    ANALOG_ = 2,
};

struct ClockSettings {
    ClockMode mode = ClockMode::ANALOG_;
    int start_pos_x = 0;
    int start_pos_y = 0;
    bool hidden = false;
    bool blinking_colon = true;
};

struct ClockHand {
        int x;
        int y;
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
    void updateDigital();
    void updateAnalog();

    void calculateClkHandPos(ClockHand& hand, int radius, float percent_of_wheel);

    void drawColon(int x, int y, Graphics& g);

    void drawDigital(Graphics& g);
    void drawAnalog(Graphics& g);

private:
    ClockSettings* s;
    _TextParameters* t;

    time_t raw_time;
    struct tm* time_info;

    ClockHand hour_hand;
    ClockHand min_hand;
    ClockHand sec_hand;

    String str_hh, str_mm, str_ss; 

};


#endif