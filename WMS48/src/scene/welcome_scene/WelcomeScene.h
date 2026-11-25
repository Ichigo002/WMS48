#ifndef WELCOME_SCENE_H
#define WELCOME_SCENE_H

#include "scene/Scene.h"
#include "ByteReader.h"
#include "BLE/Protocol.h"
#include "TextAnimator.h"
#include <Arduino.h>

class WelcomeScene : public Scene
{
public:
    WelcomeScene(FontManager& font_mgr);
    ~WelcomeScene() override;

    virtual void setup();

    virtual void onEnter();
    virtual void onExit();
    
    virtual void update(float deltaTime);
    virtual void draw(Graphics& g);

    virtual void onCommand(const uint8_t* data, size_t n);

private:
    TextAnimator animator;
    TextAnimator animator2;


};
#endif