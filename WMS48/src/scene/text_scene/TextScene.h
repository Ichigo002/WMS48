#ifndef TEXT_SCENE_H
#define TEXT_SCENE_H

#include "scene/Scene.h"
#include "BLE/Protocol.h"

class TextScene : public Scene
{
public:
    TextScene();
    ~TextScene();

    virtual void setup();

    virtual void onEnter();
    virtual void onExit();
    
    virtual void update(float deltaTime);
    virtual void draw(Graphics& g);

    virtual void onCommand();

};




#endif