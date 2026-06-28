#ifndef IEVENT_LISTENER_H
#define IEVENT_LISTENER_H

#include "Event.h"

class IEventListener {
public:
    virtual ~IEventListener() = default;
    virtual void onEvent(const Event& event) = 0;
};

#endif
