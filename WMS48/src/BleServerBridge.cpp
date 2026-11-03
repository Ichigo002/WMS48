#include "BleServerBridge.h"
#include "BleProtocol.h"

#include <Arduino.h>

BleServerBridge::BleServerBridge(/* args */)
{
}

BleServerBridge::~BleServerBridge()
{
}

void BleServerBridge::begin(char *device_name)
{
    BLEDevice::init(device_name);
    BLEServer *pServer = BLEDevice::createServer();
    
    pServer->setCallbacks(new ServerCb);

    /* BUILDING SERVICE */

    BLEService *pService = pServer->createService(BLE_UUIDs::WMS_SERVICE);

    chars.command =
        pService->createCharacteristic(BLE_UUIDs::COMMAND_CHAR, BLECharacteristic::PROPERTY_WRITE);

    chars.command_scene =
        pService->createCharacteristic(BLE_UUIDs::COMMAND_SCENE_CHAR, BLECharacteristic::PROPERTY_WRITE);

    CharsCommandSceneCb* c = new CharsCommandSceneCb();

    c->handler = onWriteCommandScene;

    chars.command_scene->setCallbacks(c);

    chars.event =
        pService->createCharacteristic(BLE_UUIDs::EVENT_CHAR, BLECharacteristic::PROPERTY_NOTIFY | BLECharacteristic::PROPERTY_READ);

    chars.response =
        pService->createCharacteristic(BLE_UUIDs::RESPONSE_CHAR, BLECharacteristic::PROPERTY_READ);

    chars.scene_index =
        pService->createCharacteristic(BLE_UUIDs::SCENE_INDEX_CHAR, BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_READ);

    chars.unix_time =
        pService->createCharacteristic(BLE_UUIDs::UNIX_TIME_CHAR, BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_READ);


        pService->start(); // it ends building service,

    /* Advertising */
    BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();

    pAdvertising->addServiceUUID(BLE_UUIDs::WMS_SERVICE);
    pAdvertising->setScanResponse(true);
    pAdvertising->setMinPreferred(0x06);
    pAdvertising->setMaxPreferred(0x12);

    BLEDevice::startAdvertising();
}
