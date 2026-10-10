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
        .hint_details = " x y f b txt",
        .help_details = " [x start] [y start] [font size 1-3] [brightness 0-32] [your text] ",
        .execute = [](ExecTools ext, std::vector<String> &args)
        {
            if (args.size() < 5 + 1)
                return -1;

            int v1 = args[1].toInt();
            int v2 = args[2].toInt();
            int v4 = args[3].toInt();
            int v5 = args[4].toInt();
            String txt = "";
            for (size_t i = 5; i < args.size(); i++)
            {
                txt += args[i];
                txt += " ";
            }

            txt.remove(txt.length()-1);
            
            ext.graphics.drawText(v1, v2, txt, ext.font, v4, v5);
            return 0;
        }});

        command_list.push_back(CommandBody{
        .executable_name = "txtBasic",
        .category = "Graphics",
        .one_word_cmd = false,
        .hint_details = " x y text",
        .help_details = " [x start] [y start] [your text] ",
        .execute = [](ExecTools ext, std::vector<String> &args)
        {
            if (args.size() < 3 + 1)
                return -1;

            int v1 = args[1].toInt();
            int v2 = args[2].toInt();
            String txt = "";
            for (size_t i = 3; i < args.size(); i++)
            {
                txt += args[i];
                txt += " ";
            }

            txt.remove(txt.length()-1);
            
            ext.graphics.drawText(v1, v2, txt, ext.font, 1);
            return 0;
        }});

        command_list.push_back(CommandBody{
        .executable_name = "txt",
        .category = "Graphics",
        .one_word_cmd = false,
        .hint_details = " text",
        .help_details = " [your text] Automatic text placement",
        .execute = [](ExecTools ext, std::vector<String> &args)
        {
            if (args.size() < 1 + 1)
                return -1;

            std::vector<String> txts;
            String txt = "";
            for (size_t i = 1; i < args.size(); i++)
            {
                if(args[i] == "\\n") // enter sign '\n'
                {
                    txts.push_back(txt);
                    txt = "";
                }
                else
                {
                    if((txt + args[i]).length() > 8)
                    {
                        txts.push_back(txt);
                        txt = "";
                        txt += args[i];
                        txt += " ";
                    }
                    else
                    {
                        txt += args[i];
                        txt += " ";
                    }
                }
            }

            txt.remove(txt.length()-1);

            txts.push_back(txt);

            int s = txts.size();

            if(s > 4)
                s = 4;

            ext.graphics.clear();
            
            for (size_t i = 0; i < s; i++)
            {
                ext.graphics.drawText(0, 8*i, txts[i], ext.font, 1);
            }
            
            return 0;
        }});

    /* DISPLAY CMDS*/

    command_list.push_back(CommandBody{
        .executable_name = "setBrightness",
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
        .help_details = " [frequency in Hz of screen. Def: 60Hz]",
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
        .hint_details = " (1 or 0)",
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
