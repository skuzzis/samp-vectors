/*
# natives.cpp

This source file contains the bridge between natives and implementations. I
prefer to keep the actual implementation separate. The implementation contains
no instances of `cell` or `AMX*` and is purely C++ and external library code.
The code here acts as the translation between AMX data types and native types.
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

#include "natives.hpp"

std::vector<std::vector<int>> vects;
std::vector<int> vects_size;

bool debugging = false;
int vectorID = -1;

cell Natives::Vector_Size(AMX* amx, cell* params) {

    if (static_cast<int>(params[1]) < 0 || static_cast<int>(params[1]) > vectorID)
        return -1;

    if(debugging) logprintf("[SA:MP Vectors Debug] returns size for vector %d, %d", static_cast<int>(params[1]), vects_size.at(static_cast<int>(params[1])));

    return vects_size.at(static_cast<int>(params[1]));
}

cell Natives::Vector_Even(AMX* amx, cell* params) {
    if (static_cast<int>(params[1]) < 0 || static_cast<int>(params[1]) > vectorID)
        return -1;

    if (debugging) logprintf("[SA:MP Vectors Debug] returns vector even value: %d", vects_size.at(static_cast<int>(params[1])) % 2 == 0);

    return vects_size.at(static_cast<int>(params[1])) % 2 == 0;
}

cell Natives::Vector_Odd(AMX* amx, cell* params) {
    if (static_cast<int>(params[1]) < 0 || static_cast<int>(params[1]) > vectorID)
        return -1;

    if (debugging) logprintf("[SA:MP Vectors Debug] returns vector odd value: %d", vects_size.at(static_cast<int>(params[1])) % 2 == 1);

    return vects_size.at(static_cast<int>(params[1])) % 2 == 1;
}

cell Natives::Vector_Clear(AMX* amx, cell* params) {
    if (static_cast<int>(params[1]) < 0 || static_cast<int>(params[1]) > vectorID)
        return -1;

    if (debugging) logprintf("[SA:MP Vectors Debug] vector empty: %s", vects_size.at(static_cast<int>(params[1])) == 0 ? "yes" : "no");

    if (vects_size.at(static_cast<int>(params[1])) == 0)
        return 0;

    vects_size[static_cast<int>(params[1])] = 0;

    return vects[static_cast<int>(params[1])].clear(), 1;
}

cell Natives::Vector_Empty(AMX* amx, cell* params) {
    if (static_cast<int>(params[1]) < 0 || static_cast<int>(params[1]) > vectorID)
        return -1;

    if (debugging) logprintf("[SA:MP Vectors Debug] vector empty: %s", vects_size.at(static_cast<int>(params[1])) == 0 ? "yes" : "no");

    return vects_size.at(static_cast<int>(params[1])) == 0;
}

cell Natives::Vector_PopFront(AMX* amx, cell* params) {

    if (static_cast<int>(params[1]) < 0 || static_cast<int>(params[1]) > vectorID)
        return -1;

    if (debugging) logprintf("[SA:MP Vectors Debug] vector PopFront size: %d, returns %d", vects_size[static_cast<int>(params[1])], vects_size[static_cast<int>(params[1])] > 0);

    if (vects_size[static_cast<int>(params[1])] < 1)
        return 0;

    vects_size[static_cast<int>(params[1])] --;

    int first = vects[static_cast<int>(params[1])][0];
    return vects[static_cast<int>(params[1])].erase(vects[static_cast<int>(params[1])].begin()), first;
}

cell Natives::Vector_PopBack(AMX* amx, cell* params) {
    if (static_cast<int>(params[1]) < 0 || static_cast<int>(params[1]) > vectorID)
        return -1;

    if (debugging) logprintf("[SA:MP Vectors Debug] vector PopBack size: %d, returns %d", vects_size[static_cast<int>(params[1])], vects_size[static_cast<int>(params[1])] > 0);

    if (vects_size[static_cast<int>(params[1])] < 1)
        return 0;

    vects_size[static_cast<int>(params[1])] --;

    int last = vects[static_cast<int>(params[1])][vects_size.at(static_cast<int>(params[1]))];
    return vects[static_cast<int>(params[1])].pop_back(), last;
}

cell Natives::Vector_FindIndex(AMX* amx, cell* params) {
    if (static_cast<int>(params[1]) < 0 || static_cast<int>(params[1]) > vectorID)
        return -1;

    if (std::is_sorted(vects[static_cast<int>(params[1])].begin(), vects[static_cast<int>(params[1])].end())) {
        auto i = std::lower_bound(vects[static_cast<int>(params[1])].begin(), vects[static_cast<int>(params[1])].end(), static_cast<int>(params[2]));
        return i != vects[static_cast<int>(params[1])].end() && !(static_cast<int>(params[2]) < *i) ? std::distance(vects[static_cast<int>(params[1])].begin(), i) : -1;
    }
    else {
        auto i = std::find(vects[static_cast<int>(params[1])].begin(), vects[static_cast<int>(params[1])].end(), static_cast<int>(params[2]));
        return (i != vects[static_cast<int>(params[1])].end()) ? i - vects[static_cast<int>(params[1])].begin() : -1;
    }
}

cell Natives::Vector_Add(AMX* amx, cell* params) {
    if (static_cast<int>(params[1]) < 0 || static_cast<int>(params[1]) > vectorID)
        return -1;

    if (debugging) logprintf("[SA:MP Vectors Debug] vector add element: %d, new size %d", static_cast<int>(params[2]), vects_size[static_cast<int>(params[1])] + 1);

    vects_size[static_cast<int>(params[1])] ++;

    return vects[static_cast<int>(params[1])].push_back(static_cast<int>(params[2])), 1;
}

cell Natives::Vector_FindValue(AMX* amx, cell* params) {
    if (static_cast<int>(params[1]) < 0 || static_cast<int>(params[1]) > vectorID || vects_size[static_cast<int>(params[1])] <= static_cast<int>(params[2]) || static_cast<int>(params[2]) < 0)
        return -1;

    if (debugging) logprintf("[SA:MP Vectors Debug] vector find at index: %d, found %d", static_cast<int>(params[2]), vects[static_cast<int>(params[1])].at(static_cast<int>(params[2])));

    return vects[static_cast<int>(params[1])].at(static_cast<int>(params[2]));
}

cell Natives::Vector_Random(AMX* amx, cell* params) {
    if (static_cast<int>(params[1]) < 0 || static_cast<int>(params[1]) > vectorID)
        return -1;

    srand(static_cast<unsigned int>(time(0)));

    if (debugging) logprintf("[SA:MP Vectors Debug] vector random seed: %d", static_cast<unsigned int>(time(0)));

    return vects[static_cast<int>(params[1])].at(rand() % vects_size[static_cast<int>(params[1])]);
}

cell Natives::Vector_ReplaceIndex(AMX* amx, cell* params) {
    if (static_cast<int>(params[1]) < 0 || static_cast<int>(params[1]) > vectorID || vects_size[static_cast<int>(params[1])] <= static_cast<int>(params[2]) || static_cast<int>(params[2]) < 0)
        return -1;

    if (debugging) logprintf("[SA:MP Vectors Debug] vector replacing index %d with value %d, to %d", static_cast<int>(params[2]), vects[static_cast<int>(params[1])].at(static_cast<int>(params[2])), static_cast<int>(params[3]));
        
    vects[static_cast<int>(params[1])].erase(vects[static_cast<int>(params[1])].begin() + static_cast<int>(params[2]));
    vects[static_cast<int>(params[1])].insert(vects[static_cast<int>(params[1])].begin() + static_cast<int>(params[2]), static_cast<int>(params[3]));

    return 1;
}

cell Natives::Vector_Remove(AMX* amx, cell* params) {
    if (static_cast<int>(params[1]) < 0 || static_cast<int>(params[1]) > vectorID)
        return -1;

    int index = -1;

    if (std::is_sorted(vects[static_cast<int>(params[1])].begin(), vects[static_cast<int>(params[1])].end())) {
        auto i = std::lower_bound(vects[static_cast<int>(params[1])].begin(), vects[static_cast<int>(params[1])].end(), static_cast<int>(params[2]));
        if(!(i != vects[static_cast<int>(params[1])].end() && !(static_cast<int>(params[2]) < *i)))
            return debugging ? logprintf("[SA:MP Vectors Debug] vector cannot remove element %d because it doesn't exists", static_cast<int>(params[2])), 0 : 0;

        index = std::distance(vects[static_cast<int>(params[1])].begin(), i);
    }
    else {
        auto i = std::find(vects[static_cast<int>(params[1])].begin(), vects[static_cast<int>(params[1])].end(), static_cast<int>(params[2]));
        if(i == vects[static_cast<int>(params[1])].end())
            return debugging ? logprintf("[SA:MP Vectors Debug] vector cannot remove element %d because it doesn't exists", static_cast<int>(params[2])), 0 : 0;
        index = i - vects[static_cast<int>(params[1])].begin();
    }

    if (debugging) logprintf("[SA:MP Vectors Debug] removed element %d which had index %d.", static_cast<int>(params[2]), index);
    return vects[static_cast<int>(params[1])].erase(vects[static_cast<int>(params[1])].begin() + index), vects_size[static_cast<int>(params[1])] --, 1;
}

cell Natives::Vector_Delete(AMX* amx, cell* params) {
    if (static_cast<int>(params[1]) < 0 || static_cast<int>(params[1]) > vectorID || vects_size[static_cast<int>(params[1])] <= static_cast<int>(params[2]) || static_cast<int>(params[2]) < 0)
        return -1;
    
    return vects[static_cast<int>(params[1])].erase(vects[static_cast<int>(params[1])].begin() + static_cast<int>(params[2])), vects_size[static_cast<int>(params[1])] --, 1;
}

cell Natives::Vector_Replace(AMX* amx, cell* params)
{
    if (static_cast<int>(params[1]) < 0 || static_cast<int>(params[1]) > vectorID)
        return -1;

    int index = -1;

    if (std::is_sorted(vects[static_cast<int>(params[1])].begin(), vects[static_cast<int>(params[1])].end())) {
        auto i = std::lower_bound(vects[static_cast<int>(params[1])].begin(), vects[static_cast<int>(params[1])].end(), static_cast<int>(params[2]));
        if (!(i != vects[static_cast<int>(params[1])].end() && !(static_cast<int>(params[2]) < *i)))
            return debugging ? logprintf("[SA:MP Vectors Debug] vector cannot replace element %d because it doesn't exists", static_cast<int>(params[2])), 0 : 0;

        index = std::distance(vects[static_cast<int>(params[1])].begin(), i);
    }
    else {
        auto i = std::find(vects[static_cast<int>(params[1])].begin(), vects[static_cast<int>(params[1])].end(), static_cast<int>(params[2]));
        if (i == vects[static_cast<int>(params[1])].end())
            return debugging ? logprintf("[SA:MP Vectors Debug] vector cannot replace element %d because it doesn't exists", static_cast<int>(params[2])), 0 : 0;
        index = i - vects[static_cast<int>(params[1])].begin();
    }

    if (debugging) logprintf("[SA:MP Vectors Debug] replaced element %d which had index %d to %d.", static_cast<int>(params[2]), index, static_cast<int>(params[3]));
    return vects[static_cast<int>(params[1])][index] = static_cast<int>(params[3]), 1;
}

cell Natives::Vector_Insert(AMX* amx, cell* params) {
    if (static_cast<int>(params[1]) < 0 || static_cast<int>(params[1]) > vectorID || vects_size[static_cast<int>(params[1])] <= static_cast<int>(params[2]) || static_cast<int>(params[2]) < 0)
        return -1;

    if (debugging) logprintf("[SA:MP Vectors Debug] inserted element at index %d with value %d.", static_cast<int>(params[2]), static_cast<int>(params[3]));
    return vects[static_cast<int>(params[1])].insert(vects[static_cast<int>(params[1])].begin() + static_cast<int>(params[2]), static_cast<int>(params[3])), vects_size[static_cast<int>(params[1])] ++, 1;
}

cell Natives::Vector_Begin(AMX* amx, cell* params) {
    if (static_cast<int>(params[1]) < 0 || static_cast<int>(params[1]) > vectorID || vects_size[static_cast<int>(params[1])] < 1)
        return -1;

    if (debugging) logprintf("[SA:MP Vectors Debug] vector begin size: %d | element at index 0: %d.", vects_size[static_cast<int>(params[1])], vects[static_cast<int>(params[1])].at(0));
    return vects[static_cast<int>(params[1])].at(0) - 1;
}

cell Natives::Vector_End(AMX* amx, cell* params) {
    if (static_cast<int>(params[1]) < 0 || static_cast<int>(params[1]) > vectorID || vects_size[static_cast<int>(params[1])] < 1)
        return -1;

    if (debugging) logprintf("[SA:MP Vectors Debug] vector end size: %d | element at index %d: %d.", vects_size[static_cast<int>(params[1])], vects_size[static_cast<int>(params[1])] - 1, vects[static_cast<int>(params[1])].at(vects_size[static_cast<int>(params[1])] - 1));
    return vects[static_cast<int>(params[1])].at(vects_size[static_cast<int>(params[1])] - 1) + 1;
}

cell Natives::Vector_First(AMX* amx, cell* params) {
    if (static_cast<int>(params[1]) < 0 || static_cast<int>(params[1]) > vectorID || vects_size[static_cast<int>(params[1])] < 1)
        return -1;

    if (debugging) logprintf("[SA:MP Vectors Debug] vector first size: %d | element at index 0: %d.", vects_size[static_cast<int>(params[1])], vects[static_cast<int>(params[1])].at(0));
    return vects[static_cast<int>(params[1])].at(0);
}

cell Natives::Vector_Last(AMX* amx, cell* params) {
    if (static_cast<int>(params[1]) < 0 || static_cast<int>(params[1]) > vectorID || vects_size[static_cast<int>(params[1])] < 1)
        return -1;

    if (debugging) logprintf("[SA:MP Vectors Debug] vector last size: %d | element at index %d: %d.", vects_size[static_cast<int>(params[1])], vects_size[static_cast<int>(params[1])] - 1, vects[static_cast<int>(params[1])].at(vects_size[static_cast<int>(params[1])] - 1));
    return vects[static_cast<int>(params[1])].at(vects_size[static_cast<int>(params[1])] - 1);
}

cell Natives::Vector_Next(AMX* amx, cell* params) {
    if (static_cast<int>(params[1]) < 0 || static_cast<int>(params[1]) > vectorID)
        return -1;

    if (debugging) logprintf("[SA:MP Vectors Debug] vector valid for using vector_next: %d.", vects_size[static_cast<int>(params[1])] >= 2);
    if (vects_size[static_cast<int>(params[1])] < 2)
        return -1;

    int index = -1;

    if (std::is_sorted(vects[static_cast<int>(params[1])].begin(), vects[static_cast<int>(params[1])].end())) {
        auto i = std::lower_bound(vects[static_cast<int>(params[1])].begin(), vects[static_cast<int>(params[1])].end(), static_cast<int>(params[2]));
        if (!(i != vects[static_cast<int>(params[1])].end() && !(static_cast<int>(params[2]) < *i)))
            return debugging ? logprintf("[SA:MP Vectors Debug] A next value cannot be shown because is the last element from the vector."), -1 : -1;
        index = std::distance(vects[static_cast<int>(params[1])].begin(), i);
    }
    else {
        auto i = std::find(vects[static_cast<int>(params[1])].begin(), vects[static_cast<int>(params[1])].end(), static_cast<int>(params[2]));
        if(i == vects[static_cast<int>(params[1])].end())
            return debugging ? logprintf("[SA:MP Vectors Debug] A next value cannot be shown because is the last element from the vector."), -1 : -1;

        index = i - vects[static_cast<int>(params[1])].begin();
    }

    return debugging ? logprintf("[SA:MP Vectors Debug] Showing up the element %d.", vects[static_cast<int>(params[1])].at(index + 1)), vects[static_cast<int>(params[1])].at(index + 1) : vects[static_cast<int>(params[1])].at(index + 1);
}

cell Natives::Vector_Prev(AMX* amx, cell* params) {
    if (static_cast<int>(params[1]) < 0 || static_cast<int>(params[1]) > vectorID)
        return -1;

    if (vects_size[static_cast<int>(params[1])] < 2)
        return -1;

    int index = -1;

    if (std::is_sorted(vects[static_cast<int>(params[1])].begin(), vects[static_cast<int>(params[1])].end())) {
        auto i = std::lower_bound(vects[static_cast<int>(params[1])].begin(), vects[static_cast<int>(params[1])].end(), static_cast<int>(params[2]));
        if (!(i != vects[static_cast<int>(params[1])].end() && !(static_cast<int>(params[2]) < *i)))
            return debugging ? logprintf("[SA:MP Vectors Debug] A previvous value cannot be shown because is the first element from the vector."), -1 : -1;
        index = std::distance(vects[static_cast<int>(params[1])].begin(), i);
    }
    else {
        auto i = std::find(vects[static_cast<int>(params[1])].begin(), vects[static_cast<int>(params[1])].end(), static_cast<int>(params[2]));
        if (i == vects[static_cast<int>(params[1])].end())
            return debugging ? logprintf("[SA:MP Vectors Debug] A previvous value cannot be shown because is the first element from the vector."), -1 : -1;

        index = i - vects[static_cast<int>(params[1])].begin();
    }

    return debugging ? logprintf("[SA:MP Vectors Debug] Showing up the element %d.", vects[static_cast<int>(params[1])].at(index - 1)), vects[static_cast<int>(params[1])].at(index - 1) : vects[static_cast<int>(params[1])].at(index - 1);
}

cell Natives::Vector_Create(AMX* amx, cell* params) {
    std::vector<int> a;

    vects.push_back(a);
    vects_size.push_back(0);

    if (debugging) logprintf("[SA:MP Vectors Debug] Creating up the vector with id %d.", vectorID + 1);

    return static_cast<int>(++vectorID);
}

cell Natives::Vector_DebugMode(AMX* amx, cell* params) {
    if(static_cast<bool>(params[1]) == debugging)
        logprintf("[SA:MP Vectors Debug] Debugging mode is already %s.", debugging == false ? "disabled" : "enabled");

    debugging = static_cast<bool>(params[1]);
    if (debugging) logprintf("[SA:MP Vectors Debug] Debugging mode has been enables.");
    else logprintf("[SA:MP Vectors Debug] Debugging mode has been disabled.");
    return 1;
}
