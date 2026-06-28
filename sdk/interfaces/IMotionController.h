#ifndef IMOTION_CONTROLLER_H
#define IMOTION_CONTROLLER_H

#include <Arduino.h>

struct AxisConfig {
    int stepPin;
    int dirPin;
    int enablePin;
    int homePin;
    float stepsPerDegree;
    float maxSpeed;
    float acceleration;
    int microSteps;
};

struct AxisState {
    long currentPosition;
    float currentSpeed;
    bool isHomed;
    bool isMoving;
    bool isEnabled;
};

class IMotionController {
public:
    virtual ~IMotionController() = default;
    virtual bool init(const AxisConfig& config) = 0;
    virtual bool moveTo(long targetSteps) = 0;
    virtual bool moveRelative(long steps) = 0;
    virtual bool stop() = 0;
    virtual bool home() = 0;
    virtual bool setSpeed(float speed) = 0;
    virtual bool setAcceleration(float accel) = 0;
    virtual AxisState getState() const = 0;
    virtual bool isBusy() const = 0;
};

#endif
