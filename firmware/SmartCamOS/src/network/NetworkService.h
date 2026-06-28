#ifndef SMARTCAM_NETWORK_SERVICE_H
#define SMARTCAM_NETWORK_SERVICE_H

#include <Arduino.h>
#include "../../sdk/interfaces/SmartCamService.h"

struct NetworkConfig {
    char ssid[32] = "";
    char password[64] = "";
    char hostname[32] = "SmartCamOS";
    bool dhcpEnabled = true;
    char staticIp[16] = "";
    char gateway[16] = "";
    char subnet[16] = "";
    int apChannel = 6;
};

enum class WiFiMode : uint8_t {
    Station = 0,
    AccessPoint = 1,
    StationAP = 2
};

class NetworkService : public SmartCamService {
public:
    bool init() override;
    void tick() override;
    bool deinit() override;
    bool isRunning() const override;

    bool connect(const NetworkConfig& config);
    bool disconnect();
    bool setMode(WiFiMode mode);
    bool startAccessPoint(const char* ssid, const char* password = nullptr);
    bool startCaptivePortal();
    bool scanNetworks();
    int getRssi() const;
    IPAddress getIp() const;
    bool isConnected() const;
    NetworkConfig getConfig() const;

    const char* name() const override { return "NetworkService"; }

private:
    NetworkConfig m_config;
    WiFiMode m_mode;
    bool m_running;
    bool m_apActive;
    bool m_portalActive;
    unsigned long m_lastTick;

    void handleDHCP();
    void handleStaticIP();
    void startDNSServer();
    void stopDNSServer();

public:
    NetworkService();
    ~NetworkService();
};

#endif
