#ifndef PROTOCOL_H
#define PROTOCOL_H

/*----------------------------------------------------------------
|                                                                |
|    The whole BLE protocol required to communicate.             |
|    It should be identical on both side: server and client      |
|                                                                |
------------------------------------------------------------------*/

namespace BLE_UUIDs
{
    constexpr const char* WMS_SERVICE = "1c7bfa9a-e1cb-4537-afcb-7720637cd505";

    /* DATA TYPE: uint8_t (255)*/
    constexpr const char* SCENE_INDEX_CHAR = "ca6978b1-f7e3-421f-94bc-74fae22d92f2"; // WRITE & READ current scene index

    /* DATA TYPE: byte array (command OP)*/
    constexpr const char* COMMAND_SCENE_CHAR = "b2e76ce4-8868-4862-9b7e-88ec99b4798e"; // WRITE commands to current scene
    /* DATA TYPE: byte array (command OP)*/
    constexpr const char* COMMAND_CHAR = "5d6fa55f-d1bd-4f9c-bae9-598ba3df44fe"; // WRITE commands to general use
    
    constexpr const char* RESPONSE_CHAR = "b123c315-1d13-4794-a638-749d6a4ee644"; // READ, respond of command_Char
    constexpr const char* EVENT_CHAR = "48a9f150-92ae-44b1-b3a6-baa1c0530e6a"; // NOTIFY & READ to client

    /*DATA TYPE: 4 bytes (uint32_t)*/
    constexpr const char* UNIX_TIME_CHAR = "9a3fa590-b5da-4368-bbb5-41c680a2051e";
};

enum SceneIDs // cannot be negative <0
{
    TEXT_SCENE = 1,
    WELCOME_SCENE = 2,
};


namespace BLE_CMD_SCENE {
    /*
    NAME: Set only raw text. TEST COMMAND
    BODY:
        OP_CODE, [0]
        TEXT BYTES... [length: n-1]
    */
    constexpr const uint8_t OP_SET_TEXT = 0x01;

    /*
    NAME: updates integer values
    BODY:
        OP_CODE, [0]
        VALUE1 (int8_t), [1]
        VALUE2 (int8_t), [2]
        ...
        VALUEN (int8_t), [n-1]
    */
    constexpr const uint8_t OP_UPDATE_VALUES = 0x02;
}

#endif