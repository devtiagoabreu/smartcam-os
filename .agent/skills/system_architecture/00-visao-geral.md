# SMARTCAM-OS

## Documento 01 - Visão Geral do Projeto

**Versão:** 1.0.0

**Status:** Em Desenvolvimento

**Plataforma:** T-SIMCAM ESP32-S3

**IDE Oficial:** Arduino IDE 2.x

**Repositório GitHub:**

```text
smartcam-os
```

---

# 1. Introdução

O SmartCam OS é uma plataforma embarcada desenvolvida para a T-SIMCAM ESP32-S3 com o objetivo de fornecer uma infraestrutura única para aplicações de:

* Rastreamento de pessoas
* Rastreamento facial
* Controle de motores
* Automação
* Visão computacional
* Monitoramento industrial
* Monitoramento de fissuras (Geofissura)
* Processamento de imagens

O sistema será acessado completamente através de uma interface web responsiva.

Nenhuma alteração de parâmetros operacionais exigirá recompilação do firmware.

---

# 2. Objetivo da Primeira Entrega

A primeira versão funcional deverá ser capaz de:

### Capturar vídeo

Utilizando a câmera da T-SIMCAM.

---

### Detectar pessoas

Utilizando algoritmos de visão computacional.

---

### Detectar rostos

Como alternativa ao rastreamento de corpo inteiro.

---

### Controlar um motor de passo

Através do driver DM556D.

---

### Centralizar automaticamente o alvo

Mantendo a pessoa no centro da imagem.

---

### Fornecer interface web

Para:

* Configuração
* Operação
* Diagnóstico
* Atualização

---

# 3. Hardware Inicial

## Controlador

T-SIMCAM ESP32-S3

Responsável por:

* Wi-Fi
* Streaming
* Interface Web
* Processamento da câmera
* Controle do motor
* IA

---

## Driver

DM556D

Responsável por:

* Controle do motor de passo

Sinais:

```text
STEP
DIR
ENABLE
```

---

## Motor

Motor de Passo

Inicialmente:

NEMA 23 (configurável)

---

# 4. Filosofia do Projeto

O SmartCam OS NÃO será um firmware único para um projeto específico.

Ele será uma plataforma reutilizável.

Exemplo:

```text
SmartCam OS

├── Person Tracking
├── Face Tracking
├── Geofissura
├── QR Reader
├── AI Vision
├── PTZ Camera
└── Industrial Inspection
```

---

# 5. Tecnologias Utilizadas

## Firmware

Arduino IDE

Linguagem:

```text
C++
```

---

## Front-End

```text
HTML5
CSS3
JavaScript
```

---

## Comunicação

```text
HTTP
REST API
WebSocket
```

---

## Persistência

```text
LittleFS
Preferences (NVS)
```

---

## IA

```text
ESP-DL
```

---

# 6. Requisitos Funcionais

O sistema deverá permitir:

### RF001

Configurar Wi-Fi

---

### RF002

Visualizar vídeo ao vivo

---

### RF003

Controlar motor manualmente

---

### RF004

Executar testes de motor

---

### RF005

Configurar driver

---

### RF006

Configurar motor

---

### RF007

Salvar perfis

---

### RF008

Rastrear pessoas

---

### RF009

Rastrear rostos

---

### RF010

Atualizar firmware OTA

---

### RF011

Exportar configurações

---

### RF012

Importar configurações

---

### RF013

Visualizar logs

---

# 7. Requisitos Não Funcionais

### RNF001

Interface responsiva.

---

### RNF002

Operação 24/7.

---

### RNF003

Baixo consumo de memória.

---

### RNF004

Atualização OTA.

---

### RNF005

Arquitetura modular.

---

### RNF006

Código reutilizável.

---

### RNF007

Configuração persistente.

---

# 8. Fluxo Operacional

```text
Inicialização

↓

Carrega Configurações

↓

Conecta Wi-Fi

↓

Inicializa Web Server

↓

Inicializa Câmera

↓

Inicializa Driver

↓

Inicializa Rastreamento

↓

Sistema Operacional
```

---

# 9. Roadmap

## Fase 1

SmartCam OS Core

* Wi-Fi
* Dashboard
* Câmera
* Motor
* Driver
* Testes
* OTA

---

## Fase 2

Tracking Engine

* Face Tracking
* Person Tracking
* PID
* IA

---

## Fase 3

GeoFissura Engine

* Captura Programada
* Medição de Fissuras
* Relatórios
* Histórico

---

# 10. Convenção de Nomes

## Repositório

```text
smartcam-os
```

---

## Branch Principal

```text
main
```

---

## Branch Desenvolvimento

```text
develop
```

---

## Branch Feature

```text
feature/nome-da-feature
```

Exemplo:

```text
feature/wifi
feature/camera
feature/tracking
feature/motor
```

---

# 11. Estrutura Inicial do GitHub

```text
smartcam-os
│
├── README.md
├── LICENSE
├── CHANGELOG.md
├── docs/
├── firmware/
├── data/
├── tools/
└── examples/
```

---

# 12. Critério de Sucesso da Primeira Entrega

O projeto será considerado funcional quando:

✅ A T-SIMCAM criar um AP para configuração.

✅ Conectar ao Wi-Fi.

✅ Exibir vídeo ao vivo.

✅ Controlar o DM556D.

✅ Detectar uma pessoa.

✅ Girar o motor para seguir a pessoa.

✅ Permitir configuração pela interface web.

✅ Atualizar firmware via OTA.

---
