#!/usr/bin/env python3
"""
convert_flare_creatures.py

Complete Ingestion and Conversion Pipeline:
Converts Flare RPG 8-directional pre-rendered 3D characters/monsters into
Dink Smallwood engine assets (Complete/Definitive Edition for Nintendo Switch & PC).

Supports 45 entities across Skeletons, Spiders, Goblins, Dragons, Undead, Golems, and NPCs.
"""

import os
import re
import sys
import json
import urllib.request
from collections import defaultdict
from concurrent.futures import ThreadPoolExecutor

BASE_DIR = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", ".."))
RAW_CACHE_DIR = os.path.join(BASE_DIR, "research", "flare_raw")
ANIMS_DIR = os.path.join(RAW_CACHE_DIR, "animations")
IMAGES_DIR = os.path.join(RAW_CACHE_DIR, "images")
WEB_ASSETS_DIR = os.path.join(BASE_DIR, "research", "web_assets", "flare")
DINK_GRAPHICS_DIR = os.path.join(BASE_DIR, "bin", "dink", "graphics", "foes")
DINK_STORY_PT_DIR = os.path.join(BASE_DIR, "bin", "dink", "story_pt")
DINK_STORY_EN_DIR = os.path.join(BASE_DIR, "bin", "dink", "story")
DATA_OUT_DIR = os.path.join(BASE_DIR, "switch", "data")

FLARE_TO_DINK_DIR = {
    0: '4',  # West (Left)            - ⬅
    1: '7',  # North-West (Up-Left)   - ↖
    2: '8',  # North (Up)             - ⬆
    3: '9',  # North-East (Up-Right)  - ↗
    4: '6',  # East (Right)           - ➡
    5: '3',  # South-East (Down-Right)- ↘
    6: '2',  # South (Down)           - ⬇
    7: '1',  # South-West (Down-Left) - ↙
}

ACTION_MAP = {
    'stance': ('idle', 's', 'Parado'),
    'run': ('walk', 'w', 'Caminhando'),
    'run_alt': ('walk', 'w', 'Corrida Rápida'),
    'swing': ('attack', 'a', 'Atacando'),
    'dash_attack': ('attack', 'a', 'Investida'),
    'shield_bash': ('attack', 'a', 'Golpe Escudo'),
    'hit': ('hit', 'h', 'Ferido'),
    'die': ('die', 'd', 'Morte'),
    'critdie': ('die', 'd', 'Morte Crítica'),
    'cast': ('magic', 'm', 'Magia'),
    'cast_alt': ('magic', 'm', 'Especial'),
    'shoot': ('ranged', 'r', 'Disparo'),
    'spawn': ('spawn', 'p', 'Surgindo'),
    'block': ('block', 'b', 'Bloqueio'),
}

