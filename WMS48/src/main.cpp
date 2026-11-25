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
#include "scene/welcome_scene/WelcomeScene.h"

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
TextScene _TextScene(font_mgr);
WelcomeScene _WelcomeScene(font_mgr);

/*=== END SCENES ===*/

/*=== SERIAL PARSER OBSCOLETE*/
//TextAnimator cmd_txt;
//ClockAnimator cmd_clk(font_mgr);
//SerialCmdsParser cmdParser(graphics, display, font_mgr.getFont(FONT_MONOSPACE), hardwareInterface, cmd_txt, cmd_clk);
/*=== END SERIAL ===*/

#ifdef USE_BT_CLASSIC
BluetoothSerial bl;
#endif

void pushNewScenes()
{
  smgr.pushNewScene(&_TextScene);
  smgr.pushNewScene(&_WelcomeScene);
}

void handle_ble_server_events()
{
  ble_server.onWriteSceneIndex = [](const uint8_t *d, size_t n)
  {
    ByteReader r(d, n);
    uint8_t id;
    if(r.u8(id))
    {
      smgr.switchScene(id);
    }
  };

  ble_server.onReadSceneIndex = [](BLECharacteristic *pCharacteristic)
  {
    uint8_t id = smgr.getCurrentSceneID();
    pCharacteristic->setValue(&id, 1);
  };

  ble_server.onWriteCommandScene = [](const uint8_t *d, size_t n)
  {
    smgr.onCommandScene(d, n);
  };

  ble_server.onWriteCommand = [](const uint8_t *d, size_t n)
  {
    // ???????????????????/
  };

  ble_server.onWriteUnixTime = [](const uint8_t *d, size_t n)
  {
    ByteReader r(d, n);
    uint32_t time;

    if(r.u32(time))
    {
      setESP32UnixTimeStamp(time);
    }
  };

  ble_server.onReadUnixTime = [](BLECharacteristic *pCharacteristic)
  {
    uint32_t t = getESP32Timestamp();
    pCharacteristic->setValue((uint8_t*)&t, 4);
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

  smgr.switchScene(_WelcomeScene.ID);
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
  smgr.update(deltaTime);

  //cmdParser.processSerialIfAvailable(Serial);

#ifdef USE_BT_CLASSIC
  cmdParser.processSerialIfAvailable(bl);
#endif

  smgr.draw(graphics);
  //cmd_clk.draw(graphics);
  //cmd_txt.draw(graphics);
  display.update();
}