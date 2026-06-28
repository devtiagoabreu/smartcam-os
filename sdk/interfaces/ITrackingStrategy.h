#ifndef ITRACKING_STRATEGY_H
#define ITRACKING_STRATEGY_H

#include <Arduino.h>

struct Target {
    float x;
    float y;
    float width;
    float height;
    float velocityX;
    float velocityY;
    unsigned long lastSeen;
    int id;
};

class ITrackingStrategy {
public:
    virtual ~ITrackingStrategy() = default;
    virtual void selectTarget(Target* targets, int count) = 0;
    virtual float computeCorrection(float error, float dt) = 0;
    virtual void reset() = 0;
};

#endif
