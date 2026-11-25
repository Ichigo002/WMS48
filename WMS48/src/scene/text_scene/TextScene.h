#ifndef TEXT_SCENE_H
#define TEXT_SCENE_H

#include "scene/Scene.h"
#include "ByteReader.h"
#include "BLE/Protocol.h"
#include <Arduino.h>

class TextScene : public Scene
{
public:
    TextScene();
    ~TextScene() override;

    virtual void setup();

    virtual void onEnter();
    virtual void onExit();
    
    virtual void update(float deltaTime);
    virtual void draw(Graphics& g);

    virtual void onCommand(const uint8_t* data, size_t n);

};
#endif