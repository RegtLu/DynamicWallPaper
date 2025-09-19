//
// Created by Regt on 25-9-16.
//


#include "Hook.h"

#include <iostream>
#include <mutex>
#include <windows.h>

#include "EventManager.h"
#include "MinHookDLL.h"
#include "EventDef.h"

// 键盘
// LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
//     try {
//         if (nCode >= 0) {
//             KBDLLHOOKSTRUCT *keyBoard = reinterpret_cast<KBDLLHOOKSTRUCT *>(lParam);
//             em->push(keyBoard->vkCode);
//             //std::wcout << L"Key code: " << keyBoard->vkCode << std::endl;
//         }
//         return CallNextHookEx(NULL, nCode, wParam, lParam);
//     } catch (const std::exception &e) {
//         std::cerr << "ERROR: " << e.what() << std::endl;
//         return CallNextHookEx(NULL, nCode, wParam, lParam);
//     }
// }
// 鼠标
LRESULT CALLBACK LowLevelMouseProc(int nCode, WPARAM wParam, LPARAM lParam) {
    try {
        if (nCode >= 0) {
            auto *mouse = reinterpret_cast<MSLLHOOKSTRUCT *>(lParam);
            MouseData d{};
            d.event = static_cast<int>(wParam);
            d.x = mouse->pt.x;
            d.y = mouse->pt.y;
            em->push(d);
        }
        return CallNextHookEx(nullptr, nCode, wParam, lParam);
    } catch (const std::exception &e) {
        std::cerr << "ERROR: " << e.what() << std::endl;
        return CallNextHookEx(nullptr, nCode, wParam, lParam);
    }
}


void ProcessHook() {
    //HHOOK hook1 = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, NULL, 0);
    HHOOK hook2 = SetWindowsHookEx(WH_MOUSE_LL, LowLevelMouseProc, NULL, 0);
    //if (!hook1) throw std::runtime_error("SetWindowsHookEx WH_KEYBOARD_LL failed");
    if (!hook2) throw std::runtime_error("SetWindowsHookEx WH_MOUSE_LL failed");

    MSG message;
    while (GetMessage(&message, NULL, 0, 0)) {
        TranslateMessage(&message);
        DispatchMessage(&message);
    }
    //UnhookWindowsHookEx(hook1);
    UnhookWindowsHookEx(hook2);
}
