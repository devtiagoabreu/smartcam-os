Perfeito. Agora entramos em uma fase que poucas pessoas documentam antes de começar a programar, mas que faz toda a diferença na qualidade do projeto.

Este documento vai definir **como garantir que cada versão do SmartCam OS funcione corretamente** antes de ser publicada no GitHub.

---

# SMARTCAM OS

# Documento 18 – Master Test Plan (Plano Mestre de Testes)

**Versão:** 1.0.0

---

# 1. Objetivo

Definir todos os testes necessários para validar o SmartCam OS.

Cada módulo deverá possuir testes próprios antes de ser integrado ao sistema.

Objetivos:

* Garantir estabilidade.
* Detectar regressões.
* Medir desempenho.
* Validar hardware.
* Padronizar homologação.

---

# 2. Estratégia

Os testes serão divididos em níveis.

```text
Nível 1 → Unitários

↓

Nível 2 → Integração

↓

Nível 3 → Hardware

↓

Nível 4 → Performance

↓

Nível 5 → Estresse

↓

Nível 6 → Homologação
```

---

# 3. Testes Unitários

Cada serviço será testado isoladamente.

```text
Camera Service

Motion Service

Vision Service

Tracking Service

Inference Service

Storage Service

Logger Service

Network Service
```

---

# 4. Camera Service

Testes.

✅ Inicializa câmera

✅ Captura Frame

✅ Reinicializa

✅ Troca resolução

✅ Troca FPS

✅ Troca qualidade

✅ Auto Exposure

✅ White Balance

---

Critério.

```text
100% dos testes aprovados
```

---

# 5. Motion Service

Testes.

```text
Mover direita

Mover esquerda

Parar

HOME

Velocidade

Aceleração

Desaceleração

Limites
```

---

Critério.

Erro máximo.

```text
±1 passo
```

---

# 6. Tracking Service

Testes.

```text
Encontrar alvo

Centralizar

Perder alvo

Retomar alvo

Dead Zone

PID

Velocidade
```

---

Critério.

Centro da imagem.

```text
±10 pixels
```

---

# 7. Vision Service

Filtros.

```text
Gray

HSV

Threshold

Blur

Blob

Edges

Overlay
```

Todos devem produzir resultados consistentes.

---

# 8. Inference Service

Testar.

```text
Carrega modelo

Executa

Retorna objetos

Libera memória

Recarrega modelo
```

---

# 9. Storage

Testar.

```text
Salvar

Ler

Excluir

Formatar

Pouco espaço
```

---

# 10. Logger

Testar.

```text
INFO

DEBUG

WARNING

ERROR

FATAL
```

---

# 11. Network

Testar.

```text
Conectar

Reconectar

Perda Wi-Fi

Mudança IP

Scan
```

---

# 12. Dashboard

Testes.

```text
Carrega

Troca páginas

Atualiza WebSocket

Responsividade

Tema Escuro

Tema Claro
```

---

# 13. API REST

Todos endpoints.

```text
GET

POST

DELETE (quando existir)

PUT (se necessário)
```

---

Todos deverão responder.

```text
200

400

404

500
```

Conforme esperado.

---

# 14. WebSocket

Validar.

```text
Conecta

Reconecta

Eventos

Desconexão

Múltiplos clientes
```

---

# 15. OTA

Testar.

```text
Firmware válido

Firmware inválido

Interrupção

Rollback (futuro)
```

---

# 16. LittleFS

Testar.

```text
Upload

Download

Excluir

Arquivo grande

Arquivo inexistente
```

---

# 17. Testes de Hardware

Hardware oficial.

```text
T-SIMCAM ESP32-S3

↓

DM556D

↓

Motor de Passo

↓

Fonte

↓

Rede Wi-Fi
```

---

# 18. Testes da Câmera

Verificar.

Imagem.

FPS.

Ruído.

Latência.

Consumo.

---

# 19. Testes do Motor

Executar.

```text
100 passos

↓

1000 passos

↓

10000 passos

↓

1 hora contínua
```

Sem perda de passos.

---

# 20. Teste de Rastreamento

Pessoa.

Entrando.

Saindo.

Correndo.

Parando.

Mudança de iluminação.

---

Critério.

Nunca travar.

---

# 21. Testes de Iluminação

Ambientes.

```text
Escuro

Luz Natural

LED

Contraluz

Noite
```

---

# 22. Testes de Performance

Medir.

```text
FPS

CPU

Heap

PSRAM

Latência

Inferência
```

---

# 23. Benchmark

Gerar relatório.

```text
FPS Médio

FPS Máximo

FPS Mínimo

Tempo IA

Tempo Tracking

Tempo Vision
```

---

# 24. Teste de Estresse

