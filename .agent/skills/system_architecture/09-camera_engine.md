Excelente. Agora chegamos ao módulo que alimenta todo o SmartCam OS.

Na maioria dos projetos ESP32-CAM, a câmera é inicializada uma vez e esquecida.

**Nós não faremos isso.**

A câmera será tratada como um equipamento profissional, semelhante ao que ocorre em sistemas industriais de visão computacional.

Ela será totalmente configurável em tempo real, sem reiniciar o ESP32.

Além disso, este módulo será a base do **GeoFissura**, onde a qualidade da imagem será muito mais importante que a velocidade.

---

# SMARTCAM OS

# Documento 11 – Camera Engine (CE)

**Versão:** 1.0.0

**Hardware:** LILYGO T-SIMCAM ESP32-S3

---

# 1. Objetivo

O Camera Engine será responsável exclusivamente por:

* Inicializar a câmera.
* Capturar imagens.
* Configurar o sensor.
* Gerenciar buffers.
* Disponibilizar frames para os demais módulos.
* Fornecer streaming MJPEG.
* Capturar fotos.
* Controlar todos os parâmetros da câmera.

Nenhum outro módulo acessará diretamente a biblioteca da câmera.

---

# 2. Arquitetura

```text
                 Dashboard

                     │

                     ▼

              Camera Engine

     ┌────────────┬──────────────┐

     ▼            ▼              ▼

 Streaming     Capture API     Camera Config

     │            │              │

     └────────────┴──────────────┘

                Driver OV2640
```

---

# 3. Organização do Projeto

```text
firmware/

camera/

camera_engine.cpp

camera_engine.h

camera_driver.cpp

camera_driver.h

camera_stream.cpp

camera_stream.h

camera_capture.cpp

camera_capture.h

camera_settings.cpp

camera_settings.h

camera_buffers.cpp

camera_buffers.h
```

---

# 4. Fluxo

```text
Inicializa

↓

Sensor

↓

Frame Buffer

↓

Captura

↓

Frame

↓

Vision Engine
```

---

# 5. Estados

```text
OFF

↓

BOOTING

↓

READY

↓

STREAMING

↓

CAPTURING

↓

ERROR
```

---

# 6. Configurações

Todas alteráveis pelo Dashboard.

Resolução

FPS

Qualidade JPEG

Brilho

Contraste

Saturação

Nitidez

Espelhamento

Flip Vertical

Exposição

Ganho

White Balance

AEC

AGC

AWB

---

# 7. Resoluções

Suportadas.

```text
96 x 96

QQVGA

HQVGA

QVGA

VGA

SVGA

XGA

HD (quando suportado)
```

O sistema recomendará automaticamente a melhor resolução para cada aplicação.

---

# 8. Perfis de Captura

Teremos perfis prontos.

### Person Tracker

```text
QVGA

Alta velocidade

Baixa latência
```

---

### GeoFissura

```text
VGA

Alta qualidade

Baixo ruído

Exposição fixa
```

---

### Scanner

```text
Máxima resolução

Compressão mínima
```

---

# 9. Buffer

Utilizaremos Double Buffer.

```text
Buffer A

↓

Processamento

Enquanto

Buffer B

↓

Nova captura
```

Evita perda de frames.

---

# 10. Streaming

Servidor MJPEG.

Fluxo.

```text
Frame

↓

JPEG

↓

HTTP

↓

Dashboard
```

---

# 11. Snapshot

O usuário poderá.

Capturar.

↓

Salvar.

↓

Download.

Tudo pela interface.

---

# 12. Captura Programada

Também teremos.

```text
1 foto

↓

A cada 5 segundos

↓

Salvar
```

Reservado para Time Lapse.

---

# 13. ROI (Region of Interest)

O usuário poderá desenhar uma região na imagem.

Apenas essa região será enviada para o Vision Engine.

Aumenta significativamente o desempenho.

---

# 14. Sobreposição (Overlay)

O Camera Engine poderá desenhar sobre o vídeo:

* Cruz central.
* Grade.
* Bounding Box.
* Centro do alvo.
* Eixos.
* Nome do alvo.
* FPS.
* Hora.
* Status.

---

# 15. Benchmark

O sistema medirá continuamente:

* FPS de captura.
* FPS de streaming.
* Latência.
* Tempo médio de captura.

Esses dados serão exibidos em tempo real.

---

# 16. Camera Health

Monitoramento constante.

```text
Frame Timeout

↓

Erro

↓

Reinicializar Driver

↓

Continuar
```

