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
  /*for (size_t i = 0; i < 48; i++)
  {
    for (size_t j = 0; j < 32; j++)
    {
      display.setPixelRaw(i, j, 255);
    }
    
  }*/
  
}

void loop()
{

  if (Serial.available() != 0)
  {
    int value = Serial.parseInt();

    Serial.print("Pixel[");
    Serial.print(value);
    Serial.print("][0] = ");

      display.setPixelRaw(0, value, 0xFF);
      display.setPixelRaw(1, value, 0xFF);
      display.setPixelRaw(2, value, 0xFF);
      display.setPixelRaw(3, value, 0xFF);
      Serial.println("1\n");
  }

  //display.refresh();
  // if(millis() - timec > 200)
  //   {
  //     timec = millis();
  //     if(k>48)
  //     {
  //       k=0;
  //       y++;
  //     }
  //     if(y>32)
  //     {
  //       y = k = 0;
  //     }
  //     display.setPixelRaw(k, y, 0xFF);
  //     k++;

  //   }
}