# Complete Master Bestiary Catalog (45 Entities)
CREATURE_CONFIGS = {
    # --- ESQUELETOS & CHEFES MORTOS-VIVOS ---
    'skeleton': {'prefix': 'sk', 'name_pt': 'Esqueleto Guerreiro', 'desc_pt': 'Guerreiro esquelético com espada e escudo cravado.', 'scale': 0.55, 'base_seq': 850, 'hp': 40, 'strength': 6, 'defense': 4, 'speed': 2, 'exp': 35, 'gold': 8, 'sounds': {'hit': 14, 'die': 15, 'att': 17}, 'quotes_hit': ["Apenas ossos... não sinto dor!", "Minha lâmina ainda cortará você!"], 'quotes_die': ["Voltarei... para a terra..."]},
    'skeleton_weak': {'prefix': 'skw', 'name_pt': 'Esqueleto Frágil', 'desc_pt': 'Recruta esquelético desarmado, ataca com garras ósseas.', 'scale': 0.50, 'base_seq': 860, 'hp': 20, 'strength': 3, 'defense': 1, 'speed': 2, 'exp': 15, 'gold': 4, 'sounds': {'hit': 14, 'die': 15, 'att': 17}, 'quotes_hit': ["*Clac-clac!*", "Ossos soltos!"], 'quotes_die': ["*Desmorona em pó...*"]},
    'skeleton_archer': {'prefix': 'ska', 'name_pt': 'Esqueleto Arqueiro', 'desc_pt': 'Atirador de elite morto-vivo que dispara flechas perfurantes.', 'scale': 0.55, 'base_seq': 870, 'hp': 30, 'strength': 7, 'defense': 2, 'speed': 2, 'exp': 40, 'gold': 10, 'sounds': {'hit': 14, 'die': 15, 'att': 17}, 'quotes_hit': ["Você não pode desviar das minhas flechas!", "Minha mira nunca falha!"], 'quotes_die': ["O arco... se parte..."]},
    'skeleton_mage': {'prefix': 'skm', 'name_pt': 'Esqueleto Necromante', 'desc_pt': 'Conjurador ósseo mestre das trevas que canaliza maldições.', 'scale': 0.55, 'base_seq': 880, 'hp': 45, 'strength': 8, 'defense': 3, 'speed': 2, 'exp': 50, 'gold': 15, 'sounds': {'hit': 14, 'die': 15, 'att': 17}, 'quotes_hit': ["As sombras consomem você!", "Sinta o frio do além!"], 'quotes_die': ["A morte é apenas o começo..."]},
    'skeleton_knight_boss': {'prefix': 'skk', 'name_pt': 'Lorde Cavaleiro da Morte', 'desc_pt': 'Chefe colosso morto-vivo em armadura negra de batalha.', 'scale': 0.65, 'base_seq': 890, 'hp': 140, 'strength': 15, 'defense': 10, 'speed': 2, 'exp': 200, 'gold': 50, 'sounds': {'hit': 14, 'die': 15, 'att': 17}, 'quotes_hit': ["CURVE-SE PERANTE O VERDADEIRO REI!", "Sua espada é fraca demais!"], 'quotes_die': ["MEU REINO... NUNCA... CAIRÁ!"]},
    'skeleton_mage_boss': {'prefix': 'smb', 'name_pt': 'Lorde Lich Necromante', 'desc_pt': 'Chefe supremo dos mortos-vivos com báculo de almas.', 'scale': 0.60, 'base_seq': 900, 'hp': 110, 'strength': 16, 'defense': 6, 'speed': 2, 'exp': 180, 'gold': 45, 'sounds': {'hit': 14, 'die': 15, 'att': 17}, 'quotes_hit': ["SUA ALMA PERTENCE AO MEU BÁCULO!", "Tolos mortais!"], 'quotes_die': ["EU VOLTAREI... EM OUTRA ERA!"]},
    'skeleton_mage_fire': {'prefix': 'smf', 'name_pt': 'Lich Piromante Infernal', 'desc_pt': 'Feiticeiro esquelético que lança rajadas de fogo demoníaco.', 'scale': 0.58, 'base_seq': 910, 'hp': 65, 'strength': 12, 'defense': 4, 'speed': 2, 'exp': 85, 'gold': 22, 'sounds': {'hit': 14, 'die': 15, 'att': 17}, 'quotes_hit': ["QUEIME NAS CHAMAS ETERNAS!", "Cinzas ao vento!"], 'quotes_die': ["O fogo... se apaga..."]},
    'skeleton_mage_ice': {'prefix': 'smi', 'name_pt': 'Lich Criomante Glacial', 'desc_pt': 'Feiticeiro dos cumes gelados capaz de congelar os ossos de Dink.', 'scale': 0.58, 'base_seq': 920, 'hp': 65, 'strength': 11, 'defense': 5, 'speed': 2, 'exp': 85, 'gold': 22, 'sounds': {'hit': 14, 'die': 15, 'att': 17}, 'quotes_hit': ["Sinta o abraço glacial da morte!", "Seu sangue vai congelar!"], 'quotes_die': ["Gelo... quebrado..."]},
    'skeleton_mage_high_boss': {'prefix': 'smh', 'name_pt': 'Arquilich Ancião Soberano', 'desc_pt': 'A mais poderosa entidade necromântica, soberano das catacumbas.', 'scale': 0.65, 'base_seq': 930, 'hp': 200, 'strength': 20, 'defense': 12, 'speed': 2, 'exp': 300, 'gold': 100, 'sounds': {'hit': 14, 'die': 15, 'att': 17}, 'quotes_hit': ["INSIGNIFICANTE! EU DOMINO A PRÓPRIA VIDA!", "DESTRUIÇÃO TOTAL!"], 'quotes_die': ["COMO... UM MERO... HUMANO?!"]},

    # --- ARACNÍDEOS, INSETOS & ENXAMES ---
    'antlion': {'prefix': 'sp', 'name_pt': 'Aranha Gigante das Cavernas', 'desc_pt': 'Aracnídeo colossal predador com presas venenosas afiadas.', 'scale': 0.58, 'base_seq': 940, 'hp': 35, 'strength': 8, 'defense': 2, 'speed': 3, 'exp': 40, 'gold': 5, 'sounds': {'hit': 18, 'die': 19, 'att': 20}, 'quotes_hit': ["*Chiiiisss!*", "*O veneno ferve!*"], 'quotes_die': ["*Chiiii...*"]},
    'antlion_small': {'prefix': 'sps', 'name_pt': 'Aranha Filhote do Enxame', 'desc_pt': 'Pequena e veloz, ataca em bandos vorazes nas profundezas.', 'scale': 0.38, 'base_seq': 950, 'hp': 12, 'strength': 3, 'defense': 1, 'speed': 4, 'exp': 10, 'gold': 2, 'sounds': {'hit': 18, 'die': 19, 'att': 20}, 'quotes_hit': ["*Cric!*", "*Chii!*"], 'quotes_die': ["*Esmagada...*"]},
    'antlion_armored': {'prefix': 'spa', 'name_pt': 'Aranha Blindada de Aço', 'desc_pt': 'Aranha gigante com carapaça metálica impenetrável por flechas.', 'scale': 0.60, 'base_seq': 960, 'hp': 75, 'strength': 11, 'defense': 9, 'speed': 2, 'exp': 90, 'gold': 20, 'sounds': {'hit': 18, 'die': 19, 'att': 20}, 'quotes_hit': ["*Clang! Carapaça de aço!*", "*Presas de ferro!*"], 'quotes_die': ["*A armadura quebra...*"]},
    'antlion_fossilized': {'prefix': 'spf', 'name_pt': 'Aranha Fóssil de Pedra', 'desc_pt': 'Aracnídeo pré-histórico petrificado que despertou da rocha.', 'scale': 0.60, 'base_seq': 970, 'hp': 60, 'strength': 9, 'defense': 8, 'speed': 2, 'exp': 75, 'gold': 15, 'sounds': {'hit': 18, 'die': 19, 'att': 20}, 'quotes_hit': ["*Rocha sólida!*", "*Poeira ancestral!*"], 'quotes_die': ["*Desaba em cascalho...*"]},
    'fire_ant': {'prefix': 'fia', 'name_pt': 'Formiga de Fogo Flamejante', 'desc_pt': 'Inseto gigante escarlate que queima ao contato.', 'scale': 0.45, 'base_seq': 980, 'hp': 25, 'strength': 6, 'defense': 3, 'speed': 3, 'exp': 30, 'gold': 6, 'sounds': {'hit': 18, 'die': 19, 'att': 20}, 'quotes_hit': ["*Chamas ardentes!*", "*Tsssk!*"], 'quotes_die': ["*Brasas apagadas...*"]},
    'ice_ant': {'prefix': 'ica', 'name_pt': 'Formiga de Gelo Cristalina', 'desc_pt': 'Inseto ártico com mandíbulas afiadas de gelo puro.', 'scale': 0.45, 'base_seq': 990, 'hp': 25, 'strength': 6, 'defense': 3, 'speed': 3, 'exp': 30, 'gold': 6, 'sounds': {'hit': 18, 'die': 19, 'att': 20}, 'quotes_hit': ["*Estilhaços de gelo!*", "*Frio cortante!*"], 'quotes_die': ["*Derrete...*"]},

    # --- GOBLINS & HOBGOBLINS ---
    'goblin': {'prefix': 'gb', 'name_pt': 'Goblin Saqueador', 'desc_pt': 'Criatura ágil e traiçoeira que ataca armada com clavas.', 'scale': 0.48, 'base_seq': 1000, 'hp': 25, 'strength': 4, 'defense': 1, 'speed': 3, 'exp': 20, 'gold': 12, 'sounds': {'hit': 11, 'die': 12, 'att': 13}, 'quotes_hit': ["Eeeek! Não bate no goblin!", "Covarde!"], 'quotes_die': ["Meu ouro... não leve meu ouro..."]},
    'goblin_runner': {'prefix': 'gbr', 'name_pt': 'Goblin Rastreador', 'desc_pt': 'Batedor ultra-rápido que cerca Dink antes que ele possa reagir.', 'scale': 0.46, 'base_seq': 1010, 'hp': 20, 'strength': 4, 'defense': 1, 'speed': 4, 'exp': 22, 'gold': 10, 'sounds': {'hit': 11, 'die': 12, 'att': 13}, 'quotes_hit': ["Você é muito lento!", "Pega se puder!"], 'quotes_die': ["Fui... pego..."]},
    'goblin_elite': {'prefix': 'gbe', 'name_pt': 'Goblin Guerreiro de Elite', 'desc_pt': 'Campeão do clã goblin com elmo e escudo reforçado.', 'scale': 0.50, 'base_seq': 1020, 'hp': 45, 'strength': 7, 'defense': 5, 'speed': 3, 'exp': 45, 'gold': 18, 'sounds': {'hit': 11, 'die': 12, 'att': 13}, 'quotes_hit': ["Pela glória do grande chefe!", "Escudo forte!"], 'quotes_die': ["O clã... vingará..."]},
    'goblin_elite_runner': {'prefix': 'gsa', 'name_pt': 'Goblin Assassino das Sombras', 'desc_pt': 'Guerreiro furtivo armado com adagas venenosas.', 'scale': 0.48, 'base_seq': 1030, 'hp': 35, 'strength': 8, 'defense': 3, 'speed': 4, 'exp': 50, 'gold': 20, 'sounds': {'hit': 11, 'die': 12, 'att': 13}, 'quotes_hit': ["Um golpe e você dorme!", "Nas sombras!"], 'quotes_die': ["A escuridão... me leva..."]},
    'goblin_minecart': {'prefix': 'gbm', 'name_pt': 'Goblin Demolidor do Carrinho', 'desc_pt': 'Goblin insano pilotando um carrinho de mineração com explosivos!', 'scale': 0.52, 'base_seq': 1040, 'hp': 55, 'strength': 12, 'defense': 6, 'speed': 4, 'exp': 70, 'gold': 25, 'sounds': {'hit': 11, 'die': 12, 'att': 13}, 'quotes_hit': ["SAI DA FRENTE! NÃO TEM FREIO!", "HAHAHA! BUM!"], 'quotes_die': ["KABOOOOOOM!"]},
    'hobgoblin': {'prefix': 'hob', 'name_pt': 'Hobgoblin Brutal', 'desc_pt': 'Primo gigante dos goblins, musculoso e sedento por sangue.', 'scale': 0.58, 'base_seq': 1050, 'hp': 70, 'strength': 10, 'defense': 6, 'speed': 2, 'exp': 80, 'gold': 25, 'sounds': {'hit': 11, 'die': 12, 'att': 13}, 'quotes_hit': ["ESMAGAR DINK!", "Você é pequeno e fraco!"], 'quotes_die': ["Grrr... como pôde..."]},
    'hobgoblin_archer': {'prefix': 'hoa', 'name_pt': 'Hobgoblin Franco-Atirador', 'desc_pt': 'Atirador bruto com arco longo de grande alcance.', 'scale': 0.58, 'base_seq': 1060, 'hp': 55, 'strength': 11, 'defense': 4, 'speed': 2, 'exp': 75, 'gold': 22, 'sounds': {'hit': 11, 'die': 12, 'att': 13}, 'quotes_hit': ["Na mosca!", "Minhas flechas atravessam árvores!"], 'quotes_die': ["Corda rompida..."]},

    # --- GOLEMS & COLOSSOS ---
    'minotaur': {'prefix': 'mi', 'name_pt': 'Minotauro Brutal', 'desc_pt': 'Chefe colossal com machado pesado de duas mãos e giro demolidor.', 'scale': 0.65, 'base_seq': 1070, 'hp': 130, 'strength': 14, 'defense': 8, 'speed': 2, 'exp': 150, 'gold': 40, 'sounds': {'hit': 21, 'die': 22, 'att': 23}, 'quotes_hit': ["MUUUAAARGH! Isso só me enfurece!", "VOU ESMAGAR CADA OSSO DO SEU CORPO!"], 'quotes_die': ["O labirinto... me chama..."]},
    'boulder': {'prefix': 'bou', 'name_pt': 'Golem de Pedra Viva', 'desc_pt': 'Monstro rochoso que rola e esmaga tudo em seu caminho.', 'scale': 0.62, 'base_seq': 1080, 'hp': 100, 'strength': 12, 'defense': 12, 'speed': 2, 'exp': 120, 'gold': 30, 'sounds': {'hit': 21, 'die': 22, 'att': 23}, 'quotes_hit': ["*Estrondo ensurdecedor!*", "*Pedra contra carne!*"], 'quotes_die': ["*Desmorona em seixos e cascalho.*"]},

    # --- DRAGÕES & WYVERNS ---
    'wyvern': {'prefix': 'wy', 'name_pt': 'Wyvern Alado', 'desc_pt': 'Dragão alado predador clássico de rasantes e mordidas mortais.', 'scale': 0.62, 'base_seq': 1090, 'hp': 90, 'strength': 12, 'defense': 6, 'speed': 4, 'exp': 110, 'gold': 25, 'sounds': {'hit': 24, 'die': 25, 'att': 26}, 'quotes_hit': ["*Rugido ensurdecedor!*", "*Asas batem furiosas!*"], 'quotes_die': ["*O dragão cai dos céus com um estrondo!*"]},
    'wyvern_air': {'prefix': 'wya', 'name_pt': 'Wyvern das Tempestades', 'desc_pt': 'Dragão elétrico que canaliza relâmpagos entre as asas.', 'scale': 0.62, 'base_seq': 1100, 'hp': 95, 'strength': 13, 'defense': 6, 'speed': 4, 'exp': 120, 'gold': 30, 'sounds': {'hit': 24, 'die': 25, 'att': 26}, 'quotes_hit': ["*Relâmpagos estalam no ar!*", "*Trovoada feroz!*"], 'quotes_die': ["*O relâmpago se extingue...*"]},
    'wyvern_fire': {'prefix': 'wyf', 'name_pt': 'Wyvern Vulcânico Infernal', 'desc_pt': 'Dragão vermelho chamejante nascido das lavas do submundo.', 'scale': 0.62, 'base_seq': 1110, 'hp': 105, 'strength': 14, 'defense': 7, 'speed': 4, 'exp': 130, 'gold': 35, 'sounds': {'hit': 24, 'die': 25, 'att': 26}, 'quotes_hit': ["*Chamas incandescentes!*", "*O ar ferve ao redor!*"], 'quotes_die': ["*O fogo do dragão se apaga...*"]},
    'wyvern_water': {'prefix': 'wyw', 'name_pt': 'Wyvern Glacial das Profundezas', 'desc_pt': 'Dragão azul das geleiras eternas com sopro congelante.', 'scale': 0.62, 'base_seq': 1120, 'hp': 100, 'strength': 13, 'defense': 7, 'speed': 4, 'exp': 125, 'gold': 30, 'sounds': {'hit': 24, 'die': 25, 'att': 26}, 'quotes_hit': ["*Vento cortante do ártico!*", "*Nevasca destruidora!*"], 'quotes_die': ["*Asas congeladas caem...*"]},
    'wyvern_air_boss': {'prefix': 'wyb', 'name_pt': 'Rei Dragão Tempestuoso Soberano', 'desc_pt': 'O mais lendário soberano dos céus, o maior chefe dracônico.', 'scale': 0.70, 'base_seq': 1130, 'hp': 250, 'strength': 22, 'defense': 14, 'speed': 4, 'exp': 450, 'gold': 120, 'sounds': {'hit': 24, 'die': 25, 'att': 26}, 'quotes_hit': ["OS CÉUS SE CURVAM AO MEU COMANDO!", "MORTAIS NÃO TOCAM AS NUVENS!"], 'quotes_die': ["A TEMPESTADE... ENFIM... CESSA..."]},

    # --- MORTOS-VIVOS, ESPECTROS & INVOCADORES ---
    'zombie': {'prefix': 'zm', 'name_pt': 'Zumbi Putrefato', 'desc_pt': 'Cadáver reanimado resistente que rasteja em busca de carne viva.', 'scale': 0.55, 'base_seq': 1140, 'hp': 50, 'strength': 5, 'defense': 3, 'speed': 1, 'exp': 25, 'gold': 6, 'sounds': {'hit': 27, 'die': 28, 'att': 29}, 'quotes_hit': ["Urggghhh...", "Carneee..."], 'quotes_die': ["Silêncio... enfim..."]},
    'frozen_zombie': {'prefix': 'zmf', 'name_pt': 'Zumbi Congelado', 'desc_pt': 'Cadáver preservado no gelo que causa lentidão ao atacar.', 'scale': 0.55, 'base_seq': 1150, 'hp': 60, 'strength': 6, 'defense': 5, 'speed': 1, 'exp': 35, 'gold': 8, 'sounds': {'hit': 27, 'die': 28, 'att': 29}, 'quotes_hit': ["Friiiooo...", "Gelo eterno..."], 'quotes_die': ["Descongelando..."]},
    'zombie_dark': {'prefix': 'zmd', 'name_pt': 'Zumbi das Sombras', 'desc_pt': 'Zumbi banhado em magia proibida que drena a vida da presa.', 'scale': 0.55, 'base_seq': 1160, 'hp': 70, 'strength': 8, 'defense': 4, 'speed': 2, 'exp': 45, 'gold': 12, 'sounds': {'hit': 27, 'die': 28, 'att': 29}, 'quotes_hit': ["Escuridããão...", "Sua vida é minha..."], 'quotes_die': ["De volta às sombras..."]},
    'zombie_ghost': {'prefix': 'zmg', 'name_pt': 'Espectro / Alma Penada', 'desc_pt': 'Fantasma etéreo translúcido imune a ataques físicos convencionais.', 'scale': 0.55, 'base_seq': 1170, 'hp': 40, 'strength': 9, 'defense': 8, 'speed': 3, 'exp': 60, 'gold': 15, 'sounds': {'hit': 27, 'die': 28, 'att': 29}, 'quotes_hit': ["*Lamento agoniante!*", "Você não pode ferir o que já morreu!"], 'quotes_die': ["Paz... finalmente..."]},
    'cursed_grave': {'prefix': 'cg1', 'name_pt': 'Tumba Amaldiçoada', 'desc_pt': 'Sepultura profana que invoca esqueletos continuamente até ser destruída.', 'scale': 0.55, 'base_seq': 1180, 'hp': 80, 'strength': 0, 'defense': 6, 'speed': 0, 'exp': 50, 'gold': 20, 'sounds': {'hit': 21, 'die': 22, 'att': 23}, 'quotes_hit': ["*Pedra da tumba range!*", "*Espíritos clamam!*"], 'quotes_die': ["*A sepultura se quebra e a maldição cessa.*"]},
    'cursed_grave_fire': {'prefix': 'cgf', 'name_pt': 'Tumba das Chamas Eternas', 'desc_pt': 'Cripta vulcânica que cospe chamas e mortos-vivos de fogo.', 'scale': 0.55, 'base_seq': 1190, 'hp': 90, 'strength': 5, 'defense': 7, 'speed': 0, 'exp': 65, 'gold': 25, 'sounds': {'hit': 21, 'die': 22, 'att': 23}, 'quotes_hit': ["*Chamas jorram da tumba!*"], 'quotes_die': ["*Cripta destruída.*"]},
    'cursed_grave_ice': {'prefix': 'cgi', 'name_pt': 'Tumba do Inverno Eterno', 'desc_pt': 'Cripta congelada que invoca horrores do gelo.', 'scale': 0.55, 'base_seq': 1200, 'hp': 90, 'strength': 5, 'defense': 7, 'speed': 0, 'exp': 65, 'gold': 25, 'sounds': {'hit': 21, 'die': 22, 'att': 23}, 'quotes_hit': ["*O gelo racha com força!*"], 'quotes_die': ["*A cripta se desfaz em neve.*"]},

    # --- NPCs, ALDEÕES & MONÓLITOS ---
    'knight': {'prefix': 'kn', 'name_pt': 'Cavaleiro Nobre Real', 'desc_pt': 'Paladino do reino com armadura de placas prateada.', 'scale': 0.55, 'base_seq': 1210, 'hp': 80, 'strength': 10, 'defense': 10, 'speed': 2, 'exp': 80, 'gold': 20, 'sounds': {'hit': 14, 'die': 15, 'att': 17}, 'quotes_hit': ["Pela honra do reino!", "Defenda-se com honra!"], 'quotes_die': ["Minha guarda... caiu..."]},
    'peasant_man1': {'prefix': 'pm1', 'name_pt': 'Camponês Trabalhador', 'desc_pt': 'Aldeão dedicado à colheita e ao trabalho nas terras.', 'scale': 0.52, 'base_seq': 1220, 'hp': 30, 'strength': 2, 'defense': 1, 'speed': 2, 'exp': 5, 'gold': 5, 'sounds': {'hit': 14, 'die': 15, 'att': 17}, 'quotes_hit': ["Ei! Cuidado com essa espada!", "Sou apenas um humilde camponês!"], 'quotes_die': ["Minha pobre família..."]},
    'peasant_man2': {'prefix': 'pm2', 'name_pt': 'Fazendeiro da Vila', 'desc_pt': 'Veterano dos campos, conhecedor dos segredos da região.', 'scale': 0.52, 'base_seq': 1230, 'hp': 30, 'strength': 2, 'defense': 1, 'speed': 2, 'exp': 5, 'gold': 5, 'sounds': {'hit': 14, 'die': 15, 'att': 17}, 'quotes_hit': ["Malditos monstros atacando meus porcos!", "O reino já foi mais seguro."], 'quotes_die': ["Adeus, boa terra..."]},
    'peasant_woman1': {'prefix': 'pw1', 'name_pt': 'Aldeã Camponesa', 'desc_pt': 'Moradora local com histórias sobre criaturas da floresta.', 'scale': 0.52, 'base_seq': 1240, 'hp': 25, 'strength': 1, 'defense': 1, 'speed': 2, 'exp': 5, 'gold': 5, 'sounds': {'hit': 14, 'die': 15, 'att': 17}, 'quotes_hit': ["Socorro! Alguém ajude!", "Não faça isso!"], 'quotes_die': ["Piedade..."]},
    'peasant_woman2': {'prefix': 'pw2', 'name_pt': 'Matrona da Vila', 'desc_pt': 'Cozinheira e curandeira respeitada da aldeia.', 'scale': 0.52, 'base_seq': 1250, 'hp': 25, 'strength': 1, 'defense': 1, 'speed': 2, 'exp': 5, 'gold': 5, 'sounds': {'hit': 14, 'die': 15, 'att': 17}, 'quotes_hit': ["Menino mal-educado!", "Vou te dar um corretivo!"], 'quotes_die': ["Quem cuidará da sopa..."]},
    'guild_man': {'prefix': 'gm1', 'name_pt': 'Mestre da Guilda / Alquimista', 'desc_pt': 'Erudito respeitado que vende fórmulas raras e missões.', 'scale': 0.54, 'base_seq': 1260, 'hp': 50, 'strength': 5, 'defense': 5, 'speed': 2, 'exp': 30, 'gold': 50, 'sounds': {'hit': 14, 'die': 15, 'att': 17}, 'quotes_hit': ["Cuidado com as poções!", "Conhecimento é poder!"], 'quotes_die': ["Minhas pesquisas..."]},
    'wandering_trader': {'prefix': 'wt1', 'name_pt': 'Mercador da Caravana', 'desc_pt': 'Comerciante itinerante que viaja com artefatos exóticos.', 'scale': 0.54, 'base_seq': 1270, 'hp': 45, 'strength': 3, 'defense': 4, 'speed': 2, 'exp': 20, 'gold': 100, 'sounds': {'hit': 14, 'die': 15, 'att': 17}, 'quotes_hit': ["Tenho mercadorias de terras distantes!", "Não toque nas relíquias sem pagar!"], 'quotes_die': ["Meus tesouros..."]},
    'peddler_goblin': {'prefix': 'pgb', 'name_pt': 'Goblin Mascate Pacífico', 'desc_pt': 'Raro goblin amigável que troca bugigangas brilhantes.', 'scale': 0.48, 'base_seq': 1280, 'hp': 30, 'strength': 3, 'defense': 3, 'speed': 2, 'exp': 15, 'gold': 40, 'sounds': {'hit': 11, 'die': 12, 'att': 13}, 'quotes_hit': ["Goblin bom não ataca humano! Goblin só quer moedinhas!", "Não me machuca!"], 'quotes_die': ["Brilhantes... adeus..."]},
    'return_obelisk1': {'prefix': 'obo', 'name_pt': 'Monólito Mágico de Retorno', 'desc_pt': 'Pilar rúnico místico que serve de ponto de teleporte e save.', 'scale': 0.55, 'base_seq': 1290, 'hp': 999, 'strength': 0, 'defense': 99, 'speed': 0, 'exp': 0, 'gold': 0, 'sounds': {'hit': 21, 'die': 22, 'att': 23}, 'quotes_hit': ["*O monólito rúnico brilha intensamente ao toque.*"], 'quotes_die': ["*Luz rúnica dissipa.*"]},
}

