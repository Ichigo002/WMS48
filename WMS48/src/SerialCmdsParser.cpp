#include "SerialCmdsParser.h"

SerialCmdsParser::SerialCmdsParser(Graphics &g, Display &d, Font& f)
    : graphics(g), display(d), font(f)
{
    execTools = new ExecTools{
        graphics,
        font,
        display};

    initCommands();
}

SerialCmdsParser::~SerialCmdsParser()
{
}

void SerialCmdsParser::updateSerial()
{
    if (Serial.available() != 0)
    {
        std::vector<String> args;

        parseCommand(Serial.readString(), args);
        processArgumentList(args);
    }
}

void SerialCmdsParser::parseCommand(String cmd, std::vector<String> &ready_args)
{
    cmd.trim();

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

int SerialCmdsParser::processArgumentList(std::vector<String> &args)
{
    if (args.empty())
    {
        return -1;
    }

    int cmd_number = -1;
    for (size_t i = 0; i < command_list.size(); i++)
    {

        if (command_list[i].executable_name == args[0])
        {
            cmd_number = i;
            i = command_list.size();
        }
    }

    if (cmd_number == -1)
    {
        if (args[0] == "help")
        {
            printHelp();
            return 0;
        }
        Serial.println("Command not found. Use 'help' for more information");
        return -1;
    }

    CommandBody &cb = command_list[cmd_number];

    if (args.size() == 1 && !cb.one_word_cmd) // hint
    {
        Serial.print(cb.executable_name);
        Serial.println(cb.hint_details);
        return 0;
    }
    else if (args.size() > 1 && args[1] == "help") // help
    {
        Serial.print(cb.executable_name);
        Serial.println(cb.help_details);
        return 0;
    }
    else // world.execute(me);
    {
        int r = cb.execute(*execTools, args);
        if(r == 0)
        {
            Serial.print(cb.executable_name);
            Serial.println(" successfully executed.");
            return 0;
        }
        else
        {
            Serial.print(cb.executable_name);
            Serial.print(", error occured: ");
            Serial.println(r);
            return -1;
        }
    }

    return 1;
}

void SerialCmdsParser::printHelp()
{
    String h = "\n";

    for (size_t i = 0; i < 10; i++)
    {
        h += "-+";
    }
    h += " HELP ";
    for (size_t i = 0; i < 10; i++)
    {
        h += "-+";
    }

    h += "\n\n";

    for (size_t i = 0; i < command_list.size(); i++)
    {
        h += command_list[i].executable_name + command_list[i].help_details + "\n";
    }

    h += "\n";

    for (size_t i = 0; i < 10; i++)
    {
        h += "-+";
    }
    h += " HELP ";
    for (size_t i = 0; i < 10; i++)
    {
        h += "-+";
    }
    h += "\n\n";
    Serial.print(h);
}
