Excelente. Agora chegamos ao documento que considero o **coração do SmartCam OS**.

Se o Motion Control Engine é o "músculo", o **Tracking Engine (TE)** é o "cérebro". Ele decidirá **quando**, **quanto** e **como** mover o eixo para manter uma pessoa centralizada na imagem.

E aqui vou fazer mais uma melhoria importante na arquitetura.

> **Não vamos desenvolver um "Person Tracker".**
>
> Vamos desenvolver um **Target Tracking Engine (TTE)**.

A palavra **Target** (Alvo) muda completamente a filosofia do projeto.

Hoje o alvo é uma pessoa.

Amanhã poderá ser:

* 👤 Pessoa
* 😀 Rosto
* 🟢 Ponto Neon (GeoFissura)
* 📌 ArUco Marker
* 🔴 Objeto vermelho
* 📦 Caixa
* 🚗 Veículo
* 📏 Linha
* ⚫ Centro de uma fissura

Toda a lógica continuará exatamente igual.

---

# SMARTCAM OS

# Documento 10 — Target Tracking Engine (TTE)

**Versão:** 1.0.0

---

# 1. Objetivo

O Target Tracking Engine será responsável por manter um alvo centralizado na imagem.

Ele **não detecta** o alvo.

Ele **não movimenta** o motor.

Ele apenas recebe a posição do alvo e calcula qual deve ser o próximo movimento.

---

# 2. Arquitetura

```text
              AI Engine
                  │
                  ▼
         Bounding Box / Target
                  │
                  ▼
        Target Tracking Engine
                  │
          Calcula Erro
                  │
                  ▼
          Motion Planner
                  │
                  ▼
       Motion Control Engine
```

---

# 3. Responsabilidades

O TTE será responsável por:

* Selecionar o alvo
* Calcular o centro do alvo
* Calcular o erro
* Aplicar filtros
* Aplicar PID
* Gerar comandos de movimento
* Detectar perda do alvo
* Recuperar o alvo

---

# 4. O que NÃO faz

O TTE nunca:

* Acessa GPIO
* Controla STEP
* Captura imagens
* Executa IA

---

# 5. Fluxo

```text
Frame

↓

Detector

↓

Lista de Objetos

↓

Seleciona Alvo

↓

Calcula Centro

↓

Calcula Erro

↓

PID

↓

Motion Planner
```

---

# 6. Estrutura do Alvo

Todos os detectores utilizarão exatamente a mesma estrutura.

```cpp
struct Target
{
    uint32_t id;

    String type;

    int x;

    int y;

    int width;

    int height;

    float confidence;

    uint32_t timestamp;
};
```

---

# 7. Centro do Alvo

O Tracking Engine trabalha apenas com o centro.

```text
cx = x + largura / 2

cy = y + altura / 2
```

---

# 8. Centro da Imagem

Também será calculado.

```text
camera_center_x

camera_center_y
```

---

# 9. Erro

```text
erro_x = centro_imagem - centro_alvo

erro_y = centro_imagem - centro_alvo
```

Inicialmente utilizaremos apenas:

```text
erro_x
```

Porque nosso projeto possui apenas PAN.

---

# 10. Futuro PTZ

Quando existir TILT.

Teremos.

```text
erro_x

erro_y
```

---

# 11. Zona Morta

Muito importante.

```text
───────────────

     ███

───────────────
```

Enquanto o alvo permanecer nessa região.

Motor parado.

---

# 12. Zona Dinâmica

Outra melhoria.

A zona morta poderá variar.

Exemplo.

Pessoa longe.

Zona pequena.

Pessoa perto.

Zona maior.

---

# 13. Filtro

Antes do PID.

Aplicaremos.

Filtro exponencial.

```text
Novo =

Anterior × α

+

Atual × (1−α)
```

Evita tremores.

---

# 14. PID

Entrada.

Erro.

Saída.

Velocidade.

```text
Erro

↓

KP

↓

KI

↓

KD

↓

Velocidade
```

---

# 15. Anti-Windup

Teremos.

Integral limitada.

Evita saturação.

---

# 16. Saturação

Nunca permitir.

```text
Velocidade >

RPM Máxima
```

---

# 17. Seleção do Alvo

Quando houver duas pessoas.

Critérios.

Maior Bounding Box.

Ou.

Maior confiança.

Ou.

Mais próximo do centro.

Configurável.

---

# 18. Prioridade

No Dashboard.

```text
Modo

○ Centro

○ Maior

○ Menor

○ Confiança

○ Manual
```

---

# 19. Travamento

Após selecionar um alvo.

