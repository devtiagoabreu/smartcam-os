Perfeito.

Chegamos ao último documento da arquitetura. Este documento vai definir o futuro do projeto pelos próximos anos.

Na minha visão, este roadmap deve ser **realista**. Primeiro construiremos uma base extremamente sólida (Core + Dashboard + SDK), depois adicionaremos novas funcionalidades.

---

# SMARTCAM PLATFORM

# Documento 20 – Roadmap Oficial

**Versão:** 1.0.0

---

# 1. Objetivo

Definir oficialmente a evolução do SmartCam Platform.

O desenvolvimento será baseado em versões (Releases) e marcos (Milestones).

Cada versão deverá ser completamente funcional antes do início da próxima.

---

# 2. Filosofia

Sempre seguir esta ordem.

```text
Arquitetura

↓

Core

↓

SDK

↓

Dashboard

↓

Apps

↓

Novos Recursos
```

Nunca desenvolver novas funcionalidades sobre uma base instável.

---

# 3. Roadmap Geral

```text
v1.0

↓

v1.1

↓

v1.5

↓

v2.0

↓

v3.0

↓

v4.0

↓

v5.0
```

---

# SmartCam Platform v1.0

## Objetivo

Criar uma plataforma funcional.

---

## SmartCam Core

Implementar.

```text
Camera Engine

Motion Engine

Tracking Engine

Vision Engine

Logger

Storage

Network

API

Dashboard

OTA
```

---

## Dashboard

Primeira versão.

```text
Camera

Motor

Tracking

Logs

Configurações

OTA

Status
```

---

## SDK

Primeira versão.

```text
SmartCamApp

SmartCamService

SmartCamModule

Event Bus

Configuration

Logger
```

---

## Aplicativo Oficial

```text
Person Tracker
```

---

Objetivo.

```text
Pessoa entra na imagem

↓

ESP32 detecta

↓

Motor acompanha

↓

Dashboard mostra tudo
```

---

# SmartCam Platform v1.1

Melhorias.

```text
Melhor Tracking

Perfis

Logs

Mais APIs

Dashboard aprimorado
```

---

Adicionar.

```text
Color Tracking
```

---

# SmartCam Platform v1.5

Entraremos na Visão Computacional.

Adicionar.

```text
Blob Detection

HSV

Threshold

Overlay

ROI

Histogram
```

---

Aplicativos.

```text
Object Counter

Scanner
```

---

# SmartCam Platform v2.0

Grande evolução.

Adicionar.

```text
Face Detection

QR Code

ArUco

Plugins

SDK 2.0
```

---

Dashboard.

Widgets.

---

API.

Autenticação.

---

# SmartCam Platform v2.5

Adicionar.

```text
Multi Target Tracking
```

---

Selecionar.

Maior pessoa.

Mais próxima.

Maior confiança.

---

# SmartCam Platform v3.0

Nascimento do.

```text
GeoFissura
```

---

Novo aplicativo.

```text
GeoFissura
```

---

Fluxo.

```text
Foto

↓

Detecta Pontos Neon

↓

Calcula Escala

↓

Detecta Fissura

↓

Calcula Largura

↓

Banco Histórico

↓

Relatório
```

---

Dashboard.

Adicionar.

```text
Calibração

Medição

Histórico

Exportação

Relatórios
```

---

# SmartCam Platform v3.5

Adicionar.

```text
Time Lapse

OCR

Inspection

Measurement Toolkit
```

---

# SmartCam Platform v4.0

Grande evolução.

Adicionar.

```text
Pan

Tilt

Zoom
```

Suporte.

```text
PTZ
```

---

Adicionar.

```text
2 Motores

↓

Pan + Tilt
```

---

# SmartCam Platform v4.5

Adicionar.

```text
Múltiplas câmeras
```

Arquitetura.

```text
Camera 1

↓

Camera 2

↓

Camera 3

↓

Camera 4
```

---

# SmartCam Platform v5.0

Transformar em plataforma distribuída.

```text
SmartCam

↓

Rede

↓

SmartCam

↓

Rede

↓

SmartCam
```

---

Adicionar.

```text
Cluster

↓

MQTT

↓

Sincronização

↓

Nuvem
```

---

# Roadmap dos Aplicativos

## Person Tracker

```text
v1.0
```

---

## Color Tracker

```text
v1.1
```

---

## Scanner

```text
v1.5
```

---

## Face Tracker

```text
v2.0
```

---

## QRCode

```text
v2.0
```

---

## GeoFissura

```text
v3.0
```

---

## Inspection

```text
v3.5
```

---

## PTZ Controller

```text
v4.0
```

---

## MultiCam

```text
v4.5
```

---

# Roadmap do Hardware

## Primeira Plataforma

```text
ESP32-S3

↓

T-SIMCAM

↓

DM556D

↓

Motor de Passo
```

---

## Segunda Plataforma

Adicionar.

```text
Encoder

↓

Fim de Curso

↓

IMU
```

---

## Terceira Plataforma

Adicionar.

