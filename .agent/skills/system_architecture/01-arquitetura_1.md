# SMARTCAM-OS

# Documento 02 — Arquitetura Completa

**Versão:** 1.0.0

---

# 1. Filosofia da Arquitetura

O SmartCam OS será desenvolvido seguindo cinco princípios fundamentais:

* Modularidade
* Baixo acoplamento
* Alta coesão
* Configuração totalmente via Web
* Facilidade para adicionar novos módulos

Nenhum módulo deverá depender diretamente de outro.

Toda comunicação ocorrerá através do **Core do Sistema**.

---

# 2. Arquitetura Geral

```text
                     SMARTCAM OS

                   +----------------+
                   |   Dashboard    |
                   +-------+--------+
                           |
          REST API + WebSocket
                           |
+------------------------------------------------------+
|                Core do Sistema                       |
+------------------------------------------------------+
 |        |         |        |        |        |
 |        |         |        |        |        |
WiFi   Camera    Motor   Tracking  Storage   OTA
 |        |         |        |        |        |
 +--------+---------+--------+--------+--------+
                  Hardware
```

---

# 3. Organização do Repositório

```text
smartcam-os/

│
├── README.md
├── LICENSE
├── CHANGELOG.md
├── .gitignore
│
├── docs/
│
├── firmware/
│
├── data/
│
├── tools/
│
├── examples/
│
└── assets/
```

---

# 4. Pasta docs

Toda documentação ficará nesta pasta.

```text
docs/

00-visao-geral.md

01-arquitetura.md

02-instalacao.md

03-hardware.md

04-dashboard.md

05-camera.md

06-motor.md

07-driver.md

08-tracking.md

09-api.md

10-websocket.md

11-ota.md

12-testes.md

13-roadmap.md

images/
```

---

# 5. Pasta firmware

Aqui ficará todo o código Arduino.

```text
firmware/

SmartCamOS.ino

config.h

globals.h

globals.cpp

```

Cada módulo possuirá sua própria pasta.

```text
camera/

motor/

driver/

tracking/

wifi/

web/

api/

storage/

system/

tests/

pid/

utils/
```

---

# 6. Módulo Camera

Responsável por:

* Inicializar câmera
* Capturar frames
* Configurar resolução
* Configurar qualidade
* Capturar fotos

Arquivos

```text
camera.h

camera.cpp
```

Principais funções

```cpp
camera_init()

camera_start()

camera_stop()

camera_capture()

camera_setResolution()

camera_setQuality()

camera_takePhoto()
```

---

# 7. Módulo Motor

Responsável por:

Controle do DM556D.

Arquivos

```text
motor.h

motor.cpp
```

Funções

```cpp
motor_init()

motor_left()

motor_right()

motor_stop()

motor_moveSteps()

motor_moveDegrees()

motor_setSpeed()

motor_setAcceleration()
```

---

# 8. Módulo Driver

Separado do motor.

Isso permitirá utilizar outros drivers futuramente.

Arquivos

```text
driver.h

driver.cpp
```

Funções

```cpp
driver_setCurrent()

driver_setMicrostep()

driver_setDirection()

driver_enable()

driver_disable()
```

---

# 9. Módulo Tracking

Maior módulo do projeto.

Responsável por:

* IA
* Bounding Box
* Centro do alvo
* PID
* Rastreamento

Arquivos

```text
tracking.h

tracking.cpp
```

Funções

```cpp
tracking_start()

tracking_stop()

tracking_detectPerson()

tracking_detectFace()

tracking_followTarget()
```

---

# 10. Módulo PID

Separado do Tracking.

Permite reutilização.

Arquivos

```text
pid.h

pid.cpp
```

Funções

```cpp
pid_reset()

pid_calculate()

pid_setKP()

pid_setKI()

pid_setKD()
```

---

# 11. Módulo Wi-Fi

Arquivos

```text
wifi.h

wifi.cpp
```

Funções

```cpp
wifi_connect()

wifi_disconnect()

wifi_startAP()

wifi_scan()

wifi_save()
```

---

# 12. Módulo Dashboard

Responsável pela interface Web.

Arquivos

```text
dashboard.h

dashboard.cpp
```

Funções

```cpp
dashboard_init()

dashboard_update()

dashboard_sendStatus()
```

---

# 13. Módulo API

REST API.

Arquivos

```text
api.h

api.cpp
```

Endpoints

```text
/api/status

/api/camera

/api/motor

/api/driver

/api/tracking

/api/tests

/api/system
```

---

# 14. Módulo OTA

Arquivos

```text
ota.h

ota.cpp
```

Funções

```cpp
ota_init()

ota_update()
```

---

# 15. Módulo Storage

Responsável pelo armazenamento.

Utilizará

LittleFS

Preferences

Arquivos

```text
storage.h

storage.cpp
```

Funções

```cpp
saveConfig()

loadConfig()

exportConfig()

importConfig()
```

---

# 16. Módulo Tests

Toda rotina de testes ficará isolada.

Arquivos

```text
tests.h

tests.cpp
```

Funções

```cpp
test_motor()

test_driver()

test_camera()

test_tracking()
```

---

# 17. Módulo System

Gerenciamento geral.

Arquivos

```text
system.h

system.cpp
```

Responsável por

* Reiniciar
* Informações
* Uso de memória
* Tempo ligado

---

# 18. Organização da Interface Web

```text
data/

index.html

css/

style.css

theme.css

responsive.css

js/

main.js

camera.js

motor.js

tracking.js

dashboard.js

wifi.js

system.js

icons/

images/

fonts/
```

---

# 19. Organização JavaScript

Cada tela terá seu próprio JavaScript.

Exemplo

Motor

```text
motor.js
```

Nunca misturar código.

---

# 20. Fluxo do Sistema

```text
ESP32 Liga

↓

Carrega Configurações

↓

Inicializa LittleFS

↓

Inicializa Preferences

↓

Inicializa Wi-Fi

↓

Inicializa Servidor

↓

Inicializa Dashboard

↓

Inicializa Câmera

↓

Inicializa Motor

↓

Inicializa Driver

↓

Inicializa Tracking

↓

Sistema Operacional
```

---

# 21. Fluxo do Rastreamento

```text
Captura Frame

↓

IA

↓

Pessoa Detectada?

↓

SIM

↓

Calcula Centro

↓

Calcula Erro

↓

PID

↓

Motor

↓

Novo Frame
```

---

# 22. Organização dos GPIOs

Criaremos uma camada de abstração para GPIOs.

Nunca utilizaremos números diretamente no código.

Exemplo:

```cpp
PIN_STEP

PIN_DIR

PIN_ENABLE

PIN_LED

PIN_FLASH
```

Todos definidos em um único arquivo (`config.h`).

---

# 23. Convenção de Código

* Nomes de funções em `snake_case`.
* Variáveis globais com prefixo `g_`.
* Constantes em `UPPER_CASE`.
* Classes (caso sejam usadas futuramente) em `PascalCase`.
* Um módulo por responsabilidade.

Exemplo:

```cpp
motor_move_steps();
wifi_connect();
tracking_detect_person();
```

---

# 24. Objetivo da Arquitetura

Ao final desta etapa teremos uma base sólida, organizada e preparada para crescer. A ideia é que qualquer novo recurso — como o módulo **Geofissura**, reconhecimento facial ou leitura de QR Code — seja implementado apenas adicionando um novo módulo, sem alterar a estrutura existente.

---

