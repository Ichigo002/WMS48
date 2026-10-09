#ifndef SCH_H
#define SCH_H

#include "Graphics.h"
#include <Arduino.h>
#include <vector>
#include <functional>

struct CommandBody
{
    String executable_name;
    String hint_details;
    String help_details;
    std::function<void(ExecTools&, std::vector<String>&)> execute;
};

// struct containing pointers to all required objects to execute effieciently command
struct ExecTools
{
    Graphics& graphics;
    Display& display;
};

/*
Arguments order:
hint:         rect
hint example: rect x* y* w* h* b

help:         rect help
help example: rect [x=pos] [y=pos] [w=width] [h=height] [b=brightness(0-32)]
*/
class SerialCommandsHandler
{
public:
    SerialCommandsHandler(Graphics& g, Display& d);
    ~SerialCommandsHandler();

    void updateSerial();
    
    
private:
    void parseCommand(String cmd, std::vector<String>& ready_args);
    int processArgumentList(std::vector<String>& args);

    void printHelp();

private:
    Graphics graphics;
    Display display;

    ExecTools* execTools;

    std::vector<CommandBody> command_list;

    // int commands_list_size = 5;
    // String commands[6] = {
    //     "help",
    //     "drawLine",
    //     "drawRect",
    //     "drawFilledRect",
    //     "drawCircle",
    //     "drawText",
    // };
};

#endif