def ensure_dirs():
    os.makedirs(ANIMS_DIR, exist_ok=True)
    os.makedirs(IMAGES_DIR, exist_ok=True)
    os.makedirs(WEB_ASSETS_DIR, exist_ok=True)
    os.makedirs(DINK_GRAPHICS_DIR, exist_ok=True)
    os.makedirs(DINK_STORY_PT_DIR, exist_ok=True)
    os.makedirs(DINK_STORY_EN_DIR, exist_ok=True)
    os.makedirs(DATA_OUT_DIR, exist_ok=True)

def parse_animation_txt(txt_path):
    with open(txt_path, 'r', encoding='utf-8', errors='replace') as f:
        content = f.read()

    images_map = {}
    default_image = None
    sections = defaultdict(list)
    current_section = None
    section_durations = {}
    color_mod = None
    alpha_mod = None

    for raw_line in content.splitlines():
        line = raw_line.strip()
        if not line or line.startswith('#'):
            continue

        if line.startswith('color_mod='):
            try:
                color_mod = [int(c.strip()) for c in line[10:].split(',')]
            except:
                pass
        elif line.startswith('alpha_mod='):
            try:
                alpha_mod = int(line[10:].strip())
            except:
                pass
        elif line.startswith('INCLUDE '):
            inc_rel = line[8:].strip()
            inc_bname = os.path.basename(inc_rel)
            inc_path = os.path.join(ANIMS_DIR, inc_bname)
            if os.path.exists(inc_path):
                inc_imgs, inc_def, inc_sec, inc_dur, _, _ = parse_animation_txt(inc_path)
                images_map.update(inc_imgs)
                if default_image is None:
                    default_image = inc_def
                for k, v in inc_sec.items():
                    sections[k].extend(v)
                section_durations.update(inc_dur)

        elif line.startswith('image='):
            val = line[6:].strip()
            parts = val.split(',')
            img_rel = parts[0].strip()
            img_tag = parts[1].strip() if len(parts) > 1 else 'default'
            img_basename = os.path.basename(img_rel)
            images_map[img_tag] = img_basename
            if default_image is None:
                default_image = img_basename

        elif line.startswith('[') and line.endswith(']'):
            current_section = line[1:-1].strip()

        elif current_section:
            if line.startswith('duration='):
                m = re.search(r'duration=(\d+)(?:ms)?', line)
                if m:
                    section_durations[current_section] = int(m.group(1))
            elif line.startswith('frame='):
                val = line[6:].strip()
                parts = [p.strip() for p in val.split(',')]
                if len(parts) >= 8:
                    idx = int(parts[0])
                    flare_dir = int(parts[1])
                    x = int(parts[2])
                    y = int(parts[3])
                    w = int(parts[4])
                    h = int(parts[5])
                    hx = int(parts[6])
                    hy = int(parts[7])
                    img_id = parts[8] if len(parts) > 8 else 'default'
                    sections[current_section].append({
                        'idx': idx,
                        'flare_dir': flare_dir,
                        'x': x, 'y': y,
                        'w': w, 'h': h,
                        'hx': hx, 'hy': hy,
                        'img_id': img_id
                    })

    return images_map, default_image, sections, section_durations, color_mod, alpha_mod

