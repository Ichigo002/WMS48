#include "TextScene.h"

TextScene::TextScene()
    : Scene(SceneIDs::TEXT_SCENE)
{
}

TextScene::~TextScene()
{
}

void TextScene::setup()
{
}

void TextScene::onEnter()
{
}

void TextScene::onExit()
{
}

void TextScene::update(float deltaTime)
{
}

void TextScene::draw(Graphics &g)
{
}

void TextScene::onCommand(const uint8_t* data, size_t n)
{
    Serial.println("ONCOMMAND WORKING...");
    ByteReader r(data, n);

    uint8_t op;
    String s;
    if(!r.u8(op)) return;

    switch (op)
    {
    case BLE_CMD_SCENE::OP_SET_TEXT:
        r.string(s, n-1);
        Serial.println(s);
        break;
    
    default:
        break;
    }
    
}
