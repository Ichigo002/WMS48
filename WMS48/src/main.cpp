#include <Arduino.h>
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

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

#define SERVICE_UUID "4b3e2482-b393-47b8-a01b-57eac3823be0"
#define CHARACTERISTIC_UUID "0bd5b399-f7b5-4d20-9f93-65b258f62150"


// Uncomment line below in order to use Classic Serial sBluetooth
//#define USE_BT_CLASSIC

#ifdef USE_BT_CLASSIC
#include <BluetoothSerial.h>
#endif

Display display;
Graphics graphics(display);
DefaultFont defaultFont;
HardwareInterface hardwareInterface;
TextAnimator cmd_txt;
ClockAnimator cmd_clk;

SerialCmdsParser cmdParser(graphics, display, defaultFont, hardwareInterface, cmd_txt, cmd_clk);

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

  BLEDevice::init("WMS-48 BLE Tech.");
  BLEServer* pServer = BLEDevice::createServer();

  /* BUILDING SERVICE */

  BLEService* pService = pServer->createService(SERVICE_UUID);

  BLECharacteristic *pcharacteristic = 
    pService->createCharacteristic(CHARACTERISTIC_UUID, BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE);

  pcharacteristic->setValue("Hello, I'm Wiktor and like hot cookies!");

  pService->start(); // it ends building service,


  /* Advertising */
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();

  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);
  pAdvertising->setMaxPreferred(0x12);

  BLEDevice::startAdvertising();

}

uint32_t previousTime = 0;
float deltaTime;

void loop()
{

  uint32_t currentTime = millis();
  deltaTime = (currentTime - previousTime) / 1000.0f; // seconds
  previousTime = currentTime;

  cmd_txt.update(deltaTime);
  cmd_clk.update(deltaTime);

  cmdParser.processSerialIfAvailable(Serial);

#ifdef USE_BT_CLASSIC
  cmdParser.processSerialIfAvailable(bl);
#endif
  

  cmd_clk.draw(graphics);
  cmd_txt.draw(graphics);
  display.update();
}