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

    Wire.begin();

    if (veml.begin() == false)
    {
        
        while (1)
        {
            Serial.println("Unable to communicate with the VEML7700. Please check the wiring. Freezing...");
        }
    }
    veml.setIntegrationTime(VEML7700_INTEGRATION_50ms);
    veml.setSensitivityMode(VEML7700_SENSITIVITY_x2);
    veml.setPersistenceProtect(VEML7700_PERSISTENCE_4);
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
    return veml.getLux();
}
