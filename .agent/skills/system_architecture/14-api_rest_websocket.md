Perfeito. Este documento será um dos pilares do SmartCam OS, porque ele define a comunicação entre o firmware, o Dashboard Web e, futuramente, aplicativos Android, desktop e serviços externos.

Minha proposta é que a API seja estável desde a primeira versão, permitindo evoluções sem quebrar compatibilidade.

---

# SMARTCAM OS

# Documento 16 – API REST + WebSocket

**Versão:** 1.0.0

**Padrão:** REST + JSON + WebSocket

---

# 1. Objetivo

Criar uma API única para comunicação entre:

* Dashboard Web
* Firmware
* Aplicativo Android (futuro)
* Aplicativo Desktop
* MQTT Bridge (futuro)
* API externa

Toda comunicação ocorrerá através desta API.

---

# 2. Arquitetura

```text
                Dashboard

                    │

            HTTP / WebSocket

                    │

                API Service

     ┌──────────┬───────────┬───────────┐

     ▼          ▼           ▼

 Camera     Tracking      Motion

     ▼          ▼           ▼

            SmartCam Core
```

---

# 3. Padrão

Toda API começará com:

```text
/api/v1/
```

No futuro:

```text
/api/v2/
```

Sem quebrar versões anteriores.

---

# 4. Formato JSON

Todas as respostas seguirão exatamente o mesmo padrão.

Sucesso

```json
{
  "success": true,
  "code": 0,
  "message": "OK",
  "data": {}
}
```

Erro

```json
{
  "success": false,
  "code": 102,
  "message": "Camera not initialized",
  "data": null
}
```

---

# 5. Estrutura Geral

```text
/api/v1/system

/api/v1/camera

/api/v1/motion

/api/v1/tracking

/api/v1/vision

/api/v1/ai

/api/v1/network

/api/v1/storage

/api/v1/settings

/api/v1/logger

/api/v1/dashboard
```

---

# 6. System API

## Status

GET

```text
/api/v1/system/status
```

Resposta

```json
{
    "version":"1.0.0",
    "uptime":12345,
    "heap":240000,
    "psram":7600000,
    "cpu":18,
    "temperature":42.3
}
```

---

## Reiniciar

POST

```text
/api/v1/system/reboot
```

---

## Informações

GET

```text
/api/v1/system/info
```

---

# 7. Camera API

## Estado

GET

```text
/api/v1/camera/status
```

---

## Configuração

GET

```text
/api/v1/camera/config
```

---

## Atualizar Configuração

POST

```text
/api/v1/camera/config
```

Exemplo

```json
{
    "resolution":"QVGA",
    "quality":12,
    "brightness":0,
    "contrast":0,
    "fps":20
}
```

---

## Capturar Foto

POST

```text
/api/v1/camera/snapshot
```

---

## Reinicializar

POST

```text
/api/v1/camera/restart
```

---

# 8. Motion API

Status

```text
GET

/api/v1/motion/status
```

---

Mover

```text
POST

/api/v1/motion/move
```

Exemplo

```json
{
    "axis":"pan",
    "mode":"degree",
    "value":35
}
```

---

Parar

```text
POST

/api/v1/motion/stop
```

---

Home

```text
POST

/api/v1/motion/home
```

---

# 9. Tracking API

Estado

```text
GET

/api/v1/tracking/status
```

---

Iniciar

```text
POST

/api/v1/tracking/start
```

---

Parar

```text
POST

/api/v1/tracking/stop
```

---

Configuração

```text
POST

/api/v1/tracking/config
```

---

Exemplo

```json
{
    "kp":1.2,
    "ki":0,
    "kd":0.3,
    "deadzone":25
}
```

---

# 10. Vision API

Status

```text
GET

/api/v1/vision/status
```

---

Selecionar filtro

```text
POST

/api/v1/vision/filter
```

---

Blob Detection

```text
POST

/api/v1/vision/blob
```

---

# 11. AI API

Modelo atual

```text
GET

/api/v1/ai/model
```

---

Trocar modelo

```text
POST

/api/v1/ai/model
```

---

Iniciar

```text
POST

/api/v1/ai/start
```

---

Parar

```text
POST

/api/v1/ai/stop
```

---

# 12. Logger API

Últimos eventos

```text
GET

/api/v1/logger
```

---

Limpar

```text
POST

/api/v1/logger/clear
```

---

Baixar log

```text
GET

/api/v1/logger/download
```

---

# 13. Network API

Status

```text
GET

/api/v1/network/status
```

---

Scan

```text
GET

/api/v1/network/scan
```

---

Conectar

```text
POST

/api/v1/network/connect
```

---

# 14. Storage API

Arquivos

```text
GET

/api/v1/storage/files
```

---

Download

