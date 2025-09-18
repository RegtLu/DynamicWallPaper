//
// Created by Regt on 25-9-16.
//

#ifndef IRENDER_H
#define IRENDER_H

#include <SDL.h>
#include <windef.h>

#include "../KeyboardEvent/EventManager.h"

extern EventManager *em;

class ISDLWindows {
protected:
    int r = 0, g = 0, b = 255;
    SDL_Renderer* renderer = nullptr;
    SDL_Window* window = nullptr;
    HWND hwnd;

public:
    ISDLWindows();

    static bool Quit();

    static bool isForeground();

    virtual ~ISDLWindows();

    virtual void InitRender();
    virtual void RenderLoop();
};

#endif // IRENDER_H
