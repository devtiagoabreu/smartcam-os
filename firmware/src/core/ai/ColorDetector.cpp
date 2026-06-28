#include "ColorDetector.h"
#include <string.h>
#include <esp_heap_caps.h>

ColorDetector::ColorDetector()
    : m_resultCount(0)
    , m_vision(nullptr)
    , m_loaded(false) {
}

ColorDetector::ColorDetector(const ColorDetectorConfig& config)
    : m_config(config)
    , m_resultCount(0)
    , m_vision(nullptr)
    , m_loaded(false) {
}

ColorDetector::~ColorDetector() {
    unloadModel();
}

bool ColorDetector::loadModel() {
    if (m_loaded) return true;
    m_loaded = true;
    return true;
}

bool ColorDetector::runInference(uint8_t* frame, int width, int height) {
    if (!m_loaded || !frame) return false;

    if (!m_vision) {
        m_vision = new VisionEngine();
        if (!m_vision || !m_vision->begin()) {
            delete m_vision;
            m_vision = nullptr;
            return false;
        }
    }

    Frame f;
    f.data = frame;
    f.width = width;
    f.height = height;
    f.bytesPerPixel = 2;

    if (!m_vision->colorFilter(f, m_config.range)) return false;

    Blob blobs[16];
    int blobCount = m_vision->findBlobs(f, blobs, 16);

    m_resultCount = 0;
    for (int i = 0; i < blobCount && m_resultCount < 8; i++) {
        if (blobs[i].area < m_config.minBlobArea) continue;

        Detection& d = m_results[m_resultCount];
        d.x = blobs[i].x / width;
        d.y = blobs[i].y / height;
        d.width = blobs[i].width / width;
        d.height = blobs[i].height / height;
        d.confidence = blobs[i].area / (width * height);
        d.classId = 0;
        strncpy(d.label, m_config.label, sizeof(d.label) - 1);
        d.label[sizeof(d.label) - 1] = '\0';
        m_resultCount++;
    }

    return true;
}

int ColorDetector::getDetections(Detection* out, int maxCount) {
    if (!out || maxCount <= 0) return 0;
    int count = m_resultCount < maxCount ? m_resultCount : maxCount;
    for (int i = 0; i < count; i++) {
        out[i] = m_results[i];
    }
    return count;
}

void ColorDetector::unloadModel() {
    if (m_vision) {
        m_vision->stop();
        delete m_vision;
        m_vision = nullptr;
    }
    m_resultCount = 0;
    m_loaded = false;
}

void ColorDetector::setConfig(const ColorDetectorConfig& config) {
    m_config = config;
}

ColorDetectorConfig ColorDetector::getConfig() const {
    return m_config;
}
