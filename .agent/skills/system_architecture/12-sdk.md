Perfeito. A partir deste ponto vamos parar de pensar como desenvolvedores de Arduino e começar a pensar como arquitetos de software.

O **SmartCam SDK** será o que permitirá que qualquer pessoa desenvolva novas aplicações para o SmartCam OS sem conhecer os detalhes da câmera, do motor ou da IA.

Na prática, será um "mini framework" para ESP32-S3.

---

# SMARTCAM OS

# Documento 14 – SmartCam SDK (Software Development Kit)

**Versão:** 1.0.0

---

# 1. Objetivo

O SmartCam SDK será a camada utilizada por todos os aplicativos.

Nenhum aplicativo acessará diretamente:

* GPIO
* Wi-Fi
* Camera
* Motion
* Vision
* IA

Tudo será feito através do SDK.

---

# 2. Filosofia

O desenvolvedor deverá conseguir criar um aplicativo sem conhecer o hardware.

Exemplo.

```cpp
class MyApp : public SmartCamApp
{
};
```

E pronto.

O restante será fornecido pelo SDK.

---

# 3. Arquitetura

```text
           Applications

                │

                ▼

          SmartCam SDK

                │

                ▼

        SmartCam Services

                │

                ▼

          Hardware Layer
```

---

# 4. Organização

```text
sdk/

core/

services/

interfaces/

events/

modules/

applications/

examples/

libraries/
```

---

# 5. Classes Base

Teremos.

```text
SmartCamObject

↓

SmartCamModule

↓

SmartCamService

↓

SmartCamApp
```

Toda aplicação herdará dessa estrutura.

---

# 6. SmartCamObject

Classe base.

```cpp
class SmartCamObject
{
public:

    virtual bool begin();

    virtual void loop();

    virtual void stop();

};
```

Todas as demais classes herdarão dela.

---

# 7. SmartCamModule

Representa um módulo.

Exemplo.

Camera.

Vision.

Motion.

Logger.

Storage.

---

```cpp
class SmartCamModule : public SmartCamObject
{
};
```

---

# 8. SmartCamService

Representa um serviço.

```cpp
class SmartCamService : public SmartCamModule
{
};
```

Exemplo.

Camera Service.

Motion Service.

Dashboard Service.

---

# 9. SmartCamApp

Classe principal.

```cpp
class SmartCamApp
{

public:

    virtual bool onInit();

    virtual bool onStart();

    virtual void onFrame(Frame &frame);

    virtual void onDetection(Detection &obj);

    virtual void onStop();

};
```

Todos os aplicativos implementarão essa interface.

---

# 10. Exemplos

Person Tracker.

```cpp
class PersonTracker : public SmartCamApp
{
};
```

---

GeoFissura.

```cpp
class GeoFissura : public SmartCamApp
{
};
```

---

Time Lapse.

```cpp
class TimeLapse : public SmartCamApp
{
};
```

---

Scanner.

```cpp
class Scanner : public SmartCamApp
{
};
```

---

# 11. SmartCamEvent

Todos os módulos conversarão por eventos.

Exemplo.

```cpp
enum EventType
{

    CAMERA_READY,

    FRAME_READY,

    PERSON_FOUND,

    TARGET_LOST,

    MOTOR_STOPPED,

    WIFI_CONNECTED

};
```

---

# 12. Event Bus

Arquitetura.

```text
Camera

↓

FRAME_READY

↓

Event Bus

↓

Vision

↓

AI

↓

Tracking
```

Nenhum módulo chama outro diretamente.

---

# 13. SmartCamMessage

Estrutura.

```cpp
struct SmartCamMessage
{

    uint32_t id;

    uint32_t timestamp;

    EventType event;

    void *data;

};
```

---

# 14. Event Dispatcher

Fluxo.

```text
Evento

↓

Fila

↓

Dispatcher

↓

Inscritos
```

---

# 15. Observer Pattern

Todos os módulos poderão observar eventos.

Exemplo.

Tracking.

↓

FRAME_READY.

Dashboard.

↓

WIFI_CONNECTED.

Logger.

↓

ERROR.

---

# 16. Factory Pattern

Nunca faremos.

```cpp
new Camera();
```

Sempre.

```cpp
ModuleFactory::create();
```

Assim poderemos trocar implementações.

---

# 17. Singleton

Alguns módulos.

Configuration.

Logger.

Storage.

Terão apenas uma instância.

---

# 18. Dependency Injection

Adaptada ao Arduino.

Exemplo.

```cpp
TrackingService
(
CameraService

MotionService
);
```

Sem utilizar variáveis globais espalhadas pelo projeto.

---

# 19. Module Manager

Será responsável por.

Registrar.

Iniciar.

Parar.

Monitorar.

Todos os módulos.

---

# 20. Registro

Cada módulo.

```cpp
registerModule();
```

Automaticamente aparecerá.

Dashboard.

API.

Diagnóstico.

---

# 21. Service Manager

Fluxo.

