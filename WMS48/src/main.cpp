#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <SparkFun_VEML7700_Arduino_Library.h> // Click here to get the library: http://librarymanager/All#SparkFun_VEML7700
#include "Display.h"

Display display;

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
                  
  /*for (size_t i = 0; i < 48; i++)
  {
    for (size_t j = 0; j < 32; j++)
    {
      display.setPixelRaw(i, j, 255);
    }

  }*/

  for (size_t j = 0; j < 3; j++)
  {
    
  
  
    for (size_t i = 0; i < 32; i++)
    {
      display.setPixelRaw(i, j, i);
    }
  }
    
}

void loop()
{


  if (Serial.available() != 0)
  {
    float x = Serial.parseFloat();

    display.setBrightness(x);
    Serial.println(display.getBrightness());
    
    // int y = Serial.parseInt();
    // int v = Serial.parseInt();

    // if (x > 47 || y > 31 || x < 0 || y < 0 || v < 0 || v > 255)
    // {
    //   Serial.println("VALUES OUT OF RANGE");
    // }
    // else
    // {
    //   uint8_t brightness = static_cast<uint8_t>(v);

    //   Serial.printf("Pixel[%d][%d] = %hhu\n", x, y, brightness);

    //   display.setPixelRaw(x, y, brightness);
    // }

    
    
  }

  

  display.update();
}