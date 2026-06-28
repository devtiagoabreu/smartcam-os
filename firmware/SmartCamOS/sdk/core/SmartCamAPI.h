#ifndef SMARTCAM_API_H
#define SMARTCAM_API_H

#include <Arduino.h>
#include "../interfaces/SmartCamObject.h"

class SmartCamAPI {
public:
    static bool publishEvent(const char* type, void* data = nullptr, size_t size = 0);
    static void logInfo(const char* module, const char* message);
    static void logError(const char* module, const char* message);
    static void logWarning(const char* module, const char* message);
    static void logDebug(const char* module, const char* message);
    static unsigned long getTimestamp();
    static size_t getFreeHeap();
    static size_t getFreePsram();
    static int getCpuFreq();

private:
    SmartCamAPI() = default;
};

#endif
