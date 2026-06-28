Perfeito. Agora entramos na parte que, na minha opinião, será o maior diferencial do **SmartCam OS**.

A maioria dos projetos de ESP32 controla motores com `digitalWrite()`, `delayMicroseconds()` e algumas funções simples.

**Nós NÃO faremos isso.**

Vamos desenvolver um **Motor Control Engine (MCE)**, semelhante ao conceito utilizado em controladores industriais e firmwares como GRBL, Marlin e Klipper, porém totalmente adaptado ao SmartCam OS.

Isso permitirá que o mesmo motor seja utilizado para:

* Seguir pessoas
* Posicionar uma câmera
* Fazer varreduras automáticas
* Controlar o Geofissura
* Construir um PTZ profissional

Tudo utilizando exatamente o mesmo módulo.

---

# SMARTCAM OS

# Documento 09 – Motor Control Engine (MCE)

Versão 1.0.0

---

# 1. Objetivo

Desenvolver um controlador universal para motores de passo baseado em sinais STEP/DIR/ENABLE.

O MCE será completamente independente da câmera e da IA.

Sua única responsabilidade será movimentar o motor da forma mais precisa possível.

---

# 2. Filosofia

O Motor Control Engine nunca saberá:

* quem pediu o movimento;
* por que o movimento foi solicitado;
* qual algoritmo está utilizando o motor.

Ele apenas recebe comandos.

Exemplo:

```text
Mover 500 passos

↓

Executar
```

ou

```text
Mover 15°

↓

Executar
```

ou

```text
Velocidade = 350 RPM

↓

Executar
```

---

# 3. Arquitetura

```text
           Dashboard

               │

               ▼

        Motion Planner

               │

               ▼

         Motion Queue

               │

               ▼

     Motor Control Engine

               │

               ▼

       Driver STEP/DIR

               │

               ▼

           Motor
```

---

# 4. Organização

```text
firmware/

motor/

    motor.cpp

    motor.h

    motion.cpp

    motion.h

    planner.cpp

    planner.h

    queue.cpp

    queue.h

    homing.cpp

    homing.h
```

---

# 5. Camadas

Dividiremos o motor em cinco camadas.

```text
API

↓

Motion Planner

↓

Motion Queue

↓

Motor Engine

↓

GPIO
```

Nenhum módulo poderá acessar GPIO diretamente.

---

# 6. API Pública

O restante do sistema utilizará apenas estas funções.

```cpp
motor_init();

motor_enable();

motor_disable();

motor_stop();

motor_home();

motor_move_steps();

motor_move_degree();

motor_move_mm();

motor_set_speed();

motor_set_acceleration();

motor_is_busy();

motor_get_position();

motor_reset_position();
```

---

# 7. Tipos de Movimento

O SmartCam OS suportará:

Movimento absoluto

```text
Ir para 120°
```

Movimento relativo

```text
Mover +20°
```

Movimento contínuo

```text
Mover para direita
```

Movimento temporizado

```text
Mover durante 5 segundos
```

Movimento sincronizado

(Futuro Pan/Tilt)

---

# 8. Motion Planner

Será responsável por transformar comandos em trajetórias.

Exemplo.

Usuário.

```text
180°
```

Planner.

```text
180°

↓

6400 passos

↓

Perfil de velocidade

↓

Fila
```

---

# 9. Motion Queue

Todos os movimentos entram em uma fila.

Exemplo.

```text
Mover 30°

↓

Esperar

↓

Mover -15°

↓

Esperar

↓

Mover 90°
```

A fila executa automaticamente.

---

# 10. Perfis de Velocidade

Suportaremos.

Constante

```text
──────────────
```

Linear

```text
╱──────────╲
```

Trapezoidal

```text
╱────────╲
```

S-Curve

```text
⌒────────⌒
```

A S-Curve será a recomendada para evitar vibrações.

---

# 11. Controle por Graus

Muito importante.

O usuário nunca precisará pensar em passos.

Exemplo.

```text
Girar 90°
```

O sistema calcula.

```text
Passos

↓

Micropasso

↓

RPM

↓

Pulsos
```

---

# 12. Controle por Milímetros

Reservado para o GeoFissura.

```text
Mover 5 mm
```

O cálculo dependerá do fuso, correia ou redutor configurado no perfil do hardware.

---

# 13. Controle por RPM

Também disponível.

```text
250 RPM
```

---

# 14. Controle por PPS

Pulsos por segundo.

Utilizado para testes.

---

# 15. Motion Engine

Recebe:

```text
Destino

↓

Velocidade

↓

Aceleração

↓

Direção
```

Gera os pulsos STEP.

---

# 16. Geração dos Pulsos

**Nunca utilizaremos `delayMicroseconds()` para gerar STEP.**

