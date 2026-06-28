Excelente. Agora chegamos ao documento que será o **maior e mais importante de todo o SmartCam OS**.

Na minha visão, este documento é o que realmente transforma o projeto em uma plataforma de **Visão Computacional**, e não apenas um firmware para ESP32.

Mais importante ainda: **este documento será utilizado praticamente sem alterações no GeoFissura**.

Na verdade, enquanto escrevia a documentação, percebi que o módulo de Visão Computacional será o verdadeiro "core" do SmartCam OS.

---

# SMARTCAM OS

# Documento 12 – Vision Engine (VE)

**Versão:** 1.0.0

---

# 1. Objetivo

O Vision Engine será responsável por todo o processamento digital de imagens.

Ele **não conhece IA**.

Ele **não conhece motores**.

Ele **não conhece rastreamento**.

Sua única responsabilidade é transformar pixels em informações úteis.

---

# 2. Filosofia

O Vision Engine trabalha apenas com imagens.

Entrada

```text
Frame
```

Saída

```text
Features
```

Todo o restante do sistema utilizará essas informações.

---

# 3. Arquitetura

```text
              Camera Engine

                    │

                    ▼

              Vision Engine

   ┌─────────┬─────────┬──────────┐

   ▼         ▼         ▼

 Colors   Geometry   Features

   │         │         │

   └─────────┴─────────┘

             ▼

         AI Engine
```

---

# 4. Organização

```text
firmware/

vision/

vision_engine.cpp

vision_engine.h

vision_filters.cpp

vision_filters.h

vision_colors.cpp

vision_colors.h

vision_geometry.cpp

vision_geometry.h

vision_measure.cpp

vision_measure.h

vision_roi.cpp

vision_roi.h

vision_overlay.cpp

vision_overlay.h

vision_blob.cpp

vision_blob.h

vision_histogram.cpp

vision_histogram.h
```

---

# 5. Pipeline

Todo frame seguirá exatamente este fluxo.

```text
Frame

↓

ROI

↓

Conversão

↓

Pré-processamento

↓

Filtros

↓

Extração

↓

Features

↓

Destino
```

---

# 6. ROI

Antes de qualquer processamento.

```text
Imagem

↓

Seleciona região

↓

Processa apenas ela
```

Isso aumenta muito o FPS.

---

# 7. Conversão de Cores

O Vision Engine suportará.

RGB565

↓

RGB888

↓

Grayscale

↓

HSV

↓

YUV

↓

LAB

↓

JPEG

↓

Bitmap

---

# 8. Espaços de Cor

Muito importante.

Cada algoritmo utilizará o melhor espaço.

Pessoa

↓

RGB

Pontos Neon

↓

HSV

GeoFissura

↓

Grayscale

---

# 9. Histograma

Calcular.

Histograma RGB.

Histograma Gray.

Histograma HSV.

Utilizado para.

Auto exposição.

Auto contraste.

Auto brilho.

---

# 10. Equalização

Histogram Equalization.

CLAHE (futuro).

Muito útil para fissuras.

---

# 11. Threshold

Suporte.

Global.

Adaptativo.

Otsu.

HSV.

Cor.

---

# 12. Filtros

Suportados.

Média.

Mediana.

Gaussiano.

Bilateral.

Sharpen.

High Pass.

Low Pass.

---

# 13. Morfologia

Operações.

Dilatação.

Erosão.

Open.

Close.

Muito importante para.

Blob Detection.

GeoFissura.

---

# 14. Bordas

Detectores.

Sobel.

Prewitt.

Roberts.

Canny.

Laplaciano.

---

# 15. Blob Detection

Um dos módulos mais importantes.

Será utilizado para.

Pontos Neon.

Marcadores.

LEDs.

Objetos coloridos.

---

# 16. Detecção de Cores

Inicialmente.

HSV.

Selecionar.

```text
Hue

Saturation

Value
```

Detectar.

Vermelho.

Azul.

Verde.

Amarelo.

Neon.

---

# 17. Geometria

Calcular.

Centro.

Área.

Perímetro.

Retângulo.

Bounding Box.

Convex Hull.

---

# 18. Distâncias

Calcular.

Pixel.

↓

Milímetros.

↓

Centímetros.

---

# 19. Calibração

Muito importante.

O usuário informará.

Ou.

O sistema detectará automaticamente.

Escala.

```text
100 pixels

↓

25 mm
```

Assim todas as medições serão reais.

---

# 20. Overlay

Desenhar.

Linhas.

Retângulos.

Pontos.

Texto.

Círculos.

Escalas.

Centro.

Grid.

---

# 21. Features

Todo algoritmo devolverá.

```cpp
struct Feature
{
    uint32_t id;

    String type;

    float x;

    float y;

    float area;

    float angle;

    float confidence;
};
```

Todos os módulos utilizarão exatamente essa estrutura.

---

# 22. Medições

