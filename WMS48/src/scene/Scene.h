#ifndef SCENE_H
#define SCENE_H

#include "Graphics.h"

class Scene
{
public:
    Scene(const int id) : ID(id) { }
    virtual ~Scene() = 0;

    virtual void setup() = 0;

    virtual void onEnter() = 0;
    virtual void onExit() = 0;
    
    virtual void update(float deltaTime) = 0;
    virtual void draw(Graphics& g) = 0;

    virtual void onCommand() = 0;

    const int ID;
};



#endif