Sem reiniciar todo o ESP32.

---

# 17. API

```text
GET

/api/camera/status

/api/camera/frame

/api/camera/settings
```

---

```text
POST

/api/camera/settings

/api/camera/capture

/api/camera/restart
```

---

# 18. JSON

Exemplo de configuração.

```json
{
  "resolution":"QVGA",
  "quality":12,
  "brightness":0,
  "contrast":0,
  "saturation":0,
  "mirror":false,
  "flip":false,
  "fps":20
}
```

---

# 19. Dashboard

A página "Câmera" será dividida em quatro abas.

### Visualização

* Stream ao vivo.
* FPS.
* Latência.

---

### Ajustes

* Brilho.
* Contraste.
* Saturação.
* White Balance.
* Exposição.
* Ganho.
* Qualidade JPEG.

---

### Captura

* Foto.
* Download.
* Time Lapse.
* Intervalo.

---

### Diagnóstico

* Frames capturados.
* Frames perdidos.
* Buffer.
* Uso de memória.
* Temperatura do sensor (quando disponível).

---

# 20. Auto Tuning

Uma funcionalidade muito interessante.

Ao clicar em:

```text
Auto Ajustar
```

O Camera Engine executará um assistente.

Passos:

1. Captura uma imagem.
2. Mede brilho médio.
3. Mede contraste.
4. Ajusta exposição.
5. Ajusta ganho.
6. Ajusta White Balance.
7. Salva o perfil.

Isso permitirá que o usuário obtenha uma boa imagem sem conhecimento técnico.

---

# 21. Integração com o Vision Engine

O Camera Engine não conhece IA.

Ele apenas entrega um objeto `Frame`.

```cpp
Frame frame;

camera.capture(frame);

vision.process(frame);
```

Essa separação facilita testes e futuras substituições de hardware.

---

# 22. Preparação para o GeoFissura

Este módulo já será preparado para recursos específicos do futuro aplicativo:

* Exposição fixa para evitar variações entre medições.
* Ganho fixo.
* White Balance travado.
* Captura em horários programados.
* Sequência automática de fotos.
* Metadados (data, hora, temperatura, perfil ativo).

---

# 23. Recuperação de Falhas

Se o sensor deixar de responder:

```text
Erro detectado

↓

Interrompe captura

↓

Reinicializa driver

↓

Recria buffers

↓

Retorna ao estado READY
```

Sem reiniciar o restante do sistema.

---

# 24. Objetivo Final

O Camera Engine será um módulo totalmente desacoplado, capaz de alimentar qualquer algoritmo de visão computacional do SmartCam OS com imagens estáveis, configuráveis e monitoradas continuamente.

---

# 🚀 Nova evolução da arquitetura

Enquanto documentava este módulo, ficou claro que o SmartCam OS está crescendo além de um firmware.

Minha proposta é que, ao final da documentação, organizemos o projeto em **Camadas (Layers)**, semelhante a um sistema operacional embarcado.

Teremos algo como:

```text
+----------------------------------------------------+
|                    Applications                    |
| Person Tracker | GeoFissura | Scanner | TimeLapse |
+----------------------------------------------------+
|                  Behavior Engine                   |
+----------------------------------------------------+
| Tracking | Vision | AI | Motion | Camera | Storage |
+----------------------------------------------------+
| Web | API | Config | Logger | OTA | Diagnostics    |
+----------------------------------------------------+
| Drivers | GPIO | Wi-Fi | LittleFS | FreeRTOS       |
+----------------------------------------------------+
|              ESP32-S3 Hardware Layer               |
+----------------------------------------------------+
```

Essa organização permitirá que qualquer novo aplicativo reutilize praticamente 90% do código existente.

---

# 📘 Próximo Documento (12)

## Vision Engine (VE)

Este será, provavelmente, o maior documento de todo o projeto.

Nele definiremos:

* Processamento digital de imagens.
* Conversão de cores.
* Histogramas.
* Equalização.
* Threshold.
* Filtros Gaussianos e Median.
* Morfologia (Erode/Dilate).
* Canny.
* Sobel.
* Detecção de blobs.
* Detecção de círculos.
* Detecção de linhas.
* Medição de distâncias.
* Calibração por escala.
* Detecção dos pontos neon do **GeoFissura**.
* Medição automática da abertura da fissura em milímetros.

Esse documento será a ponte entre o **Person Tracker** e o **GeoFissura**, garantindo que toda a infraestrutura construída até aqui seja reutilizada nas duas aplicações.
