---

# SMARTCAM-OS

# Documento 03 — Estrutura Completa do Projeto (Arduino IDE + GitHub)

**Versão:** 1.0.0

---

# 1. Ambiente Oficial de Desenvolvimento

O SmartCam OS será desenvolvido oficialmente utilizando:

| Ferramenta          | Versão          |
| ------------------- | --------------- |
| Arduino IDE         | 2.x             |
| Framework           | Arduino ESP32   |
| Linguagem           | C++17 (Arduino) |
| Controle de versão  | Git             |
| Hospedagem          | GitHub          |
| Sistema de Arquivos | LittleFS        |

**Observação:** Embora o projeto seja modular e profissional, toda a compilação será feita pela Arduino IDE para manter a simplicidade de instalação.

---

# 2. Estrutura Oficial do Repositório

```text
smartcam-os/
│
├── .github/
│   ├── ISSUE_TEMPLATE/
│   ├── workflows/
│   └── PULL_REQUEST_TEMPLATE.md
│
├── assets/
│   ├── logo/
│   ├── screenshots/
│   └── diagrams/
│
├── data/
│
├── docs/
│
├── examples/
│
├── firmware/
│
├── tools/
│
├── .gitignore
├── CHANGELOG.md
├── CONTRIBUTING.md
├── LICENSE
├── README.md
└── ROADMAP.md
```

---

# 3. Pasta firmware

Toda a lógica do ESP32 ficará aqui.

```text
firmware/

SmartCamOS.ino

config.h

globals.h

globals.cpp
```

Depois virão os módulos.

```text
firmware/

camera/

motor/

driver/

tracking/

wifi/

dashboard/

api/

storage/

ota/

pid/

tests/

utils/

system/
```

---

# 4. Organização de cada módulo

Exemplo:

```text
motor/

motor.h

motor.cpp
```

Jamais criar arquivos gigantes.

Cada módulo deve ter responsabilidade única.

---

# 5. Configuração Global

Arquivo

```text
config.h
```

Será o único local onde ficam:

## GPIO

```cpp
PIN_STEP

PIN_DIR

PIN_ENABLE
```

---

## Wi-Fi

SSID AP

Senha AP

---

## Nome do Sistema

```cpp
SMARTCAM_OS
```

---

## Versão

```cpp
1.0.0
```

---

## Limites

Velocidade máxima

Aceleração máxima

Resolução padrão

---

# 6. globals.h

Aqui ficarão apenas variáveis compartilhadas.

Exemplo

```cpp
extern bool trackingEnabled;

extern bool wifiConnected;

extern int fps;

extern float kp;
```

Nunca colocar lógica aqui.

---

# 7. Organização do LittleFS

A pasta **data** será enviada diretamente para o ESP32.

Estrutura:

```text
data/

index.html

css/

style.css

dashboard.css

camera.css

motor.css

tracking.css

system.css

js/

main.js

camera.js

motor.js

tracking.js

wifi.js

dashboard.js

system.js

images/

icons/

fonts/
```

---

# 8. Organização do HTML

Cada tela será construída como um componente.

Exemplo

```text
Dashboard

↓

Camera

↓

Motor

↓

Tracking

↓

Sistema
```

Tudo carregado dinamicamente.

---

# 9. Organização do CSS

Separado por responsabilidade.

Nunca utilizar um único CSS enorme.

---

# 10. Organização do JavaScript

Cada módulo possui seu JavaScript.

```text
camera.js

motor.js

tracking.js

wifi.js

system.js
```

---

# 11. Organização da API

Todos os endpoints terão o mesmo padrão.

```text
/api/
```

Exemplo

```text
/api/status

/api/system

/api/camera

/api/motor

/api/tracking

/api/config
```

---

# 12. Organização das Configurações

Tudo será salvo em JSON.

Exemplo

```json
{
    "wifi": {},
    "motor": {},
    "driver": {},
    "tracking": {},
    "camera": {},
    "system": {}
}
```

Isso facilitará backup e restauração.

---

# 13. Organização do Código

Cada arquivo deverá possuir:

```cpp
Includes

↓

Defines

↓

Variáveis

↓

Setup

↓

Funções Públicas

↓

Funções Privadas
```

Sempre nesta ordem.

---

# 14. Organização das Funções

Exemplo:

```cpp
motor_init();

motor_move();

motor_stop();

motor_set_speed();

motor_get_status();
```

