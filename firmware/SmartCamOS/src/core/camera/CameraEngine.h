#ifndef SMARTCAM_CAMERA_ENGINE_H
#define SMARTCAM_CAMERA_ENGINE_H

#include <Arduino.h>
#include "../../sdk/interfaces/SmartCamModule.h"
#include "../../sdk/interfaces/IFrameProcessor.h"

struct CameraPins {
    int pwdn = 38;
    int reset = 39;
    int xclk = 11;
    int siod = 5;
    int sioc = 6;
    int d7 = 12;
    int d6 = 16;
    int d5 = 18;
    int d4 = 17;
    int d3 = 15;
    int d2 = 14;
    int d1 = 10;
    int d0 = 9;
    int vsync = 47;
    int href = 48;
    int pclk = 13;
};

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
    CameraPins getPins() const;
    bool setPins(const CameraPins& pins);
    bool captureFrame();
    bool getFrame(uint8_t** out, int* w, int* h);
    void returnFrame();
    const Frame* getCurrentFrame() const;
    bool addProcessor(IFrameProcessor* processor);
    bool removeProcessor(IFrameProcessor* processor);
    int getFps() const;
    bool isStreaming() const;
    bool isInitialized() const;

    const char* name() const override { return "CameraEngine"; }

private:
    CameraConfig m_config;
    CameraPins m_pins;
    Frame m_frame;
    bool m_initialized;
    bool m_streaming;
    int m_fps;
    unsigned long m_lastFrameTime;
    int m_frameCount;
    unsigned long m_fpsTimer;
    IFrameProcessor* m_processors[4];
    int m_processorCount;
    void* m_currentFb;

    void resetFrame();
    void updateFps();

public:
    CameraEngine();
    ~CameraEngine();
};

#endif
