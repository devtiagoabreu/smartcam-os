#ifndef SMARTCAM_EVENT_BUS_H
#define SMARTCAM_EVENT_BUS_H

#include <Arduino.h>
#include "../interfaces/IEventListener.h"
#include "../interfaces/Event.h"

class EventBus : public SmartCamObject {
public:
    static EventBus& instance();

    bool subscribe(const char* eventType, IEventListener* listener);
    bool unsubscribe(const char* eventType, IEventListener* listener);
    bool publish(const Event& event);
    void processQueue();

    const char* name() const override { return "EventBus"; }

private:
    EventBus() = default;
    ~EventBus() = default;
    EventBus(const EventBus&) = delete;
    EventBus& operator=(const EventBus&) = delete;
};

#endif