Funcionamento.

```text
24 horas
```

Depois.

```text
72 horas
```

Depois.

```text
7 dias
```

Sem reinicializar.

---

# 25. Teste de Memória

Monitorar.

Heap.

PSRAM.

Fragmentação.

Leaks.

---

# 26. Teste de Reinicialização

Executar.

```text
100 boots consecutivos
```

Sem erro.

---

# 27. Teste de Wi-Fi

Reconectar automaticamente.

Após desligar o roteador.

---

# 28. Teste OTA

Atualizar.

```text
v1.0

↓

v1.0.1

↓

v1.1
```

Sem perder configurações.

---

# 29. Testes do Dashboard

Abrir.

Chrome.

Edge.

Firefox.

Safari.

Android.

iPhone.

---

# 30. Testes do GeoFissura

(Planejado para o App)

```text
Detectar Pontos Neon

↓

Calcular Escala

↓

Detectar Fissura

↓

Medir

↓

Salvar

↓

Exportar
```

---

# 31. Critérios de Aprovação

Uma versão só poderá ser publicada quando:

* Todos os testes unitários passarem.
* Todos os testes de integração passarem.
* Todos os testes de hardware passarem.
* Nenhum vazamento de memória for detectado.
* O sistema permanecer estável por pelo menos **72 horas** em teste contínuo.
* A API REST e o Dashboard forem compatíveis com a versão anterior.

---

# 32. Matriz de Testes

Cada funcionalidade terá uma ficha de validação.

| ID      | Funcionalidade          | Teste             | Resultado | Status |
| ------- | ----------------------- | ----------------- | --------- | ------ |
| TST-001 | Inicialização da câmera | Boot              | OK        | ✅      |
| TST-002 | Movimento do motor      | 1000 passos       | OK        | ✅      |
| TST-003 | Rastreamento            | Pessoa caminhando | OK        | ✅      |
| TST-004 | API REST                | GET /status       | OK        | ✅      |

---

# 33. Testes Automatizados (Futuro)

Embora a primeira versão seja desenvolvida na Arduino IDE, o projeto será preparado para automatizar testes futuramente.

Planejamento:

* GitHub Actions para compilação automática.
* Verificação de estilo de código.
* Testes de API.
* Geração automática de documentação.

---

# 34. Relatório de Homologação

Cada release oficial terá um relatório contendo:

* Versão do firmware.
* Hardware utilizado.
* Tempo total de testes.
* Desempenho médio.
* Problemas encontrados.
* Problemas corrigidos.
* Assinatura da versão.

---

# 35. Objetivo Final

Nenhuma versão será publicada apenas porque "funciona na bancada".

Ela deverá atender critérios técnicos mensuráveis e repetíveis, garantindo confiabilidade tanto para o **Person Tracker** quanto para o futuro **GeoFissura**.

---

# 🚀 Evolução da estratégia de testes

Durante a elaboração deste documento, surgiu uma ideia que considero extremamente útil para um projeto embarcado.

## Modo Self-Test (Autodiagnóstico)

Ao ligar o equipamento, ou sob comando do usuário, o SmartCam OS poderá executar um autoteste completo.

Fluxo:

```text
Boot

↓

Self-Test

↓

Camera

↓

PSRAM

↓

Flash

↓

Wi-Fi

↓

Motor

↓

API

↓

Dashboard

↓

READY
```

Caso algum teste falhe, o Dashboard exibirá exatamente qual módulo apresentou problema, facilitando a manutenção em campo.

---

## Modo Demo

Também podemos incluir um **Modo Demo**, útil para apresentações e desenvolvimento.

Nesse modo:

* A câmera pode reproduzir imagens gravadas.
* O rastreamento pode usar alvos simulados.
* O motor pode ser substituído por um simulador lógico.
* A API continua funcionando normalmente.

Isso permitirá desenvolver boa parte do sistema sem depender do hardware conectado.

---

# 📘 Próximo Documento (19)

Agora vamos projetar a **Estrutura Definitiva do Repositório GitHub**.

Esse documento definirá:

* Organização completa das pastas.
* Estratégia de branches (Git Flow).
* Versionamento semântico.
* GitHub Actions.
* Releases.
* Templates de Issues.
* Templates de Pull Requests.
* Licenciamento.
* Documentação automática.
* Organização para o **SmartCam Core**, **SDK** e **Apps**.

> **Na minha opinião, este documento encerrará a fase de arquitetura do projeto.** Depois dele, construiremos o **Documento 20 (Roadmap Oficial)** e, em seguida, consolidaremos tudo no **SmartCam OS Architecture Book**, que será o guia definitivo para iniciar a implementação do firmware na Arduino IDE.
