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

private:
    static const int MAX_SCHEMA_ENTRIES = 64;
    static const int MAX_PROFILES = 16;
    static const int PROFILE_NAME_LEN = 32;

    ConfigSchema m_schemas[MAX_SCHEMA_ENTRIES];
    int m_schemaCount;
    char m_currentProfile[PROFILE_NAME_LEN];
    bool m_running;
    bool m_dirty;

    bool validateKey(const char* key) const;
    int findSchema(const char* key) const;

public:
    ConfigManager();
    ~ConfigManager();
};

#endif
