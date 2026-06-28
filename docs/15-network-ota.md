# SmartCam Platform — Network and OTA

## Objective

Define the Network Service and OTA Update Service, responsible for Wi-Fi connectivity, access point mode, network scanning, and over-the-air firmware updates.

## Scope

This document covers Wi-Fi connection management (STA + AP), network scanning, DHCP/static IP configuration, hostname resolution, connection monitoring, and OTA firmware update protocol.

## Architecture

```mermaid
flowchart TD
    subgraph NET [Network Service]
        STA[Station Mode]
        AP[Access Point Mode]
        SCAN[Wi-Fi Scanner]
        MON[Connection Monitor]
        DNS[Captive DNS]
    end

    subgraph OTA [OTA Service]
        UPDATE[Update Handler]
        VERIFY[Verification]
        ROLLBACK[Rollback - Future]
    end

    subgraph FW [Firmware]
        HTTP[Async Web Server]
        LFS[LittleFS]
        APP[Application]
    end

    NET --> STA
    NET --> AP
    STA --> MON
    AP --> DNS
    MON --> HTTP
    HTTP --> OTA
    OTA --> FW
    OTA --> LFS
```

## Components

### Wi-Fi Modes

```mermaid
stateDiagram-v2
    [*] --> INIT
    INIT --> AP_MODE
    AP_MODE --> CONNECTING
    CONNECTING --> CONNECTED
    CONNECTED --> DISCONNECTED
    DISCONNECTED --> CONNECTING
    CONNECTED --> AP_MODE
    AP_MODE --> CONNECTING
```

### Wi-Fi Configuration

```json
{
    "mode": "STA",
    "ssid": "HomeNetwork",
    "password": "",
    "hostname": "smartcam-os",
    "ip_mode": "dhcp",
    "ip": "",
    "gateway": "",
    "subnet": "",
    "dns": "",
    "ap_ssid": "SmartCam-AP",
    "ap_password": "smartcam123"
}
```

## Fluxos

### Connection Flow

```mermaid
sequenceDiagram
    participant NET as Network Service
    participant WiFi as ESP32 Wi-Fi
    participant DHCP as DHCP Server
    participant AP as Access Point
    participant HTTP as Web Server

    NET->>WiFi: Load saved credentials
    alt Has saved SSID
        NET->>WiFi: Connect to station
        WiFi->>DHCP: Request IP
        DHCP->>WiFi: Assign IP
        WiFi->>NET: Connection success
        NET->>HTTP: Start server
    else No saved SSID
        NET->>AP: Start access point
        AP->>AP: SSID: SmartCam-AP
        NET->>DNS: Start captive portal
        NET->>HTTP: Start server with setup page
    end
```

### OTA Update Flow

```mermaid
sequenceDiagram
    participant DASH as Dashboard
    participant OTA as OTA Service
    participant LFS as LittleFS
    participant FW as Firmware

    DASH->>DASH: User selects firmware.bin
    DASH->>OTA: POST /api/v1/system/ota
    OTA->>OTA: Begin update
    OTA->>DASH: Progress 0%
    DASH->>OTA: Upload binary chunks
    OTA->>LFS: Write to update partition
    OTA->>DASH: Progress 50%
    DASH->>OTA: Upload complete
    OTA->>OTA: Verify checksum
    OTA->>OTA: Set boot partition
    OTA->>DASH: Progress 100%
    OTA->>FW: Restart in 3 seconds
```

## Interfaces

### Network Service API

```cpp
class NetworkService {
public:
    Result begin();
    Result connect(const String& ssid, const String& password);
    Result disconnect();
    Result startAP(const String& ssid, const String& password);
    Result scanNetworks(Vector<NetworkInfo>& networks);
    Result setStaticIP(const String& ip, const String& gateway, const String& subnet);
    Result setHostname(const String& hostname);
    bool isConnected();
    String getIP();
    String getSSID();
    int8_t getRSSI();
    NetworkConfig getConfig();
};
```

### OTA Service API

```cpp
class OTAService {
public:
    Result begin();
    Result startUpdate(size_t firmwareSize);
    Result writeChunk(const uint8_t* data, size_t length);
    Result finishUpdate();
    Result abortUpdate();
    float getProgress();
    OTAStatus getStatus();
    bool isInProgress();

    // Callbacks
    void onProgress(std::function<void(float)> callback);
    void onError(std::function<void(int)> callback);
};
```

## Estrutura de Pastas

```text
firmware/
    network/
        network_service.h
        network_service.cpp
        wifi_manager.h
        wifi_manager.cpp
        wifi_scanner.h
        wifi_scanner.cpp
        captive_portal.h
        captive_portal.cpp
    ota/
        ota_service.h
        ota_service.cpp
        ota_handler.h
        ota_handler.cpp
```

## Responsabilidades

| Component | Responsibility |
|-----------|----------------|
| Network Service | Public API, mode switching, configuration |
| Wi-Fi Manager | Connection, reconnection, AP mode |
| Wi-Fi Scanner | Network scan with RSSI and security info |
| Captive Portal | DNS redirect for first-time setup |
| OTA Service | Firmware update lifecycle |
| OTA Handler | Partition management, checksum verification |

## Requisitos

| ID | Requirement |
|----|-------------|
| NET-001 | Auto-connect to last known Wi-Fi network on boot |
| NET-002 | Fall back to AP mode if no saved credentials exist |
| NET-003 | AP mode SSID: "SmartCam-AP" with captive portal |
| NET-004 | Support static IP and DHCP configuration |
| NET-005 | Automatic reconnection with exponential backoff |
| NET-006 | Hostname configuration (default: "smartcam-os") |
| NET-007 | Wi-Fi scan returns SSID, RSSI, encryption type, channel |
| OTA-001 | Update firmware via HTTP upload |
| OTA-002 | Progress reporting via WebSocket |
| OTA-003 | Firmware validation with SHA-256 checksum |
| OTA-004 | Preserve configuration across OTA updates |
| OTA-005 | Abort safety: invalid firmware does not apply |
| OTA-006 | Update progress accessible from Dashboard |

## Considerações

The Network Service handles two distinct scenarios: configured (STA mode) and first-time setup (AP mode with captive portal). The automatic fallback ensures the device is always accessible on the network, even after configuration loss or network changes. The OTA Service is designed for reliability: firmware is verified before application, and the update partition is marked only after successful checksum validation.

## Próximos documentos relacionados

- [11-dashboard-web.md](11-dashboard-web.md) — OTA and network configuration pages
- [12-api-rest-websocket.md](12-api-rest-websocket.md) — Network and OTA API endpoints
- [13-configuration-manager.md](13-configuration-manager.md) — Wi-Fi credential storage
