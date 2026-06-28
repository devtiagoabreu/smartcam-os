#ifndef SMARTCAM_APP_H
#define SMARTCAM_APP_H

#include "SmartCamModule.h"

class SmartCamApp : public SmartCamModule {
public:
    virtual void onEvent(const char* eventType, void* data) = 0;
    virtual bool isEnabled() const = 0;
    virtual void setEnabled(bool enabled) = 0;
};

#endif