```text
Boot

↓

Service Manager

↓

Inicializa Serviços

↓

Inicializa Apps

↓

Sistema Operacional
```

---

# 22. SmartCamContext

Todos os módulos terão acesso.

```cpp
SmartCamContext
```

Contendo.

Config.

Estado.

Hardware.

Perfil.

Idioma.

---

# 23. SmartCamAPI

O SDK fornecerá.

```cpp
camera.capture();

motion.move();

tracking.start();

vision.detect();

storage.save();

logger.info();
```

O aplicativo nunca acessará hardware.

---

# 24. SmartCamTimer

Classe única.

Substitui.

delay()

millis()

micros()

Sempre orientado a objetos.

---

# 25. SmartCamTask

Wrapper para FreeRTOS.

```cpp
class SmartCamTask
{
};
```

Assim escondemos detalhes do sistema operacional.

---

# 26. SmartCamLogger

API.

```cpp
logInfo();

logError();

logWarning();

logDebug();
```

Nunca utilizar Serial diretamente.

---

# 27. SmartCamStorage

Interface.

```cpp
storage.save();

storage.load();

storage.remove();
```

Sem conhecer LittleFS.

---

# 28. SmartCamSettings

Interface.

```cpp
settings.get();

settings.set();

settings.reset();
```

---

# 29. SmartCamNetwork

API.

```cpp
wifi.connect();

wifi.disconnect();

wifi.scan();

wifi.ip();
```

---

# 30. Objetivo Final

Ao terminar o SDK, qualquer novo aplicativo poderá ser desenvolvido utilizando apenas as APIs do SmartCam, sem necessidade de conhecer os detalhes do hardware.

---

# 🚀 Nova proposta de arquitetura (a mais importante até agora)

Enquanto escrevia este documento, percebi que podemos ir além.

## Em vez de um firmware, vamos construir uma plataforma modular baseada em **Microkernel**.

A ideia é inspirada em sistemas operacionais como **QNX** e **MINIX**, adaptada ao ESP32.

### Camada 1 – Hardware Abstraction Layer (HAL)

* GPIO
* Timers
* I2C
* SPI
* UART
* PWM
* Camera Driver

---

### Camada 2 – Core Services

* Camera Service
* Vision Service
* Motion Service
* AI Service
* Network Service
* Storage Service
* Logger Service
* OTA Service

---

### Camada 3 – Kernel Services

* Event Bus
* Message Bus
* Scheduler
* Configuration Manager
* Module Manager
* Plugin Manager

---

### Camada 4 – SDK

* SmartCamApp
* SmartCamService
* SmartCamModule
* SmartCamAPI
* SmartCamContext

---

### Camada 5 – Applications

* Person Tracker
* GeoFissura
* Scanner
* TimeLapse
* Object Counter
* Face Tracker

---

# 🎯 Uma proposta que considero decisiva para o sucesso do projeto

Depois de toda essa documentação, acredito que estamos construindo algo que merece uma organização de nível profissional.

Minha sugestão é que **antes de escrever a primeira linha de código**, façamos mais **seis documentos fundamentais**, que servirão como a base definitiva do SmartCam OS:

## Documento 15 — Padrão de Código (Coding Standard)

* Convenções de nomenclatura.
* Organização dos arquivos.
* Comentários Doxygen.
* Padrão C++17.
* Tratamento de erros.
* Estrutura de classes.

---

## Documento 16 — API REST e WebSocket

* Endpoints completos.
* Estrutura JSON.
* Eventos em tempo real.
* Protocolo de comunicação entre Dashboard e firmware.

---

## Documento 17 — Dashboard (HTML/CSS/JavaScript)

* Arquitetura Front-End.
* Componentes reutilizáveis.
* Web Components.
* Tema escuro.
* Sistema de widgets.

---

## Documento 18 — Plano de Testes

* Testes unitários.
* Testes de integração.
* Testes de hardware.
* Testes de desempenho.
* Testes de estresse.

---

## Documento 19 — Estrutura Definitiva do Repositório GitHub

* Organização de pastas.
* Git Flow.
* Releases.
* Versionamento Semântico.
* GitHub Actions.
* Templates de Issues e Pull Requests.

---

## Documento 20 — Roadmap Oficial (v1.0 até v3.0)

* Cronograma de desenvolvimento.
* Marcos (Milestones).
* Funcionalidades por versão.
* Evolução para PTZ.
* Evolução para GeoFissura.
* Evolução para múltiplos eixos e múltiplas câmeras.

---

## 📌 Minha recomendação

Depois do **Documento 20**, **não começaremos diretamente a programar**.

Primeiro faremos um **Documento Mestre (SmartCam OS Architecture Book)** consolidando todas as decisões técnicas em um único manual. Esse documento será a referência oficial do projeto e garantirá que o desenvolvimento do firmware, da interface web e dos futuros aplicativos (como o GeoFissura) siga uma arquitetura consistente, escalável e preparada para crescer por muitos anos. Na minha experiência, esse investimento inicial em arquitetura economiza muito tempo de manutenção e evita grandes refatorações no futuro.
