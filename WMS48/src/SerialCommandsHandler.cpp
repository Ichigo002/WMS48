#include "SerialCommandsHandler.h"


SerialCommandsHandler::SerialCommandsHandler(Graphics &g, Display& d)
    : graphics(g), display(d)
{
    execTools = new ExecTools {
        graphics,
        display
    };


    command_list.push_back(CommandBody() = {
        .executable_name = "drawLine",
        .hint_details = " x0 y0 x1 y1",
        .help_details = " [x start] [y start] [x end] [y end]",
        .execute = [](ExecTools ext, std::vector<String>& args) {
            if (args.empty()) {
                return;
            }
            
            
        }
    });
}

SerialCommandsHandler::~SerialCommandsHandler()
{
}

void SerialCommandsHandler::updateSerial()
{
    if (Serial.available() != 0)
    {
        std::vector<String> args;

        parseCommand(Serial.readString(), args);
        processArgumentList(args);
    }
}

void SerialCommandsHandler::parseCommand(String cmd, std::vector<String>& ready_args)
{
    cmd.trim();

    while (cmd.length() > 1)
    {
        int pos = cmd.indexOf(' ');
        if (pos == -1)
        {
            break;
        }
        ready_args.push_back(cmd.substring(0, pos));

        cmd = cmd.substring(pos + 1);
    }
}

int SerialCommandsHandler::processArgumentList(std::vector<String>& args)
{
    if(args.empty())
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

    if(cmd_number == -1)
    {
        if(args[0] == "help")
        {
            printHelp();
            return 0;
        }
        Serial.println("Command not found. Use 'help' for existing commands");
        return -1;
    }

    CommandBody &cb = command_list[cmd_number];

    if (args.size() == 1) // hint
    {
        Serial.print(cb.executable_name);
        Serial.println(cb.hint_details);
        return 0;
    }
    else if (args[1] == "help") // help
    {
        Serial.print(cb.executable_name);
        Serial.println(cb.help_details);
        return 0;
    }
    else // world.execute(me);
    {
        cb.execute(, args);
        return 0;
    }

    return 1;
}

void SerialCommandsHandler::printHelp()
{
    String h = "";

    for (size_t i = 0; i < 8; i++)
    {
        h += "-+";
    }

    h += "\n";

    for (size_t i = 0; i < command_list.size(); i++)
    {
        h += i + ". " + command_list[i].executable_name + command_list[i].help_details + "\n";
    }
    
    h += "\n";

    for (size_t i = 0; i < 8; i++)
    {
        h += "-+";
    }
    h += "\n\n";
    Serial.print(h);
}

// void SerialCommandsHandler::handleHints(int command)
// {
//     String output = "";
//     switch (command)
//     {
//     case 0: // help
//         output = "";
//         break;
//     case 1:
//         output = commands[1] + " x0 y0 x1 y1";
//         break;
//     case 2:
//         output = commands[2] + " x y w h";
//         break;
//     case 3:
//         output = commands[3] + " x y w h";
//         break;
//     case 4:
//         output = commands[4] + " x y r";
//         break;
//     case 5:
//         output = commands[5] + "x y s [text]";
//         break;

//     default:
//         output = "Command not found. Use 'help' for existing commands";
//         break;
//     }

//     Serial.println(output);
// }

// void SerialCommandsHandler::handleHelps(int command)
// {
//         String output = "";
//     switch (command)
//     {
//     case 0: // help
//         output = "";
//         break;
//     case 1:
//         output = commands[1] + " [x start] [y start] [x end] [y end]";
//         break;
//     case 2:
//         output = commands[2] + " [x pos] [y pos] [width] [height]";
//         break;
//     case 3:
//         output = commands[3] +  "[x pos] [y pos] [width] [height]";
//         break;
//     case 4:
//         output = commands[4] + " [x pos] [y pos] [radius]";
//         break;
//     case 5:
//         output = commands[5] + " [x pos] [y pos] [font size] [text]";
//         break;

//     default:
//         output = "Command not found. Use 'help' for existing commands";
//         break;
//     }

//     Serial.println(output);
// }