Ele recebe.

```text
ID = 25
```

Enquanto existir.

Continuará sendo seguido.

---

# 20. Perda do Alvo

Fluxo.

```text
Alvo Sumiu

↓

Timer

↓

Continua Sumido

↓

SEARCH
```

---

# 21. Busca

Primeira estratégia.

Continuar.

Na última direção.

---

Segunda.

Oscilar.

```text
←

→

←

→
```

---

Terceira.

Voltar ao centro.

---

# 22. Limites

Nunca movimentar.

Além dos Soft Limits.

---

# 23. Estados

```text
IDLE

↓

SEARCHING

↓

LOCKED

↓

TRACKING

↓

LOST

↓

RECOVERING
```

---

# 24. Eventos

```text
Target Locked

Target Lost

Target Recovered

Tracking Started

Tracking Stopped
```

---

# 25. Dashboard

Mostrar.

```text
Modo

Target ID

Confiança

Erro X

Erro Y

Zona Morta

PID

FPS

Estado
```

---

# 26. API

GET

```text
/api/tracking/status
```

POST

```text
/api/tracking/start
```

POST

```text
/api/tracking/stop
```

POST

```text
/api/tracking/config
```

---

# 27. JSON

```json
{
    "mode":"person",
    "deadzone":20,
    "kp":1.2,
    "ki":0,
    "kd":0.4
}
```

---

# 28. Modo Simulação

Uma funcionalidade muito útil para desenvolvimento.

Sem câmera.

Sem IA.

Moveremos um alvo virtual.

```text
Mouse

↓

Centro

↓

Tracking

↓

Motor
```

Isso permitirá desenvolver e ajustar o algoritmo de rastreamento sem depender da câmera.

---

# 29. Testes

Tela exclusiva.

Teste.

Zona morta.

Teste.

PID.

Teste.

Velocidade.

Teste.

Perda do alvo.

Teste.

Busca.

Tudo visual.

---

# 30. Objetivo Final

O Tracking Engine será totalmente independente do tipo de alvo.

Isso permitirá que o mesmo código seja reutilizado em qualquer aplicação de visão computacional.

---

# 🚀 Grande evolução da arquitetura do SmartCam OS

Aqui está uma decisão que pode transformar o projeto em uma plataforma realmente única.

Até agora falamos de:

* Camera
* Vision
* AI
* Tracking
* Motion

Mas existe uma camada acima de todas elas.

Vamos chamá-la de:

# Behavior Engine (BE)

Ela será responsável por decidir **o comportamento do equipamento**.

Exemplos:

### App "Seguir Pessoa"

```text
Detecta Pessoa

↓

Tracking

↓

Motor
```

---

### App "Scanner"

```text
Mover 10°

↓

Fotografar

↓

Mover 10°

↓

Fotografar
```

---

### App "GeoFissura"

```text
Capturar

↓

Detectar Pontos

↓

Calibrar Escala

↓

Medir Fissura

↓

Gerar Relatório
```

---

### App "Patrulha"

```text
Ir para posição 1

↓

Esperar

↓

Ir para posição 2

↓

Esperar

↓

Loop
```

---

Perceba que a IA, a câmera e o motor continuam os mesmos. O que muda é apenas o **comportamento**.

## 📌 Minha proposta para a arquitetura definitiva

Teremos cinco grandes motores (Engines):

```
Camera Engine

↓

Vision Engine

↓

AI Engine

↓

Target Tracking Engine

↓

Motion Control Engine

↓

Behavior Engine
```

Na prática, o **Behavior Engine** ficará acima de todos eles, orquestrando o fluxo conforme o aplicativo ativo.

Isso significa que o SmartCam OS deixa de ser apenas um firmware para ESP32 e passa a ser uma **plataforma modular de visão computacional e automação**, onde novos aplicativos poderão ser criados reutilizando a mesma infraestrutura.

### Próximo Documento (11)

Será um dos maiores de todo o projeto:

# Camera Engine (CE)

Nele vamos projetar:

* Driver da câmera.
* Streaming MJPEG.
* Captura de alta velocidade.
* Controle automático de exposição.
* Controle de ganho.
* White Balance.
* ROI.
* Múltiplas resoluções.
* Captura de fotos.
* Time Lapse.
* Buffer duplo.
* Benchmark de FPS.
* Interface Web completa para ajuste fino.
* Arquitetura preparada para OV2640, OV5640 e futuras câmeras.

Esse documento será a base para garantir que o SmartCam OS tenha uma câmera robusta, configurável e reutilizável em qualquer aplicação futura.
