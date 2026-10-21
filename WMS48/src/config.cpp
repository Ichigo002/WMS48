#ifndef CONFIG_H
#define CONFIG_H

#define WIDTH 48
#define HEIGHT 32
#define MAX_BRIGHTNESS 0b11111
#define MIN_BRIGHTNESS 0

namespace config
{
    namespace display
    {
        constexpr int columns_clk = 25;
        constexpr int columns_latch = 27;
        constexpr int columns_data = 33;
        constexpr int columns_oe = 32;

        constexpr int rows_clk = 2;
        constexpr int rows_latch = 5;
        constexpr int rows_data = 18;
        constexpr int rows_oe = 17;
    }

    constexpr int pin_led = 23;
    constexpr int bluetooth_btn = 34;
    constexpr int motion_sensor = 19;

    constexpr int refresh_rate_hz = 60;
}

#endif