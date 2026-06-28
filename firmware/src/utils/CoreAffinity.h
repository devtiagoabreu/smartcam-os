#ifndef SMARTCAM_CORE_AFFINITY_H
#define SMARTCAM_CORE_AFFINITY_H

#include <Arduino.h>

enum class CoreAffinity : uint8_t {
    Core0 = 0,
    Core1 = 1,
    Any = 2
};

enum class TaskPriority : uint8_t {
    Idle = 0,
    Low = 1,
    Normal = 2,
    High = 3,
    Critical = 4
};

struct TaskConfig {
    const char* name;
    TaskPriority priority;
    CoreAffinity core;
    uint32_t stackSize;
    uint32_t periodMs;

    TaskConfig()
        : name("task"), priority(TaskPriority::Normal),
          core(CoreAffinity::Any), stackSize(4096), periodMs(10) {}
};

#endif
