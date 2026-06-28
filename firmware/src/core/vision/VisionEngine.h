#ifndef SMARTCAM_VISION_ENGINE_H
#define SMARTCAM_VISION_ENGINE_H

#include <Arduino.h>
#include "../../sdk/interfaces/SmartCamModule.h"
#include "../../sdk/interfaces/IFrameProcessor.h"

struct Blob {
    float x;
    float y;
    float width;
    float height;
    float area;
    uint8_t meanR;
    uint8_t meanG;
    uint8_t meanB;
};

struct ColorRange {
    uint8_t hMin;
    uint8_t hMax;
    uint8_t sMin;
    uint8_t sMax;
    uint8_t vMin;
    uint8_t vMax;
};

class VisionEngine : public SmartCamModule {
public:
    bool begin() override;
    void update() override;
    bool stop() override;

    bool toGrayscale(Frame& frame);
    bool toHsv(Frame& frame);
    bool threshold(Frame& frame, uint8_t min, uint8_t max);
    bool colorFilter(Frame& frame, const ColorRange& range);
    int findBlobs(const Frame& frame, Blob* out, int maxCount);
    bool drawOverlay(Frame& frame, const Blob& blob);

    const char* name() const override { return "VisionEngine"; }
};

#endif
