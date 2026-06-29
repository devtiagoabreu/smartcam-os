#include "AIEngine.h"
#include <string.h>

// ============================================================
// InferenceEngine
// ============================================================

InferenceEngine::InferenceEngine()
    : m_modelData(nullptr)
    , m_modelSize(0)
    , m_loaded(false) {}

InferenceEngine::~InferenceEngine() {
    unloadModel();
}

bool InferenceEngine::loadModel(const uint8_t* modelData, size_t modelSize) {
    if (!modelData || modelSize == 0) return false;
    if (m_loaded) unloadModel();
    m_modelData = modelData;
    m_modelSize = modelSize;
    m_loaded = true;
    return true;
}

bool InferenceEngine::runInference(uint8_t* input, int width, int height) {
    if (!m_loaded || !input) return false;
    return true;
}

bool InferenceEngine::unloadModel() {
    m_modelData = nullptr;
    m_modelSize = 0;
    m_loaded = false;
    return true;
}

bool InferenceEngine::isModelLoaded() const {
    return m_loaded;
}

size_t InferenceEngine::getModelSize() const {
    return m_modelSize;
}

unsigned long InferenceEngine::getLastInferenceTime() const {
    return 0;
}

// ============================================================
// DetectionEngine
// ============================================================

DetectionEngine::DetectionEngine()
    : m_detectorCount(0)
    , m_activeIndex(-1)
    , m_running(false) {
    for (int i = 0; i < MAX_DETECTORS; i++) {
        m_detectors[i].detector = nullptr;
        m_detectors[i].name[0] = '\0';
        m_detectors[i].active = false;
    }
}

DetectionEngine::~DetectionEngine() {
    stop();
}

bool DetectionEngine::begin() {
    if (m_running) return true;
    m_running = true;
    return true;
}

void DetectionEngine::update() {
}

bool DetectionEngine::stop() {
    for (int i = 0; i < m_detectorCount; i++) {
        if (m_detectors[i].detector) {
            m_detectors[i].detector->unloadModel();
        }
    }
    m_detectorCount = 0;
    m_activeIndex = -1;
    m_running = false;
    return true;
}

bool DetectionEngine::registerDetector(const char* name, IDetector* detector) {
    if (!name || !detector || m_detectorCount >= MAX_DETECTORS) return false;

    for (int i = 0; i < m_detectorCount; i++) {
        if (strcmp(m_detectors[i].name, name) == 0) return false;
    }

    DetectorEntry& entry = m_detectors[m_detectorCount];
    strncpy(entry.name, name, sizeof(entry.name) - 1);
    entry.name[sizeof(entry.name) - 1] = '\0';
    entry.detector = detector;
    entry.active = false;
    m_detectorCount++;

    if (m_activeIndex < 0) {
        m_activeIndex = 0;
        entry.active = true;
        entry.detector->loadModel();
    }

    return true;
}

bool DetectionEngine::unregisterDetector(const char* name) {
    if (!name) return false;

    for (int i = 0; i < m_detectorCount; i++) {
        if (strcmp(m_detectors[i].name, name) == 0) {
            if (m_detectors[i].detector) {
                m_detectors[i].detector->unloadModel();
            }
            if (m_activeIndex == i) m_activeIndex = -1;
            for (int j = i; j < m_detectorCount - 1; j++) {
                m_detectors[j] = m_detectors[j + 1];
            }
            m_detectorCount--;
            return true;
        }
    }
    return false;
}

IDetector* DetectionEngine::getDetector(const char* name) {
    if (!name) return nullptr;
    for (int i = 0; i < m_detectorCount; i++) {
        if (strcmp(m_detectors[i].name, name) == 0) {
            return m_detectors[i].detector;
        }
    }
    return nullptr;
}

IDetector* DetectionEngine::getActiveDetector() const {
    if (m_activeIndex < 0 || m_activeIndex >= m_detectorCount) return nullptr;
    return m_detectors[m_activeIndex].detector;
}

bool DetectionEngine::setActiveDetector(const char* name) {
    if (!name) return false;

    for (int i = 0; i < m_detectorCount; i++) {
        if (strcmp(m_detectors[i].name, name) == 0) {
            if (m_activeIndex >= 0) {
                m_detectors[m_activeIndex].active = false;
            }
            m_activeIndex = i;
            m_detectors[i].active = true;
            m_detectors[i].detector->loadModel();
            return true;
        }
    }
    return false;
}

int DetectionEngine::getAllDetections(Detection* out, int maxCount) {
    if (!out || maxCount <= 0) return 0;

    int total = 0;
    for (int i = 0; i < m_detectorCount && total < maxCount; i++) {
        if (m_detectors[i].active && m_detectors[i].detector) {
            int n = m_detectors[i].detector->getDetections(out + total, maxCount - total);
            total += n;
        }
    }
    return total;
}
