#ifndef TEXT_ANIMATOR_H
#define TEXT_ANIMATOR_H

#include "Graphics.h"

#define WIDTH 48
#define HEIGHT 32

struct _TextParameters
{
    String text = "Undefined";
    Font* font = nullptr;
    int font_size = 1;
    uint8_t brightness = 32;
    int text_spacing = 1;
};

enum AnimMode {
    LOOP = 0,
    SINGLE = 2,
    PING_PONG_OUTSIDE = 3,
    PING_PONG_INSIDE = 4,
};

struct _AnimParameters
{
    int start_pos_x = 0;
    int start_pos_y = 0;

    float speed_x = 1;
    float speed_y = 0;

    AnimMode animation_mode = AnimMode::LOOP;
};

class TextAnimator
{
public:
    TextAnimator();
    ~TextAnimator();

    //use to modify text settings
    _TextParameters text_settings;

    //use to modify aniamtion settings
    _AnimParameters anim_settings;
    


    void update(float deltaTime);
    void draw(Graphics& g);

    void updateOnlySpeedParameter(float sx, float sy);

    void start();
    void restart();

    void stop();
    
    void pause();
    void unpause();

    bool isAnimationPlaying();
    bool isAnimationStopped();
    bool isAnimationPaused();
private:
    int initSettings();

private:
    _TextParameters* t;
    _AnimParameters* a;

    // unit: speed: pixels per second
    float pos_x, pos_y;
    float prev_x, prev_y;
    float speed_x, speed_y;

    int txt_w, txt_h;

    bool is_playing;
    bool is_paused;
};

#endif