Utilizaremos:

* Timer por hardware
* Interrupções
* Controle preciso de frequência

Isso garante estabilidade e permite que o ESP32 continue executando câmera, IA e servidor web simultaneamente.

---

# 17. Controle de Direção

Antes de qualquer movimento.

```text
DIR

↓

Tempo mínimo

↓

STEP
```

Respeitando o tempo exigido pelo DM556D.

---

# 18. Enable

O Driver poderá permanecer.

Sempre ligado.

Ou.

Desligar automaticamente após alguns segundos sem movimento.

Configuração.

```text
Tempo Idle

↓

5 segundos
```

---

# 19. Posição Atual

Sempre manteremos.

```cpp
int64_t current_position;
```

Nunca perderemos a posição lógica.

---

# 20. Zero Mecânico

Também teremos.

```cpp
int64_t home_position;
```

---

# 21. Homing

Na V1 ficará preparado.

Na V2.

```text
Liga

↓

Vai lentamente

↓

Sensor

↓

Para

↓

Recuo

↓

Confirma

↓

Zero
```

---

# 22. Soft Limits

O usuário configura.

Esquerda.

```text
-90°
```

Direita.

```text
+90°
```

O motor nunca ultrapassa.

---

# 23. Hard Limits

Utilizando sensores.

Futuro.

---

# 24. Segurança

Nunca permitir.

RPM negativa.

Micropasso inválido.

Velocidade acima do permitido.

Destino fora do limite.

---

# 25. Rastreamento

O Tracking nunca controlará STEP.

Ele apenas envia.

```text
Erro = +32 pixels
```

O Motion Planner decide.

```text
Mover 120 passos
```

---

# 26. Dashboard

Página Motor.

Mostrar.

```text
Posição

Velocidade

RPM

Passos

Graus

Estado

Fila

Temperatura Driver (futuro)
```

---

# 27. Testes

Tela exclusiva.

### Teste STEP

100 passos

500 passos

1000 passos

10000 passos

---

### Teste DIR

Esquerda.

Direita.

---

### Teste Enable

Liga.

Desliga.

---

### Teste RPM

50

100

200

500

1000

---

### Teste Perfil

Linear.

Trapezoidal.

S-Curve.

---

### Teste Completo

Executa todos.

Gera relatório.

---

# 28. API

```text
GET

/api/motor/status

/api/motor/position

/api/motor/config
```

---

POST

```text
/api/motor/move

/api/motor/home

/api/motor/stop

/api/motor/config
```

---

# 29. JSON

Mover.

```json
{
    "mode":"degree",
    "value":45
}
```

---

Mover.

```json
{
    "mode":"step",
    "value":1200
}
```

---

# 30. Objetivo Final

Ao concluir o Motor Control Engine teremos um módulo totalmente independente, reutilizável e preparado para aplicações muito além do rastreamento de pessoas.

---

# 🚀 Nova decisão de arquitetura (muito importante)

Enquanto escrevia este documento, percebi que podemos transformar o SmartCam OS em algo ainda mais profissional.

Em vez de pensar apenas em um motor, vamos projetar desde o início uma arquitetura para **eixos**.

Ou seja, o sistema não conhecerá "motor", mas sim **Axis**.

Exemplo:

```text
Axis X

↓

Motor
```

```text
Axis Y

↓

Motor
```

```text
Axis Z

↓

Motor
```

Na primeira versão, teremos apenas o **Axis PAN**, mas toda a arquitetura já ficará preparada para:

* **Axis PAN** (horizontal)
* **Axis TILT** (vertical)
* **Axis FOCUS**
* **Axis ZOOM**
* **Axis LINEAR** (Geofissura)
* **Axis ROTARY** (mesa giratória)

Isso significa que o **Motor Control Engine** se transformará em um **Motion Control Engine**, semelhante ao que controladores industriais utilizam.

## 📌 Minha proposta

A partir do **Documento 10**, vou fazer uma pequena mudança de nomenclatura no projeto:

* **Motor Control Engine (MCE)** passa a ser **Motion Control Engine (MCE)**.
* O conceito principal deixa de ser "motor" e passa a ser "eixo (Axis)".
* Toda a API será baseada em eixos (`axis_pan`, `axis_tilt`, etc.).

Essa decisão praticamente não altera a complexidade da V1, mas abre caminho para transformar o SmartCam OS em uma plataforma completa de automação e visão computacional.

**Na minha opinião, essa é uma das melhores decisões que podemos tomar agora, antes de escrever a primeira linha de código.** Ela evitará uma grande refatoração quando chegarmos ao módulo PTZ e, principalmente, ao **GeoFissura**, que poderá utilizar um eixo linear para posicionar a câmera automaticamente.
