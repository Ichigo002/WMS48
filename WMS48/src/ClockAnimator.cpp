#include "ClockAnimator.h"

ClockAnimator::ClockAnimator(/* args */)
{
    s = &settings;
    t = &text_settings;
}

ClockAnimator::~ClockAnimator()
{
}

void ClockAnimator::update(float deltaTime)
{
    if (s->hidden)
        return;

    raw_time = getESP32Time_t();
    time_info = gmtime(&raw_time);

    if (s->mode == ClockMode::DIGITAL_HH_MM_SS || s->mode == ClockMode::DIGITAL_HH_MM)
    {
        str_hh = (time_info->tm_hour < 10 ? "0" : "");
        str_hh += time_info->tm_hour;

        str_mm = (time_info->tm_min < 10 ? "0" : "");
        str_mm += time_info->tm_min;

        str_ss = (time_info->tm_sec < 10 ? "0" : "");
        str_ss += time_info->tm_sec;
    }
}

void ClockAnimator::draw(Graphics &g)
{
    if (t->font == nullptr || s->hidden)
    {
        return;
    }

    if (s->mode == ClockMode::DIGITAL_HH_MM_SS || s->mode == ClockMode::DIGITAL_HH_MM)
    {
        int w = Graphics::getTextWidth(str_hh, *t->font, t->font_size, t->text_spacing) +
                Graphics::getTextWidth(str_mm, *t->font, t->font_size, t->text_spacing) +
                t->font_size * 4; // colon width

        if (s->mode == ClockMode::DIGITAL_HH_MM_SS)
            w += Graphics::getTextWidth(str_ss, *t->font, t->font_size, t->text_spacing) +
                 t->font_size * 4; // second colon

        // CLEAR AREA
        g.drawFilledRect(s->start_pos_x, s->start_pos_y, w, t->font->getCharacterHeight(), 0);

        // DRAW HOURS
        g.drawText(s->start_pos_x, s->start_pos_y, str_hh, *t->font, t->font_size, t->brightness, t->text_spacing);

        int start_str_mm = s->start_pos_x + Graphics::getTextWidth(str_hh, *t->font, t->font_size, t->text_spacing) +
                           4 * t->font_size;

        // DRAW MINUTES
        g.drawText(start_str_mm, s->start_pos_y, str_mm, *t->font, t->font_size, t->brightness, t->text_spacing);

        // DRAW TOP SPLITTER
        if (s->blinking_colon && s->mode == DIGITAL_HH_MM && time_info->tm_sec % 2 == 0)
        {
            return;
        }

        drawColon(start_str_mm - 4 * t->font_size, s->start_pos_y, g);

        if (s->mode == ClockMode::DIGITAL_HH_MM_SS)
        {
            // DRAW SECOND COLON
            start_str_mm += Graphics::getTextWidth(str_hh, *t->font, t->font_size, t->text_spacing);
            drawColon(start_str_mm, s->start_pos_y, g);

            start_str_mm += 4 * t->font_size;
            
            g.drawText(start_str_mm, s->start_pos_y, str_ss, *t->font, t->font_size, t->brightness, t->text_spacing);

        }
        
    }
}

void ClockAnimator::drawColon(int x, int y, Graphics &g)
{
    int x1 = x + t->font_size;
    int y1 = y + t->font_size;
    g.drawFilledRect(x1, y1, 2 * t->font_size, 2 * t->font_size, t->brightness);

    // DRAW BOTTOM SPLITTER
    y1 += 3 * t->font_size;
    g.drawFilledRect(x1, y1, 2 * t->font_size, 2 * t->font_size, t->brightness);
}
