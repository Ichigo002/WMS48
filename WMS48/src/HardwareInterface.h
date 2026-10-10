#ifndef HARDWARE_INTERFACE_H
#define HARDWARE_INTERFACE_H

#include <Arduino.h>
#include "config.cpp"

class HardwareInterface
{
public:
    HardwareInterface();
    ~HardwareInterface();

    void setup();
    void update();

    // turn on or off built in led at the back of display
    void turnBuiltInLED(bool v);

    // returns true if Button was pressed
    bool isButtonBTPressed();

    // returns current status is anyone moving in front of display
    bool getMovementSensorStatus();

    // returns value of lux from Veml7700 sensor
    float getLuxValue();
private:

    bool is_bt_pressed;
    bool is_bt_up;

};



#endif