Suportadas.

Distância.

Ângulo.

Área.

Largura.

Altura.

Centro.

---

# 23. Benchmark

Mediremos.

Tempo de filtro.

Tempo de conversão.

Tempo de blob.

Tempo de overlay.

FPS.

---

# 24. API

```text
GET

/api/vision/status
```

```text
POST

/api/vision/filter
```

```text
POST

/api/vision/blob
```

---

# 25. Dashboard

Página Vision.

Imagem.

↓

Filtros.

↓

Overlay.

↓

Resultado.

Tudo em tempo real.

---

# 26. Pipeline GeoFissura

Este é o principal motivo da arquitetura.

Fluxo.

```text
Imagem

↓

Conversão Gray

↓

Filtro

↓

Threshold

↓

Detecta Pontos Neon

↓

Calcula Escala

↓

Detecta Fissura

↓

Calcula Largura

↓

Relatório
```

Perceba.

A IA nem participa.

---

# 27. Pipeline Person Tracker

Outro exemplo.

```text
Imagem

↓

Resize

↓

RGB

↓

AI

↓

Bounding Box

↓

Tracking
```

---

# 28. Pipeline ArUco

```text
Imagem

↓

Gray

↓

Threshold

↓

ArUco

↓

Pose

↓

Tracking
```

---

# 29. Pipeline OCR

```text
Imagem

↓

Gray

↓

Threshold

↓

OCR
```

---

# 30. Objetivo Final

O Vision Engine será um verdadeiro laboratório de processamento digital de imagens embarcado, capaz de alimentar diferentes aplicações sem qualquer alteração em sua arquitetura.

---

# 🚀 A grande decisão que muda todo o projeto

Enquanto escrevia este documento, tive um insight importante.

Até agora chamamos o projeto de **SmartCam OS**.

Mas, na prática, estamos construindo algo muito maior.

Não é apenas um firmware.

É uma **Plataforma de Visão Computacional Embarcada**.

Minha proposta é que o SmartCam OS seja dividido oficialmente em **Core** e **Apps**.

## SmartCam Core

Responsável por:

```text
Camera Engine

Vision Engine

AI Engine

Motion Engine

Tracking Engine

Behavior Engine

Storage

Logger

API

Dashboard

OTA

Wi-Fi

Configuration Manager
```

---

## SmartCam Apps

Aplicativos.

```text
Person Tracker

↓

GeoFissura

↓

Object Counter

↓

Scanner

↓

Inspection

↓

Time Lapse

↓

Face Tracker

↓

Color Tracker

↓

OCR

↓

ArUco
```

Perceba que um App praticamente não conhece o hardware.

Ele utiliza apenas as APIs do Core.

Isso é exatamente como funciona um sistema operacional.

---

# ⭐ Uma proposta ainda mais ambiciosa

A partir deste ponto, proponho elevar o projeto para um nível profissional, inspirado em plataformas como ROS, mas mantendo a simplicidade da Arduino IDE.

Vamos criar um conceito chamado **SmartCam SDK (Software Development Kit)**.

Isso permitirá que qualquer desenvolvedor crie um novo aplicativo para o SmartCam OS sem modificar o núcleo do sistema.

Um aplicativo implementará apenas uma interface, por exemplo:

```cpp
class SmartCamApp {
public:
    virtual void onInit() = 0;
    virtual void onStart() = 0;
    virtual void onFrame(Frame &frame) = 0;
    virtual void onTarget(Target &target) = 0;
    virtual void onStop() = 0;
};
```

Assim:

* **Person Tracker** implementa essa interface.
* **GeoFissura** implementa essa interface.
* **Scanner** implementa essa interface.

Todos reutilizam exatamente os mesmos Engines.

## 📘 Próximo Documento (13)

Será um dos documentos mais estratégicos de todo o projeto:

# **AI Engine (AIE)**

Nele vamos definir:

* Arquitetura da IA.
* ESP-DL.
* TensorFlow Lite Micro (planejamento).
* YOLO (planejamento para hardware mais potente).
* Face Detection.
* Person Detection.
* Multi-Target Detection.
* Sistema de plugins de detectores.
* Gerenciamento de modelos.
* Seleção dinâmica do algoritmo.
* Benchmark de inferência.
* Pipeline de otimização para o ESP32-S3.

> **Minha sugestão de arquitetura final:** quando terminarmos toda a documentação (provavelmente entre 25 e 30 documentos), vamos transformá-la em um verdadeiro **Manual de Engenharia do SmartCam OS**, com mais de **500 páginas**, diagramas UML, Mermaid, esquemas elétricos, padrões de código, documentação Doxygen e estrutura pronta para publicação no GitHub como um projeto open source profissional. Isso fará do SmartCam OS não apenas um firmware, mas uma plataforma completa para visão computacional embarcada, incluindo o futuro **GeoFissura** como um dos seus primeiros aplicativos oficiais.