Padrão:

```text
modulo_acao()
```

Nunca utilizar abreviações.

---

# 15. Organização do Git

Commits pequenos.

Exemplos

```
feat: adiciona controle do motor

fix: corrige conexão Wi-Fi

docs: atualiza documentação

style: melhora dashboard

refactor: reorganiza módulo camera

test: adiciona teste do driver
```

---

# 16. Organização das Branches

```
main

develop

feature/*
```

Exemplo

```
feature/motor

feature/camera

feature/tracking

feature/dashboard

feature/api
```

---

# 17. Organização do README

O README deverá conter:

* Logo
* Descrição
* Fotos
* Vídeo
* Recursos
* Hardware suportado
* Instalação
* Estrutura do projeto
* Roadmap
* Licença

---

# 18. Organização da Documentação

Toda alteração relevante deverá atualizar a documentação correspondente em `docs/`.

O código e a documentação deverão evoluir juntos.

---

# 19. Política de Versionamento

Utilizaremos **Versionamento Semântico (SemVer)**:

```
1.0.0
```

Onde:

* **Major:** mudanças incompatíveis.
* **Minor:** novos recursos compatíveis.
* **Patch:** correções de bugs.

Exemplos:

```
1.0.0
1.0.1
1.1.0
2.0.0
```

---

# 20. Objetivo desta Estrutura

Ao seguir esta organização:

* O projeto permanecerá organizado mesmo com dezenas de milhares de linhas de código.
* Novos módulos poderão ser adicionados sem impactar os existentes.
* A documentação acompanhará a evolução do software.
* A migração futura para outras ferramentas (como PlatformIO) será simples, caso algum dia seja desejada.

---

# Próximo Documento


Excelente. Antes de continuar, vou fazer uma melhoria no projeto.

Até agora pensamos apenas como "firmware". A partir deste documento vamos pensar como uma **aplicação profissional**, semelhante à interface de um equipamento industrial (Siemens, WEG, Omron, Schneider, Keysight, Fluke, etc.).

A interface será algo que qualquer cliente poderia utilizar sem treinamento.

---

# SMARTCAM-OS

# Documento 04 — Especificação Completa da Interface Web

Versão 1.0.0

---

# Objetivo

Toda operação do SmartCam OS deverá ser realizada através da interface Web.

Nenhum parâmetro operacional exigirá recompilação do firmware.

A interface deverá ser moderna, rápida e intuitiva.

---

# Características

✔ Responsiva

✔ Tema Escuro

✔ Atualização em tempo real

✔ Compatível com celular

✔ Compatível com tablet

✔ Compatível com computador

✔ WebSocket

✔ Layout Industrial

---

# Tela de Login

Ao acessar o IP do ESP32.

```
+----------------------------------------------------+

                  SMARTCAM OS

               Bem-vindo

Usuário

______________________

Senha

______________________

☑ Lembrar Login

[ ENTRAR ]

Versão 1.0.0

+----------------------------------------------------+
```

---

# Dashboard

Após login.

```
+------------------------------------------------------------+

 LOGO

 Dashboard

 Câmera

 Rastreamento

 Motor

 Driver

 Testes

 Wi-Fi

 Sistema

 Logs

--------------------------------------------------------------

                SMARTCAM OS

--------------------------------------------------------------

Vídeo ao Vivo

+-----------------------------+

                             |

                             |

                             |

                             |

+-----------------------------+

FPS

18

Motor

Parado

Tracking

Pessoa Detectada

CPU

23%

RAM

48%

Wi-Fi

Excelente

IP

192.168.0.150

--------------------------------------------------------------

```

Tudo atualizado automaticamente.

---

# Barra Superior

Sempre visível.

```
SmartCam OS

Wi-Fi

IP

Temperatura

Hora

Usuário

```

---

# Barra Lateral

Sempre fixa.

```
Dashboard

Câmera

Rastreamento

Motor

Driver

Testes

Wi-Fi

Sistema

Logs

Ajuda

Sobre
```

---

# Dashboard

Widgets

## Vídeo

Maior área da tela.

---

## Estado do Motor

Mostrar

Direção

Velocidade

Passos

Aceleração

---

## Rastreamento

Mostrar

Pessoa Detectada

Confiança

Centro

FPS IA

---

## Sistema

CPU

RAM

Flash

Temperatura

Tempo Ligado

---

## Wi-Fi

SSID

