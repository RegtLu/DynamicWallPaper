//
// Created by Regt on 25-9-17.
//

#ifndef RENDER_H
#define RENDER_H

#include "IRender.h"

class WallPaperWindow : public ISDLWindows {
    std::deque<std::pair<int,int>> pts;
public:
    WallPaperWindow(): ISDLWindows() {
    };

    ~WallPaperWindow() override = default;

    void InitRender() override;

    void RenderLoop() override;

    void PumpMouseQueue(int &r, int &g, int &b, int &x, int &);
};


#endif //RENDER_H
