#ifndef SMARTCAM_LOGGER_SERVICE_H
#define SMARTCAM_LOGGER_SERVICE_H

#include <Arduino.h>
#include "../../sdk/interfaces/SmartCamService.h"

enum class LogLevel : uint8_t {
    Debug = 0,
    Info = 1,
    Warning = 2,
    Error = 3,
    Critical = 4,
    None = 5
};

struct LogEntry {
    unsigned long timestamp;
    LogLevel level;
    char module[16];
    char message[64];
};

class LoggerService : public SmartCamService {
public:
    bool init() override;
    void tick() override;
    bool deinit() override;
    bool isRunning() const override;

    void log(LogLevel level, const char* module, const char* format, ...);
    void debug(const char* module, const char* message);
    void info(const char* module, const char* message);
    void warning(const char* module, const char* message);
    void error(const char* module, const char* message);
    void critical(const char* module, const char* message);

    bool setLevel(LogLevel level);
    LogLevel getLevel() const;
    bool setRingBufferSize(int size);
    int getEntryCount() const;
    bool getEntries(LogEntry* out, int maxCount, int& outCount) const;
    bool exportToFile(const char* path);

    const char* name() const override { return "LoggerService"; }
};

#endif
