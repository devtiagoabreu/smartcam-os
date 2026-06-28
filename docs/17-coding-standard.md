# SmartCam Platform — Coding Standard

## Objective

Define the official coding standard for all SmartCam Platform development. Every source file across the firmware, SDK, tools, and tests must conform to this standard.

## Scope

This document covers naming conventions, file organization, formatting rules, documentation requirements, and programming patterns for the C++17 codebase targeting the Arduino ESP32 framework.

## Architecture

The coding standard enforces consistent code organization across all modules. Each module follows the same structure:

```text
module/
    module_service.h
    module_service.cpp
    module_config.h
    module_config.cpp
```

## Components

### Naming Conventions

#### Classes and Structs

```cpp
class CameraEngine {};         // PascalCase
struct Frame {};               // PascalCase
enum class CameraState {};     // PascalCase
```

#### Methods and Functions

```cpp
void captureFrame();           // camelCase
int getFrameCount();           // camelCase
bool isRunning();              // camelCase - boolean prefix
```

#### Variables

```cpp
int frameCount;                // camelCase
uint8_t* frameBuffer;          // camelCase, no prefix
bool isEnabled;                // camelCase with is/has/can prefix
```

#### Constants and Macros

```cpp
constexpr int MAX_FRAME_SIZE = 320 * 240 * 2;  // UPPER_CASE
const int DEFAULT_FPS = 20;                      // UPPER_CASE
```

#### File Names

```text
camera_engine.h               // snake_case
camera_engine.cpp             // snake_case
camera_settings.h             // snake_case
```

### File Organization

Every `.cpp` and `.h` file must follow this section order:

```cpp
// 1. License header
// 2. Includes (system, library, project)
// 3. Defines and constants
// 4. Local variables
// 5. Public methods
// 6. Private methods
// 7. Static callbacks
```

#### Include Order

```cpp
#include <Arduino.h>           // System libraries first
#include <WiFi.h>              // Library headers
#include <ESPAsyncWebServer.h>

#include "camera_engine.h"     // Project headers
#include "config.h"            // Local headers
```

#### Class Member Order

```cpp
class CameraEngine {
public:
    // Constructor, destructor
    // begin(), loop(), stop()
    // Public methods
    // Public static methods

protected:
    // protected methods

private:
    // Private methods
    // Member variables
};
```

### Formatting Rules

```cpp
// Braces: Allman style
if (condition)
{
    statement;
}

// Spaces inside parentheses
if (value > 10)

// 4-space indentation, no tabs
// Maximum line length: 120 characters

// Pointer alignment
uint8_t* buffer;          // * next to name
CameraEngine* engine;
```

## Fluxos

### Documentation Flow

Every public method requires Doxygen-style documentation:

```cpp
/**
 * Captures a single frame from the camera sensor.
 *
 * @param frame Reference to Frame struct to fill
 * @return Result::Ok on success, Result::Error on failure
 *
 * The frame buffer is allocated statically and reused.
 * This method blocks for up to frameTimeoutMs ms.
 */
Result captureFrame(Frame& frame);
```

## Interfaces

### Error Handling

```cpp
// Use typed errors, never raw bool
enum class Result {
    Ok,
    Error,
    Timeout,
    InvalidParameter,
    Busy,
    NotInitialized,
    HardwareFailure
};

// Always check return values
Result result = camera.begin();
if (result != Result::Ok)
{
    logger.error("Camera", "Init failed: %d", result);
}
```

### Logging

```cpp
// Never use Serial.println()
logger.trace("Module", "Detail message");
logger.info("Module", "Operation completed");
logger.warning("Module", "Potential issue: %s", detail);
logger.error("Module", "Failure: %s", reason);

// Log levels
// TRACE (0) - Detailed debug
// DEBUG (1) - General debug
// INFO  (2) - Normal operations
// WARN  (3) - Potential issues
// ERROR (4) - Operation failures
// FATAL (5) - Critical errors
```

### Memory Management

```cpp
// Prefer static allocation
static uint8_t frameBuffer[320 * 240 * 2];

// Avoid dynamic allocation
// Avoid String concatenation in loops
// Use constexpr for compile-time constants

constexpr int kMaxDetections = 16;
```

## Estrutura de Pastas

```text
firmware/
    SmartCamOS.ino
    config.h
    core/
        camera/
            camera_engine.h
            camera_engine.cpp
        vision/
            vision_engine.h
            vision_engine.cpp
        tracking/
            tracking_engine.h
            tracking_engine.cpp
        motion/
            motion_engine.h
            motion_engine.cpp
        ai/
            ai_engine.h
            ai_engine.cpp
    network/
        network_service.h
        network_service.cpp
    storage/
        storage_service.h
        storage_service.cpp
    logger/
        logger_service.h
        logger_service.cpp
    api/
        api_service.h
        api_service.cpp
    config/
        config_manager.h
        config_manager.cpp
    dashboard/
        dashboard_server.h
        dashboard_server.cpp
    utils/
        utils.h
        utils.cpp
```

## Responsabilidades

| Rule | Responsibility |
|------|----------------|
| Naming | All developers must follow PascalCase/camelCase/snake_case rules |
| File Structure | Every file follows the defined section order |
| Error Handling | All operations return Result type, never raw bool |
| Logging | No Serial.println — only Logger service |
| Memory | No `new`/`delete` — prefer static allocation |
| Documentation | Public API methods require Doxygen comments |
| Formatting | Allman braces, 4-space indent, 120-char lines |

## Requisitos

| ID | Requirement |
|----|-------------|
| COD-001 | All files use `#pragma once` instead of `#ifndef` |
| COD-002 | All enum types use `enum class` |
| COD-003 | No `delay()` in production code |
| COD-004 | No `Serial.println()` in production code |
| COD-005 | No hardcoded GPIO numbers — always via config.h |
| COD-006 | No `String` concatenation in performance-critical paths |
| COD-007 | Functions default to 30 lines max, hard limit 80 lines |
| COD-008 | Classes default to 300 lines max |
| COD-009 | Single responsibility per class |
| COD-010 | All pointer dereferences check for nullptr |
| COD-011 | All `TODO` and `FIXME` comments include ticket reference |
| COD-012 | Code compiles without warnings under Arduino IDE 2.x |

## Considerações

This coding standard prioritizes readability and maintainability over brevity. The Allman brace style and explicit error handling increase verbosity but reduce ambiguity during code review. The static memory policy is driven by ESP32-S3 constraints — dynamic allocation in interrupt context or real-time loops can cause unpredictable behavior. All new modules must pass a code review checklist verifying compliance with every rule in this document.

## Próximos documentos relacionados

- [10-sdk-framework.md](10-sdk-framework.md) — SDK conventions and class hierarchy
- [18-test-plan.md](18-test-plan.md) — Code review and testing criteria
- [19-github-repository.md](19-github-repository.md) — PR template with coding standard checklist
