#ifndef SCH_H
#define SCH_H

#include "Graphics.h"
#include "HardwareInterface.h"
#include <Arduino.h>
#include <vector>
#include <functional>

// struct containing pointers to all required objects to execute effieciently command
struct ExecTools
{
    Graphics& graphics;
    Font& font;
    Display& display;
    HardwareInterface& hardwareInterface;
};

struct CommandBody
{
    String executable_name;
    String category;
    bool one_word_cmd;
    String hint_details;
    String help_details;
    std::function<int(ExecTools&, std::vector<String>&)> execute;
};



/*
Arguments order:
hint:         rect
hint example: rect x* y* w* h* b

help:         rect help
help example: rect [x=pos] [y=pos] [w=width] [h=height] [b=brightness(0-32)]
*/
class SerialCmdsParser
{
public:
    SerialCmdsParser(Graphics& g, Display& d, Font& f, HardwareInterface& h);
    ~SerialCmdsParser();

    void updateSerial();
    
    
private:
    void parseCommand(String cmd, std::vector<String>& ready_args);
    int processArgumentList(std::vector<String>& args);

    void printHelp();
    void printHelpDecoration(String& h);
    void printHelpTree(String& h);

    void initCommands();
    void createCategoryList();

private:
    Graphics& graphics;
    Display& display;
    Font& font;
    HardwareInterface& hardwareInterface;

    ExecTools* execTools;

    std::vector<CommandBody> command_list;
    std::vector<String> category_list;
};

#endif
