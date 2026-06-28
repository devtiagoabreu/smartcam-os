#ifndef SMARTCAM_EVENT_H
#define SMARTCAM_EVENT_H

#include <Arduino.h>

struct Event {
    const char* type;
    void* data;
    size_t dataSize;

    Event() : type(nullptr), data(nullptr), dataSize(0) {}

    Event(const char* t, void* d = nullptr, size_t s = 0)
        : type(t), data(d), dataSize(s) {}
};

#endif
