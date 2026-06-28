Perfeito! Agora chegamos ao documento que vai diferenciar o **SmartCam OS** de um simples projeto de ESP32. A partir daqui vamos projetar um verdadeiro sistema de visão computacional embarcada.

> **Importante:** Vou fazer uma mudança na arquitetura em relação ao que eu havia proposto inicialmente.

Inicialmente eu pensei em usar apenas **ESP-DL** para detectar pessoas.

**Mas isso NÃO será nossa arquitetura definitiva.**

Como seu objetivo é evoluir o SmartCam OS para o **GeoFissura**, precisamos criar um **Pipeline de Visão Computacional**, onde a IA será apenas um dos módulos.

Assim, no futuro, poderemos adicionar:

* Medição de fissuras
* OCR
* QRCode
* ArUco Marker
* Blob Detection
* Color Tracking
* Medição dimensional
* Reconhecimento de objetos

sem alterar a arquitetura do sistema.

Essa mudança vai economizar centenas de horas no futuro.

---

# SMARTCAM OS

# Documento 08 – Arquitetura Completa da Visão Computacional

Versão 1.0.0

---

# 1. Objetivo

Criar um Pipeline de Processamento de Imagem totalmente modular.

Nunca escreveremos código diretamente dentro do módulo da câmera.

A câmera apenas fornece frames.

Todo o restante ocorre em módulos independentes.

---

# 2. Arquitetura Geral

```text
                CAMERA

                   │

                   ▼

          Frame Capture Engine

                   │

                   ▼

         Image Processing Engine

                   │

      ┌────────────┼────────────┐

      ▼            ▼            ▼

  AI Engine   Vision Engine   Recorder

      │            │

      ▼            ▼

 Tracking      Measurements

      │

      ▼

 Motor Controller
```

---

# 3. Organização do Projeto

```text
firmware/

vision/

    frame.cpp

    preprocess.cpp

    colors.cpp

    filters.cpp

    geometry.cpp

    drawing.cpp

    roi.cpp

ai/

    person.cpp

    face.cpp

    detector.cpp

tracking/

motor/

camera/
```

Observe que IA e Visão Computacional são módulos diferentes.

---

# 4. Pipeline

Cada frame seguirá sempre esta sequência.

```text
Captura

↓

Pré-processamento

↓

Conversão

↓

ROI

↓

IA

↓

Tracking

↓

Motor

↓

Dashboard
```

---

# 5. Captura

A câmera nunca será acessada diretamente.

Sempre através de:

```cpp
Frame frame;

camera_capture(frame);
```

Isso permitirá trocar a câmera futuramente.

---

# 6. Pré-processamento

Antes da IA.

Poderemos aplicar:

Correção

Brilho

Contraste

Nitidez

Redução de ruído

Balanceamento de branco

Gamma

---

# 7. Conversão

Dependendo do algoritmo.

RGB565

↓

RGB888

↓

Grayscale

↓

YUV

↓

JPEG

Tudo automático.

---

# 8. ROI

Região de Interesse.

Inicialmente:

Imagem inteira.

Futuramente:

Somente uma área.

Isso aumenta muito o FPS.

---

# 9. Image Processing Engine

Será responsável por:

Filtros

Detecção de cores

Morfologia

Threshold

Bordas

Histogramas

Blob

Operações geométricas

Nada disso ficará na IA.

---

# 10. AI Engine

Responsável apenas por:

Detecção

Classificação

Bounding Box

Confiança

Nada além disso.

---

# 11. Vision Engine

Responsável por:

Linhas

Círculos

Pontos

Distâncias

Ângulos

Escalas

Calibração

Esse módulo será extremamente importante no **GeoFissura**.

---

# 12. Tracking Engine

Recebe:

Bounding Box

↓

Centro

↓

Erro

↓

PID

↓

Motor

---

# 13. Frame Buffer

Sempre existirão dois buffers.

```text
Frame Atual

Frame Anterior
```

Isso permitirá:

Comparação

Movimento

Diferenças

---

# 14. Estrutura Frame

```cpp
struct Frame
{
    uint16_t width;

    uint16_t height;

    uint8_t *buffer;

    uint32_t timestamp;
};
```

Todos os módulos trabalharão com essa estrutura.

---

# 15. Vision Objects

Padronização.

Pessoa

```cpp
struct VisionObject
{
    int x;

    int y;

    int width;

    int height;

    float confidence;
};
```

No futuro.

Fissura.

QR Code.

Marcadores.

Tudo utilizará a mesma estrutura.

---

# 16. Tracking

Fluxo.

```text
Bounding Box

↓

Centro X

↓

Erro

↓

PID

↓

Motor
```

Erro.

```text
Erro = CentroImagem - CentroObjeto
```

---

# 17. Zona Morta

Muito importante.

```text
|---------|

    X
```

Enquanto o objeto permanecer nessa região:

Motor parado.

Evita tremores.

---

# 18. Pessoa Perdida

Fluxo.

```text
Pessoa Sumiu

↓

Espera 1 segundo

↓

Ainda Sumiu?

↓

Inicia Busca
```

---

# 19. Estratégia de Busca

Inicialmente.

Última direção conhecida.

```text
Pessoa saiu

↓

Direita

↓

Motor gira lentamente

↓

Pessoa encontrada

↓

Tracking
```

---

# 20. Bounding Box

O Dashboard desenhará.

Retângulo.

Centro.

Confiança.

FPS.

---

# 21. Sobreposição

Também desenharemos.

Centro da câmera.

Centro da pessoa.

Linha ligando ambos.

---

# 22. Futuro GeoFissura

O Pipeline continuará exatamente igual.

A única diferença.

Em vez de.

Pessoa.

Teremos.

```text
Imagem

↓

Pré-processamento

↓

Detecção da Fissura

↓

Detecção dos Pontos Neon

↓

Medição

↓

Relatório
```

Perceba.

Não muda a arquitetura.

Muda apenas o módulo Vision.

---

# 23. Futuro ArUco

Também entra aqui.

```text
Imagem

↓

ArUco

↓

Pose

↓

Distância

↓

Orientação
```

---

# 24. Futuro OCR

Mesmo Pipeline.

---

# 25. Futuro QRCode

Mesmo Pipeline.

---

# 26. Desenho do Pipeline

```text
             CAMERA

                │

                ▼

         Frame Capture

                │

                ▼

        Image Processing

                │

      ┌─────────┼──────────┐

      ▼         ▼          ▼

     IA      Vision      Recorder

      │         │

      ▼         ▼

   Tracking   Measurements

        \      /

         ▼    ▼

     Motor Controller

             │

             ▼

         Dashboard
```

---

# 27. Objetivo Final

Essa arquitetura permitirá que o SmartCam OS evolua por muitos anos sem precisar ser reescrito. O módulo de visão computacional será independente da câmera, da IA e do controle do motor, permitindo adicionar novos algoritmos apenas criando novos "plugins" de processamento.

---

# 🚀 A partir do próximo documento, o projeto entra em outro nível

Até agora documentamos **o sistema**.

Agora vamos documentar **cada módulo como se fosse um produto comercial**.

Os próximos documentos terão aproximadamente **20 a 30 páginas cada**.

Vamos detalhar:

* Fluxogramas.
* Diagramas UML.
* Sequência de chamadas.
* Estruturas C++.
* Classes.
* Interfaces.
* Eventos.
* API completa.
* JSON de comunicação.
* WebSocket.
* Máquina de estados.
* Casos de uso.
* Diagramas Mermaid.
* Plano de testes.
* Critérios de aceitação.

