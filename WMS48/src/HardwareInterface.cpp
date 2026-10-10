#include "HardwareInterface.h"

HardwareInterface::HardwareInterface(/* args */)
{
}

HardwareInterface::~HardwareInterface()
{
}

void HardwareInterface::setup()
{
    pinMode(config::pin_led, OUTPUT);
    pinMode(config::bluetooth_btn, INPUT);

    pinMode(config::motion_sensor, INPUT);
}

void HardwareInterface::update()
{

}

void HardwareInterface::turnBuiltInLED(bool v)
{
    digitalWrite(config::pin_led, v);
}

bool HardwareInterface::isButtonBTPressed()
{
    return digitalRead(config::bluetooth_btn) == LOW;
}

bool HardwareInterface::getMovementSensorStatus()
{
    return digitalRead(config::motion_sensor);
}

float HardwareInterface::getLuxValue()
{
    return 0.0f;
}