def convert_creature(name, cfg, force=False):
    scale = cfg['scale']
    prefix = cfg['prefix']
    base_seq = cfg['base_seq']

    creature_web_dir = os.path.join(WEB_ASSETS_DIR, name)
    creature_dink_dir = os.path.join(DINK_GRAPHICS_DIR, f"flare_{name}")
    creature_ini_path = os.path.join(DATA_OUT_DIR, f"flare_{name}_dink.ini")

    if not force and os.path.exists(creature_ini_path) and os.path.exists(creature_web_dir) and len(os.listdir(creature_web_dir)) > 0:
        print(f"  [CACHE] {cfg['name_pt']} ({name}) already converted. Skipping.")
        return True

    print(f"\n=======================================================")
    print(f" Processing: {cfg['name_pt']} ({name})")
    print(f" Scale: {scale:.2f}x | Base Seq: {base_seq} | Prefix: {prefix}")
    print(f"=======================================================")

    txt_local = os.path.join(ANIMS_DIR, f"{name}.txt")
    if not os.path.exists(txt_local):
        print(f"[ERROR] Missing {txt_local}")
        return False

    images_map, default_img, sections, durations, color_mod, alpha_mod = parse_animation_txt(txt_local)

    mod_filter = ""
    if color_mod and len(color_mod) == 3:
        r, g, b = color_mod
        mod_filter += f" -channel R -evaluate multiply {r/255.0:.3f} -channel G -evaluate multiply {g/255.0:.3f} -channel B -evaluate multiply {b/255.0:.3f} +channel"
    if alpha_mod:
        mod_filter += f" -channel A -evaluate multiply {alpha_mod/255.0:.3f} +channel"

    # Resolve local images
    local_images = {}
    for tag, bname in images_map.items():
        img_path = os.path.join(IMAGES_DIR, bname)
        if os.path.exists(img_path):
            local_images[tag] = img_path

    if 'default' not in local_images and default_img:
        img_path = os.path.join(IMAGES_DIR, default_img)
        if os.path.exists(img_path):
            local_images['default'] = img_path

    os.makedirs(creature_web_dir, exist_ok=True)
    os.makedirs(creature_dink_dir, exist_ok=True)

    action_seq_offsets = {
        'walk': 0,
        'attack': 10,
        'die': 20,
        'idle': 30,
        'hit': 40,
        'magic': 50,
        'ranged': 60,
        'block': 70,
        'spawn': 80,
    }

    commands_to_run = []
    dink_ini_lines = []
    converted_count = 0

    for flare_section, frame_list in sections.items():
        if flare_section not in ACTION_MAP:
            continue

        act_name, act_code, act_label = ACTION_MAP[flare_section]
        if not frame_list:
            continue

        dir_frames = defaultdict(list)
        for fr in frame_list:
            dink_dir = FLARE_TO_DINK_DIR.get(fr['flare_dir'])
            if dink_dir:
                dir_frames[dink_dir].append(fr)

        max_l = max(fr['hx'] for fr in frame_list)
        max_r = max(fr['w'] - fr['hx'] for fr in frame_list)
        max_t = max(fr['hy'] for fr in frame_list)
        max_b = max(fr['h'] - fr['hy'] for fr in frame_list)

        cw = max_l + max_r
        ch = max_t + max_b

        scw = max(16, int(round(cw * scale)))
        sch = max(16, int(round(ch * scale)))
        center_x = int(round(max_l * scale))
        center_y = int(round(max_t * scale))

        box_half_w = max(10, int(scw * 0.22))
        box_top = -max(8, int(sch * 0.12))
        box_bot = max(8, int(sch * 0.10))
        box_l = -box_half_w
        box_r = box_half_w

        dur_ms = durations.get(flare_section, 600)
        num_frames = max(len(flist) for flist in dir_frames.values())
        delay_ms = max(40, min(150, int(dur_ms / max(1, num_frames))))

        act_web_dir = os.path.join(creature_web_dir, act_name)
        os.makedirs(act_web_dir, exist_ok=True)

        for dink_dir, flist in sorted(dir_frames.items()):
            flist.sort(key=lambda x: x['idx'])

            file_pfx = f"{prefix}-{act_code}{dink_dir}-"
            seq_id = base_seq + action_seq_offsets.get(act_name, 0) + int(dink_dir)

            dink_rel_path = f"graphics\\foes\\flare_{name}\\{file_pfx}"
            ini_entry = (
                f"load_sequence {dink_rel_path} {seq_id} {delay_ms} "
                f"{center_x} {center_y} {box_l} {box_top} {box_r} {box_bot}"
            )
            dink_ini_lines.append(ini_entry)

            for i, fr in enumerate(flist):
                frame_num = i + 1
                img_path = local_images.get(fr['img_id']) or local_images.get('default')
                if not img_path:
                    continue

                px = max_l - fr['hx']
                py = max_t - fr['hy']

                web_png = os.path.join(act_web_dir, f"{file_pfx}{frame_num:02d}.png")
                dink_bmp = os.path.join(creature_dink_dir, f"{file_pfx}{frame_num:02d}.bmp")
                dink_png = os.path.join(creature_dink_dir, f"{file_pfx}{frame_num:02d}.png")

                cmd_png = (
                    f"magick -size {cw}x{ch} xc:none "
                    f"\\( \"{img_path}\" -crop {fr['w']}x{fr['h']}+{fr['x']}+{fr['y']} +repage \\) "
                    f"-geometry +{px}+{py} -composite{mod_filter} -resize {scw}x{sch} \"{web_png}\" && "
                    f"cp \"{web_png}\" \"{dink_png}\""
                )
                cmd_bmp = (
                    f"magick -size {cw}x{ch} xc:black "
                    f"\\( \"{img_path}\" -crop {fr['w']}x{fr['h']}+{fr['x']}+{fr['y']} +repage \\) "
                    f"-geometry +{px}+{py} -composite{mod_filter} -resize {scw}x{sch} -alpha remove -type truecolor bmp3:\"{dink_bmp}\""
                )

                commands_to_run.append(cmd_png)
                commands_to_run.append(cmd_bmp)
                converted_count += 1

    if commands_to_run:
        print(f"  Executing {len(commands_to_run)} conversion operations with parallel workers...")
        with ThreadPoolExecutor(max_workers=8) as pool:
            results = list(pool.map(lambda c: os.system(c), commands_to_run))
            failures = sum(1 for r in results if r != 0)
            if failures > 0:
                print(f"  [WARN] {failures} operations returned non-zero code.")

    print(f"  Converted {converted_count} animation frames successfully!")

    with open(creature_ini_path, 'w') as f:
        f.write(f"; ========================================================\n")
        f.write(f"; {cfg['name_pt']} ({name}) - Flare RPG Definitive Edition\n")
        f.write(f"; {cfg['desc_pt']}\n")
        f.write(f"; ========================================================\n\n")
        f.write("\n".join(dink_ini_lines) + "\n")
    print(f"  Saved dink.ini sequence definitions: {creature_ini_path}")

    generate_dinkc_script(name, cfg)
    return True

