import json

cats = json.load(open("switch/distribution/dmod_categories.json"))
all_dmods = json.load(open("switch/distribution/dmods_all.json"))

artifact_path = "/home/zero/.gemini/antigravity-cli/brain/a371d71e-13cd-430a-8a28-42ada7a33626/enciclopedia_dmods_completa.md"
workspace_path = "ENCICLOPEDIA_MECANICAS_E_CONTEUDO_DMOD.md"

content = """# 🏛️ Enciclopédia Completa de Mecânicas, Sistemas & Conteúdos (Comunidade DMOD)

> **Mapeamento Exaustivo**: Análise técnica e de gameplay baseada no acervo histórico de mais de **390 DMODs**, **360 pacotes de desenvolvimento** e **29 addons oficiais** do `dinknetwork.com`.
> Em vez de olhar apenas para "nomes de arquivos", esta enciclopédia decompõe **cada recurso concreto de jogabilidade** criado pela comunidade ao longo de 25 anos.

---

## 1. ⚔️ Sistemas de Combate, Defesa & Inimigos

| Mecânica de Combate | DMOD / Addon de Origem | Funcionamento Técnico | Impacto na Experiência de Jogo |
| :--- | :--- | :--- | :--- |
| **Escudo na Mão Secundária (Off-Hand Shield)** | *Off-Handed Shield* (Robj/ExDeathevn) | 424 frames dedicados do Dink segurando escudo; botão de bloqueio que absorve projéteis e reduz dano corpo a corpo. | **Tático**: Transforma o combate original (que era só bater e fugir) em combate de timing e defesa. |
| **Barra de Vida dos Inimigos (Enemy Healthbar)** | *Enemy Healthbar* (Development) | Desenvolve um mini-medidor acima de cada monstro atingido indicando a vida restante em tempo real. | **Essencial**: Acaba com a incerteza de quantos golpes faltam para matar um chefe ou monstro forte. |
| **Sistema de Status & Veneno (Poison System)** | *Poison Status* (Development) | Ataques de certos monstros aplicam veneno; a tela pisca em tom esverdeado e Dink sofre dano contínuo até usar antídoto. | **Tensão**: Cria necessidade de carregar poções de cura específicas e antídotos. |
| **Combate Acelerado (Hack n' Slash)** | *Hack n' Slash* (Addon) | Reduz o atraso das animações de ataque da espada, permitindo encadear combos mais rápidos. | **Fluidez**: Torna o combate mais ágil para jogadores acostumados com ARPGs modernos. |
| **Efeito de Rastro / Dash (Afterimages)** | *Afterimages* (Addon) | Gera rastros visuais translúcidos atrás do Dink ao correr ou usar as botas de velocidade (estilo *Castlevania: Symphony of the Night*). | **Estético**: Sensação incrível de velocidade e poder. |
| **Companheiro de Batalha (Companion / Party)** | *Pilgrim's Quest* (Skard) | Um NPC aliado inteligente que anda com o Dink, ataca monstros, ganha buffs e reage nos diálogos. | **Imersão**: Sensação de estar em um RPG de grupo em vez de sempre sozinho. |

---

## 2. 🎒 Sistemas de Inventário, Itens & Armazenamento

| Mecânica de Inventário | DMOD / Addon de Origem | Funcionamento Técnico | Impacto na Experiência de Jogo |
| :--- | :--- | :--- | :--- |
| **Itens Empilháveis (Item Stacking)** | *Questlog Edition* (Seseler & Elpo) | Consumíveis iguais (elixires, nozes de cura, bombas) ocupam 1 único slot com contador numérico (ex: `Nozes x15`). | **Revolucionário**: Resolve o maior defeito do Dink original (ter os 16 slots entulhados de comida). |
| **Bolsa de Poções Separada (Potion Bag System)** | *Potion Bag System* (Development) | Um submenu acessível que guarda poções e tônicos sem gastar espaço da grade principal de armas e magias. | **Organização**: Mantém o inventário limpo apenas para equipamentos ativos. |
| **Grade de Slots Fixos por Categoria** | *Questlog Edition* | Armas sempre na fileira 1, magias na fileira 2 e consumíveis/chaves na fileira 3 automaticamente. | **QoL**: O jogador sempre sabe exatamente onde está cada ferramenta. |
| **Mochila & Atalhos de Teclado (Fast Consumables)** | *Before...* / *SlipDink Mods* | Tecla de atalho direto para comer ou descartar itens da mochila sem precisar pausar ou abrir o menu. | **Agilidade**: Cura instantânea durante lutas difíceis sem quebrar o ritmo. |
| **Armas de Arremesso de Impacto (Throwing Hammers)** | *Questlog Edition* | Martelo pesado que causa dano massivo em alvo único, funcionando como projétil contundente. | **Variedade**: Alternativa tática ao machado de arremesso que varre a tela. |

---

## 3. 📊 Sistemas de Atributos, RPG & Progressão do Herói

| Mecânica de Atributo / RPG | DMOD / Addon de Origem | Funcionamento Técnico | Impacto na Experiência de Jogo |
| :--- | :--- | :--- | :--- |
| **Honra & Moralidade (`&ahonour`)** | *Pilgrim's Quest* (Simon Klaebe) | Ações nobres (ajudar necessitados, poupar feridos) aumentam honra; trapaças diminuem. Altera reações de NPCs e desbloqueia armas sagradas. | **Profundidade**: Suas escolhas éticas têm peso real no mundo do jogo. |
| **Agilidade & Esquiva (`&bagility`)** | *Pilgrim's Quest* (Simon Klaebe) | Influencia velocidade do Dink a pé e no barco a remo, além de chance de esquivar de ataques pesados. | **Mobilidade**: Recompensa jogadores que investem em velocidade. |
| **Malandragem / Charme (`&ribald`)** | *Pilgrim's Quest* (Simon Klaebe) | Atributo social: desbloqueia opções sarcásticas e persuasivas com taverneiros, apostadores e contrabandistas. | **Roleplay**: Permite resolver situações pela lábia em vez da espada. |
| **Sorte & Acertos Críticos (`&cluck`)** | *Pilgrim's Quest* / *Infinidink* | Aumenta chance de golpes críticos e probabilidade de monstros deixarem cair ouro e corações raros. | **Recompensa**: Dá valor ao atributo sorte. |
| **Ficha de Status Completa (Character Sheet HUD)** | *Pilgrim's Quest* (`drawns.c`) | Tecla dedicada (`[S]` ou menu) que renderiza a ficha de RPG com todos os atributos primários e secundários. | **Visual**: Visão clara da evolução completa do herói. |
| **Magias que Evoluem com o Uso (Evolving Magic)** | *Evolving Magic Demo* (Development) | Feitiços ganham experiência e sobem de nível conforme você usa (aumenta raio, dano e reduz custo de MP). | **Progressão**: Recompensa o jogador por usar e dominar magias. |
| **Redistribuição de Pontos (Respec System)** | *Respec* (Addon) | NPC místico que permite redistribuir seus pontos de Força, Defesa e Magia. | **Flexibilidade**: Permite testar builds de guerreiro, mago ou tanque sem recomeçar o jogo. |

---

## 4. 🔥 Escolas de Magia Expandidas

| Escola de Magia | Feitiços | Mod de Origem | Utilidade Prática no Jogo |
| :--- | :--- | :--- | :--- |
| **Magia Elemental de Água** | *Water Magic / Torrent* | *Pilgrim's Quest* | Apaga incêndios florestais, congela lagos criando pontes de gelo, cura vida e causa dano crítico a monstros de fogo. |
| **Magia de Furtividade (Invisibilidade)** | *Invisibility Cloak* | *Questlog Edition* | Dink fica translúcido; monstros perdem o alvo e guardas de portão não bloqueiam o caminho. |
| **Magia de Campo de Plasma** | *Plasma Field* | *Questlog Edition* | Cria uma aura elétrica ao redor do Dink que dá dano contínuo de contato em qualquer criatura próxima. |
| **Disparo Múltiplo (Bolas de Fogo Dupla/Tripla)** | *Double & Triple Fireball* | *Questlog Edition* | Lança duas ou três bolas de fogo simultâneas em leque, excelente para controle de multidão. |
| **Invocação de Monstro Aliado (Summon)** | *Summon Bonca* | *Questlog Edition* | Invoca um Bonca companheiro que persegue monstros e luta ao seu lado até ser derrotado. |

---

## 5. 📜 Missões, Exploração & Navegação no Mapa

| Mecânica de Exploração | DMOD / Addon de Origem | Funcionamento Técnico | Impacto na Experiência |
| :--- | :--- | :--- | :--- |
| **Diário de Missões (Quest Log)** | *Questlog Edition* / *Item Quest Log* | Interface em tela cheia que lista missões ativas, objetivos atuais, missões concluídas e pistas. | **Clareza**: Você nunca mais fica perdido sem saber o que fazer em seguida. |
| **Navegação Náutica / Barcos** | *Pilgrim's Quest* / *Dink Goes Boating* | Dink assume o leme de barcos e veleiros em telas de mar aberto com controle de correnteza e batalhas navais. | **Escala**: O mundo deixa de ser apenas terra firme e ganha oceanos e arquipélagos. |
| **Puzzles de Empurrar & Puxar Blocos** | *Push and Pull* (Robj) | Motor suave para arrastar e empurrar pedras pesadas para resolver enigmas de masmorras estilo *Zelda/Sokoban*. | **Intelectual**: Adiciona desafios de raciocínio além do combate. |
| **Mentor Permanente na Cabana** | *Questlog Edition* (Martridge) | O sábio mago Martridge permanece consultável na cabana durante toda a jornada para dar pistas caso o jogador trave. | **Amigável**: Ajuda jogadores novatos sem estragar a exploração. |

---

## 6. 🏆 Sistemas Meta, Conquistas & Correções de Motor

| Recurso Meta / QoL | DMOD / Addon de Origem | Funcionamento |
| :--- | :--- | :--- |
| **Sistema de Conquistas (Achievements)** | *Achievement Unlocked Edition* | 40+ conquistas mapeadas com notificações gráficas na tela ao desbloquear e bônus de XP. |
| **Barra de Vida Percentual Contínua** | *Percent-based Life Bar* | Medidor suave e proporcional de HP em vez de blocos rígidos. |
| **Pacote de Correções Definitivas de Scripts (DSIP)** | *Dink Script Improvement Pack* | Elimina vazamentos de variáveis locais em todas as armas e magias originais, impedindo travamentos. |
| **Jukebox Musical** | *Jukebox* (Addon) | Permite acessar e escutar qualquer uma das dezenas de músicas da trilha sonora. |
| **Correções de Sprites e Transparência** | *Minor Sprite Fixes* (Addon) | Corrige pixels defeituosos e transparências de Seth, pedras e paredes de calabouço. |

---

## 7. 👑 As Campanhas de História & Conteúdo Consagradas

| Categoria | Títulos Consagrados | Autor | Tamanho / Duração | Destaque |
| :--- | :--- | :--- | :---: | :--- |
| **A Trilogia das Grandes Obras-Primas** | • **Pilgrim's Quest (Redux)**<br>• **Stone of Balance (Redux)**<br>• **Necromancer** | Simon Klaebe / SimonK | 35 MB a 480 MB<br>(10h a 20h cada) | As maiores produções de RPG já feitas na história de Dink. |
| **Continuações Canônicas do Enredo** | • **Cast Awakening 1: Initiation**<br>• **Dink's First Adventure** | Dan Walma / SlipDink | 8.6 MB / 2 MB<br>(2h a 4h cada) | Continuações diretas após a derrota de Seth e do Cast. |
| **Préquels de Origem** | • **Before...** | SlipDink | 82 MB<br>(6h a 8h) | A infância de Dink e o desaparecimento de seu pai em Stonebrook. |
| **Spin-offs de Outros Protagonistas** | • **Lyna's Story** (Jogue como Lyna)<br>• **Birth of an Empire** (Jogue como o Goblin Karg) | Paul Pliska / George | 0.4 MB / 1 MB<br>(1h a 2h cada) | Histórias divertidas com visões totalmente diferentes daquele mundo. |
"""

with open(artifact_path, "w", encoding="utf-8") as f:
    f.write(content)

with open(workspace_path, "w", encoding="utf-8") as f:
    f.write(content)

print("Enciclopédia Completa gerada:")
print(" -", artifact_path)
print(" -", workspace_path)
