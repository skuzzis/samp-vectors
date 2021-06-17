/*
# natives.hpp

Contains all the `PAWN_NATIVE_DECL` for native function declarations.
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

#ifndef PROJECTNAME_NATIVES_H
#define PROJECTNAME_NATIVES_H

#include <string>
#include <vector>
#include <time.h>
#include "amx/amx2.h"

#include "common.hpp"

namespace Natives {

cell Vector_Create(AMX* amx, cell* params);
cell Vector_Size(AMX* amx, cell* params);
cell Vector_Even(AMX* amx, cell* params);
cell Vector_Odd(AMX* amx, cell* params);
cell Vector_Clear(AMX* amx, cell* params);
cell Vector_Empty(AMX* amx, cell* params);
cell Vector_PopBack(AMX* amx, cell* params);
cell Vector_PopFront(AMX* amx, cell* params);
cell Vector_FindIndex(AMX* amx, cell* params);
cell Vector_Add(AMX* amx, cell* params);
cell Vector_FindValue(AMX* amx, cell* params);
cell Vector_Remove(AMX* amx, cell* params);
cell Vector_Delete(AMX* amx, cell* params);
cell Vector_ReplaceIndex(AMX* amx, cell* params);
cell Vector_Replace(AMX* amx, cell* params);
cell Vector_Insert(AMX* amx, cell* params);
cell Vector_Random(AMX* amx, cell* params);
cell Vector_Begin(AMX* amx, cell* params);
cell Vector_End(AMX* amx, cell* params);
cell Vector_First(AMX* amx, cell* params);
cell Vector_Last(AMX* amx, cell* params);
cell Vector_Next(AMX* amx, cell* params);
cell Vector_Prev(AMX* amx, cell* params);
cell Vector_DebugMode(AMX* amx, cell* params);

}

#endif
