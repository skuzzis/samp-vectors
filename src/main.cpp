/*
# main.cpp

The "main" source file with most of the boilerplate code. Includes the
`NativesMain` header for initialising plugin-natives.

- `Supports` declares to the SA:MP server which features this plugin uses.
- `Load` is called when the plugin loads and sets up the `logprintf` function.
*/

/*
=================================================================================================================================================

Copyright 2021 - Andrei "SkuZZi" Sebastian

Permission is hereby granted, free of charge, to any person obtaining a copy of this software
and associated documentation files (the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

=================================================================================================================================================
*/

#include "amx/amx.h"
#include "plugincommon.h"

#include "common.hpp"
#include "natives.hpp"

logprintf_t logprintf;

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports()
{
    return SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES;
}

PLUGIN_EXPORT bool PLUGIN_CALL Load(void** ppData)
{
    pAMXFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];
    logprintf = (logprintf_t)ppData[PLUGIN_DATA_LOGPRINTF];
    return true;
}

extern "C" const AMX_NATIVE_INFO native_list[] = {
    { "Vector_Create", Natives::Vector_Create },
    { "Vector_Size", Natives::Vector_Size },
    { "Vector_Clear", Natives::Vector_Clear },
    { "Vector_Even", Natives::Vector_Even },
    { "Vector_Odd", Natives::Vector_Odd },
    { "Vector_Empty", Natives::Vector_Empty },
    { "Vector_PopBack", Natives::Vector_PopBack },
    { "Vector_PopFront", Natives::Vector_PopFront },
    { "Vector_FindIndex", Natives::Vector_FindIndex },
    { "Vector_Add", Natives::Vector_Add },
    { "Vector_FindValue", Natives::Vector_FindValue },
    { "Vector_Remove", Natives::Vector_Remove },
    { "Vector_Delete", Natives::Vector_Delete }, 
    { "Vector_ReplaceIndex", Natives::Vector_ReplaceIndex },
    { "Vector_Replace", Natives::Vector_Replace },
    { "Vector_Insert", Natives::Vector_Insert },
    { "Vector_Random", Natives::Vector_Random },

    { "Vector_Begin", Natives::Vector_Begin },
    { "Vector_End", Natives::Vector_End },
    { "Vector_First", Natives::Vector_First },
    { "Vector_Last", Natives::Vector_Last },
    { "Vector_Next", Natives::Vector_Next },
    { "Vector_Prev", Natives::Vector_Prev },
    { NULL, NULL }
};

PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX* amx)
{
    return amx_Register(amx, native_list, -1);
}

PLUGIN_EXPORT int PLUGIN_CALL Unload()
{
    return 1;
}

PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX* amx)
{
    return 1;
}
