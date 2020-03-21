#pragma once

#include "event-keyboard.h"
#include "event-mousemotion.h"

enum EventType{
    NONE = 0,
    EVENT_QUIT,
    EVENT_KEYDOWN, EVENT_KEYUP,
    EVENT_MOUSEMOTION, EVENT_MOUSEDOWN, EVENT_MOUSEUP
};

struct Event{
    EventType type;
    EventKeyboard key;
    EventMouseMotion motion;
};