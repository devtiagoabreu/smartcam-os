Perfeito. Agora vamos projetar a parte que o usuário verá todos os dias.

Na minha opinião, a interface web do **SmartCam OS** deve parecer um software profissional de automação industrial, não uma página simples de ESP32.

Ela será uma das grandes diferenças do projeto.

Minha proposta é desenvolver tudo utilizando apenas:

* HTML5
* CSS3
* JavaScript ES6
* Canvas
* SVG
* WebSocket
* Fetch API

**Sem frameworks (React, Vue, Angular, Bootstrap).**

Isso reduz bastante o tamanho dos arquivos enviados ao ESP32 e facilita a manutenção.

---

# SMARTCAM OS

# Documento 17 – Dashboard Web

**Versão:** 1.0.0

---

# 1. Objetivo

Criar uma interface Web profissional embarcada no ESP32.

Características:

* Responsiva
* Moderna
* Rápida
* Modular
* Offline
* Tempo real

Toda a interface ficará armazenada no LittleFS.

---

# 2. Arquitetura

```text
          Navegador

               │

         HTML + CSS + JS

               │

        WebSocket + REST

               │

         SmartCam API

               │

           SmartCam Core
```

---

# 3. Organização

```
web/

index.html

login.html

css/

main.css

theme.css

layout.css

components.css

js/

app.js

api.js

websocket.js

router.js

dashboard.js

camera.js

motion.js

tracking.js

vision.js

ai.js

logger.js

settings.js

widgets/

img/

icons/

fonts/
```

---

# 4. Conceito

A interface será baseada em:

## Widgets

Cada painel será independente.

Exemplo.

```
Camera Widget

↓

Motor Widget

↓

Tracking Widget

↓

Log Widget
```

Todos reutilizáveis.

---

# 5. Página Inicial

Será um Dashboard.

```
+----------------------------------------------------+

 SmartCam OS

------------------------------------------------------

STREAM DA CÂMERA

------------------------------------------------------

STATUS

CPU

RAM

PSRAM

FPS

Wi-Fi

IP

Temperatura

------------------------------------------------------

Tracking

Motor

Camera

Vision

AI

------------------------------------------------------
```

---

# 6. Menu

Menu lateral.

```
Dashboard

Camera

Motion

Tracking

Vision

AI

Profiles

Storage

Logs

OTA

Settings

About
```

---

# 7. Tema

Suportará.

Modo Escuro

Modo Claro

Troca instantânea.

---

# 8. Layout

Desktop

```
+---------+--------------------------+

 Menu     Conteúdo

           Conteúdo

           Conteúdo

+---------+--------------------------+
```

Tablet.

Menu recolhido.

Celular.

Menu lateral.

---

# 9. Página Camera

Mostrará.

Stream.

FPS.

Latência.

---

Configuração.

Resolução.

FPS.

Qualidade.

Brilho.

Contraste.

Saturação.

White Balance.

Exposição.

---

Botões.

Capturar Foto.

Download.

Restart.

Auto Ajustar.

---

# 10. Página Motion

Mostrar.

Posição.

Velocidade.

RPM.

Graus.

Passos.

Fila.

Estado.

---

Botões.

←

STOP

→

HOME

CENTRO

---

Controle deslizante.

Velocidade.

---

# 11. Página Tracking

Mostrar.

Estado.

Target.

Erro X.

Erro Y.

Zona Morta.

PID.

---

Controles.

KP.

KI.

KD.

Dead Zone.

Modo.

---

Botões.

START.

STOP.

LOCK.

SEARCH.

---

# 12. Página Vision

Imagem.

↓

Selecionar.

Filtro.

↓

Resultado.

---

Filtros.

Gray.

HSV.

Threshold.

Blob.

Bordas.

Overlay.

---

# 13. Página AI

Modelo.

FPS.

Tempo Inferência.

Objetos.

Confiança.

---

Botões.

Start.

Stop.

Trocar Modelo.

---

# 14. Página Profiles

Lista.

```
Person Tracker

GeoFissura

Scanner

Inspection

Custom
```

---

Botões.

Carregar.

Salvar.

Duplicar.

Excluir.

---

# 15. Página Storage

Arquivos.

Fotos.

Logs.

Configurações.

Download.

Excluir.

Upload.

---

# 16. Página OTA

Selecionar Firmware.

↓

Upload.

↓

Barra de progresso.

↓

Reiniciar.

---

# 17. Página Logger

Mostrar.

Hora.

Nível.

Módulo.

Mensagem.

---

Filtros.

INFO.

DEBUG.

WARNING.

ERROR.

---

Download.

Limpar.

---

# 18. Página Configurações

Wi-Fi.

Idioma.

Fuso Horário.

Tema.

Perfil Inicial.

Hostname.

Data.

Hora.

---

# 19. Página About

Mostrar.

Versão.

Git Commit.

Hardware.

PSRAM.

