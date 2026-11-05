#include "SceneManager.h"

SceneManager::SceneManager(/* args */)
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::pushNewScene(Scene *s)
{
    if (s)
        scene_list.push_back(s);
}

void SceneManager::switchScene(int newId)
{
    for (size_t i = 0; i < scene_list.size(); i++)
    {

        if (scene_list[i]->ID == newId)
        {
            if (current)
                current->onExit();
            current = scene_list[i];
            current->onEnter();
        }
        
    }
}

Scene *SceneManager::getCurrentScene()
{
    return current;
}

int SceneManager::getCurrentSceneID()
{
    if(!current)
        return SceneIDs::NULL_S;
    return current->ID;
}

void SceneManager::setup()
{
    for (size_t i = 0; i < scene_list.size(); i++)
    {
        scene_list[i]->setup();
    }
    
}

void SceneManager::update(float deltaTime)
{
    if(current)
    {
        current->update(deltaTime);
    }
}

void SceneManager::draw(Graphics &g)
{
    if(current)
    {
        current->draw(g);
    }
}

void SceneManager::onCommandScene(const uint8_t *d, size_t n)
{
    // TODO
}
