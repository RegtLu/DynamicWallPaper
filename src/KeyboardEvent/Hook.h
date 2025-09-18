//
// Created by Regt on 25-9-16.
//

#ifndef HOOK_H
#define HOOK_H
#include "EventManager.h"

#include "windows.h"

extern EventManager *em;


struct MouseData {
    WPARAM wParam;
    POINT  pt;
};

void ProcessHook();
#endif //HOOK_H
