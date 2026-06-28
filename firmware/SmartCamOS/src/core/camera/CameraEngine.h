#ifndef SMARTCAM_CAMERA_ENGINE_H
#define SMARTCAM_CAMERA_ENGINE_H

#include <Arduino.h>
#include "../../sdk/interfaces/SmartCamModule.h"
#include "../../sdk/interfaces/IFrameProcessor.h"

struct CameraPins {
    int pwdn = -1;
    int reset = -1;
    int xclk = 10;
    int siod = 4;
    int sioc = 5;
    int d7 = 14;
    int d6 = 15;
    int d5 = 16;
    int d4 = 17;
    int d3 = 18;
    int d2 = 19;
    int d1 = 21;
    int d0 = 26;
    int vsync = 12;
    int href = 13;
    int pclk = 11;
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
