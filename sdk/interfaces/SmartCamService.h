#ifndef SMARTCAM_SERVICE_H
#define SMARTCAM_SERVICE_H

#include "SmartCamObject.h"

class SmartCamService : public SmartCamObject {
public:
    virtual bool init() = 0;
    virtual void tick() = 0;
    virtual bool deinit() = 0;
    virtual bool isRunning() const = 0;
};

#endif