```text
GET

/api/v1/storage/file
```

---

Excluir

```text
POST

/api/v1/storage/delete
```

---

# 15. Settings API

Salvar

```text
POST

/api/v1/settings/save
```

---

Carregar

```text
GET

/api/v1/settings/load
```

---

Restaurar

```text
POST

/api/v1/settings/reset
```

---

# 16. Dashboard API

Estado geral

```text
GET

/api/v1/dashboard
```

Retorna todas as informações resumidas para a página inicial.

---

# 17. WebSocket

Além da API REST, utilizaremos WebSocket para atualização em tempo real.

Endpoint

```text
ws://ip-do-esp32/ws
```

---

# 18. Eventos

Todos os eventos utilizarão JSON.

Exemplo

```json
{
    "event":"camera.ready"
}
```

---

Outro exemplo

```json
{
    "event":"tracking.started"
}
```

---

Outro

```json
{
    "event":"target.locked",
    "id":4
}
```

---

# 19. Eventos previstos

```text
camera.ready

camera.error

frame.ready

motion.started

motion.finished

tracking.started

tracking.stopped

target.locked

target.lost

wifi.connected

wifi.disconnected

ota.started

ota.finished
```

---

# 20. Streaming

Status do sistema.

```json
{
    "fps":22,
    "cpu":15,
    "heap":245000,
    "psram":7300000,
    "temperature":41.2
}
```

Atualizado continuamente.

---

# 21. Códigos HTTP

Utilizaremos:

```text
200 OK

201 Created

400 Bad Request

401 Unauthorized

404 Not Found

409 Conflict

500 Internal Error
```

---

# 22. Códigos de Erro

Padronizados.

Exemplo

```text
CAM001

CAM002

MOT001

MOT002

NET001

AI001

SYS001
```

---

# 23. Segurança

Na V1.

Sem login.

Na V2.

Token.

Na V3.

JWT.

---

# 24. Compatibilidade

A API será utilizada por:

* Dashboard HTML
* Aplicativo Android
* Aplicativo Windows
* MQTT Gateway
* Home Assistant (futuro)
* Node-RED (futuro)

---

# 25. Objetivo Final

Criar uma API estável, documentada e preparada para crescer sem quebrar compatibilidade entre versões.

---

# 🚀 Evolução importante da arquitetura

Enquanto documentava a API, identifiquei uma oportunidade para tornar o SmartCam OS ainda mais profissional.

## API REST para Configuração

Toda configuração será persistida por perfis.

Exemplo:

```text
Perfil: Person Tracker

↓

Camera

↓

Tracking

↓

Motion

↓

AI
```

Outro perfil:

```text
Perfil: GeoFissura

↓

Camera

↓

Vision

↓

Measurement

↓

Storage
```

Assim, um único clique no Dashboard poderá trocar completamente o comportamento do equipamento.

---

## Sistema de Perfis

Teremos uma API exclusiva:

```text
GET

/api/v1/profiles
```

```text
POST

/api/v1/profiles/load
```

```text
POST

/api/v1/profiles/save
```

Exemplo:

```json
{
    "profile":"GeoFissura"
}
```

---

## API de Diagnóstico

Outra funcionalidade importante será um endpoint de diagnóstico completo.

```text
GET

/api/v1/diagnostics
```

Retornando:

```json
{
    "camera":"OK",
    "motion":"OK",
    "tracking":"OK",
    "vision":"OK",
    "network":"OK",
    "storage":"OK",
    "uptime":86400
}
```

Esse endpoint será muito útil para manutenção em campo.

---

# 📘 Próximo Documento (17)

Agora vamos projetar toda a interface gráfica do sistema:

# **Dashboard Web (HTML5 + CSS + JavaScript)**

Será uma interface profissional, responsiva e moderna, desenvolvida para funcionar diretamente no navegador, sem necessidade de aplicativos externos.

Ela incluirá:

* Página inicial com status em tempo real.
* Streaming MJPEG.
* Controle manual do motor.
* Configuração completa da câmera.
* Ajuste fino do Tracking (PID).
* Configuração dos modelos de IA.
* Ferramentas de Visão Computacional.
* Gerenciador de perfis.
* Logs e diagnósticos.
* Atualização OTA.
* Explorador de arquivos (LittleFS).
* Tema claro/escuro.
* Interface preparada para desktop, tablet e smartphone.

> **Minha sugestão adicional:** vamos desenvolver esse Dashboard com uma arquitetura de componentes reutilizáveis (Cards, Widgets e Painéis), permitindo que novos aplicativos, como o **GeoFissura**, adicionem suas próprias telas sem alterar o restante da interface. Isso manterá o SmartCam OS organizado e facilitará muito a evolução do projeto ao longo do tempo.
