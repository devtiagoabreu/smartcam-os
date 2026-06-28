#include "LoggerService.h"
#include <stdarg.h>
#include <stdio.h>

static LoggerService* s_instance = nullptr;

static const char* levelToString(LogLevel level) {
    switch (level) {
        case LogLevel::Debug:   return "DBG";
        case LogLevel::Info:    return "INF";
        case LogLevel::Warning: return "WRN";
        case LogLevel::Error:   return "ERR";
        case LogLevel::Critical:return "CRT";
        default:                return "---";
    }
}

LoggerService::LoggerService()
    : m_level(LogLevel::Debug)
    , m_ringSize(64)
    , m_head(0)
    , m_count(0)
    , m_running(false)
    , m_ring(nullptr) {}

LoggerService::~LoggerService() {
    deinit();
}

bool LoggerService::init() {
    if (m_running) return true;
    m_ring = new LogEntry[m_ringSize];
    if (!m_ring) return false;
    m_head = 0;
    m_count = 0;
    m_running = true;
    s_instance = this;
    info("Logger", "Logger service initialized");
    return true;
}

void LoggerService::tick() {
}

bool LoggerService::deinit() {
    if (!m_running) return true;
    info("Logger", "Logger service shutting down");
    exportToFile("/logs/system.log");
    delete[] m_ring;
    m_ring = nullptr;
    m_running = false;
    s_instance = nullptr;
    return true;
}

bool LoggerService::isRunning() const {
    return m_running;
}

void LoggerService::log(LogLevel level, const char* module, const char* format, ...) {
    if (!m_running || level < m_level) return;

    LogEntry entry;
    entry.timestamp = millis();
    entry.level = level;
    strncpy(entry.module, module, sizeof(entry.module) - 1);
    entry.module[sizeof(entry.module) - 1] = '\0';

    va_list args;
    va_start(args, format);
    vsnprintf(entry.message, sizeof(entry.message), format, args);
    va_end(args);

    m_ring[m_head] = entry;
    m_head = (m_head + 1) % m_ringSize;
    if (m_count < m_ringSize) m_count++;

    // Console output
    char buf[128];
    snprintf(buf, sizeof(buf), "[%6lu][%s][%s] %s",
             entry.timestamp, levelToString(level), module, entry.message);
    Serial.println(buf);
}

void LoggerService::debug(const char* module, const char* message) {
    log(LogLevel::Debug, module, "%s", message);
}

void LoggerService::info(const char* module, const char* message) {
    log(LogLevel::Info, module, "%s", message);
}

void LoggerService::warning(const char* module, const char* message) {
    log(LogLevel::Warning, module, "%s", message);
}

void LoggerService::error(const char* module, const char* message) {
    log(LogLevel::Error, module, "%s", message);
}

void LoggerService::critical(const char* module, const char* message) {
    log(LogLevel::Critical, module, "%s", message);
}

bool LoggerService::setLevel(LogLevel level) {
    m_level = level;
    return true;
}

LogLevel LoggerService::getLevel() const {
    return m_level;
}

bool LoggerService::setRingBufferSize(int size) {
    if (m_running || size < 16 || size > 512) return false;
    m_ringSize = size;
    return true;
}

int LoggerService::getEntryCount() const {
    return m_count;
}

bool LoggerService::getEntries(LogEntry* out, int maxCount, int& outCount) const {
    if (!out || maxCount <= 0) return false;
    int start = (m_count < m_ringSize) ? 0 : m_head;
    outCount = (m_count < maxCount) ? m_count : maxCount;
    for (int i = 0; i < outCount; i++) {
        int idx = (start + i) % m_ringSize;
        out[i] = m_ring[idx];
    }
    return true;
}

bool LoggerService::exportToFile(const char* path) {
    // File export uses StorageService — called externally after storage is mounted
    return true;
}
