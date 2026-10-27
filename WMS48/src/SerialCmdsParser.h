#ifndef SCH_H
#define SCH_H

#include "Graphics.h"
#include "HardwareInterface.h"
#include "TextAnimator.h"
#include "ClockAnimator.h"
#include <Arduino.h>
#include <vector>
#include <functional>

// struct containing pointers to all required objects to execute effieciently command
struct ExecTools
{
    Stream* out;
    ClockAnimator& clk;
    Graphics& graphics;
    Font& font;
    Display& display;
    HardwareInterface& hardwareInterface;
    TextAnimator& txt_anim;
    bool animation_initialized;
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
    SerialCmdsParser(Graphics& g, Display& d, Font& f, HardwareInterface& h, TextAnimator& t, ClockAnimator& c);
    ~SerialCmdsParser();

    // check if Stream has any new data to read and if it has, then it process data to call approppierate command
    void processSerialIfAvailable(Stream& s);
    
    // it parses raw cmd String into ready vector with arguments to use.
    void parseCommand(String cmd, std::vector<String>& ready_args);
    // it executes command which is found inside args, output of command is written to Stream
    int executeFromArgsList(std::vector<String>& args, Stream& s);
    // prints help tree into Stream
    void printHelp(Stream& s);

    void removePolishDiacritics(String &str);

private:

    void makeHelpDecoration(String& h);
    void makeHelpTree(String& h);

    void initCommands();
    void createCategoryList();

private:
    ClockAnimator& clk;
    Graphics& graphics;
    Display& display;
    Font& font;
    HardwareInterface& hardwareInterface;
    TextAnimator& txt_anim;

    ExecTools* execTools;

    std::vector<CommandBody> command_list;
    std::vector<String> category_list;

    String cmd_raw;
};

#endif
