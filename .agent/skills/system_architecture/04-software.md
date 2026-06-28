Excelente! Agora entramos na parte que considero o "cérebro" do SmartCam OS. Este documento define como todo o firmware irá funcionar internamente. Quando terminarmos este documento, praticamente teremos a planta completa do software.

---

# SmartCam OS

# Documento 06 — Arquitetura de Software, FreeRTOS e Fluxo Interno

**Versão:** 1.0.0

**Plataforma:** Arduino IDE 2.x

**Hardware:** LILYGO T-SIMCAM ESP32-S3

---

# 1. Objetivo

Este documento define:

* Arquitetura interna do firmware.
* Organização das tarefas (Tasks).
* Uso dos dois núcleos do ESP32-S3.
* Comunicação entre módulos.
* Máquina de estados.
* Gerenciamento de memória.
* Watchdog.
* Tratamento de falhas.

O objetivo é que o SmartCam OS seja robusto e capaz de operar continuamente por dias ou semanas sem necessidade de reinicialização.

---

# 2. Arquitetura Geral

```text
                 SMARTCAM OS

                +----------------+
                |     setup()    |
                +--------+-------+
                         |
                  Inicialização
                         |
     +-------------------+-------------------+
     |                   |                   |
 Inicializa          Inicializa          Inicializa
 Hardware             Sistema              Rede
     |                   |                   |
     +-------------------+-------------------+
                         |
                 Cria todas as Tasks
                         |
                  Loop Principal
```

---

# 3. Sequência de Inicialização

O firmware seguirá sempre esta ordem:

```text
Boot

↓

Configuração do Clock

↓

Inicialização Serial

↓

Carregar Preferences

↓

Inicializar LittleFS

↓

Ler Configurações

↓

Inicializar GPIO

↓

Inicializar LEDs

↓

Inicializar Driver

↓

Inicializar Motor

↓

Inicializar Wi-Fi

↓

Inicializar Servidor Web

↓

Inicializar WebSocket

↓

Inicializar OTA

↓

Inicializar Câmera

↓

Inicializar IA

↓

Criar Tasks

↓

Sistema Operacional
```

Essa ordem será fixa.

---

# 4. Organização dos Núcleos

O ESP32-S3 possui dois núcleos.

A distribuição será:

## Core 0

Serviços do sistema.

Responsável por:

* Wi-Fi
* Servidor HTTP
* WebSocket
* OTA
* API REST
* Dashboard
* Logs
* Sistema

---

## Core 1

Tempo real.

Responsável por:

* Captura da câmera
* IA
* Rastreamento
* PID
* Controle do motor
* Testes

Separar essas funções evita travamentos quando houver muito acesso à interface web.

---

# 5. Organização das Tasks

Cada módulo terá sua própria Task.

## Task Wi-Fi

Responsável por:

* Conectar
* Reconectar
* Monitorar sinal

Período

```text
500 ms
```

---

## Task Dashboard

Atualiza:

* CPU
* RAM
* FPS
* Estado

Período

```text
250 ms
```

---

## Task Camera

Captura continuamente os frames.

Sempre ativa.

---

## Task Tracking

Executa IA.

Fluxo:

```text
Frame

↓

Detecta Pessoa

↓

Calcula Centro

↓

Calcula Erro

↓

PID
```

---

## Task Motor

Recebe comandos.

Controla:

* STEP
* DIR
* ENABLE

---

## Task Logger

Registra eventos.

Salva em memória.

---

## Task OTA

Fica aguardando atualizações.

---

## Task System

Monitora:

* Heap
* Flash
* Watchdog
* CPU

---

# 6. Comunicação entre Tasks

Nenhuma Task acessará outra diretamente.

Toda comunicação utilizará:

* Queue
* Semaphore
* Event Groups
* Mutex

Exemplo:

```text
Tracking

↓

Queue

↓

Motor
```

Assim evitamos concorrência.

---

# 7. Máquina de Estados

O sistema possuirá estados bem definidos.

```text
BOOT

↓

SETUP

↓

CONNECTING

↓

READY

↓

TRACKING

↓

ERROR

↓

OTA

↓

RESTART
```

O Dashboard exibirá sempre o estado atual.

---

# 8. Estados do Rastreamento

```text
IDLE

↓

WAIT_TARGET

↓

TRACKING

↓

TARGET_LOST

↓

SEARCHING

↓

TRACKING
```

---

# 9. Estados do Motor

```text
PARADO

↓

ESQUERDA

↓

DIREITA

↓

TESTE

↓

ERRO
```