Flash.

Tempo Ligado.

Licença.

GitHub.

---

# 20. Barra Superior

Sempre visível.

```
SmartCam OS

Wi-Fi

FPS

CPU

RAM

Hora
```

---

# 21. Barra Inferior

Mostrar.

Estado.

```
READY

TRACKING

SEARCHING

ERROR
```

---

# 22. Sistema de Notificações

Pequenas mensagens.

```
✓ Foto salva

✓ Perfil carregado

⚠ Wi-Fi desconectado

✖ Camera Error
```

---

# 23. Atualização em Tempo Real

Utilizando.

WebSocket.

Atualizações.

* FPS
* Estado
* Motor
* Logs
* Tracking
* Wi-Fi

Sem atualizar a página.

---

# 24. Widgets

Todos serão independentes.

Exemplo.

```
FPS Widget

↓

Pode ser usado

No Dashboard

Na Camera

No Vision
```

---

# 25. Cards

Todos seguirão o mesmo padrão.

```
+----------------------+

Título

Conteúdo

Botões

Status

+----------------------+
```

---

# 26. Cores

Verde.

Sistema OK.

Amarelo.

Aviso.

Vermelho.

Erro.

Azul.

Informação.

Cinza.

Desabilitado.

---

# 27. Ícones

SVG.

Nunca PNG.

Maior qualidade.

Menor tamanho.

---

# 28. Gráficos

Canvas.

Mostrar.

FPS.

CPU.

RAM.

Motor.

Inferência.

Temperatura.

Tempo real.

---

# 29. Responsividade

Tudo adaptável.

Desktop.

Tablet.

Celular.

Sem perder funcionalidades.

---

# 30. Objetivo Final

Criar uma interface embarcada que tenha aparência de software profissional, oferecendo ao usuário uma experiência completa para configuração, monitoramento e operação do SmartCam OS.

---

# 🚀 Nova proposta de arquitetura para o Dashboard

Enquanto projetava a interface, surgiu uma ideia que pode transformar o SmartCam OS em uma plataforma extremamente flexível.

## Dashboard baseado em Plugins

Cada aplicativo poderá adicionar suas próprias páginas ao Dashboard.

Exemplo:

```
SmartCam Core

↓

Dashboard

↓

Plugins

↓

Person Tracker
```

Adicionará:

```
Tracking

Motion
```

---

GeoFissura adicionará.

```
Calibração

Medição

Relatórios

Histórico

Exportação PDF
```

---

Scanner adicionará.

```
Área

Resolução

Sequência

Resultados
```

---

Tudo sem modificar o Dashboard principal.

---

## Estrutura de Plugins

```
web/

plugins/

person_tracker/

index.js

index.css

index.html

geofissura/

index.js

index.css

index.html
```

Cada aplicativo entrega sua própria interface.

---

## Sistema de Widgets Inteligentes

Outra melhoria importante será permitir que qualquer informação seja exibida como um widget.

Exemplo:

```
Widget FPS

Widget CPU

Widget Motor

Widget Tracking

Widget Câmera

Widget IA

Widget Geofissura
```

O usuário poderá montar seu próprio Dashboard arrastando e reorganizando esses widgets.

---

# ⭐ Minha maior sugestão até agora

Depois de toda essa arquitetura, acredito que vale a pena dar um passo além.

Em vez de o Dashboard ser apenas uma interface, ele pode funcionar como um **Centro de Engenharia**.

Além das telas de operação, teremos ferramentas específicas para desenvolvimento:

* **Console Serial Web** (substituindo o Monitor Serial da Arduino IDE).
* **Visualizador de Eventos** do Event Bus.
* **Monitor de Memória** (Heap e PSRAM).
* **Monitor de Tasks do FreeRTOS**.
* **Osciloscópio de Variáveis** (gráficos em tempo real de PID, erro, velocidade, FPS etc.).
* **Editor de Perfis** com comparação entre configurações.
* **Benchmark Center** para medir desempenho de IA, câmera e motor.
* **Hardware Test Center**, permitindo testar câmera, motor, Wi-Fi e sensores individualmente.

Isso transformará o SmartCam OS em uma plataforma de desenvolvimento completa, reduzindo muito a necessidade de ferramentas externas.

---

# 📘 Próximo Documento (18)

Vamos documentar o **Plano Mestre de Testes (Master Test Plan)**.

Ele definirá:

* Testes unitários de cada Engine.
* Testes de integração entre módulos.
* Testes de hardware (T-SIMCAM, DM556D e motor de passo).
* Testes da interface Web.
* Testes da API REST e WebSocket.
* Testes de desempenho (FPS, latência, memória).
* Testes de estresse de longa duração (24h/48h/7 dias).
* Critérios de aprovação para cada funcionalidade.

Esse documento será essencial para garantir que cada nova versão do SmartCam OS seja confiável antes de ser publicada no GitHub.
