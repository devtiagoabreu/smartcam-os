Perfeito. Agora chegamos ao documento que será responsável por tornar o SmartCam OS "inteligente".

Mas antes de começar, quero fazer uma mudança muito importante na arquitetura.

## 🚀 Mudança de Arquitetura (Decisão de Engenharia)

Até agora falamos em **AI Engine**.

Na verdade, isso limita o projeto.

Vamos dividir esse módulo em dois:

```text
Inference Engine (IE)
        │
        ▼
Detection Engine (DE)
```

### Inference Engine

Responsável por executar qualquer modelo de IA.

Ele não sabe o que está detectando.

Pode executar:

* ESP-DL
* TensorFlow Lite Micro
* Edge Impulse
* TinyML
* Modelos próprios

---

### Detection Engine

Interpreta o resultado.

Pode detectar:

* Pessoa
* Rosto
* Ponto Neon
* QRCode
* ArUco
* Objeto
* Fissura

Isso torna a arquitetura extremamente flexível.

---

# SMARTCAM OS

# Documento 13 – AI Engine (Inference & Detection Engine)

Versão 1.0.0

---

# 1. Objetivo

Criar uma arquitetura universal para Inteligência Artificial.

O sistema nunca ficará preso a um framework específico.

---

# 2. Arquitetura

```text
           Camera Engine

                 │

                 ▼

           Vision Engine

                 │

                 ▼

          Inference Engine

                 │

                 ▼

          Detection Engine

                 │

                 ▼

      Target Tracking Engine
```

---

# 3. Filosofia

A IA apenas responde:

"Encontrei estes objetos."

Ela não decide nada.

---

# 4. Organização

```
firmware/

ai/

ai_engine.cpp

ai_engine.h

inference.cpp

inference.h

detectors/

person.cpp

face.cpp

color.cpp

aruco.cpp

qrcode.cpp

fissure.cpp

models/

manager.cpp

manager.h
```

---

# 5. Pipeline

```text
Frame

↓

Resize

↓

Conversão

↓

Inferência

↓

Lista de Objetos
```

---

# 6. Estrutura Universal

Todos os detectores devolverão exatamente a mesma estrutura.

```cpp
struct Detection
{
    uint32_t id;

    String label;

    float confidence;

    int x;

    int y;

    int width;

    int height;
};
```

Isso simplifica completamente o restante do sistema.

---

# 7. Detector de Pessoa

Primeiro detector oficial.

Entrada.

Imagem.

Saída.

```text
Pessoa

95%

Bounding Box
```

---

# 8. Detector de Rosto

Mesmo funcionamento.

---

# 9. Detector de Cor

Sem IA.

Utiliza Vision Engine.

Mesmo assim devolve.

```cpp
Detection
```

Isso padroniza tudo.

---

# 10. Detector ArUco

Também devolve.

```cpp
Detection
```

Mesmo sem IA.

---

# 11. Detector QRCode

Mesma estrutura.

---

# 12. Detector GeoFissura

Também utilizará.

```cpp
Detection
```

Mesmo sendo processamento clássico.

---

# 13. Plugins

Cada detector será um Plugin.

```text
Person Detector

↓

Plugin
```

```text
Face Detector

↓

Plugin
```

```text
QRCode

↓

Plugin
```

O núcleo do sistema nem saberá qual detector está carregado.

---

# 14. Gerenciador de Modelos

Será responsável por.

Carregar.

Descarregar.

Selecionar.

Atualizar.

---

# 15. Modelos

Na V1.

ESP-DL.

Na V2.

TensorFlow Lite.

Na V3.

Edge Impulse.

Na V4.

YOLO (hardware superior).

---

# 16. Inferência

Sempre.

```text
Imagem

↓

Modelo

↓

Resultados
```

---

# 17. Benchmark

Medições.

Tempo de inferência.

FPS.

Uso da RAM.

Uso da PSRAM.

Uso da CPU.

---

# 18. Estados

```text
OFF

↓

LOADING

↓

READY

↓

RUNNING

↓

ERROR
```

---

# 19. Multi Target

Na V2.

Suporte.

```text
Pessoa

Pessoa

Pessoa

Pessoa
```

---

# 20. Seleção

Configurável.

