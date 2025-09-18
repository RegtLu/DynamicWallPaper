//
// Created by Regt on 25-9-16.
//

#include <condition_variable>
#include <Windows.h>
#include <mutex>
#include <queue>


#include "EventManager.h"

#include <iostream>

#include "Hook.h"

std::queue<MouseData> events;
std::mutex queueMutex;
std::condition_variable notify;

void EventManager::push(MouseData arg) { {
        std::lock_guard<std::mutex> lock(queueMutex);
        events.push(arg);
    }
    notify.notify_one();
}

bool EventManager::pop_v(MouseData &in) {
    std::unique_lock<std::mutex> lock(queueMutex);
    if (events.empty()) {
        return false;
    }
    in = events.front();
    events.pop();
    return true;
}