def generate_dinkc_script(name, cfg):
    prefix = cfg['prefix']
    base_seq = cfg['base_seq']
    walk_base = base_seq
    att_base = base_seq + 10
    die_base = base_seq + 20

    is_npc = cfg['strength'] == 0 or name.startswith('peasant') or name.startswith('guild') or name.startswith('wandering') or name.startswith('return')
    brain = 16 if is_npc else 9

    quotes_hit = cfg.get('quotes_hit', ["Ouch!"])
    quotes_die = cfg.get('quotes_die', ["Adeus..."])
    sounds = cfg.get('sounds', {'hit': 14, 'die': 15, 'att': 17})

    script_content = f"""// ========================================================
// en-{name}.c
// Dink Smallwood Definitive Edition (Nintendo Switch / PC)
// Criatura: {cfg['name_pt']} ({name})
// Descricao: {cfg['desc_pt']}
// ========================================================

void main( void )
{{
    int &mhold;
    sp_brain(&current_sprite, {brain});
    sp_speed(&current_sprite, {cfg['speed']});
    sp_distance(&current_sprite, 55);
    sp_timing(&current_sprite, 0);
    sp_exp(&current_sprite, {cfg['exp']});
    
    sp_base_walk(&current_sprite, {walk_base});
    sp_base_attack(&current_sprite, {att_base});
    sp_base_death(&current_sprite, {die_base});
    
    sp_touch_damage(&current_sprite, {cfg['strength']});
    sp_hitpoints(&current_sprite, {cfg['hp']});
    sp_defense(&current_sprite, {cfg['defense']});
    
    sp_target(&current_sprite, 1);
}}

void touch( void )
{{
    if (&life > 0 && {cfg['strength']} > 0)
    {{
        &mhold = random(3, 1);
        if (&mhold == 1)
        {{
            playsound({sounds['att']}, 22050, 0, &current_sprite, 0);
        }}
    }}
}}

void hit( void )
{{
    playsound({sounds['hit']}, 22050, 0, &current_sprite, 0);
    sp_target(&current_sprite, 1);
    
    &mhold = random(4, 1);
    if (&mhold == 1)
    {{
        say("{quotes_hit[0]}", &current_sprite);
    }}
    if (&mhold == 2 && {len(quotes_hit)} > 1)
    {{
        say("{quotes_hit[1 % len(quotes_hit)]}", &current_sprite);
    }}
}}

void die( void )
{{
    playsound({sounds['die']}, 22050, 0, &current_sprite, 0);
    say("{quotes_die[0]}", &current_sprite);
    
    &mhold = random(3, 1);
    if (&mhold == 1 && {cfg['gold']} > 0)
    {{
        int &gold = create_sprite(&current_sprite_x, &current_sprite_y, 0, 160, 1);
        sp_brain(&gold, 6);
    }}
    
    int &hold = sp_editor_num(&current_sprite);
    if (&hold != 0)
    {{
        editor_type(&hold, 1);
    }}
}}
"""
    pt_path = os.path.join(DINK_STORY_PT_DIR, f"en-{name}.c")
    en_path = os.path.join(DINK_STORY_EN_DIR, f"en-{name}.c")
    with open(pt_path, 'w', encoding='utf-8') as f:
        f.write(script_content)
    with open(en_path, 'w', encoding='utf-8') as f:
        f.write(script_content)

