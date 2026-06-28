#ifndef SMARTCAM_AI_ENGINE_H
#define SMARTCAM_AI_ENGINE_H

#include <Arduino.h>
#include "../../sdk/interfaces/SmartCamModule.h"
#include "../../sdk/interfaces/IDetector.h"

class InferenceEngine : public SmartCamObject {
public:
    bool loadModel(const uint8_t* modelData, size_t modelSize);
    bool runInference(uint8_t* input, int width, int height);
    bool unloadModel();
    bool isModelLoaded() const;
    size_t getModelSize() const;
    unsigned long getLastInferenceTime() const;

    const char* name() const override { return "InferenceEngine"; }
};

class DetectionEngine : public SmartCamModule {
public:
    bool begin() override;
    void update() override;
    bool stop() override;

    bool registerDetector(const char* name, IDetector* detector);
    bool unregisterDetector(const char* name);
    IDetector* getDetector(const char* name);
    bool setActiveDetector(const char* name);
    int getAllDetections(Detection* out, int maxCount);

    const char* name() const override { return "DetectionEngine"; }
};

#endif
