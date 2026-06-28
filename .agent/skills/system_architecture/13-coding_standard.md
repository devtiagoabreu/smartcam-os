Perfeito. Agora vamos escrever um dos documentos mais importantes de todo o projeto.

Na minha opinião, este documento vale mais do que milhares de linhas de código.

Ele vai definir **como todo o código será escrito**, garantindo que o SmartCam OS continue organizado daqui a 5 ou 10 anos.

---

# SMARTCAM OS

# Documento 15 — Coding Standard (Padrão Oficial de Desenvolvimento)

**Versão:** 1.0.0

---

# 1. Objetivo

Definir um padrão único para todo o código do SmartCam OS.

Todos os arquivos deverão seguir exatamente este documento.

Objetivos:

* Código legível.
* Fácil manutenção.
* Fácil documentação.
* Fácil expansão.
* Compatível com Arduino IDE.
* Compatível com PlatformIO (futuro).

---

# 2. Linguagem

Todo o projeto será desenvolvido em:

```text
C++17
```

Utilizando o framework Arduino para ESP32-S3.

---

# 3. IDE Oficial

Primeira versão.

```text
Arduino IDE 2.x
```

No futuro.

PlatformIO.

VSCode.

Sem alterar o código.

---

# 4. Estrutura de Pastas

```text
smartcam-os/

docs/

firmware/

camera/

vision/

tracking/

motion/

ai/

network/

storage/

logger/

dashboard/

sdk/

hardware/

cad/

tests/

tools/

examples/
```

Nunca misturar módulos.

---

# 5. Organização de Arquivos

Cada módulo possuirá.

```text
camera_engine.h

camera_engine.cpp
```

Nunca arquivos gigantes.

---

# 6. Convenção de Nomes

Classes.

```cpp
CameraEngine

MotionController

TrackingService
```

PascalCase.

---

Métodos.

```cpp
captureFrame()

startTracking()

moveAxis()

stopMotor()
```

camelCase.

---

Variáveis.

```cpp
frameRate

motorSpeed

cameraWidth
```

camelCase.

---

Constantes.

```cpp
MAX_SPEED

DEFAULT_FPS

CAMERA_TIMEOUT
```

UPPER_CASE.

---

Macros.

Somente quando inevitável.

---

Arquivos.

```text
camera_engine.cpp

camera_engine.h
```

snake_case.

---

# 7. Prefixos

Boolean.

```cpp
isRunning

hasTarget

canMove

shouldStop
```

---

Ponteiros.

```cpp
frameBuffer

cameraDriver
```

Sem prefixos como `pFrame`.

---

# 8. Tipos

Sempre utilizar.

```cpp
uint8_t

uint16_t

uint32_t

int32_t

float

bool
```

Nunca.

```cpp
unsigned long
```

---

# 9. Includes

Sempre.

```cpp
Bibliotecas

↓

Projeto

↓

Arquivos locais
```

Exemplo.

```cpp
#include <Arduino.h>

#include <WiFi.h>

#include "camera_engine.h"
```

---

# 10. Namespace

Utilizar.

```cpp
namespace smartcam
{

}
```

Todos os módulos.

---

# 11. Arquivos Header

Sempre utilizar.

```cpp
#pragma once
```

Nunca `#ifndef`.

---

# 12. Comentários

Todo método.

```cpp
/**
 * Captura um frame da câmera.
 *
 * @return true se sucesso.
 */
```

Padrão Doxygen.

---

# 13. Comprimento das Funções

Ideal.

Até.

```text
30 linhas
```

Máximo.

```text
80 linhas
```

Acima disso.

Refatorar.

---

# 14. Comprimento das Classes

Ideal.

Até.

```text
300 linhas
```

Acima disso.

Dividir.

---

# 15. Responsabilidade Única

Cada classe faz apenas uma coisa.

Exemplo.

Errado.

```text
Camera

↓

Captura

↓

Wi-Fi

↓

Motor
```

Correto.

```text
Camera

↓

Captura
```

Apenas.

---

# 16. Nunca utilizar delay()

Proibido.

```cpp
delay(100);
```

Utilizar.

```cpp
SmartCamTimer
```

Ou.

FreeRTOS.

---

# 17. Nunca utilizar Serial

Nunca.

```cpp
Serial.println();
```

Sempre.

```cpp
logger.info();

logger.error();

logger.debug();
```

---

# 18. Strings

Evitar.

```cpp
String
```

Sempre que possível.

```cpp
char

std::string (futuro)
```

Quando usar `String`, evitar concatenações frequentes para reduzir fragmentação de memória.

---

# 19. Memória

Evitar.

```cpp
new

delete
```

Preferir.

Objetos estáticos.

Buffers.

Pools.

---

# 20. Ponteiros

Sempre verificar.

```cpp
if(frame != nullptr)
{
}
```

---

# 21. Tratamento de Erros

Nunca.

Ignorar.

Sempre.

```cpp
if(!camera.begin())
{

    logger.error();

}
```

---

