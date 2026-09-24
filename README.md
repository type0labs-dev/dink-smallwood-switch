# Dink Smallwood HD — Nintendo Switch Port

[![GitHub Release](https://img.shields.io/github/v/release/type0labs-dev/dink-smallwood-switch?color=blue&logo=github)](https://github.com/type0labs-dev/dink-smallwood-switch/releases/latest)
[![Platform](https://img.shields.io/badge/Platform-Nintendo%20Switch%20%28Homebrew%29-red?logo=nintendoswitch)](https://github.com/type0labs-dev/dink-smallwood-switch)
[![Languages](https://img.shields.io/badge/Languages-English%20%7C%20Portugu%C3%AAs%20(Brasil)-yellow)](https://github.com/type0labs-dev/dink-smallwood-switch)
[![License: RTsoft](https://img.shields.io/badge/License-RTsoft%20zlib--style-green.svg)](LICENSE.md)

[English](#english) | [Português (Brasil)](#português-do-brasil)

---

<a name="english"></a>
## English

Native homebrew port of **Dink Smallwood HD** for the **Nintendo Switch** (CFW / Atmosphère), based on the official [RTDink](https://github.com/SethRobinson/RTDink) engine and Proton SDK by Seth Robinson.

This edition features the complete 1997 classic campaign with over two decades of community improvements, full native synthesized MIDI music, modern quality-of-life additions, and seamless **dual-language support** (Original English and Brazilian Portuguese).

### 🌟 Features
- **🌐 Dual Language Support (English & Portuguese):**
  - Interactive language selector on first boot with on-the-fly toggling in the Options menu.
  - Complete original 1997 English dialogues by Seth Robinson + full Brazilian Portuguese translation.
- **⚡ Switch Engineering & Performance:**
  - Stable 60 FPS or 30 FPS (configurable in Options).
  - Fast-seeking map loader (`MapRecordReader`) for seamless screen transitions without stuttering.
  - **SafeSave (Atomic Journaled Saves):** Journaled save system with rollback protection to prevent MicroSD corruption.
  - Full Joy-Con and Switch Pro Controller button mappings (sticks, D-Pad, ZL/ZR).
- **🎵 Native MIDI Synthesis (TiMidity + FreePats):**
  - High-fidelity hardware-synthesized soundtrack playing all original village and dungeon tunes.
- **📜 Interactive Quest Log:**
  - Open anytime via Pause Menu or by pressing **`Q`** to track all 21 main storyline quests.
- **🏆 Achievement System:**
  - 28 in-game achievements with custom pop-up toast notifications and tracking menu.
- **💎 Quality of Life & Visual Polish:**
  - High-definition 3D pre-rendered sprites for gold drops, potions, and animated treasure chests.
  - Fixed consumable stacking (bombs, nuts, elixirs) and audio channel overlapping.

### 📥 Installation (Nintendo Switch)
1. Head to the **[Releases](https://github.com/type0labs-dev/dink-smallwood-switch/releases/latest)** page and download `DinkSmallwoodHD-Switch-PTBR-v0.3.2.zip`.
2. Extract the archive directly to the root of your Switch MicroSD card.
3. The folder hierarchy should match:
   ```text
   SD Card:/
     └── switch/
          └── dink-smallwood/
               ├── DinkSmallwood.nro
               ├── dink/
               ├── interface/
               └── audio/
   ```
4. Insert the SD card, open the **Homebrew Menu** (Application Title Takeover mode recommended for full RAM access), and launch **Dink Smallwood HD**.

---

<a name="português-do-brasil"></a>
## Português do Brasil

Port homebrew nativo de **Dink Smallwood HD** para o **Nintendo Switch** (CFW Atmosphère), baseado no engine oficial [RTDink](https://github.com/SethRobinson/RTDink) e Proton SDK de Seth Robinson.

Esta edição une a campanha clássica original completa de 1997 a mais de 20 anos de melhorias da comunidade, pela primeira vez **100% em Português do Brasil**, com áudio MIDI sintetizado nativamente e otimizações dedicadas para o console.

### 🌟 Principais Recursos
- **🇧🇷 Tradução Completa para Português do Brasil:**
  - 425 scripts traduzidos com o humor satírico e irreverente original intacto.
  - Tela de seleção de idioma no primeiro boot e alternador nas Opções (Português / Inglês).
  - Botões do menu principal estilizados em português.
- **⚡ Engenharia e Desempenho no Switch:**
  - 60 FPS ou 30 FPS estáveis com taxa configurável.
  - Leitor de mapas com busca direta (`MapRecordReader`), eliminando engasgos ao caminhar entre telas.
  - **SafeSave (Proteção Atômica de Saves):** Gravação journalizada com backup que previne corrupção de saves no cartão MicroSD.
  - Controles integrados para Joy-Cons e Switch Pro Controller (analógicos, D-Pad, ZL/ZR).
- **🎵 Áudio MIDI TiMidity + FreePats:**
  - Músicas de todos os vilarejos e masmorras sintetizadas nativamente com timbres clássicos.
- **📜 Diário de Missões Interativo (Quest Log):**
  - Acessível a qualquer momento pelo menu de pausa ou pressionando **`Q`**.
  - Acompanha em tempo real as 21 missões da campanha principal (ativas, pistas e histórico).
- **🏆 Sistema de Conquistas (Achievements):**
  - 28 conquistas exclusivas com banners pop-up estilizados na tela e efeitos sonoros.
  - Tela de consulta de conquistas acessível pelo menu.
- **💎 Visual Atualizado:**
  - Sprites pré-renderizados em alta definição para moedas de ouro, sacos de ouro, poções e baús de tesouro animados.
  - Empilhamento de consumíveis (bombas, nozes, elixires) com contador no inventário.

### 📥 Como Instalar no Nintendo Switch
1. Acesse a aba de **[Releases](https://github.com/type0labs-dev/dink-smallwood-switch/releases/latest)** e baixe o arquivo **`DinkSmallwoodHD-Switch-PTBR-v0.3.2.zip`**.
2. Extraia o conteúdo diretamente na raiz do cartão MicroSD do seu Switch.
3. A estrutura final no MicroSD ficará assim:
   ```text
   SD Card:/
     └── switch/
          └── dink-smallwood/
               ├── DinkSmallwood.nro
               ├── dink/
               ├── interface/
               └── audio/
   ```
4. Insira o cartão no Switch, abra o **Homebrew Menu** (modo aplicação/title takeover recomendado) e selecione o ícone de **Dink Smallwood HD**.

---

## 🛠️ Compilando a partir do Código-Fonte / Building from Source

Este port é compilado com o toolchain **devkitA64** (devkitPro) para Nintendo Switch:

1. Clone o repositório recursivamente:
   ```bash
   git clone --recursive https://github.com/type0labs-dev/dink-smallwood-switch.git
   cd dink-smallwood-switch
   ```
2. Instale as dependências via `dkp-pacman`:
   - `devkitA64`, `libnx`, `switch-sdl2`, `switch-sdl2_mixer`, `switch-mesa`, `switch-glad`, `switch-libcurl`, `switch-zlib`, `switch-bzip2`.
3. Execute os scripts de build:
   ```bash
   ./switch/scripts/prepare-proton.sh
   ./switch/scripts/build.sh
   python3 switch/scripts/prepare-music.py
   python3 switch/scripts/package.py
   ```
   O binário final será gerado em `build-switch/DinkSmallwood.nro`.

---

## 📜 Licenças e Direitos Autorais / Licenses & Credits

- **Original Game & RTDink Engine:** [Robinson Technologies](https://www.rtsoft.com/) / Seth A. Robinson ([`LICENSE.md`](LICENSE.md)).
- **Proton SDK:** Seth A. Robinson ([`proton/LICENSE.md`](proton/LICENSE.md)).
- **FreePats Audio Bank:** FreePats / TiMidity (GPL).
- **3D Graphic Assets (Loot & Chests):** Clint Bellanger & Flare RPG Team (CC-BY-SA 3.0).
- **Nintendo Switch Homebrew Libraries:** [switchbrew / libnx](https://github.com/switchbrew/libnx) (ISC).

---

## 🤖 Transparência sobre o Uso de IA / AI Transparency

Em compromisso com a transparência técnica e ética perante a comunidade open source e homebrew:

* A engenharia de port para o Nintendo Switch (adaptação do pipeline gráfico, SafeSave, sistema de busca direta de mapa, TiMidity), a depuração de scripts do DinkC e a tradução integral dos diálogos para Português do Brasil foram desenvolvidas com **assistência de modelos de Inteligência Artificial** (Anthropic Claude, Google DeepMind Antigravity e OpenAI Codex).
* Todo o trabalho passou por **concepção, direção técnica, revisão minuciosa de código e bateria de testes de validação funcional em hardware real de Nintendo Switch** por desenvolvedores humanos.
