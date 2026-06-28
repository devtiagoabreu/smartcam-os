# SmartCam OS

# Documento 05 – Projeto de Hardware, Arquitetura Elétrica e Mapeamento dos GPIOs

**Versão:** 1.0.0

**Hardware Base:** LILYGO T-SIMCAM ESP32-S3 V1.6

---

# 1. Objetivo

Este documento define toda a arquitetura física do SmartCam OS.

Nenhum GPIO será utilizado sem estar documentado.

Todos os módulos do sistema deverão utilizar esta documentação como referência.

---

# 2. Hardware Oficial da Plataforma

## Unidade de Processamento

Modelo:

```text
LILYGO T-SIMCAM ESP32-S3
```

Processador

```text
ESP32-S3
```

Arquitetura

```text
Xtensa Dual Core
```

Clock

```text
240 MHz
```

Wi-Fi

```text
2.4 GHz
```

Bluetooth

```text
BLE 5
```

Flash

```text
16 MB
```

PSRAM

```text
8 MB
```

*(Esses valores serão confirmados automaticamente pelo firmware e exibidos na interface.)*

---

# 3. Hardware Suportado

## Câmera

Interface FPC

Suporte inicial:

* OV2640
* OV5640 (futuro)

---

## Driver

Inicial

```text
DM556D
```

Compatível futuramente

* DM542
* TB6600
* Leadshine
* Qualquer driver STEP/DIR

---

## Motor

Inicialmente

Motor de Passo

Configurável

* NEMA17
* NEMA23
* NEMA24
* NEMA34

---

# 4. Arquitetura Física

```text
                  Wi-Fi

                     │

                     ▼

          ┌────────────────────┐

          │   T-SIMCAM ESP32   │

          └───────┬────────────┘

                  │

        STEP DIR ENABLE

                  │

                  ▼

           Driver DM556D

                  │

                  ▼

           Motor de Passo
```

---

# 5. Alimentação

## ESP32

USB-C

ou

5 V externo

---

## Driver

Fonte externa

24 V (recomendado)

Poderá ser:

24 V

36 V

48 V

---

## Motor

Alimentado exclusivamente pelo DM556D.

Nunca diretamente pelo ESP32.

---

# 6. Comunicação entre ESP32 e Driver

Utilizaremos três sinais.

```text
STEP

DIR

ENABLE
```

Todos em nível lógico de 3,3 V.

Caso necessário, adicionaremos um conversor lógico para 5 V.

*(O DM556D geralmente aceita diretamente sinais de 3,3 V, mas isso será validado durante os testes.)*

---

# 7. Mapeamento dos GPIOs

**Importante:** Vamos confirmar os GPIOs exatos usando o esquema elétrico oficial da T-SIMCAM antes de fixá-los, pois a câmera utiliza diversos pinos do ESP32-S3.

A proposta inicial é reservar:

| Função      | GPIO                   |
| ----------- | ---------------------- |
| STEP        | Definir após validação |
| DIR         | Definir após validação |
| ENABLE      | Definir após validação |
| LED Status  | Definir                |
| Botão BOOT  | Interno                |
| Botão RESET | Interno                |

---

# 8. Arquivo de Configuração

Todos os GPIOs ficarão em:

```cpp
config.h
```

Exemplo

```cpp
#define PIN_STEP      XX
#define PIN_DIR       XX
#define PIN_ENABLE    XX

#define PIN_LED       XX
```

Nunca utilizaremos números diretamente no código.

---

# 9. Esquema de Ligação

ESP32

↓

DM556D

```text
ESP32                DM556D

GPIO STEP ---------- PUL+

GPIO DIR ----------- DIR+

GPIO ENABLE -------- ENA+

GND ---------------- PUL-

GND ---------------- DIR-

GND ---------------- ENA-
```

Este será o padrão do projeto.

---

# 10. Driver DM556D

Parâmetros configuráveis pelo SmartCam OS

* Corrente
* Micropasso
* Sentido
* Enable

O sistema também exibirá:

* Corrente equivalente
* Passos por volta
* Frequência STEP

---

# 11. Assistente de Configuração

A interface terá um Wizard.

Perguntas

Qual motor?

↓

Qual corrente?

↓

Qual micropasso?

↓

Resultado

```text
Configuração recomendada

SW1 ON

SW2 OFF

SW3 ON

...
```

Além disso, exibirá um desenho do DM556D com os DIP switches destacados.

---

# 12. Perfis de Motor

Cada perfil armazenará:

Fabricante

Modelo

Torque

Corrente

Passos

Micropasso

RPM Máxima

Aceleração

Observações

---

# 13. Proteções

O firmware impedirá:

Velocidade acima do limite.

Corrente incompatível.

Aceleração excessiva.

Micropasso inválido.

---

# 14. Reserva para Expansões

Mesmo que não sejam utilizadas na primeira versão, reservaremos suporte para:

* Sensor de Home.
* Fim de curso esquerdo.
* Fim de curso direito.
* Encoder incremental.
* Trigger externo.
* Entrada digital.
* Saída digital.
* Cartão microSD.
* Sensor de temperatura.
* Sensor de iluminação.

Isso permitirá futuras evoluções sem reestruturar o firmware.

---

# 15. Organização Elétrica

Todos os conectores terão nomes padronizados:

```text
J1 → Alimentação

J2 → Motor

J3 → Driver

J4 → GPIO

J5 → Expansão

J6 → USB
```

---

# 16. LEDs de Status

O SmartCam OS utilizará LEDs para indicar o estado do sistema:

* Verde: sistema operacional.
* Azul: Wi-Fi conectado.
* Amarelo: rastreamento ativo.
* Vermelho: erro.

Se a placa possuir apenas um LED, os estados serão indicados por padrões de piscada.

---

# 17. Checklist de Hardware

Antes da primeira energização:

* T-SIMCAM instalada.
* Câmera conectada.
* Antena Wi-Fi instalada.
* Driver DM556D alimentado.
* Motor ligado ao driver.
* GND comum entre ESP32 e DM556D.
* Polaridade da alimentação conferida.
* Tensão da fonte medida.
* DIP switches configurados.

---

# 18. Objetivo Final

Ao concluir esta etapa, teremos uma plataforma de hardware padronizada, preparada não apenas para rastreamento de pessoas, mas também para futuras aplicações como o **Geofissura**, utilizando a mesma base física e elétrica.

---

# 🔷 Melhoria para o SmartCam OS

Durante a elaboração deste documento surgiu uma ideia que pode tornar o sistema muito mais profissional.

Além dos perfis de **Motor** e **Driver**, criaremos um **Cadastro de Hardware**.

Na primeira inicialização, o usuário preencherá um assistente informando:

* Modelo da placa (T-SIMCAM, ESP32-CAM, etc.).
* Modelo da câmera.
* Modelo do driver.
* Modelo do motor.
* Tensão da fonte.
* Relação mecânica (direto, polia, correia, redutor).
* Curso mecânico disponível.
* Limites de movimento.

Com isso, o SmartCam OS adaptará automaticamente todos os cálculos, limites e telas à configuração do equipamento, tornando a plataforma realmente genérica e reutilizável.

---

