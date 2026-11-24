#include "ClockAnimator.h"

ClockAnimator::ClockAnimator(FontManager& font_mgr)
{
    s = &settings;
    font = &font_mgr.getFont(FONT_MONOSPACE);
    is_hidden = true;

}

ClockAnimator::~ClockAnimator()
{
}

void ClockAnimator::update(float deltaTime)
{
    if (is_hidden)
        return;

    raw_time = getESP32Time_t();
    time_info = localtime(&raw_time);

    if (s->mode == ClockMode::ANALOG_)
    {
        updateAnalog();
        return;
    }
    updateDigital();
}

void ClockAnimator::draw(Graphics &g)
{
    if (font == nullptr || is_hidden)
    {
        return;
    }

    if (s->mode == ClockMode::ANALOG_)
    {
        drawAnalog(g);
        return;
    }
    drawDigital(g);
}

void ClockAnimator::start()
{
    is_hidden = false;
}

void ClockAnimator::stop()
{
    is_hidden = true;
}

void ClockAnimator::updateDigital()
{
    str_hh = (time_info->tm_hour < 10 ? "0" : "");
    str_hh += time_info->tm_hour;

    str_mm = (time_info->tm_min < 10 ? "0" : "");
    str_mm += time_info->tm_min;

    str_ss = (time_info->tm_sec < 10 ? "0" : "");
    str_ss += time_info->tm_sec;
}

void ClockAnimator::updateAnalog()
{
    calculateClkHandPos(sec_hand, 14, (time_info->tm_sec + 1) / 60.0f);
    calculateClkHandPos(min_hand, 12, (time_info->tm_min + 1) / 60.0f);
    calculateClkHandPos(hour_hand, 7, ((time_info->tm_hour % 12) + 1) / 12.0f);
}

void ClockAnimator::calculateClkHandPos(ClockHand &hand, int radius, float percent_of_wheel)
{
    hand.x = ANALOG_CENTER_X - round(radius * cos(2 * 3.141 * (percent_of_wheel + 0.25f)));
    hand.y = ANALOG_CENTER_Y - round(radius * sin(2 * 3.141 * (percent_of_wheel + 0.25f)));

    if (hand.x > ANALOG_CENTER_X)
        hand.x++;
    if (hand.y > ANALOG_CENTER_Y)
        hand.y++;
}

void ClockAnimator::drawColon(int x, int y, Graphics &g)
{
    int x1 = x + font_size - 1;
    int y1 = y + font_size;
    g.drawFilledRect(x1, y1, 2 * font_size, 2 * font_size, brightness);

    // DRAW BOTTOM SPLITTER
    y1 += 3 * font_size;
    g.drawFilledRect(x1, y1, 2 * font_size, 2 * font_size, brightness);
}

void ClockAnimator::drawDigital(Graphics &g)
{
    int w = font->getTextWidth(str_hh) + font->getTextWidth(str_mm) + font_size * 4; // colon width

    if (s->mode == ClockMode::DIGITAL_HH_MM_SS)
        w += font->getTextWidth(str_ss) +
             font_size * 4; // second colon

    // CLEAR AREA
    g.drawFilledRect(s->start_pos_x, s->start_pos_y, w+font_size*2, font->getTextHeight("1"), 0);

    // DRAW HOURS
    g.drawText(s->start_pos_x, s->start_pos_y - font->max_Yoffset, str_hh, *font, font_size, brightness);

    int start_str_mm = s->start_pos_x + font->getTextWidth(str_hh) +
                       4 * font_size;

    // DRAW MINUTES
    g.drawText(start_str_mm, s->start_pos_y - font->max_Yoffset, str_mm, *font, font_size, brightness);

    // DRAW TOP SPLITTER
    if (s->blinking_colon && s->mode == DIGITAL_HH_MM && time_info->tm_sec % 2 == 0)
    {
        return;
    }

    drawColon(start_str_mm - 4 * font_size, s->start_pos_y, g);

    if (s->mode == ClockMode::DIGITAL_HH_MM_SS)
    {
        // DRAW SECOND COLON
        start_str_mm += font->getTextWidth(str_hh);
        drawColon(start_str_mm, s->start_pos_y, g);

        start_str_mm += 4 * font_size;

        g.drawText(start_str_mm, s->start_pos_y - font->max_Yoffset, str_ss, *font, font_size, brightness);
    }
}

void ClockAnimator::drawAnalog(Graphics &g)
{

    // CLEAR
    g.drawFilledRect(ANALOG_CENTER_X - ANALOG_RADIUS, ANALOG_CENTER_Y - ANALOG_RADIUS, 2 * ANALOG_RADIUS, 2 * ANALOG_RADIUS, 0);

    // DRAW CIRCLE
    g.drawCircle(ANALOG_CENTER_X, ANALOG_CENTER_Y, ANALOG_RADIUS, brightness);

    // DRAW CENTER PIXEL
    g.drawPixel(ANALOG_CENTER_X, ANALOG_CENTER_Y, brightness);

    // DRAW HOUR HAND
    g.drawLine(ANALOG_CENTER_X, ANALOG_CENTER_Y, hour_hand.x, hour_hand.y, s->hour_hand_brightness);
    // DRAW MINUTE HAND
    g.drawLine(ANALOG_CENTER_X, ANALOG_CENTER_Y, min_hand.x, min_hand.y, s->minute_hand_brightness);
    // DRAW SECOND HAND
    g.drawLine(ANALOG_CENTER_X, ANALOG_CENTER_Y, sec_hand.x, sec_hand.y, s->second_hand_brightness);
}
