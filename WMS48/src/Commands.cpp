#include "SerialCmdsParser.h"

void SerialCmdsParser::initCommands()
{
    command_list.push_back(CommandBody{
        .executable_name = "clear",
        .category = "Graphics",
        .one_word_cmd = true,
        .hint_details = "",
        .help_details = "",
        .execute = [](ExecTools ext, std::vector<String> &args)
        {
            ext.graphics.clear();
            return 0;
        }});

    command_list.push_back(CommandBody{
        .executable_name = "drawLine",
        .category = "Graphics",
        .one_word_cmd = false,
        .hint_details = " x0 y0 x1 y1",
        .help_details = " [x start] [y start] [x end] [y end]",
        .execute = [](ExecTools ext, std::vector<String> &args)
        {
            if (args.size() < 4 + 1)
                return -1;

            int v1 = args[1].toInt();
            int v2 = args[2].toInt();
            int v3 = args[3].toInt();
            int v4 = args[4].toInt();

            ext.graphics.drawLine(v1, v2, v3, v4);
            return 0;
        }});

    command_list.push_back(CommandBody{
        .executable_name = "drawRect",
        .category = "Graphics",
        .one_word_cmd = false,
        .hint_details = " x0 y0 w h",
        .help_details = " [x start] [y start] [width] [height]",
        .execute = [](ExecTools ext, std::vector<String> &args)
        {
            if (args.size() < 4 + 1)
                return -1;

            int v1 = args[1].toInt();
            int v2 = args[2].toInt();
            int v3 = args[3].toInt();
            int v4 = args[4].toInt();

            ext.graphics.drawRect(v1, v2, v3, v4);
            return 0;
        }});

    command_list.push_back(CommandBody{
        .executable_name = "drawFilledRect",
        .category = "Graphics",
        .one_word_cmd = false,
        .hint_details = " x0 y0 w h",
        .help_details = " [x start] [y start] [width] [height]",
        .execute = [](ExecTools ext, std::vector<String> &args)
        {
            if (args.size() < 4 + 1)
                return -1;

            int v1 = args[1].toInt();
            int v2 = args[2].toInt();
            int v3 = args[3].toInt();
            int v4 = args[4].toInt();

            ext.graphics.drawFilledRect(v1, v2, v3, v4);
            return 0;
        }});

    command_list.push_back(CommandBody{
        .executable_name = "drawCircle",
        .category = "Graphics",
        .one_word_cmd = false,
        .hint_details = " x y r",
        .help_details = " [x center] [y center] [radius]",
        .execute = [](ExecTools ext, std::vector<String> &args)
        {
            if (args.size() < 3 + 1)
                return -1;

            int v1 = args[1].toInt();
            int v2 = args[2].toInt();
            int v3 = args[3].toInt();

            ext.graphics.drawCircle(v1, v2, v3);
            return 0;
        }});

    command_list.push_back(CommandBody{
        .executable_name = "drawText",
        .category = "Graphics",
        .one_word_cmd = false,
        .hint_details = " x y f txt",
        .help_details = " [x start] [y start] [font size 1-3] [your text] ",
        .execute = [](ExecTools ext, std::vector<String> &args)
        {
            if (args.size() < 4 + 1)
                return -1;

            int v1 = args[1].toInt();
            int v2 = args[2].toInt();
            int v4 = args[3].toInt();
            String txt = "";
            for (size_t i = 4; i < args.size(); i++)
            {
                txt += args[i];
                txt += " ";
            }

            txt.remove(txt.length()-1);
            
            ext.graphics.drawText(v1, v2, txt, ext.font, v4);
            return 0;
        }});

    /* DISPLAY CMDS*/

    command_list.push_back(CommandBody{
        .executable_name = "setTotalBrig",
        .category = "Display",
        .one_word_cmd = false,
        .hint_details = " v",
        .help_details = " [brightness value from 0.0f to 1.0f]",
        .execute = [](ExecTools ext, std::vector<String> &args)
        {
            if (args.size() < 1 + 1)
                return -1;

            float v1 = args[1].toFloat();

            ext.display.setBrightness(v1);
            return 0;
        }});

    command_list.push_back(CommandBody{
        .executable_name = "setRefreshFreq",
        .category = "Display",
        .one_word_cmd = false,
        .hint_details = " f",
        .help_details = " [frequency in Hz units of screen. Default: 60Hz] TO FIX IT",
        .execute = [](ExecTools ext, std::vector<String> &args)
        {
            if (args.size() < 1 + 1)
                return -1;

            int v1 = args[1].toInt();

            ext.display.setNewRefreshRate(v1);
            return 0;
        }});

    command_list.push_back(CommandBody{
        .executable_name = "turnLed",
        .category = "Hardware",
        .one_word_cmd = false,
        .hint_details = " v",
        .help_details = " [1 - on, 0 - off]",
        .execute = [](ExecTools ext, std::vector<String> &args)
        {
            if (args.size() < 1 + 1)
                return -1;

            int v1 = args[1].toInt();

            if(v1 == 1)
            {
                digitalWrite(config::pin_led, HIGH);
            } else {
                digitalWrite(config::pin_led, LOW);
            }
            
            return 0;
        }});
}