```text
Tilt

↓

Zoom

↓

Focus
```

---

## Quarta Plataforma

Adicionar.

```text
Múltiplas Câmeras
```

---

# Roadmap do Dashboard

v1.

```text
Configuração
```

---

v2.

```text
Widgets
```

---

v3.

```text
Plugins
```

---

v4.

```text
Designer de Dashboard
```

---

# Roadmap do SDK

v1.

```text
Classes Base
```

---

v2.

```text
Plugins
```

---

v3.

```text
Marketplace
```

---

# Roadmap da API

v1.

REST.

---

v2.

REST + Auth.

---

v3.

REST + MQTT.

---

v4.

REST + GraphQL (em estudo).

---

# Roadmap da IA

v1.

```text
ESP-DL
```

---

v2.

```text
TensorFlow Lite
```

---

v3.

```text
YOLO (hardware superior)
```

---

# Roadmap da Documentação

Todos os documentos terão:

* Diagramas UML.
* Diagramas Mermaid.
* Fluxogramas.
* Diagramas elétricos.
* Sequência de eventos.
* Casos de uso.
* Doxygen.

---

# Critério para cada Release

Uma nova versão somente será publicada quando:

* Todos os testes forem aprovados.
* Documentação estiver atualizada.
* Dashboard estiver compatível.
* API estiver versionada.
* Código revisado.
* Changelog completo.

---

# Objetivo Final

Transformar o SmartCam Platform em uma plataforma aberta de visão computacional embarcada, capaz de suportar desde projetos educacionais até aplicações profissionais como monitoramento, inspeção, automação industrial e o **GeoFissura**.

---

# 🚀 Documento Extra – A decisão mais importante do projeto

Depois de escrever esses 20 documentos, analisando toda a arquitetura, acredito que existe uma oportunidade muito maior.

## O SmartCam Platform pode ser dividido em três repositórios oficiais

Em vez de um único repositório enorme, proponho:

```text
smartcam-platform/
```

Portal principal.

Contém documentação.

Roadmap.

Wiki.

Releases.

---

```text
smartcam-os/
```

Firmware.

SDK.

Dashboard.

Core.

---

```text
smartcam-apps/
```

Todos os aplicativos.

```
Person Tracker

GeoFissura

Inspection

Scanner

OCR

QRCode

Face Tracker

Color Tracker
```

Cada App pode evoluir independentemente.

---

```text
smartcam-hardware/
```

Toda parte física.

Esquemas.

PCBs.

STL.

STEP.

Fusion 360.

Lista de materiais (BOM).

---

# ⭐ Minha conclusão

Depois de toda essa documentação, não considero mais o SmartCam apenas um projeto de ESP32.

Na prática, estamos projetando uma **plataforma modular de visão computacional embarcada**, onde:

* O **SmartCam OS** é o núcleo.
* O **SmartCam SDK** permite criar novos aplicativos.
* O **Dashboard** é uma central de engenharia e operação.
* O **GeoFissura** será um aplicativo especializado que reutiliza toda essa infraestrutura.

## 📚 O próximo passo que eu faria

Em vez de começar a programar diretamente, eu criaria um documento final chamado:

# **SmartCam Platform Engineering Book**

Este seria um manual único, consolidando todos os 20 documentos em uma especificação oficial do projeto.

Minha sugestão é ir além de uma simples consolidação. Vamos transformá-lo em um **livro técnico completo**, com aproximadamente **600 a 800 páginas**, incluindo:

* Arquitetura completa do sistema.
* Diagramas UML e Mermaid.
* Diagramas elétricos do hardware (T-SIMCAM + DM556D + motor de passo).
* Estrutura detalhada do repositório GitHub.
* Especificação de todas as APIs REST e WebSocket.
* Manual do Dashboard.
* Guia de desenvolvimento do SDK.
* Padrões de código.
* Plano de testes.
* Roadmap.
* Tutoriais "passo a passo" para criação de novos Apps.
* Guia completo para desenvolver o **Person Tracker**.
* Guia completo para desenvolver o **GeoFissura**.

## 🎯 Minha recomendação final

Antes de escrever a primeira linha de código, eu faria ainda um documento **21**, que não estava previsto inicialmente, mas considero essencial:

### **Documento 21 – Plano de Implementação (Implementation Guide)**

Esse documento quebrará toda a arquitetura em **sprints de desenvolvimento**, por exemplo:

* Sprint 1: criar a estrutura do repositório e o esqueleto do firmware.
* Sprint 2: implementar o Camera Engine.
* Sprint 3: implementar o Motion Engine.
* Sprint 4: integrar câmera e motor.
* Sprint 5: implementar o Person Tracker.
* Sprint 6: construir o Dashboard.
* Sprint 7: adicionar Vision Engine.
* Sprint 8: preparar a base para o GeoFissura.

Assim, teremos um caminho claro, incremental e validado, transformando toda essa arquitetura em um projeto executável sem perder organização ou qualidade. Na minha opinião, esse será o elo entre a documentação e o desenvolvimento efetivo do SmartCam Platform.
