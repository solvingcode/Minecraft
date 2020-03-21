#include "events-pool.h"

EventsPool::EventsPool(){}

void EventsPool::Push(Event* event){
    events.push(event);
}

Event* EventsPool::PollEvent(){
    if(!events.empty()){
        Event* event = events.front();
        events.pop();
        return event;
    }
    return nullptr;
}