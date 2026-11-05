#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "graphics/Graphics.h"
#include "Scene.h"
#include "BLE/Protocol.h"
#include <vector>

class SceneManager
{
public:
    SceneManager();
    ~SceneManager();

    void pushNewScene(Scene *s);

    void switchScene(int newId);


    Scene* getCurrentScene();
    int getCurrentSceneID();

    void setup();
    void update(float deltaTime);
    void draw(Graphics& g);
    
    void onCommandScene(const uint8_t* d, size_t n);

private:
    Scene* current;

    std::vector<Scene*> scene_list;

};




#endif