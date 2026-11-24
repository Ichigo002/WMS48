#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <SparkFun_VEML7700_Arduino_Library.h> // Click here to get the library: http://librarymanager/All#SparkFun_VEML7700
#include "Display.h"
#include "graphics/Graphics.h"
#include "graphics/fonts/FontManager.h"
#include "SerialCmdsParser.h"
#include "HardwareInterface.h"
#include "TextAnimator.h"
#include "ClockAnimator.h"
#include "scene/SceneManager.h"
#include "scene/text_scene/TextScene.h"

#include "BLE/BleServerBridge.h"

// Uncomment line below in order to use Classic Serial sBluetooth
// #define USE_BT_CLASSIC

#ifdef USE_BT_CLASSIC
#include <BluetoothSerial.h>
#endif

BleServerBridge ble_server;

Display display;
FontManager font_mgr;
Graphics graphics(display, font_mgr.getFont(FONT_MONOSPACE));
HardwareInterface hardwareInterface;

SceneManager smgr;

/*=== SCENES ===*/
TextScene _TextScene;


/*=== END SCENES ===*/


TextAnimator cmd_txt;
ClockAnimator cmd_clk(font_mgr);

SerialCmdsParser cmdParser(graphics, display, font_mgr.getFont(FONT_MONOSPACE), hardwareInterface, cmd_txt, cmd_clk);



#ifdef USE_BT_CLASSIC
BluetoothSerial bl;
#endif

void pushNewScenes()
{
  smgr.pushNewScene(&_TextScene);
}

void handle_ble_server_events()
{
  ble_server.onWriteSceneIndex = [](const uint8_t *d, size_t n)
  {
    Serial.println("WRITE INDEX: ");
    Serial.println(*d);
    Serial.println(n);
  };

  ble_server.onWriteUnixTime = [](const uint8_t *d, size_t n)
  {
    Serial.println("HELLO THERE");
    cmd_txt.text_settings.text = "It works";
    cmd_txt.text_settings.font = &font_mgr.getFont(FONT_NATALIA);
    cmd_txt.start();
  };
}

void setup()
{
#ifdef USE_BT_CLASSIC
  bl.begin("ESP32-WMS48");
#endif

  display.setup(config::refresh_rate_hz);
  hardwareInterface.setup();
  pushNewScenes();

  Serial.begin(115200);

  handle_ble_server_events();

  ble_server.begin("WMS-48 NEW BORN");

  smgr.setup();

  smgr.switchScene(_TextScene.ID);
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
  smgr.update(deltaTime);

  cmdParser.processSerialIfAvailable(Serial);

#ifdef USE_BT_CLASSIC
  cmdParser.processSerialIfAvailable(bl);
#endif

  smgr.draw(graphics);
  cmd_clk.draw(graphics);
  cmd_txt.draw(graphics);
  display.update();
}