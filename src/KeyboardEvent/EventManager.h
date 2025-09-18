//
// Created by Regt on 25-9-16.
//

#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H
#include <condition_variable>
#include <mutex>
#include <queue>

struct MouseData;

class EventManager {
    std::queue<MouseData> events;
    std::mutex queueMutex;
    std::condition_variable notify;

public:
    void push(MouseData arg);

    MouseData pop();
    bool pop_v(MouseData& in);
};

#endif //EVENTMANAGER_H
