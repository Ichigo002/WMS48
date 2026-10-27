#include "SerialCmdsParser.h"

SerialCmdsParser::SerialCmdsParser(Graphics &g, Display &d, Font &f, HardwareInterface &h, TextAnimator& t, ClockAnimator& c)
    : graphics(g), display(d), font(f), hardwareInterface(h), txt_anim(t), clk(c)
{

    clk.text_settings.font = &font;

    execTools = new ExecTools{
        nullptr,
        clk,
        graphics,
        font,
        display,
        hardwareInterface,
        txt_anim,
        false};

    initCommands();
    createCategoryList();
    cmd_raw = "";
}

SerialCmdsParser::~SerialCmdsParser()
{
}

void SerialCmdsParser::processSerialIfAvailable(Stream& s)
{
    while (s.available() > 0)
    {
        char c = s.read();
        cmd_raw += c;
    }
    if(cmd_raw != "")
    {
        std::vector<String> args;

        parseCommand(cmd_raw, args); 
        cmd_raw = "";
        executeFromArgsList(args, s);
    }
}

void SerialCmdsParser::parseCommand(String cmd, std::vector<String> &ready_args)
{
    cmd.trim();

    removePolishDiacritics(cmd);

    String cutout = "";

    for (size_t i = 0; i < cmd.length(); i++)
    {
        if (cmd[i] == ' ')
        {
            ready_args.push_back(cutout);
            ready_args[ready_args.size() - 1].trim();
            cutout = "";
        }
        cutout += cmd[i];
    }
    ready_args.push_back(cutout);
    ready_args[ready_args.size() - 1].trim();
}

int SerialCmdsParser::executeFromArgsList(std::vector<String> &args, Stream& s)
{
    if (args.empty())
    {
        return -1;
    }

    int cmd_number = -1;
    args[0].toLowerCase();

    for (size_t i = 0; i < command_list.size(); i++)
    {
        String s = command_list[i].executable_name;
        s.toLowerCase();

        if (s == args[0])
        {
            cmd_number = i;
            i = command_list.size();
        }
    }

    if (cmd_number == -1)
    {
        if (args[0] == "help")
        {
            printHelp(s);
            return 0;
        }
        s.println("Command not found. Use 'help' for more information");
        return -1;
    }

    CommandBody &cb = command_list[cmd_number];

    if (args.size() == 1 && !cb.one_word_cmd) // hint
    {
        s.print(cb.executable_name);
        s.println(cb.hint_details);
        return 0;
    }
    else if (args.size() > 1 && args[1] == "help") // help
    {
        s.print(cb.executable_name);
        s.println(cb.help_details);
        return 0;
    }
    else // world.execute(me);
    {
        execTools->out = &s;
        int r = cb.execute(*execTools, args);
        if (r == 0)
        {
            s.print(cb.executable_name);
            s.println(" successfully executed.");
            return 0;
        }
        else
        {
            s.print(cb.executable_name);
            s.print(", error occured: ");
            s.println(r);
            return -1;
        }
    }

    return 1;
}

void SerialCmdsParser::createCategoryList()
{
    for (size_t i = 0; i < command_list.size(); i++)
    {
        bool found = false;
        for (size_t j = 0; j < category_list.size(); j++)
        {
            if (command_list[i].category == category_list[j])
                found = true;
        }

        if (!found)
        {
            category_list.push_back(command_list[i].category);
        }
    }
}

void SerialCmdsParser::printHelp(Stream& s)
{
    String h = "\n";

    makeHelpDecoration(h);

    h += "\n\n # For command's syntax type: 'command help' # \n";

    makeHelpTree(h);

    h += "\n";

    makeHelpDecoration(h);

    h += "\n";

    s.print(h);
}

void SerialCmdsParser::makeHelpDecoration(String &h)
{
    for (size_t i = 0; i < 10; i++)
    {
        h += "-+";
    }
    h += " HELP ";
    for (size_t i = 0; i < 10; i++)
    {
        h += "-+";
    }
}

void SerialCmdsParser::makeHelpTree(String &h)
{
    String c;
    for (size_t i = 0; i < category_list.size(); i++)
    {
        c = category_list[i];
        h += "\n+-- ";
        h += c;

        for (size_t j = 0; j < command_list.size(); j++)
        {
            if(command_list[j].category == c)
            {
                h += "\n|   +-- ";
                h += command_list[j].executable_name;
            }
        }
        
    }
}

void SerialCmdsParser::removePolishDiacritics(String &str) {
        // Ą and ą
    str.replace("\xC4\x84", "A");
    str.replace("\xC4\x85", "a");
    
    // Ę and ę
    str.replace("\xC4\x98", "E");
    str.replace("\xC4\x99", "e");
    
    // Ć and ć
    str.replace("\xC4\x86", "C");
    str.replace("\xC4\x87", "c");
    
    // Ł and ł 
    str.replace("\xC5\x81", "L");
    str.replace("\xC5\x82", "l");

    // Ń and ń
    str.replace("\xC5\x83", "N");
    str.replace("\xC5\x84", "n");
    
    // Ó and ó
    str.replace("\xC3\x93", "O");
    str.replace("\xC3\xB3", "o");
    
    // Ś and ś
    str.replace("\xC5\x9A", "S");
    str.replace("\xC5\x9B", "s");
    
    // Ź and ź
    str.replace("\xC5\xB9", "Z");
    str.replace("\xC5\xBA", "z");
    
    // Ż and ż
    str.replace("\xC5\xBB", "Z");
    str.replace("\xC5\xBC", "z");
}
