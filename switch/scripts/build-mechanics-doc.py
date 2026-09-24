#!/usr/bin/env python3
import os

artifact_path = "/home/zero/.gemini/antigravity-cli/brain/a371d71e-13cd-430a-8a28-42ada7a33626/analise_mecanicas_comunidade.md"
workspace_path = "MECANICAS_E_SISTEMAS_DMOD.md"

content = """# 🔬 Decomposição de Sistemas & Mecânicas da Comunidade Dink Smallwood
> **Objetivo**: Mapear detalhadamente *o que* a comunidade desenvolveu em termos de recursos de jogabilidade (gameplay features), separando por sistemas de jogo para orientar a criação de uma **Complete Edition** definitiva.

---

## 1. 📊 Sistemas de Atributos & Progressão de RPG

| Mecânica / Recurso | Mod de Referência | Como Funciona na Prática | Variáveis / Scripts DinkC | Viabilidade no Jogo Base |
| :--- | :--- | :--- | :--- | :---: |
| **Honra & Moralidade** | *Pilgrim's Quest* | Ações nobres (ajudar necessitados, poupar feridos) aumentam Honra; trapaças e crueldade diminuem. NPCs reagem ao seu nível de virtude, desbloqueia bênçãos e armas sagradas. | `&ahonour`, `ypotion.c`, `save.c` | **Altíssima** |
| **Agilidade & Esquiva** | *Pilgrim's Quest* | Influencia diretamente a velocidade de navegação de barcos a remo, velocidade de sprint do Dink e chance de esquivar de ataques pesados. | `&bagility`, `water_ap.c` | **Altíssima** |
| **Malandragem / Charme** | *Pilgrim's Quest* | Atributo social: desbloqueia opções sarcásticas/maliciosas em diálogos com taverneiros, apostadores e contrabandistas. | `&ribald` | **Alta** |
| **Sorte & Crítico** | *Pilgrim's Quest* / *Infinidink* | Aumenta a taxa de drops de ouro e corações de monstros, além de chances de acerto crítico em combate. | `&cluck` | **Alta** |
| **Ficha de Status Completa (HUD)** | *Pilgrim's Quest* / *Dink Arena* | Tela acionável por tecla (ex: `[S]` ou pelo menu) que desenha uma ficha detalhada com todos os atributos primários e secundários. | `drawns.c`, `key-83.c` | **Altíssima** |

---

## 2. 🎒 Sistemas de Inventário & Gerenciamento de Itens

| Mecânica / Recurso | Mod de Referência | Como Funciona na Prática | Impacto na Experiência |
| :--- | :--- | :--- | :--- |
| **Itens Empilháveis (Item Stacking)** | *Questlog Edition* | Consumíveis idênticos (elixires, nozes de AlkTree, bombas) agrupam-se em um único slot com contador numérico (ex: `Nozes x12`), libertando o jogador do limite sufocante de 16 slots cheios de comida. | **Revolucionário**: Acaba com o maior problema de inventário do jogo original. |
| **Mão Esquerda / Escudo (Off-Hand)** | *Off-Handed Shield* | Dink empunha um escudo na mão esquerda com 424 sprites dedicados. Permite bloquear golpes e projéteis em tempo real. | **Excelente**: Dá uma camada tática ao combate que originalmente era só bater e correr. |
| **Slots Fixos por Categoria** | *Questlog Edition* | O inventário organiza armas na fileira superior, magias no meio e consumíveis/chaves na fileira inferior automaticamente. | **QoL Total**: Evita itens bagunçados toda vez que você pega algo novo. |
| **Mochila & Atalhos Rápidos** | *Before...* | Teclas de atalho rápido: comer comida da mochila instantaneamente sem abrir o menu, ou alternar entre ferramentas e armas. | **Muito Bom**: Agiliza a jogabilidade em combate intenso. |

---

## 3. ⚔️ Sistemas de Combate & Companheiros (Companions)

| Mecânica / Recurso | Mod de Referência | Como Funciona na Prática | Destaques Técnicos |
| :--- | :--- | :--- | :--- |
| **Invocação de Aliado (Summon)** | *Questlog Edition* | Dink aprende a magia `Summon Bonca`, invocando um monstro aliado inteligente que patrulha e ataca inimigos ao seu redor. | `item-bonc.c`, scripts com `brain 9` e `target_enemy`. |
| **Companheiro de Grupo (Party Member)** | *Pilgrim's Quest* | O guerreiro Skard acompanha Dink em explorações e batalhas, lutando ao seu lado, conversando em cutscenes e podendo ser revivido. | Sistema de controle de sprite auxiliar amarrado à posição do jogador. |
| **Armas de Arremesso Pesadas** | *Questlog Edition* / *Pilgrim's Quest* | Martelos de arremesso que causam dano massivo em alvo único (diferente do machado que atravessa) e shurikens estelares. | Novos projéteis balísticos com ricochete. |
| **Arco com Flechas Elementais** | *Quest for Dorinthia* | Permite disparar flechas de gelo (congelam), fogo (queimam) e veneno. | Script de projétil que aciona o efeito elemental no alvo atingido. |

---

## 4. 🔥 Escolas de Magia Expandidas

| Escola de Magia | Feitiços Notáveis | Mod de Referência | Utilidade e Efeitos |
| :--- | :--- | :--- | :--- |
| **Magia de Água** | *Water Magic / Torrente* | *Pilgrim's Quest* | Apaga incêndios no cenário, congela superfícies d'água para criar pontes, cura ferimentos e causa dano extra a demônios de fogo. |
| **Invisibilidade** | *Invisibility Cloak* | *Questlog Edition* | Torna Dink translúcido; monstros perdem o alvo e guardas de portão não atacam. |
| **Magia Protetora / Plasma** | *Plasma Field* | *Questlog Edition* | Cria um escudo de energia ao redor do corpo de Dink que eletrocuta qualquer criatura que tente tocá-lo. |
| **Projéteis Múltiplos** | *Double / Triple Fireball* | *Questlog Edition* | Lança duas ou três bolas de fogo simultâneas em leque, limpando hordas de monstros. |

---

## 5. 📜 Missões, Exploração & Navegação

| Sistema | Mod de Referência | Como Funciona |
| :--- | :--- | :--- |
| **Diário de Missões (Quest Log)** | *Questlog Edition* | Menu acessível a qualquer momento que lista: Missões Ativas, Objetivos Atuais, Missões Concluídas e Pistas. |
| **NPC Mentor Permanente** | *Questlog Edition* | O mago Martridge permanece em sua cabana ao longo de toda a história, servindo como guia consultável caso o jogador se perca. |
| **Navegação Náutica / Barcos** | *Pilgrim's Quest* | Dink assume o leme de barcos a remo e veleiros, navegando livremente entre arquipélagos em telas marítimas abertas. |
| **Puzzles de Empurrar & Puxar (Sokoban)** | *Push and Pull* | Motor aprimorado para arrastar e empurrar blocos pesados de forma fluida para destrancar portas e caminhos em masmorras. |

---

## 6. 🏆 Sistemas Meta & Conquistas

| Sistema | Mod de Referência | Detalhes |
| :--- | :--- | :--- |
| **Sistema de Conquistas (Achievements)** | *Achievement Unlocked* | Mais de 40 desafios mapeados (ex: *'Primeiro Pato'*, *'Amigo dos Porcos'*, *'Mestre da Espada'*). Exibe pop-up gráfico na tela ao conquistar e concede bônus de XP. |
"""

with open(artifact_path, "w", encoding="utf-8") as f:
    f.write(content)

with open(workspace_path, "w", encoding="utf-8") as f:
    f.write(content)

print("Documentos gerados:")
print(" -", artifact_path)
print(" -", workspace_path)
