#include "WelcomeScene.h"

WelcomeScene::WelcomeScene(FontManager& font_mgr)
    : Scene(SceneIDs::WELCOME_SCENE, font_mgr)
{
    animator.text_settings.font = &font_mgr.getFont(FONT_NATALIA);
    animator.text_settings.text = "WMS48";
    animator.anim_settings.animation_mode = AnimMode::SINGLE;

    animator2.text_settings.font = &font_mgr.getFont(FONT_NATALIA);
    animator2.text_settings.text = "Wiktor";
    animator2.anim_settings.animation_mode = AnimMode::SINGLE;

}

WelcomeScene::~WelcomeScene()
{
}

void WelcomeScene::setup()
{
    animator.anim_settings.speed_x = 0;
    animator.anim_settings.speed_y = -20;
    animator.anim_settings.start_pos_x = 8;
    animator.anim_settings.start_pos_y = 2*HEIGHT;
    

    animator2.anim_settings.speed_x = 0;
    animator2.anim_settings.speed_y = -20;
    animator2.anim_settings.start_pos_x = 9;
    animator2.anim_settings.start_pos_y = 2*HEIGHT + 9;
}

void WelcomeScene::onEnter()
{
    animator.start();
    animator2.start();
}

void WelcomeScene::onExit()
{
    animator.stop();
    animator2.stop();
}

void WelcomeScene::update(float deltaTime)
{
    animator.update(deltaTime);
    animator2.update(deltaTime);
}

void WelcomeScene::draw(Graphics &g)
{
    animator.draw(g);
    animator2.draw(g);
}

void WelcomeScene::onCommand(const uint8_t* data, size_t n)
{
    // ByteReader r(data, n);
    // uint8_t op;
    // if(!r.u8(op)) return;

    // switch (op)
    // {
    // case BLE_CMD_SCENE::OP_UPDATE_VALUES:
    //     int8_t v;
    //     if(r.i8(v))
    //     {
    //         speed_y = v;
    //         setup();
    //         onEnter();
    //     }
    //     r.skip(n-2);
    //     break;
    
    // default:
    //     break;
    // }
    
}
