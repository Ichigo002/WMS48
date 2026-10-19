#include "TextAnimator.h"

TextAnimator::TextAnimator()
{
    t = &text_settings;
    a = &anim_settings;
}

TextAnimator::~TextAnimator()
{
}

void TextAnimator::update(float deltaTime)
{
    if(is_paused || !is_playing)
        return;
    
    if(a->animation_mode == AnimMode::SINGLE)
    {
        if ((a->speed_x > 0 && pos_x > WIDTH+1) ||
        (a->speed_x < 0 && pos_x + txt_w+1 < 0) ||
        (a->speed_y > 0 && pos_y > HEIGHT+1) ||
        (a->speed_y < 0 && pos_y + txt_h+1 < 0))
        {
            stop();
            return;
        }
    }
    if(a->animation_mode == AnimMode::LOOP) 
    {
         if (a->speed_x > 0 && pos_x > WIDTH) // right edge
        {
            pos_x = -txt_w;
        }
        if (a->speed_x < 0 && pos_x + txt_w+1 < 0) // left edge
        {
            pos_x = WIDTH;
        }
        if (a->speed_y > 0 && pos_y > HEIGHT) // bottom edge
        {
            pos_y = -txt_h;
        }
        if (a->speed_y < 0 && pos_y + txt_h < 0) // top edge
        {
            pos_y = HEIGHT;
        }
        
    }
    if(a->animation_mode == AnimMode::PING_PONG_OUTSIDE)
    {
        if (a->speed_x > 0 && pos_x > WIDTH) // right edge
        {
           a->speed_x *= -1;
        }
        if (a->speed_x < 0 && pos_x + txt_w+1 < 0) // left edge
        {
            a->speed_x *= -1;
        }
        if (a->speed_y > 0 && pos_y > HEIGHT) // bottom edge
        {
           a->speed_y *= -1;
        }
        if (a->speed_y < 0 && pos_y + txt_h < 0) // top edge
        {
           a->speed_y *= -1;
        }
    }
    if(a->animation_mode == AnimMode::PING_PONG_INSIDE)
    {
        if (a->speed_x > 0 && pos_x + txt_w >= WIDTH) // right edge
        {
           a->speed_x *= -1;
        }
        if (a->speed_x < 0 && pos_x < 0) // left edge
        {
            a->speed_x *= -1;
        }
        if (a->speed_y > 0 && pos_y + txt_h > HEIGHT) // bottom edge
        {
           a->speed_y *= -1;
        }
        if (a->speed_y < 0 && pos_y < 0) // top edge
        {
           a->speed_y *= -1;
        }
    }

    prev_x = pos_x;
    prev_y = pos_y;

    pos_x += a->speed_x * deltaTime;
    pos_y += a->speed_y * deltaTime;
}

void TextAnimator::draw(Graphics &g)
{
    if(is_paused || !is_playing)
        return;

    g.drawFilledRect(prev_x, prev_y, txt_w, txt_h, 0);
    g.drawText(pos_x, pos_y, t->text, *t->font, t->font_size, t->brightness, t->text_spacing);
}

int TextAnimator::initSettings()
{
    if(t->font == nullptr)
    {
        Serial.println("Font* font is nullptr in TextAnimator.text_params, can't start aniamtion");
        return -1;
    }

    pos_x = a->start_pos_x;
    pos_y = a->start_pos_y;

    txt_w = t->text.length() * t->font_size * (t->font->getCharacterWidth() + t->text_spacing);
    txt_h = t->font_size * t->font->getCharacterHeight();
    return 0;
}

void TextAnimator::start()
{
    if(!is_playing && !is_paused)
    {
        if(initSettings() != 0)
            return;
    }
    is_playing = true;
}

void TextAnimator::restart()
{
    is_playing = is_paused = false;
    start();
}

void TextAnimator::pause()
{
    is_paused = true;
}

void TextAnimator::unpause()
{
    is_paused = false;
}

bool TextAnimator::isAnimationPlaying()
{
    return is_playing;
}

bool TextAnimator::isAnimationStopped()
{
    return (!is_playing && !is_paused);
}

bool TextAnimator::isAnimationPaused()
{
    return is_paused;
}

void TextAnimator::stop()
{
    is_playing = false;
    is_paused = false;
}

