#ifndef SMARTCAM_RESULT_H
#define SMARTCAM_RESULT_H

#include <Arduino.h>

enum class ResultCode : uint8_t {
    Ok = 0,
    Error = 1,
    InvalidParam = 2,
    NotInitialized = 3,
    AlreadyInitialized = 4,
    Timeout = 5,
    OutOfMemory = 6,
    NotFound = 7,
    Busy = 8,
    HardwareError = 9,
    NotImplemented = 10
};

struct Result {
    ResultCode code;
    char message[64];

    Result() : code(ResultCode::Ok) { message[0] = '\0'; }

    Result(ResultCode c, const char* msg = "")
        : code(c) {
        strncpy(message, msg, sizeof(message) - 1);
        message[sizeof(message) - 1] = '\0';
    }

    bool isOk() const { return code == ResultCode::Ok; }
    bool isError() const { return code != ResultCode::Ok; }
};

#define RETURN_OK() return Result(ResultCode::Ok)
#define RETURN_ERROR(msg) return Result(ResultCode::Error, msg)
#define RETURN_IF_ERROR(expr) do { Result _r = (expr); if (_r.isError()) return _r; } while(0)

#endif