def build_master_ini():
    master_ini_path = os.path.join(DATA_OUT_DIR, "flare_bestiary_all.ini")
    all_lines = [
        "; ========================================================",
        "; DINK SMALLWOOD DEFINITIVE EDITION - FLARE RPG BESTIARY",
        "; Professional 3D Pre-rendered Bestiary Sequences",
        "; ========================================================\n"
    ]
    for name in CREATURE_CONFIGS.keys():
        ini_file = os.path.join(DATA_OUT_DIR, f"flare_{name}_dink.ini")
        if os.path.exists(ini_file):
            with open(ini_file, 'r') as f:
                all_lines.append(f.read())
    with open(master_ini_path, 'w') as f:
        f.write("\n".join(all_lines))
    print(f"\nCreated Master Bestiary INI: {master_ini_path}")

def main():
    ensure_dirs()
    args = sys.argv[1:]
    force = '--force' in args
    targets = [a for a in args if not a.startswith('--')]

    if not targets or targets[0] in ('all', 'ALL'):
        targets = list(CREATURE_CONFIGS.keys())

    print(f"=== FLARE RPG MASTER BESTIARY PIPELINE ===")
    print(f"Total targets: {len(targets)} creatures / entities (Force={force})")

    for t in targets:
        if t in CREATURE_CONFIGS:
            convert_creature(t, CREATURE_CONFIGS[t], force=force)
        else:
            print(f"[WARN] Unknown creature '{t}'. Available: {list(CREATURE_CONFIGS.keys())}")

    build_master_ini()
    print("\n[SUCCESS] Master bestiary conversion complete!")

if __name__ == '__main__':
    main()
