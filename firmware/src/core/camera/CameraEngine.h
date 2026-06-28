#ifndef SMARTCAM_CAMERA_ENGINE_H
#define SMARTCAM_CAMERA_ENGINE_H

#include <Arduino.h>
#include "../../sdk/interfaces/SmartCamModule.h"
#include "../../sdk/interfaces/IFrameProcessor.h"

struct CameraConfig {
    int xclkFreq = 20000000;
    int frameSize = 8;
    int jpegQuality = 12;
    int fbCount = 2;
    int gmacSize = 0;
};

class CameraEngine : public SmartCamModule {
public:
    bool begin() override;
    void update() override;
    bool stop() override;

    bool startStream();
    bool stopStream();
    bool setConfig(const CameraConfig& config);
    CameraConfig getConfig() const;
    bool captureFrame();
    bool addProcessor(IFrameProcessor* processor);
    bool removeProcessor(IFrameProcessor* processor);
    int getFps() const;
    bool isStreaming() const;

    const char* name() const override { return "CameraEngine"; }
};

#endif
