#ifndef SMARTCAM_SYSTEM_STATE_H
#define SMARTCAM_SYSTEM_STATE_H

#include <Arduino.h>

enum class SystemState : uint8_t {
    Boot = 0,
    Init = 1,
    Ready = 2,
    Running = 3,
    Error = 4,
    OtaUpdate = 5,
    LowPower = 6,
    Rebooting = 7,
    Fault = 8
};

const char* systemStateToString(SystemState state);

#endif
