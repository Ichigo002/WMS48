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

    std::function<void(const uint8_t *, size_t)> onWriteSceneIndex;
    std::function<void(const uint8_t *, size_t)> onReadSceneIndex;

    std::function<void(const uint8_t *, size_t)> onWriteCommandScene;
    std::function<void(const uint8_t *, size_t)> onWriteCommand;

    std::function<void(const uint8_t *, size_t)> onWriteUnixTime;
    std::function<void(const uint8_t *, size_t)> onReadUnixTime;

private:
    Characteristics chars;

    void CreateCharacteristics(BLEService *pService);
    void setCharacteristicsCallbacks();

    class CharsSceneIndexCb : public BLECharacteristicCallbacks
    {
    public:
        std::function<void(const uint8_t *, size_t)> onWriteCb;
        std::function<void(const uint8_t *, size_t)> onReadCb;

        void onWrite(BLECharacteristic *pCharacteristic) override
        {
            if (onWriteCb)
                onWriteCb(pCharacteristic->getData(), pCharacteristic->getLength());
        }

        void onRead(BLECharacteristic *pCharacteristic) override
        {
            if (onReadCb)
                onReadCb(pCharacteristic->getData(), pCharacteristic->getLength());
        }
    };

    class CharsCommandSceneCb : public BLECharacteristicCallbacks
    {
    public:
        std::function<void(const uint8_t *, size_t)> onWriteCb;

        void onWrite(BLECharacteristic *pCharacteristic) override
        {
            if (onWriteCb)
                onWriteCb(pCharacteristic->getData(), pCharacteristic->getLength());
        }
    };

    class CharsCommandCb : public BLECharacteristicCallbacks
    {
    public:
        std::function<void(const uint8_t *, size_t)> onWriteCb;

        void onWrite(BLECharacteristic *pCharacteristic) override
        {
            if (onWriteCb)
                onWriteCb(pCharacteristic->getData(), pCharacteristic->getLength());
        }
    };

    class CharsUnixTimeCb : public BLECharacteristicCallbacks
    {
    public:
        std::function<void(const uint8_t *, size_t)> onWriteCb;
        std::function<void(const uint8_t *, size_t)> onReadCb;

        void onWrite(BLECharacteristic *pCharacteristic) override
        {
            if (onWriteCb)
                onWriteCb(pCharacteristic->getData(), pCharacteristic->getLength());
        }

        void onRead(BLECharacteristic *pCharacteristic) override
        {
            if (onReadCb)
                onReadCb(pCharacteristic->getData(), pCharacteristic->getLength());
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