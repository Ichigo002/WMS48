#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <SparkFun_VEML7700_Arduino_Library.h> // Click here to get the library: http://librarymanager/All#SparkFun_VEML7700
#include "Display.h"
#include "Graphics.h"
#include "DefaultFont.h"
#include "SerialCommandsHandler.h"

Display display;
Graphics graphics(display);
DefaultFont defaultFont;

SerialCommandsHandler sch(graphics);

void setup()
{
  // Initialize your setup code here
  display.setup(config::refresh_rate_hz);

  Serial.begin(115200);
  Serial.println("Send command: x,y,v for pixel: ");
  Serial.printf("ESP-IDF version: %s\n", ESP.getSdkVersion());
    Serial.printf("Arduino version: %d.%d.%d\n",
                  ESP_ARDUINO_VERSION_MAJOR,
                  ESP_ARDUINO_VERSION_MINOR,
                  ESP_ARDUINO_VERSION_PATCH);

  
  
    
}

void loop()
{

  sch.updateSerial();
  
  display.update();
}