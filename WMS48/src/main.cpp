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

  Serial.println(display.refresh_time);

  if (Serial.available() != 0)
  {
    int x = Serial.parseInt();
    int y = Serial.parseInt();
    int v = Serial.parseInt();

    if (x > 47 || y > 31 || x < 0 || y < 0 || v < 0 || v > 255)
    {
      Serial.println("VALUES OUT OF RANGE");
    }
    else
    {
      uint8_t brightness = static_cast<uint8_t>(v);

      Serial.printf("Pixel[%d][%d] = %hhu\n", x, y, brightness);

      display.setPixelRaw(x, y, brightness);
    }

    for (size_t i = 0; i < 20; i++)
    {
      display.setPixelRaw(4, i, 255);
      display.setPixelRaw(7, i, 255);
      display.setPixelRaw(5, 10, 255);
      display.setPixelRaw(6, 10, 255);
    }
    
  }

  display.update();

  // display.refresh();
  //  if(millis() - timec > 200)
  //    {
  //      timec = millis();
  //      if(k>48)
  //      {
  //        k=0;
  //        y++;
  //      }
  //      if(y>32)
  //      {
  //        y = k = 0;
  //      }
  //      display.setPixelRaw(k, y, 0xFF);
  //      k++;

  //   }
}