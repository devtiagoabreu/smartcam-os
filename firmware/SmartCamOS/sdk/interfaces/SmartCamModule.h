#ifndef SMARTCAM_MODULE_H
#define SMARTCAM_MODULE_H

#include "SmartCamObject.h"

class SmartCamModule : public SmartCamObject {
public:
    virtual bool begin() = 0;
    virtual void update() = 0;
    virtual bool stop() = 0;
};

#endif