# 22. Retornos

Utilizar.

```cpp
enum class Result
{
    Ok,
    Error,
    Timeout,
    InvalidParameter,
    Busy,
    NotInitialized
};
```

Evitar retornar apenas `bool` quando for importante identificar a causa do erro.

---

# 23. Enum Class

Sempre.

```cpp
enum class
```

Nunca.

```cpp
enum
```

---

# 24. Configurações

Nunca.

Hardcoded.

Sempre.

```cpp
config.json
```

Ou.

Settings Manager.

---

# 25. Constexpr

Sempre utilizar.

```cpp
constexpr int MAX_SPEED = 500;
```

Em vez de.

```cpp
#define MAX_SPEED 500
```

---

# 26. Logs

Todos os módulos registrarão.

Inicialização.

Erro.

Aviso.

Performance.

Parada.

---

# 27. Eventos

Nenhum módulo chamará outro diretamente.

Sempre.

```text
Evento

↓

Event Bus

↓

Serviço
```

---

# 28. Código Assíncrono

Sempre que possível.

Sem bloqueios.

Sem loops infinitos.

Sem espera ativa.

---

# 29. Padrão de Classes

Toda classe deverá seguir.

```cpp
public

protected

private
```

Nesta ordem.

---

# 30. Ordem dos Métodos

```cpp
Construtor

↓

Destructor

↓

begin()

↓

loop()

↓

stop()

↓

Métodos Públicos

↓

Métodos Privados
```

---

# 31. Organização Visual

Sempre utilizar.

```cpp
if(condition)
{

}
```

Nunca.

```cpp
if(condition){
}
```

---

# 32. Indentação

4 espaços.

Nunca TAB.

---

# 33. Linhas

Máximo.

120 caracteres.

---

# 34. Comentários

Explicar.

**Por que**.

Nunca.

**O que**.

Código já explica.

---

# 35. TODO

Sempre.

```cpp
// TODO:
```

---

# 36. FIXME

Sempre.

```cpp
// FIXME:
```

---

# 37. Versionamento

Todo arquivo.

```cpp
/*
SmartCam OS

Version

Author

Date
*/
```

---

# 38. Testabilidade

Toda função importante deverá poder ser testada isoladamente.

Evitar dependências ocultas.

---

# 39. Documentação

Todo módulo deverá possuir:

* README.md
* Diagrama.
* Fluxograma.
* API.
* Casos de uso.

---

# 40. Objetivo Final

Criar um padrão de desenvolvimento consistente, profissional e sustentável para todo o SmartCam OS.

---

# 🚀 Evolução importante do padrão de código

Enquanto escrevia este documento, identifiquei alguns pontos que podem deixar o projeto ainda mais robusto para um sistema embarcado como o ESP32-S3:

### Níveis de Log

Em vez de apenas `info()` e `error()`, vamos padronizar:

```cpp
logger.trace();
logger.debug();
logger.info();
logger.warning();
logger.error();
logger.fatal();
```

Assim será possível controlar o nível de detalhamento pela interface web.

---

### Padrão de Resultados

Vamos criar uma classe única para retorno de operações:

```cpp
class Result
{
public:
    bool success;
    int code;
    String message;
};
```

Isso facilitará tanto a API REST quanto o Dashboard.

---

### Gerenciador de Erros

Cada erro terá um código único.

Exemplo:

```text
CAM001 → Falha ao inicializar câmera
CAM002 → Timeout de captura

MOT001 → Driver desabilitado
MOT002 → Limite de curso atingido

NET001 → Wi-Fi desconectado

AI001 → Modelo não carregado
```

Isso permitirá que a documentação, o Dashboard e os logs utilizem exatamente os mesmos códigos.

---

### Guia de Revisão de Código

Antes de aceitar qualquer alteração no repositório GitHub, adotaremos uma checklist obrigatória:

* O código segue este padrão?
* Está documentado com Doxygen?
* Não utiliza `delay()`?
* Não acessa `Serial` diretamente?
* Não possui valores "hardcoded"?
* Possui tratamento de erros?
* Foi testado no hardware?
* Não quebrou a API pública?

Essa checklist será usada em Pull Requests e garantirá que a qualidade do projeto permaneça alta ao longo do tempo.

---

# 📘 Próximo Documento (16)

Entraremos na especificação completa da comunicação entre o firmware e a interface web:

## **API REST + WebSocket**

Vamos definir:

* Todos os endpoints REST.
* Estrutura completa dos JSONs.
* WebSocket para eventos em tempo real.
* Streaming de status.
* Controle do motor.
* Configuração da câmera.
* Configuração da IA.
* Configuração do Tracking.
* Sistema de autenticação (opcional).
* Versionamento da API (`/api/v1/...`).

Esse documento será essencial para que o Dashboard HTML/JavaScript e o firmware evoluam de forma independente, comunicando-se através de uma API estável e bem documentada. Isso também facilitará futuras integrações com aplicativos móveis, sistemas supervisórios ou plataformas IoT.
