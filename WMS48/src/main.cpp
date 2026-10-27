#include <Arduino.h>
#include <BluetoothSerial.h>
#include <Wire.h>
#include <SPI.h>
#include <SparkFun_VEML7700_Arduino_Library.h> // Click here to get the library: http://librarymanager/All#SparkFun_VEML7700
#include "Display.h"
#include "Graphics.h"
#include "DefaultFont.h"
#include "SerialCmdsParser.h"
#include "HardwareInterface.h"
#include "TextAnimator.h"
#include "ClockAnimator.h"

Display display;
Graphics graphics(display);
DefaultFont defaultFont;
HardwareInterface hardwareInterface;
TextAnimator cmd_txt;
ClockAnimator cmd_clk;

SerialCmdsParser cmdParser(graphics, display, defaultFont, hardwareInterface, cmd_txt, cmd_clk);
BluetoothSerial bl;

// void btAdvertisedDeviceFound(BTAdvertisedDevice *pDevice) used for server BT
// {
//   Serial.printf("Found a device asynchronously: %s\n", pDevice->toString().c_str());
// }

void setup()
{
  bl.begin("ESP32-WMS48");
  //bl.discoverAsync(btAdvertisedDeviceFound); used for server BT
  // Initialize your setup code here
  display.setup(config::refresh_rate_hz);
  hardwareInterface.setup();

  Serial.begin(115200);
  // Serial.printf("ESP-IDF version: %s\n", ESP.getSdkVersion());
  //   Serial.printf("Arduino version: %d.%d.%d\n",
  //                 ESP_ARDUINO_VERSION_MAJOR,
  //                 ESP_ARDUINO_VERSION_MINOR,
  //                 ESP_ARDUINO_VERSION_PATCH);
}

uint32_t previousTime = 0;
float deltaTime;

void loop()
{

  Stream& s = bl;
  uint32_t currentTime = millis();
  deltaTime = (currentTime - previousTime) / 1000.0f; // seconds
  previousTime = currentTime;

  cmd_txt.update(deltaTime);
  cmd_clk.update(deltaTime);

  //cmdParser.updateSerial();
  // if(Serial.available()) it is bluetooth classic!
  // {
  //   bl.write(Serial.read());
  // }

  // if(bl.available())
  // {
  //   Serial.write(bl.read());
  // }

  cmd_clk.draw(graphics);
  cmd_txt.draw(graphics);
  display.update();
}