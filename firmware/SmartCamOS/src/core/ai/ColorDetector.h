#ifndef SMARTCAM_COLOR_DETECTOR_H
#define SMARTCAM_COLOR_DETECTOR_H

#include <Arduino.h>
#include "../../sdk/interfaces/IDetector.h"
#include "../vision/VisionEngine.h"

struct ColorDetectorConfig {
    ColorRange range;
    int minBlobArea;
    int maxBlobs;
    const char* label;

    ColorDetectorConfig()
        : minBlobArea(50)
        , maxBlobs(8)
        , label("color") {
        range.hMin = 0; range.hMax = 255;
        range.sMin = 30; range.sMax = 255;
        range.vMin = 30; range.vMax = 255;
    }
};

class ColorDetector : public IDetector {
public:
    ColorDetector();
    explicit ColorDetector(const ColorDetectorConfig& config);
    ~ColorDetector();

    bool loadModel() override;
    bool runInference(uint8_t* frame, int width, int height, size_t size = 0) override;
    int getDetections(Detection* out, int maxCount) override;
    void unloadModel() override;

    void setConfig(const ColorDetectorConfig& config);
    ColorDetectorConfig getConfig() const;

private:
    ColorDetectorConfig m_config;
    Detection m_results[8];
    int m_resultCount;
    VisionEngine* m_vision;
    bool m_loaded;
};

#endif
