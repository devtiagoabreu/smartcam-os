#ifndef SMARTCAM_OBJECT_H
#define SMARTCAM_OBJECT_H

#include <Arduino.h>

class SmartCamObject {
public:
    virtual ~SmartCamObject() = default;

    virtual const char* name() const = 0;
};

#endif
