#ifndef BLE_PROTOCOL_H
#define BLE_RPOTOCOL_H

/*----------------------------------------------------------------
|                                                                |
|    The whole BLE protocol required to communicate.             |
|    It should be identical on both side: server and client      |
|                                                                |
------------------------------------------------------------------*/

namespace BLE_UUIDs
{
    constexpr const char* WMS_SERVICE = "1c7bfa9a-e1cb-4537-afcb-7720637cd505";

    constexpr const char* SCENE_INDEX_CHAR = "ca6978b1-f7e3-421f-94bc-74fae22d92f2"; // WRITE & READ current scene index

    constexpr const char* COMMAND_SCENE_CHAR = "b2e76ce4-8868-4862-9b7e-88ec99b4798e"; // WRITE commands to current scene
    constexpr const char* COMMAND_CHAR = "5d6fa55f-d1bd-4f9c-bae9-598ba3df44fe"; // WRITE commands to general use
    constexpr const char* RESPONSE_CHAR = "b123c315-1d13-4794-a638-749d6a4ee644"; // READ, respond of command_Char
    constexpr const char* EVENT_CHAR = "48a9f150-92ae-44b1-b3a6-baa1c0530e6a"; // NOTIFY & READ to client

    constexpr const char* UNIX_TIME_CHAR = "9a3fa590-b5da-4368-bbb5-41c680a2051e";
};

enum SceneIDs
{
    NULL_S = -1,
    SANDBOX_SCENE = 0,
    TEXT_SCENE = 1,
    WELCOME_SCENE = 2,
};

#endif