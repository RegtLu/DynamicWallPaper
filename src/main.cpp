//
// Created by Regt on 25-9-16.
//

#include "KeyboardEvent/EventManager.h"
#include "KeyboardEvent/Hook.h"
#include "render/Render.h"
EventManager *em;


int main() {
    em = new EventManager();
    std::thread hookThread(ProcessHook);
    hookThread.detach();
    std::shared_ptr<ISDLWindows> window = std::make_shared<WallPaperWindow>();
    window->InitRender();
    window->RenderLoop();
}
