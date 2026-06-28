#ifndef SMARTCAM_PERSON_DETECTOR_H
#define SMARTCAM_PERSON_DETECTOR_H

#include <Arduino.h>
#include "../../sdk/interfaces/IDetector.h"

struct PersonDetectorConfig {
    float confidenceThreshold;
    int inputWidth;
    int inputHeight;
    int tensorArenaSize;
    const char* label;

    PersonDetectorConfig()
        : confidenceThreshold(0.5f)
        , inputWidth(96)
        , inputHeight(96)
        , tensorArenaSize(120 * 1024)
        , label("person") {}
};

class PersonDetector : public IDetector {
public:
    PersonDetector();
    explicit PersonDetector(const PersonDetectorConfig& config);
    ~PersonDetector();

    bool loadModel() override;
    bool runInference(uint8_t* frame, int width, int height) override;
    int getDetections(Detection* out, int maxCount) override;
    void unloadModel() override;

    void setConfig(const PersonDetectorConfig& config);
    PersonDetectorConfig getConfig() const;

private:
    PersonDetectorConfig m_config;
    Detection m_results[8];
    int m_resultCount;
    bool m_loaded;
    uint8_t* m_tensorArena;
    uint8_t* m_inputBuffer;

    void preprocessFrame(uint8_t* frame, int width, int height);
    int argmax(const float* scores, int n) const;
    float sigmoid(float x) const;
};

#endif