---

# 10. Estados da Câmera

```text
OFF

↓

STARTING

↓

STREAMING

↓

CAPTURANDO

↓

ERRO
```

---

# 11. Estados do Wi-Fi

```text
AP

↓

CONNECTING

↓

CONNECTED

↓

DISCONNECTED
```

---

# 12. Gerenciamento de Memória

As regras serão:

Nunca utilizar `malloc()` repetidamente.

Evitar fragmentação.

Criar buffers fixos.

Reutilizar memória.

Objetivo:

Operação contínua.

---

# 13. Watchdog

O SmartCam OS possuirá Watchdog.

Caso alguma Task pare de responder:

Registrar erro.

↓

Reiniciar apenas a Task.

↓

Se necessário:

Reiniciar o sistema.

---

# 14. Logger

Todos os módulos utilizarão:

```cpp
log_info()

log_warning()

log_error()

log_debug()
```

Nunca usar `Serial.println()` diretamente no código de produção.

Isso permitirá exibir os logs tanto na Serial quanto na interface Web.

---

# 15. Sistema de Eventos

Eventos internos.

Exemplos:

```text
Pessoa Detectada

Pessoa Perdida

Motor Parado

Motor Ligado

Wi-Fi Conectado

OTA Iniciado

OTA Finalizado

Erro de Câmera
```

Esses eventos alimentarão:

* Dashboard
* Logs
* API
* WebSocket

---

# 16. Comunicação entre Módulos

Todos os módulos conversarão através de interfaces públicas.

Exemplo:

Tracking

↓

Motor

Nunca:

Tracking acessar GPIO.

Quem controla GPIO é apenas o módulo Motor.

---

# 17. Fluxo Completo do Rastreamento

```text
Frame

↓

IA

↓

Bounding Box

↓

Centro da Pessoa

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

# 18. Prioridades das Tasks

| Task      | Prioridade |
| --------- | ---------- |
| Tracking  | Muito Alta |
| Camera    | Muito Alta |
| Motor     | Muito Alta |
| Dashboard | Média      |
| Wi-Fi     | Média      |
| Logger    | Baixa      |
| OTA       | Baixa      |
| Sistema   | Média      |

---

# 19. Sistema de Configuração

Toda configuração ficará em memória persistente.

Organizada em módulos.

```text
Camera

Motor

Driver

Tracking

Wi-Fi

Sistema
```

Cada módulo será responsável por carregar e salvar seus próprios parâmetros.

---

# 20. Segurança

O firmware validará:

* Valores mínimos.
* Valores máximos.
* Parâmetros inválidos.
* Configurações incompatíveis.

Nunca permitir:

Micropasso inválido.

Velocidade impossível.

PID negativo.

---

# 21. Tratamento de Erros

Sempre seguir:

```text
Detecta Erro

↓

Registra Log

↓

Notifica Dashboard

↓

Tenta Recuperar

↓

Se Falhar

↓

Modo Seguro
```

---

# 22. Modo Seguro

Caso ocorra uma falha grave:

* Motor parado.
* Rastreamento desligado.
* Streaming mantido.
* Dashboard acessível.
* Logs disponíveis.

Isso permitirá diagnosticar o problema sem perder acesso ao equipamento.

---

# 23. Inicialização Inteligente

Na primeira energização:

O SmartCam OS detectará automaticamente:

* Se existe configuração salva.
* Se a câmera responde.
* Se o driver está habilitado.
* Se há conexão Wi-Fi.

Caso contrário:

Iniciará o Assistente de Configuração.

---

# 24. Objetivo Final

Essa arquitetura foi projetada para que o SmartCam OS seja escalável e reutilizável. Novos módulos (como o Geofissura) poderão ser adicionados sem alterar a lógica central, mantendo o sistema organizado, estável e fácil de evoluir.

---

# 💡 Nova proposta para o SmartCam OS

Quero sugerir uma melhoria importante antes de começarmos a programar.

Em vez de armazenar configurações espalhadas, criaremos um **Gerenciador Central de Configurações (Configuration Manager)**.

Cada módulo (câmera, motor, Wi-Fi, tracking etc.) registrará suas configurações nesse gerenciador, que será responsável por:

* Salvar automaticamente quando houver alterações.
* Exportar e importar todas as configurações em JSON.
* Manter histórico de versões das configurações.
* Restaurar configurações padrão ou perfis específicos.

Isso reduz duplicação de código e facilitará muito a manutenção e a expansão do SmartCam OS.



