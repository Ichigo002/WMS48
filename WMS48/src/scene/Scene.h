#ifndef SCENE_H
#define SCENE_H

#include "graphics/Graphics.h"
#include "graphics/fonts/FontManager.h"

class Scene
{
public:
    Scene(const int id, FontManager& font_mgr) : ID(id), font_mgr(font_mgr) { }
    virtual ~Scene() = default;

    virtual void setup() = 0;

    virtual void onEnter() = 0;
    virtual void onExit() = 0;
    
    virtual void update(float deltaTime) = 0;
    virtual void draw(Graphics& g) = 0;

    virtual void onCommand(const uint8_t* data, size_t n) = 0;

    const int ID;
    FontManager& font_mgr;
};


#endif