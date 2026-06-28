Perfeito. A partir deste documento vamos projetar um dos diferenciais do **SmartCam OS**. Em vez de ter dezenas de configurações espalhadas pelo código, tudo será centralizado em um único gerenciador. Isso permitirá que o mesmo firmware seja usado tanto para rastrear pessoas quanto, no futuro, para o **GeoFissura**, bastando trocar o perfil.

---

# SMARTCAM OS

# Documento 07 — Configuration Manager, Banco de Configurações e Perfis

**Versão:** 1.0.0

---

# 1. Objetivo

O Configuration Manager será o único responsável por:

* Salvar configurações
* Ler configurações
* Exportar
* Importar
* Backup
* Restauração
* Migração entre versões
* Perfis do equipamento

Nenhum módulo gravará dados diretamente no LittleFS ou Preferences.

Toda gravação passará pelo Configuration Manager.

---

# 2. Arquitetura

```text
                  Dashboard

                       │

                       ▼

          Configuration Manager

      ┌────────┬─────────┬────────┐
      │        │         │        │
   Camera    Motor     Tracking  Wi-Fi
      │        │         │        │
      └────────┴─────────┴────────┘
               │
               ▼
      Preferences + LittleFS
```

---

# 3. Organização

```text
config/

config_manager.h

config_manager.cpp

config_schema.h

config_backup.cpp

config_import.cpp

config_export.cpp
```

---

# 4. Estrutura Principal

Toda configuração será um único objeto.

```json
{
    "system": {},
    "wifi": {},
    "camera": {},
    "motor": {},
    "driver": {},
    "tracking": {},
    "dashboard": {},
    "security": {},
    "hardware": {}
}
```

---

# 5. Configuração do Sistema

```json
{
    "name":"SmartCam OS",
    "version":"1.0.0",
    "language":"pt-BR",
    "theme":"dark",
    "timezone":"America/Sao_Paulo"
}
```

---

# 6. Configuração Wi-Fi

```json
{
    "mode":"STA",
    "ssid":"",
    "password":"",
    "hostname":"smartcam-os",
    "ip":"dhcp"
}
```

---

# 7. Configuração da Câmera

```json
{
    "resolution":"VGA",
    "quality":10,
    "brightness":0,
    "contrast":0,
    "saturation":0,
    "mirror":false,
    "flip":false,
    "fps":15
}
```

---

# 8. Configuração do Motor

```json
{
    "steps":200,
    "microstep":16,
    "rpm":100,
    "acceleration":500,
    "reverse":false
}
```

---

# 9. Configuração do Driver

```json
{
    "model":"DM556D",
    "current":2.8,
    "enable":true
}
```

---

# 10. Configuração do Tracking

```json
{
    "enabled":true,
    "mode":"person",
    "kp":1.2,
    "ki":0.0,
    "kd":0.4,
    "dead_zone":25
}
```

---

# 11. Configuração do Dashboard

```json
{
    "fps":true,
    "cpu":true,
    "memory":true,
    "temperature":true,
    "logs":true
}
```

---

# 12. Configuração de Segurança

```json
{
    "login":"admin",
    "password":"admin",
    "https":false
}
```

Na primeira inicialização, o sistema obrigará a troca da senha padrão.

---

# 13. Cadastro de Hardware

Um dos recursos mais importantes do projeto.

```json
{
    "board":"T-SIMCAM",
    "camera":"OV2640",
    "driver":"DM556D",
    "motor":"NEMA23",
    "power":"24V",
    "mechanical":"Pulley"
}
```

No futuro:

* ESP32-CAM
* ESP32-S3-EYE
* ESP32-WROOM
* Outras placas

---

# 14. Perfis

Cada perfil será um conjunto completo de configurações.

Exemplo:

```text
Perfil 01

Rastreamento de Pessoas
```

```text
Perfil 02

Geofissura
```

```text
Perfil 03

Scanner 3D
```

```text
Perfil 04

Mesa Giratória
```

---

# 15. Estrutura dos Perfis

```text
profiles/

person.json

geofissura.json

scanner.json

testbench.json
```

Selecionar um perfil aplicará todas as configurações automaticamente.

---

# 16. Exportação

O Dashboard permitirá:

Exportar

↓

JSON

↓

Download

Exemplo:

```text
config-2026-07-15.json
```

---

# 17. Importação

O usuário poderá enviar um JSON.

O sistema validará:

* Versão
* Estrutura
* Campos obrigatórios
* Compatibilidade

Antes de aplicar.

---

# 18. Backup Automático

Sempre que houver alteração importante:

```text
config.json

↓

config.bak
```

Assim nunca perderemos a configuração anterior.

---

# 19. Histórico

O sistema manterá as últimas versões.

```text
config_v001.json

config_v002.json

config_v003.json
```

Configurável.

---

# 20. Migração

Se no futuro adicionarmos novos parâmetros:

Versão antiga

↓

Conversor

↓

Versão nova

Sem perder configurações.

---

# 21. Validação

Cada campo possuirá limites.

Exemplo:

RPM

Mínimo

10

Máximo

1200

Caso inválido:

Não salva.

---

# 22. API

Endpoints

```text
GET /api/config

POST /api/config

POST /api/profile/load

POST /api/profile/save

GET /api/profile/list
```

---

# 23. Dashboard

Teremos uma tela exclusiva.

```
Configurações

Sistema

Hardware

Motor

Driver

Tracking

Wi-Fi

Dashboard

Segurança

Perfis

Backup
```

---

# 24. Perfis Inteligentes

O usuário poderá criar perfis próprios.

Exemplo:

```text
Minha Câmera PTZ

Minha Bancada

Meu Scanner

Meu GeoFissura
```

Sem necessidade de editar código.

---

# 25. Objetivo Final

Ao final deste documento, o SmartCam OS terá um sistema de configuração centralizado, consistente e preparado para crescer por muitos anos, mantendo compatibilidade entre versões e diferentes equipamentos.

---

# 💡 Evolução proposta: SmartCam OS como Plataforma

Aqui está uma ideia que pode transformar o projeto em algo muito maior.

Em vez de pensar apenas em um firmware para ESP32, vamos tratar o SmartCam OS como um **sistema operacional para visão computacional embarcada**.

Isso significa que, no futuro, ele poderá carregar **Aplicações (Apps)** sobre a mesma base.

Exemplos de Apps:

* 👤 Person Tracker (seguir pessoas)
* 😀 Face Tracker (seguir rostos)
* 🪨 GeoFissura (monitoramento de fissuras)
* 📦 Object Counter (contagem de objetos)
* 📷 Time Lapse
* 📸 Photo Booth
* 🤖 Robô Seguidor
* 📡 Inspeção Industrial
* 📏 Medição Visual
* 🎯 Mira Automática (para aplicações permitidas e seguras, como apontamento de câmera ou laser de baixa potência)

Cada App reutilizaria os mesmos módulos de câmera, motor, Wi-Fi, interface Web e configuração, alterando apenas a lógica específica.

Essa arquitetura torna o SmartCam OS muito mais reutilizável e facilita a manutenção.

---

