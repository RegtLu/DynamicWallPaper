//
// Created by Regt on 25-9-17.
//

#include "Render.h"

#include <algorithm>
#include <iostream>
#include <unordered_set>

#include "../KeyboardEvent/Hook.h"
#include "windows.h"
#include "../KeyboardEvent/EventDef.h"

void DrawCircle(SDL_Renderer *renderer, int centreX, int centreY, int radius) {
    const int32_t diameter = (radius * 2);

    int32_t x = (radius - 1);
    int32_t y = 0;
    int32_t tx = 1;
    int32_t ty = 1;
    int32_t error = (tx - diameter);

    while (x >= y) {
        SDL_RenderPoint(renderer, centreX + x, centreY - y);
        SDL_RenderPoint(renderer, centreX + x, centreY + y);
        SDL_RenderPoint(renderer, centreX - x, centreY - y);
        SDL_RenderPoint(renderer, centreX - x, centreY + y);
        SDL_RenderPoint(renderer, centreX + y, centreY - x);
        SDL_RenderPoint(renderer, centreX + y, centreY + x);
        SDL_RenderPoint(renderer, centreX - y, centreY - x);
        SDL_RenderPoint(renderer, centreX - y, centreY + x);

        if (error <= 0) {
            ++y;
            error += ty;
            ty += 2;
        }

        if (error > 0) {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
    }
}

void WallPaperWindow::InitRender() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

void WallPaperWindow::PumpMouseQueue(int &r, int &g, int &b, int &x, int &y) {
    static bool leftDown = false;
    int latestX = x, latestY = y;
    int changCount = 0;

    MouseData data;
    while (em->pop_v(data)) {
        int evt = data.event;
        latestX = data.x;
        latestY = data.y;
        switch (evt) {
            case WM_LBUTTONDOWN:
                if (!leftDown) {
                    changCount += 1;
                    leftDown = true;
                }
                break;
            case WM_LBUTTONUP:
                leftDown = false;
                break;
            case WM_MOUSEMOVE:
                break;
            default:
                break;
        }
    }
    if (isForeground()) {
        for (int i = 0; i < changCount; i++) {
            int tmp = r;
            r = g;
            g = b;
            b = tmp;
        }
        x = latestX;
        y = latestY;
    }
}

void WallPaperWindow::RenderLoop() {
    int x, y;
    while (!Quit()) {
        PumpMouseQueue(r, g, b, x, y);
        if (pts.size() >= circleCount) {
            pts.pop_front();
        }
        pts.emplace_back(x, y);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, r, g, b, 255);
        std::pair<int, int> last = pts[circleCount-1];
        for (int i = circleCount-1; i > -1; i--) {
            if (last != pts[i]) {
                DrawCircle(renderer, pts[i].first, pts[i].second, 30 - 3 * i);
            }
            last = pts[i];
        }
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }
}
