#ifndef SMARTCAM_CONFIG_MANAGER_H
#define SMARTCAM_CONFIG_MANAGER_H

#include <Arduino.h>
#include "../../sdk/interfaces/SmartCamService.h"

struct ConfigSchema {
    const char* key;
    const char* type;
    const char* defaultValue;
    const char* description;
};

class ConfigManager : public SmartCamService {
public:
    bool init() override;
    void tick() override;
    bool deinit() override;
    bool isRunning() const override;

    bool registerSchema(const ConfigSchema* schema, int count);
    bool setValue(const char* key, const char* value);
    bool getValue(const char* key, char* out, size_t maxLen) const;
    bool getInt(const char* key, int& out) const;
    bool getFloat(const char* key, float& out) const;
    bool getBool(const char* key, bool& out) const;

    bool load();
    bool save();
    bool resetToDefaults();
    bool resetKey(const char* key);

    bool exportJson(char* buffer, size_t maxLen) const;
    bool importJson(const char* json);

    bool setProfile(const char* profileName);
    bool getProfile(char* out, size_t maxLen) const;
    bool saveProfile(const char* name);
    bool loadProfile(const char* name);
    bool listProfiles(char** out, int maxCount, int& outCount);

    const char* name() const override { return "ConfigManager"; }
};

#endif
