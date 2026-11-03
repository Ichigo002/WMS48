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

/*
BleServer Bridge is a brdige between smartphone (client) and this esp32 (server). It creates BLE connection
and forwards all callbacks. 

REMEMBER! All Events should be assigned before calling begin(...) method, any changes to event methods won't be applied.

*/
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

    std::function<void()> onConnectEvent;
    std::function<void()> OnDisconnectEvent;

    // group of all characteristics in BLE connection.
    Characteristics chars;
private:

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
public:
    std::function<void()> onConnectCb;
    std::function<void()> OnDisconnectCb;

    void onConnect(BLEServer *server)
    {
        if(onConnectCb)
            onConnectCb();
    }
    void onDisconnect(BLEServer *server)
    {
        if(OnDisconnectCb)
            OnDisconnectCb();
        server->startAdvertising();
    }
};

#endif