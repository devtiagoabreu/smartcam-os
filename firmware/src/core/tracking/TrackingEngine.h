#ifndef SMARTCAM_TRACKING_ENGINE_H
#define SMARTCAM_TRACKING_ENGINE_H

#include <Arduino.h>
#include "../../sdk/interfaces/SmartCamModule.h"
#include "../../sdk/interfaces/ITrackingStrategy.h"
#include "../../sdk/interfaces/IDetector.h"

struct TrackingConfig {
    float deadZone = 0.05f;
    float maxSpeed = 100.0f;
    float kp = 1.0f;
    float ki = 0.0f;
    float kd = 0.1f;
    int targetLostTimeoutMs = 2000;
    int searchHomeDelayMs = 5000;
};

class TrackingEngine : public SmartCamModule {
public:
    bool begin() override;
    void update() override;
    bool stop() override;

    bool setTarget(const Detection& detection);
    bool clearTarget();
    bool isTargetLocked() const;
    float getCorrectionAngle() const;
    bool setConfig(const TrackingConfig& config);
    TrackingConfig getConfig() const;
    bool setStrategy(ITrackingStrategy* strategy);

    const char* name() const override { return "TrackingEngine"; }
};

#endif