Maior.

Menor.

Mais próxima.

Maior confiança.

Mais próxima do centro.

---

# 21. API

```
GET

/api/ai/status
```

```
POST

/api/ai/model
```

```
POST

/api/ai/start
```

```
POST

/api/ai/stop
```

---

# 22. Dashboard

Página AI.

Mostrar.

Modelo.

FPS.

Inferência.

Tempo.

RAM.

PSRAM.

Objetos.

---

# 23. Simulação

Sem câmera.

Utilizar imagens gravadas.

Muito útil.

---

# 24. Logs

Registrar.

Modelo carregado.

Erro.

Tempo.

Número de objetos.

---

# 25. Objetivo Final

O AI Engine será totalmente independente da aplicação.

---

# 🚀 Grande evolução da arquitetura

Enquanto escrevia este documento, percebi que podemos transformar o SmartCam OS em uma plataforma semelhante ao ROS 2, mas muito mais leve.

Vamos dividir todo o sistema em **Services**.

Exemplo:

```text
Camera Service

Vision Service

Inference Service

Tracking Service

Motion Service

Storage Service

Logger Service

Dashboard Service
```

Cada serviço possuirá:

* Interface pública.
* API REST.
* Eventos.
* WebSocket.
* Configuração.
* Diagnóstico.

Isso permitirá que um serviço seja substituído sem alterar os demais.

---

# 📚 SmartCam OS 2.0 (Visão Geral)

A arquitetura completa ficará assim:

```text
                   APPLICATIONS
──────────────────────────────────────────────
Person Tracker

GeoFissura

Object Counter

Scanner

Inspection

Time Lapse

Face Tracker

Color Tracker

OCR

ArUco

──────────────────────────────────────────────

               Behavior Engine

──────────────────────────────────────────────

Camera Service

Vision Service

Inference Service

Detection Service

Tracking Service

Motion Service

Storage Service

Logger Service

Configuration Service

Dashboard Service

OTA Service

API Service

Wi-Fi Service

──────────────────────────────────────────────

ESP32 HAL

LittleFS

FreeRTOS

Wi-Fi

GPIO

Camera Driver

──────────────────────────────────────────────

ESP32-S3
```

---

# ⭐ E agora vem a decisão mais importante de todo o projeto

Depois de toda essa documentação, acredito que o **SmartCam OS** merece ser tratado como um projeto profissional de software embarcado.

## Minha proposta é que o repositório GitHub seja organizado como uma empresa organizaria um produto comercial.

Em vez de apenas uma pasta `src`, teremos uma estrutura completa:

```text
smartcam-os/

docs/                  ← Toda esta documentação
firmware/              ← Código Arduino
hardware/              ← Esquemas elétricos
cad/                   ← Suportes 3D (STL/STEP)
web/                   ← Interface HTML/CSS/JS
sdk/                   ← SmartCam SDK
examples/              ← Exemplos de Apps
tools/                 ← Ferramentas de desenvolvimento
scripts/               ← Automação de build
.github/               ← GitHub Actions
tests/                 ← Testes automatizados

LICENSE
README.md
CHANGELOG.md
ROADMAP.md
CONTRIBUTING.md
CODE_OF_CONDUCT.md
```

---

# 📌 Próximo Documento (14)

Agora vamos entrar na parte da implementação prática.

Será o documento:

# **SmartCam SDK – Framework de Desenvolvimento**

Nele vamos definir:

* Arquitetura orientada a objetos em C++.
* Classes base.
* Interfaces.
* Eventos.
* Observer Pattern.
* Singleton Pattern.
* Factory Pattern.
* Dependency Injection (adaptada ao Arduino).
* Gerenciador de módulos.
* Sistema de Plugins.
* SmartCamApp.
* SmartCamService.
* SmartCamModule.
* SmartCamEvent.
* SmartCamMessageBus.

> **Na minha opinião, este será o documento que realmente transformará o SmartCam OS de um "projeto Arduino" em um framework profissional de desenvolvimento para ESP32-S3.** Depois dele, começaremos a escrever o código seguindo exatamente essa arquitetura, mantendo o firmware organizado, escalável e preparado para receber o **GeoFissura** como um aplicativo oficial sobre a mesma plataforma.