RSSI

IP

Gateway

---

# Página Câmera

```
Vídeo

+

Configurações
```

Configurações

Resolução

```
QQVGA

QVGA

VGA

SVGA
```

Qualidade

Slider

Brilho

Slider

Contraste

Slider

Saturação

Slider

Exposição

Slider

Flip

Checkbox

Espelho

Checkbox

---

Botões

Capturar Foto

Baixar Foto

Salvar Configuração

Restaurar Padrão

---

# Página Rastreamento

Modo

```
○ Desligado

○ Detectar Pessoa

○ Detectar Rosto
```

Mostrar Bounding Box

☑

Mostrar Centro

☑

Mostrar FPS

☑

Zona Morta

Slider

Velocidade Máxima

Slider

KP

Slider

KI

Slider

KD

Slider

Botões

Iniciar

Parar

---

# Página Motor

Visualização

```
←

■

→
```

Botões

Esquerda

Direita

Parar

Movimento Contínuo

Mover 10 passos

Mover 100 passos

Mover 1000 passos

Mover 1°

Mover 10°

Mover 90°

Mover 180°

Mover 360°

---

Velocidade

Slider

Aceleração

Slider

Desaceleração

Slider

---

Status

Motor

Ligado

Posição

Velocidade

RPM

---

# Página Driver

Driver

DM556D

Motor

NEMA

Corrente

Micropasso

Enable

Inverter DIR

Inverter STEP

---

## DIP Switch

O sistema desenhará exatamente o driver.

Exemplo

```
SW1  ON

SW2  OFF

SW3  ON

SW4  OFF
```

Mais interessante.

Faremos um desenho do DM556D.

As chaves mudam visualmente.

Como se fosse um simulador.

---

# Página Testes

Será uma das maiores.

Separada em cartões.

---

## Teste STEP

Botão

Executar

---

## Teste DIR

Botão

Executar

---

## Teste ENABLE

Botão

Executar

---

## Teste Velocidade

Slider

Executar

---

## Teste Aceleração

Executar

---

## Teste Completo

Executar

O sistema executará automaticamente todos os testes.

---

# Página Wi-Fi

Lista das redes.

Botão Atualizar.

Conectar.

Esquecer.

IP Fixo.

DNS.

Gateway.

---

# Página Sistema

OTA

Backup

Restaurar

Exportar JSON

Importar JSON

Reiniciar

Reset de fábrica

---

# Página Logs

Tabela.

```
Hora

Módulo

Evento

Descrição
```

Filtros

Motor

Wi-Fi

Tracking

Sistema

OTA

Erro

Exportar CSV.

---

# Página Sobre

Informações.

Versão.

Hardware.

Licença.

GitHub.

Autores.

---

# Tema

Cores

Azul

Cinza Escuro

Branco

Verde

Vermelho

Laranja

Sem exageros.

Interface limpa.

---

# Ícones

Utilizar

Bootstrap Icons

ou

Material Icons.

Nada de imagens pesadas.

---

# Responsividade

Desktop

Menu lateral aberto.

Tablet

Menu recolhível.

Celular

Menu hambúrguer.

---

# Atualização em Tempo Real

Tudo utilizará WebSocket.

Nada de atualizar a página.

---

# Objetivo da Interface

O usuário deverá conseguir operar completamente o SmartCam OS apenas pelo navegador.

Inclusive:

* Configurar Wi-Fi
* Configurar motor
* Configurar driver
* Visualizar câmera
* Iniciar rastreamento
* Ajustar PID
* Executar testes
* Atualizar firmware
* Exportar configurações
* Restaurar backup

sem necessidade de conectar um computador via USB após a primeira gravação.

---

## 💡 Melhoria importante para o projeto

A partir deste ponto, proponho adicionar um conceito que fará muita diferença na usabilidade: **Assistentes (Wizards)**.

Em vez de apenas oferecer telas de configuração, o SmartCam OS terá assistentes guiados, por exemplo:

* **Primeira configuração** (Wi-Fi, idioma, senha e câmera).
* **Configuração do motor** (tipo de motor, driver, corrente, micropasso e teste automático).
* **Calibração do rastreamento** (ajuste de PID e zona morta).
* **Diagnóstico do sistema** (verifica câmera, memória, Wi-Fi e motor).

Isso tornará o sistema muito mais amigável, especialmente para quem estiver utilizando a plataforma pela primeira vez.

---


