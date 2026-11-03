#ifndef BLE_SERVICE_H
#define BLE_SERVICE_H

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <functional>

struct Characteristics
{
    BLECharacteristic *scene_index;
    BLECharacteristic *command_scene;
    BLECharacteristic *command;
    BLECharacteristic *response;
    BLECharacteristic *event;
    BLECharacteristic *unix_time;
};

class BleServerBridge
{
public:
    BleServerBridge(/* args */);
    ~BleServerBridge();

    void begin(char *device_name);

    std::function<void(const uint8_t*, size_t)> onWriteCommandScene;

private:
    Characteristics chars;

    class CharsCommandSceneCb : public BLECharacteristicCallbacks
    {
    public:
        std::function<void(const uint8_t*, size_t)> handler;

        void onWrite(BLECharacteristic *pCharacteristic) override {
            if(handler)
                handler(pCharacteristic->getData(), pCharacteristic->getLength());
        }
    };
};

class ServerCb : public BLEServerCallbacks
{
    void onConnect(BLEServer *server)
    {
        // phone connected
    }
    void onDisconnect(BLEServer *server)
    {
        // phone left session, start advertising
        server->startAdvertising();
    }
};

#endif