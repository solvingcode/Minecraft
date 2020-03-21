#pragma once

#include <queue>
#include "event.h"

class EventsPool{
public:
    void Push(Event* event);
    EventsPool();
    Event* PollEvent();
private:
    std::queue<Event*> events;
};