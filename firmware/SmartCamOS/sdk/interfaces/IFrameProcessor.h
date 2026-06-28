#ifndef IFRAME_PROCESSOR_H
#define IFRAME_PROCESSOR_H

#include <Arduino.h>

struct Frame {
    uint8_t* data;
    int width;
    int height;
    int bytesPerPixel;
    size_t size;
    unsigned long timestamp;
};

class IFrameProcessor {
public:
    virtual ~IFrameProcessor() = default;
    virtual bool process(Frame& frame) = 0;
    virtual const char* processorName() const = 0;
};

#endif
