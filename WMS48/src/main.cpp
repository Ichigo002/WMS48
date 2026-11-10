#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <SparkFun_VEML7700_Arduino_Library.h> // Click here to get the library: http://librarymanager/All#SparkFun_VEML7700
#include "Display.h"
#include "graphics/Graphics.h"
#include "graphics/fonts/DefaultFont.h"
#include "SerialCmdsParser.h"
#include "HardwareInterface.h"
#include "TextAnimator.h"
#include "ClockAnimator.h"

#include "BLE/BleServerBridge.h"

// Uncomment line below in order to use Classic Serial sBluetooth
// #define USE_BT_CLASSIC

#ifdef USE_BT_CLASSIC
#include <BluetoothSerial.h>
#endif

Display display;
DefaultFont defaultFont;
Graphics graphics(display, defaultFont);
HardwareInterface hardwareInterface;
TextAnimator cmd_txt;
ClockAnimator cmd_clk;

SerialCmdsParser cmdParser(graphics, display, defaultFont, hardwareInterface, cmd_txt, cmd_clk);

BleServerBridge ble_server;

#ifdef USE_BT_CLASSIC
BluetoothSerial bl;
#endif

void setup()
{
#ifdef USE_BT_CLASSIC
  bl.begin("ESP32-WMS48");
#endif

  display.setup(config::refresh_rate_hz);
  hardwareInterface.setup();

  Serial.begin(115200);
  // Serial.printf("ESP-IDF version: %s\n", ESP.getSdkVersion());
  //   Serial.printf("Arduino version: %d.%d.%d\n",
  //                 ESP_ARDUINO_VERSION_MAJOR,
  //                 ESP_ARDUINO_VERSION_MINOR,
  //                 ESP_ARDUINO_VERSION_PATCH);

  ble_server.onWriteUnixTime = [](const uint8_t *d, size_t n)
  {
    Serial.println("HELLO THERE");
    cmd_txt.text_settings.text = "It works";
    cmd_txt.text_settings.font = &defaultFont;
    cmd_txt.start();
  };

  ble_server.begin("WMS-48 NEW BORN");
}

uint32_t previousTime = 0;
float deltaTime;

void loop()
{

  uint32_t currentTime = millis();
  deltaTime = (currentTime - previousTime) / 1000.0f; // seconds
  previousTime = currentTime;

  //cmd_txt.update(deltaTime);
  //cmd_clk.update(deltaTime);

  cmdParser.processSerialIfAvailable(Serial);

#ifdef USE_BT_CLASSIC
  cmdParser.processSerialIfAvailable(bl);
#endif

  graphics.drawText(0,16,"aaa",3);
  //cmd_clk.draw(graphics);
  //cmd_txt.draw(graphics);
  display.update();
}