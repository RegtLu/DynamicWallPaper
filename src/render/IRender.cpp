//
// Created by Regt on 25-9-16.
//

#include "IRender.h"
#include "windows.h"
#include <iostream>

HWND GetWorkerW() {
    HWND workerw = nullptr;
    EnumWindows([](HWND hwnd, LPARAM lParam) -> BOOL {
        if (FindWindowEx(hwnd, nullptr, "SHELLDLL_DefView", nullptr)) {
            HWND *pWorkerW = reinterpret_cast<HWND *>(lParam);
            *pWorkerW = FindWindowEx(nullptr, hwnd, "WorkerW", nullptr);
            return false;
        }
        return true;
    }, reinterpret_cast<LPARAM>(&workerw));
    return workerw;
}

bool ISDLWindows::Quit() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) return true;
    }
    return false;
}

bool ISDLWindows::isForeground() {
    HWND hForeground = GetForegroundWindow();
    char str[1000];
    RealGetWindowClassA(hForeground, str, 1000);
    return (std::string(str) == "WorkerW");
}

ISDLWindows::ISDLWindows() {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "SDL_Init failed: " << SDL_GetError() << std::endl;
        return;
    }

    window = SDL_CreateWindow("Render", 0, 0, SDL_WINDOW_FULLSCREEN);

    if (!window) {
        std::cerr << "SDL_CreateWindow failed: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return;
    }

    renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer) {
        std::cerr << "SDL_CreateRenderer failed: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }

    SDL_PropertiesID prop = SDL_GetWindowProperties(window);
    HWND hwndDesktop = GetWorkerW();
    hwnd = static_cast<HWND>(SDL_GetPointerProperty(prop,SDL_PROP_WINDOW_WIN32_HWND_POINTER, nullptr));
    SetParent(hwnd, hwndDesktop);
}

ISDLWindows::~ISDLWindows() {
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    SDL_Quit();
}

void ISDLWindows::InitRender() {
    // SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    // SDL_RenderClear(renderer);
    // SDL_RenderPresent(renderer);
}

void ISDLWindows::RenderLoop() {
    // while (!Quit()) {
    //     DWORD code = 0;
    //     em->pop_v(code);
    //
    //     if (code == WM_LBUTTONDOWN) {
    //         int tmp = r;
    //         r = g;
    //         g = b;
    //         b = tmp;
    //         SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    //         SDL_RenderClear(renderer);
    //         SDL_RenderPresent(renderer);
    //     }
    //     SDL_Delay(16);
    // }
}
