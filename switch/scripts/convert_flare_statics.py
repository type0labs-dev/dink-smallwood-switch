#!/usr/bin/env python3
"""
convert_flare_statics.py

Ingestion and Conversion Pipeline for Static Objects, Scenery, Chests, Shrines, and Loot:
Converts Flare RPG 3D pre-rendered static assets into Dink Smallwood engine assets
(for PC and Nintendo Switch Definitive Edition).

Fixes:
- Accurately parses packed animation descriptors (*.txt) for all 39 ground loot items.
- Extracts Frame 5 (the grounded resting item) with crisp, non-fragmented boundaries.
- Also extracts the 6-frame dropping animation (*drop*) for each loot item.
- Generates 32-bit RGBA PNGs (Web & RTDink HD) and 24-bit TrueColor BMPs (classic Dink).
- Generates INI entries with proper bounding boxes and grounded anchor points.
"""

import os
import re
import sys
import json
import urllib.request
import subprocess
from concurrent.futures import ThreadPoolExecutor

BASE_DIR = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", ".."))
RAW_CACHE_DIR = os.path.join(BASE_DIR, "research", "flare_raw", "statics")
WEB_SCENERY_DIR = os.path.join(BASE_DIR, "research", "web_assets", "flare_scenery")
DINK_SCENERY_DIR = os.path.join(BASE_DIR, "bin", "dink", "graphics", "scenery")
DATA_OUT_DIR = os.path.join(BASE_DIR, "switch", "data")
GROUPED_DB_PATH = os.path.join(BASE_DIR, "research", "grouped_visual_database.json")

os.makedirs(RAW_CACHE_DIR, exist_ok=True)
os.makedirs(WEB_SCENERY_DIR, exist_ok=True)
os.makedirs(DINK_SCENERY_DIR, exist_ok=True)
os.makedirs(DATA_OUT_DIR, exist_ok=True)

GITHUB_FC_RAW = "https://raw.githubusercontent.com/flareteam/flare-game/master/mods/fantasycore"
GITHUB_EMP_RAW = "https://raw.githubusercontent.com/flareteam/flare-game/master/mods/empyrean_campaign"
GITHUB_ALPHA_RAW = "https://raw.githubusercontent.com/flareteam/flare-game/master/mods/alpha_demo"
GITHUB_ART_TILED = "https://raw.githubusercontent.com/flareteam/flare-game-art-src/master/tiled/tilesheets"

def fetch_cached(url, local_name):
    local_path = os.path.join(RAW_CACHE_DIR, local_name)
    if not os.path.exists(local_path) or os.path.getsize(local_path) == 0:
        print(f"  Downloading: {local_name}...")
        try:
            req = urllib.request.Request(url, headers={'User-Agent': 'Mozilla/5.0'})
            with urllib.request.urlopen(req) as resp, open(local_path, 'wb') as out_file:
                out_file.write(resp.read())
        except Exception as e:
            print(f"  [ERROR] Downloading {url}: {e}")
            if os.path.exists(local_path):
                os.remove(local_path)
            return None
    return local_path

LOOT_ITEMS = [
    # Consumíveis & Riquezas
    ("hp_potion", "Poção de Cura (Vida)", "potions", "Frasco de vidro lapidado com elixir vermelho de cura profunda.", 901),
    ("mp_potion", "Poção de Mana (Magia)", "potions", "Frasco de vidro com líquido azul fluorescente de restauração mística.", 902),
    ("coins5", "Pilha Pequena de Moedas de Ouro", "wealth", "Pequeno punhado de moedas de ouro maciço pré-renderizadas.", 903),
    ("coins25", "Pilha Média de Moedas de Ouro", "wealth", "Pilha reluzente de moedas de ouro puro.", 904),
    ("coins100", "Grande Monte de Moedas de Ouro", "wealth", "Grande tesouro com montante de moedas de ouro brilhantes.", 905),
    ("pouch", "Bolsa de Couro com Moedas", "wealth", "Bolsa de camurça atada contendo moedas e joias preciosas.", 906),
    ("gem", "Gema Preciosa Lapidada", "wealth", "Rubi/safira bruta lapidada de alto valor comercial.", 907),
    ("scroll", "Pergaminho de Feitiço Arcano", "tomes", "Pergaminho antigo selado com cera contendo encantamento mágico.", 908),
    ("book", "Grimório Mágico Encadernado", "tomes", "Livro encadernado em couro com cantoneiras de latão e conhecimentos arcanos.", 909),
    # Armas Brancas
    ("dagger", "Adaga de Aço", "weapons", "Adaga curta de lâmina afiada para golpes rápidos.", 910),
    ("shortsword", "Espada Curta", "weapons", "Espada de ferro equilibrada de uma mão.", 911),
    ("longsword", "Espada Longa", "weapons", "Espada de lâmina larga com guarda-cruz reforçada.", 912),
    ("greatsword", "Montante / Espada de Duas Mãos", "weapons", "Espada pesada de lâmina longa com empunhadura estendida.", 913),
    ("zweihander", "Espada Zweihander", "weapons", "Espada colossal de duas mãos para corte devastador.", 914),
    ("hand_axe", "Machadinha de Mão", "weapons", "Machado leve de caçador e lenhador.", 915),
    ("battle_axe", "Machado de Batalha", "weapons", "Machado de guerra com lâmina dupla pesada.", 916),
    ("infantry_axe", "Machado de Infantaria", "weapons", "Machado balanceado com lâmina curva de infantaria.", 917),
    ("club", "Clava Rústica", "weapons", "Clava rústica de carvalho maciço.", 918),
    ("reinforced_club", "Clava Reforçada com Cravos", "weapons", "Clava de combate reforçada com cravos de ferro.", 919),
    ("mace", "Maça de Ferro com Pontas", "weapons", "Maça de guerra medieval de ferro fundido.", 920),
    ("maul", "Maul / Malho de Guerra", "weapons", "Martelo pesado com cabeça cilíndrica para esmagamento.", 921),
    ("smith_hammer", "Martelo de Ferreiro", "weapons", "Martelo de ferro forjado usado para moldar metais e combate.", 922),
    ("war_hammer", "Martelo de Guerra", "weapons", "Martelo de combate nobre com bico de corvo perfurante.", 923),
    # Arcos e Varinhas
    ("slingshot", "Estilingue de Caça", "ranged", "Estilingue clássico de couro e madeira.", 924),
    ("shortbow", "Arco Curto de Caçador", "ranged", "Arco leve de madeira ágil para disparos rápidos.", 925),
    ("longbow", "Arco Longo de Teixo", "ranged", "Arco militar longo com grande poder de perfuração.", 926),
    ("greatbow", "Grande Arco de Guerra", "ranged", "Arco colossal reforçado com hastes de aço.", 927),
    ("wand", "Varinha Mágica", "magic", "Varinha arcana talhada para canalizar projéteis mágicos.", 928),
    ("rod", "Cetro de Canalização", "magic", "Cetro de cristal para amplificação de feitiços elementais.", 929),
    ("staff", "Cajado de Madeira Arcano", "magic", "Cajado longo de freixo encimado com orbe encantado.", 930),
    ("greatstaff", "Grande Cajado do Arquimago", "magic", "Cajado colossal com foco de energia arcana concentrada.", 931),
    # Armaduras e Vestimentas
    ("clothes", "Túnica de Linho Rústica", "armor", "Vestimenta simples de camponês.", 932),
    ("leather_armor", "Gibão de Couro Curtido", "armor", "Armadura de couro reforçada com tachas de metal.", 933),
    ("steel_armor", "Armadura de Placas de Aço", "armor", "Couraça completa de aço polido para cavaleiros.", 934),
    ("boots", "Botas de Couro de Aventureiro", "armor", "Botas resistentes com fivelas de bronze.", 935),
    ("belt", "Cinto de Couro Trabalhado", "armor", "Cinto com fivela forjada e coldre de adaga.", 936),
    ("ring", "Anel Mágico com Gema", "armor", "Anel de ouro incrustado com rubi místico.", 937),
    ("buckler", "Broquel Redondo", "shields", "Escudo pequeno e ágil para desvio rápido de golpes.", 938),
    ("shield", "Escudo de Cavaleiro Medieval", "shields", "Escudo de madeira reforçado com bordas de ferro e brasão.", 939)
]

def main():
    print("================================================================")
    print("  DINK DEFINITIVE EDITION - FLARE SCENERY & PROPS INGESTION     ")
    print("================================================================")
    
    commands_to_run = []
    scenery_db_entries = []
    ini_lines = [
        "; ========================================================",
        "; DINK SMALLWOOD DEFINITIVE EDITION - FLARE SCENERY & PROPS",
        "; Professional 3D Pre-rendered Scenery, Chests, Shrines & Loot",
        "; ========================================================\n"
    ]

    # -------------------------------------------------------------
    # 1. CONVERSÃO DO BAÚ DO CHEFE (boss_chest - 4 estágios animados)
    # -------------------------------------------------------------
    print("\n[1/6] Ingerindo Baú do Chefe Interativo (4 Fases)...")
    chest_sheet = fetch_cached(f"{GITHUB_ART_TILED}/boss_chest.png", "boss_chest.png")
    if chest_sheet and os.path.exists(chest_sheet):
        chest_web_dir = os.path.join(WEB_SCENERY_DIR, "chests", "boss_chest")
        chest_dink_dir = os.path.join(DINK_SCENERY_DIR, "flare_boss_chest")
        os.makedirs(chest_web_dir, exist_ok=True)
        os.makedirs(chest_dink_dir, exist_ok=True)

        chest_frames_web = []
        for i in range(4):
            fn = i + 1
            web_png = os.path.join(chest_web_dir, f"chest-0{fn}.png")
            dink_bmp = os.path.join(chest_dink_dir, f"ch-0{fn}.bmp")
            dink_png = os.path.join(chest_dink_dir, f"ch-0{fn}.png")
            chest_frames_web.append(f"research/web_assets/flare_scenery/chests/boss_chest/chest-0{fn}.png")

            cmd_png = (
                f"magick '{chest_sheet}' -crop 192x192+{i*192}+0 +repage -trim +repage "
                f"-resize 96x96\\> -gravity south -background none -extent 100x100 '{web_png}' && "
                f"cp '{web_png}' '{dink_png}'"
            )
            cmd_bmp = (
                f"magick '{web_png}' -background black -alpha remove -type truecolor bmp3:'{dink_bmp}'"
            )
            commands_to_run.append(f"{cmd_png} && {cmd_bmp}")

        ini_lines.append("; Bau do Chefe Ornamental (4 frames: 1=fechado, 2=destravando, 3=abrindo, 4=aberto)")
        ini_lines.append("load_sequence graphics\\scenery\\flare_boss_chest\\ch- 940 NOTANIM 50 95 -35 -20 35 10\n")

        scenery_db_entries.append({
            "id": "flare_boss_chest",
            "name": "Baú do Chefe Dourado (Interativo 4 Fases)",
            "dmod_slug": "flare",
            "dmod_title": "Acervo Flare RPG (Definitive Edition)",
            "author": "Clint Bellanger / Flare RPG Team",
            "category": "scenery",
            "tags": ["flare_rpg", "cenario", "bau", "interativo", "tesouro", "3d"],
            "preview": "research/web_assets/flare_scenery/chests/boss_chest/chest-01.png",
            "width": 100,
            "height": 100,
            "total_frames": 4,
            "available_directions": ["1"],
            "default_action": "open",
            "default_direction": "1",
            "actions": {
                "open": {
                    "key": "open",
                    "label": "Abertura do Baú",
                    "icon": "📦",
                    "directions": {
                        "1": {
                            "dir_name": "Frontal",
                            "frames": chest_frames_web,
                            "fps": 4,
                            "frame_count": 4,
                            "width": 100,
                            "height": 100,
                            "ini_info": "load_sequence graphics\\scenery\\flare_boss_chest\\ch- 940 NOTANIM 50 95 -35 -20 35 10",
                            "preview": "research/web_assets/flare_scenery/chests/boss_chest/chest-01.png"
                        }
                    }
                }
            }
        })

    # -------------------------------------------------------------
    # 2. CONVERSÃO EXATA DE CONSUMÍVEIS E ITENS DE CHÃO (39 Itens)
    # -------------------------------------------------------------
    print("\n[2/6] Ingerindo 39 Itens de Chão e Consumíveis HD (Frames Exatos)...")
    loot_web_base = os.path.join(WEB_SCENERY_DIR, "loot")
    loot_dink_base = os.path.join(DINK_SCENERY_DIR, "flare_loot")
    os.makedirs(loot_web_base, exist_ok=True)
    os.makedirs(loot_dink_base, exist_ok=True)

    for item_key, item_name, subcat, item_desc, seq_id in LOOT_ITEMS:
        item_img_url = f"{GITHUB_FC_RAW}/images/loot/{item_key}.png"
        item_txt_url = f"{GITHUB_FC_RAW}/animations/loot/{item_key}.txt"

        raw_png = fetch_cached(item_img_url, f"loot_{item_key}.png")
        raw_txt = fetch_cached(item_txt_url, f"loot_{item_key}.txt")

        if not raw_png or not raw_txt or not os.path.exists(raw_png) or not os.path.exists(raw_txt):
            continue

        with open(raw_txt, "r", encoding="utf-8") as tf:
            txt_content = tf.read()

        # Parse all frames: frame=idx,0,x,y,w,h,hx,hy
        frame_matches = re.findall(r'frame=(\d+),0,(\d+),(\d+),(\d+),(\d+)', txt_content)
        if not frame_matches:
            print(f"  [WARN] No frame definitions found for {item_key}!")
            continue

        item_web_dir = os.path.join(loot_web_base, item_key)
        os.makedirs(item_web_dir, exist_ok=True)

        # The last frame is the grounded resting item!
        last_fr = frame_matches[-1]
        gx, gy, gw, gh = int(last_fr[1]), int(last_fr[2]), int(last_fr[3]), int(last_fr[4])

        # Unified canvas dimension
        cw = max(gw + 24, 72)
        ch = max(gh + 24, 72)

        # 1. Main Ground Static Sprite (frame 5)
        web_png = os.path.join(item_web_dir, f"{item_key}-01.png")
        dink_bmp = os.path.join(loot_dink_base, f"{item_key}-01.bmp")
        dink_png = os.path.join(loot_dink_base, f"{item_key}-01.png")
        rel_web = f"research/web_assets/flare_scenery/loot/{item_key}/{item_key}-01.png"

        cmd_ground = (
            f"magick '{raw_png}' -crop {gw}x{gh}+{gx}+{gy} +repage "
            f"-background none -gravity center -extent {cw}x{ch} '{web_png}' && "
            f"cp '{web_png}' '{dink_png}' && "
            f"magick '{web_png}' -background black -alpha remove -type truecolor bmp3:'{dink_bmp}'"
        )
        commands_to_run.append(cmd_ground)

        # 2. Extract full dropping animation (all frames)
        drop_frames_web = []
        for fi, fr in enumerate(frame_matches):
            f_num = fi + 1
            fx, fy, fw, fh = int(fr[1]), int(fr[2]), int(fr[3]), int(fr[4])
            drop_png = os.path.join(item_web_dir, f"drop-0{f_num}.png")
            drop_frames_web.append(f"research/web_assets/flare_scenery/loot/{item_key}/drop-0{f_num}.png")

            cmd_drop = (
                f"magick '{raw_png}' -crop {fw}x{fh}+{fx}+{fy} +repage "
                f"-background none -gravity center -extent {cw}x{ch} '{drop_png}'"
            )
            commands_to_run.append(cmd_drop)

        ini_lines.append(f"; {item_name} ({item_key})")
        ini_lines.append(f"load_sequence graphics\\scenery\\flare_loot\\{item_key}- {seq_id} NOTANIM {cw//2} {ch-10} -15 -10 15 5\n")

        scenery_db_entries.append({
            "id": f"flare_loot_{item_key}",
            "name": f"{item_name} (Flare 3D)",
            "dmod_slug": "flare",
            "dmod_title": "Acervo Flare RPG (Definitive Edition)",
            "author": "Clint Bellanger / Flare RPG Team",
            "category": "items_weapons",
            "tags": ["flare_rpg", "loot", "item", subcat, "chao", "3d"],
            "preview": rel_web,
            "width": cw,
            "height": ch,
            "total_frames": len(frame_matches),
            "available_directions": ["1"],
            "default_action": "idle",
            "default_direction": "1",
            "actions": {
                "idle": {
                    "key": "idle",
                    "label": "No Chão (Fixo)",
                    "icon": "✨",
                    "directions": {
                        "1": {
                            "dir_name": "Fixo",
                            "frames": [rel_web],
                            "fps": 1,
                            "frame_count": 1,
                            "width": cw,
                            "height": ch,
                            "ini_info": f"load_sequence graphics\\scenery\\flare_loot\\{item_key}- {seq_id} NOTANIM {cw//2} {ch-10} -15 -10 15 5",
                            "preview": rel_web
                        }
                    }
                },
                "drop": {
                    "key": "drop",
                    "label": "Caindo no Chão",
                    "icon": "🔽",
                    "directions": {
                        "1": {
                            "dir_name": "Queda",
                            "frames": drop_frames_web,
                            "fps": 8,
                            "frame_count": len(drop_frames_web),
                            "width": cw,
                            "height": ch,
                            "ini_info": f"Animacao completa de queda e impacto (6 frames)",
                            "preview": rel_web
                        }
                    }
                }
            }
        })

    # -------------------------------------------------------------
    # 3. CONVERSÃO DE SANTUÁRIOS & MONUMENTOS ARCANOS
    # -------------------------------------------------------------
    print("\n[3/6] Ingerindo Obeliscos de Retorno & Estátuas Guardiãs...")
    ob_png = fetch_cached(f"{GITHUB_FC_RAW}/images/npcs/return_obelisk1.png", "return_obelisk1.png")
    if ob_png and os.path.exists(ob_png):
        ob_web_dir = os.path.join(WEB_SCENERY_DIR, "shrines", "obelisk")
        ob_dink_dir = os.path.join(DINK_SCENERY_DIR, "flare_obelisk")
        os.makedirs(ob_web_dir, exist_ok=True)
        os.makedirs(ob_dink_dir, exist_ok=True)

        ob_coords = [(0, 0), (117, 0), (238, 0), (0, 192), (117, 192), (234, 192)]
        ob_web_frames = []
        for i, (cx, cy) in enumerate(ob_coords):
            fn = i + 1
            web_png = os.path.join(ob_web_dir, f"ob-0{fn}.png")
            dink_bmp = os.path.join(ob_dink_dir, f"ob-0{fn}.bmp")
            dink_png = os.path.join(ob_dink_dir, f"ob-0{fn}.png")
            ob_web_frames.append(f"research/web_assets/flare_scenery/shrines/obelisk/ob-0{fn}.png")

            cmd_png = (
                f"magick '{ob_png}' -crop 117x192+{cx}+{cy} +repage -trim +repage "
                f"-resize 90x140\\> -gravity south -background none -extent 96x145 '{web_png}' && "
                f"cp '{web_png}' '{dink_png}'"
            )
            cmd_bmp = (
                f"magick '{web_png}' -background black -alpha remove -type truecolor bmp3:'{dink_bmp}'"
            )
            commands_to_run.append(f"{cmd_png} && {cmd_bmp}")

        ini_lines.append("; Obelisco de Retorno Arcano (6 frames em loop continuo pulsante de 120ms)")
        ini_lines.append("load_sequence graphics\\scenery\\flare_obelisk\\ob- 950 120 48 138 -25 -12 25 8\n")

        scenery_db_entries.append({
            "id": "flare_return_obelisk",
            "name": "Obelisco Arcano de Retorno (Runas Azuis)",
            "dmod_slug": "flare",
            "dmod_title": "Acervo Flare RPG (Definitive Edition)",
            "author": "Clint Bellanger / Flare RPG Team",
            "category": "scenery",
            "tags": ["flare_rpg", "santuario", "obelisco", "magia", "save_point", "animado", "3d"],
            "preview": "research/web_assets/flare_scenery/shrines/obelisk/ob-01.png",
            "width": 96,
            "height": 145,
            "total_frames": 6,
            "available_directions": ["1"],
            "default_action": "pulse",
            "default_direction": "1",
            "actions": {
                "pulse": {
                    "key": "pulse",
                    "label": "Pulso Rúnico",
                    "icon": "🔮",
                    "directions": {
                        "1": {
                            "dir_name": "Fixo",
                            "frames": ob_web_frames,
                            "fps": 8,
                            "frame_count": 6,
                            "width": 96,
                            "height": 145,
                            "ini_info": "load_sequence graphics\\scenery\\flare_obelisk\\ob- 950 120 48 138 -25 -12 25 8",
                            "preview": "research/web_assets/flare_scenery/shrines/obelisk/ob-01.png"
                        }
                    }
                }
            }
        })

    # Estátua Guardiã do Fogo (statue_guardian_fire)
    st_png = fetch_cached(f"{GITHUB_ALPHA_RAW}/images/npcs/statue_guardian_fire.png", "statue_fire.png")
    if st_png and os.path.exists(st_png):
        st_web_dir = os.path.join(WEB_SCENERY_DIR, "shrines", "statue_fire")
        st_dink_dir = os.path.join(DINK_SCENERY_DIR, "flare_statue_fire")
        os.makedirs(st_web_dir, exist_ok=True)
        os.makedirs(st_dink_dir, exist_ok=True)

        st_coords = [(0, 0), (0, 73), (0, 146), (42, 0), (42, 73), (42, 146), (0, 0), (42, 73)]
        st_web_frames = []
        for i, (cx, cy) in enumerate(st_coords):
            fn = i + 1
            web_png = os.path.join(st_web_dir, f"st-0{fn}.png")
            dink_bmp = os.path.join(st_dink_dir, f"st-0{fn}.bmp")
            dink_png = os.path.join(st_dink_dir, f"st-0{fn}.png")
            st_web_frames.append(f"research/web_assets/flare_scenery/shrines/statue_fire/st-0{fn}.png")

            cmd_png = (
                f"magick '{st_png}' -crop 42x73+{cx}+{cy} +repage -trim +repage "
                f"-resize 70x120\\> -gravity south -background none -extent 75x125 '{web_png}' && "
                f"cp '{web_png}' '{dink_png}'"
            )
            cmd_bmp = (
                f"magick '{web_png}' -background black -alpha remove -type truecolor bmp3:'{dink_bmp}'"
            )
            commands_to_run.append(f"{cmd_png} && {cmd_bmp}")

        ini_lines.append("; Estatua Guardiana do Fogo Ancestral (8 frames animados de 100ms)")
        ini_lines.append("load_sequence graphics\\scenery\\flare_statue_fire\\st- 951 100 37 120 -18 -12 18 8\n")

        scenery_db_entries.append({
            "id": "flare_statue_fire",
            "name": "Estátua Guardiã Ancestral (Chamas Vivas)",
            "dmod_slug": "flare",
            "dmod_title": "Acervo Flare RPG (Definitive Edition)",
            "author": "Clint Bellanger / Flare RPG Team",
            "category": "scenery",
            "tags": ["flare_rpg", "santuario", "estatua", "fogo", "monumento", "animado", "3d"],
            "preview": "research/web_assets/flare_scenery/shrines/statue_fire/st-01.png",
            "width": 75,
            "height": 125,
            "total_frames": 8,
            "available_directions": ["1"],
            "default_action": "flame",
            "default_direction": "1",
            "actions": {
                "flame": {
                    "key": "flame",
                    "label": "Chamas Crepitantes",
                    "icon": "🔥",
                    "directions": {
                        "1": {
                            "dir_name": "Fixo",
                            "frames": st_web_frames,
                            "fps": 10,
                            "frame_count": 8,
                            "width": 75,
                            "height": 125,
                            "ini_info": "load_sequence graphics\\scenery\\flare_statue_fire\\st- 951 100 37 120 -18 -12 18 8",
                            "preview": "research/web_assets/flare_scenery/shrines/statue_fire/st-01.png"
                        }
                    }
                }
            }
        })

    # -------------------------------------------------------------
    # 4. CONVERSÃO DE ARQUITETURA, PORTÕES & TORRE EM RUÍNAS
    # -------------------------------------------------------------
    print("\n[4/6] Ingerindo Portões de Ferro, Escadarias & Torre em Ruínas...")
    gate_png = fetch_cached(f"{GITHUB_ART_TILED}/dungeon_door_left.png", "dungeon_door_left.png")
    if gate_png and os.path.exists(gate_png):
        gate_web_dir = os.path.join(WEB_SCENERY_DIR, "dungeon", "gate_left")
        gate_dink_dir = os.path.join(DINK_SCENERY_DIR, "flare_gate_left")
        os.makedirs(gate_web_dir, exist_ok=True)
        os.makedirs(gate_dink_dir, exist_ok=True)

        web_png = os.path.join(gate_web_dir, "gate-01.png")
        dink_bmp = os.path.join(gate_dink_dir, "gate-01.bmp")
        dink_png = os.path.join(gate_dink_dir, "gate-01.png")
        rel_web = "research/web_assets/flare_scenery/dungeon/gate_left/gate-01.png"

        cmd_png = (
            f"magick '{gate_png}' -trim +repage -resize 160x210\\> "
            f"-gravity south -background none -extent 165x215 '{web_png}' && "
            f"cp '{web_png}' '{dink_png}'"
        )
        cmd_bmp = (
            f"magick '{web_png}' -background black -alpha remove -type truecolor bmp3:'{dink_bmp}'"
        )
        commands_to_run.append(f"{cmd_png} && {cmd_bmp}")

        ini_lines.append("; Portao Arqueado de Ferro da Masmorra")
        ini_lines.append("load_sequence graphics\\scenery\\flare_gate_left\\gate- 952 NOTANIM 82 210 -75 -15 75 10\n")

        scenery_db_entries.append({
            "id": "flare_gate_dungeon",
            "name": "Portão Arqueado de Ferro da Masmorra",
            "dmod_slug": "flare",
            "dmod_title": "Acervo Flare RPG (Definitive Edition)",
            "author": "Clint Bellanger / Flare RPG Team",
            "category": "scenery",
            "tags": ["flare_rpg", "dungeon", "portao", "ferro", "arquitetura", "3d"],
            "preview": rel_web,
            "width": 165,
            "height": 215,
            "total_frames": 1,
            "available_directions": ["1"],
            "default_action": "idle",
            "default_direction": "1",
            "actions": {
                "idle": {
                    "key": "idle",
                    "label": "Portão Fechado",
                    "icon": "🚪",
                    "directions": {
                        "1": {
                            "dir_name": "Fixo",
                            "frames": [rel_web],
                            "fps": 1,
                            "frame_count": 1,
                            "width": 165,
                            "height": 215,
                            "ini_info": "load_sequence graphics\\scenery\\flare_gate_left\\gate- 952 NOTANIM 82 210 -75 -15 75 10",
                            "preview": rel_web
                        }
                    }
                }
            }
        })

    # A Grande Torre em Ruínas (grassland_rottentower)
    tower_png = fetch_cached(f"{GITHUB_ART_TILED}/grassland_rottentower.png", "grassland_rottentower.png")
    if tower_png and os.path.exists(tower_png):
        tower_web_dir = os.path.join(WEB_SCENERY_DIR, "ruins", "rottentower")
        tower_dink_dir = os.path.join(DINK_SCENERY_DIR, "flare_rottentower")
        os.makedirs(tower_web_dir, exist_ok=True)
        os.makedirs(tower_dink_dir, exist_ok=True)

        web_png = os.path.join(tower_web_dir, "tower-01.png")
        dink_bmp = os.path.join(tower_dink_dir, "tower-01.bmp")
        dink_png = os.path.join(tower_dink_dir, "tower-01.png")
        rel_web = "research/web_assets/flare_scenery/ruins/rottentower/tower-01.png"

        cmd_png = (
            f"magick '{tower_png}' -trim +repage -resize 400x400\\> "
            f"-gravity south -background none -extent 405x405 '{web_png}' && "
            f"cp '{web_png}' '{dink_png}'"
        )
        cmd_bmp = (
            f"magick '{web_png}' -background black -alpha remove -type truecolor bmp3:'{dink_bmp}'"
        )
        commands_to_run.append(f"{cmd_png} && {cmd_bmp}")

        ini_lines.append("; A Grande Torre de Pedra em Ruinas")
        ini_lines.append("load_sequence graphics\\scenery\\flare_rottentower\\tower- 953 NOTANIM 202 395 -130 -45 130 25\n")

        scenery_db_entries.append({
            "id": "flare_rottentower",
            "name": "A Grande Torre de Pedra em Ruínas",
            "dmod_slug": "flare",
            "dmod_title": "Acervo Flare RPG (Definitive Edition)",
            "author": "Clint Bellanger / Flare RPG Team",
            "category": "scenery",
            "tags": ["flare_rpg", "ruinas", "torre", "monumental", "pedra", "3d"],
            "preview": rel_web,
            "width": 405,
            "height": 405,
            "total_frames": 1,
            "available_directions": ["1"],
            "default_action": "idle",
            "default_direction": "1",
            "actions": {
                "idle": {
                    "key": "idle",
                    "label": "Torre Monumental",
                    "icon": "🏰",
                    "directions": {
                        "1": {
                            "dir_name": "Fixo",
                            "frames": [rel_web],
                            "fps": 1,
                            "frame_count": 1,
                            "width": 405,
                            "height": 405,
                            "ini_info": "load_sequence graphics\\scenery\\flare_rottentower\\tower- 953 NOTANIM 202 395 -130 -45 130 25",
                            "preview": rel_web
                        }
                    }
                }
            }
        })

    # -------------------------------------------------------------
    # 5. CONVERSÃO DE ÁRVORES 3D PRÉ-RENDERIZADAS
    # -------------------------------------------------------------
    print("\n[5/6] Ingerindo Árvores Pré-Renderizadas 3D...")
    trees_sheet = fetch_cached(f"{GITHUB_ART_TILED}/grassland_trees.png", "grassland_trees.png")
    if trees_sheet and os.path.exists(trees_sheet):
        tree_configs = [
            ("tree_oak", "Carvalho Centenário Frondoso", 1, 1, 954, "Árvore de carvalho com copa volumosa e folhas detalhadas."),
            ("tree_gum", "Eucalipto Alto de Folhas Densas", 1, 5, 955, "Eucalipto majestoso de tronco vertical."),
            ("tree_dead", "Árvore Morta e Assombrada", 1, 9, 956, "Tronco retorcido com galhos secos para florestas sombrias."),
            ("tree_stump", "Toco de Madeira com Musgo", 2, 0, 957, "Toco antigo com musgo e raízes aparentes.")
        ]

        for t_key, t_name, tr, tc, seq_id, t_desc in tree_configs:
            tree_web_dir = os.path.join(WEB_SCENERY_DIR, "nature", t_key)
            tree_dink_dir = os.path.join(DINK_SCENERY_DIR, f"flare_{t_key}")
            os.makedirs(tree_web_dir, exist_ok=True)
            os.makedirs(tree_dink_dir, exist_ok=True)

            web_png = os.path.join(tree_web_dir, f"{t_key}-01.png")
            dink_bmp = os.path.join(tree_dink_dir, f"{t_key}-01.bmp")
            dink_png = os.path.join(tree_dink_dir, f"{t_key}-01.png")
            rel_web = f"research/web_assets/flare_scenery/nature/{t_key}/{t_key}-01.png"

            cmd_png = (
                f"magick '{trees_sheet}' -crop 192x384+{tc*192}+{tr*384} +repage -trim +repage "
                f"-resize 180x310\\> -gravity south -background none -extent 185x315 '{web_png}' && "
                f"cp '{web_png}' '{dink_png}'"
            )
            cmd_bmp = (
                f"magick '{web_png}' -background black -alpha remove -type truecolor bmp3:'{dink_bmp}'"
            )
            commands_to_run.append(f"{cmd_png} && {cmd_bmp}")

            ini_lines.append(f"; {t_name}")
            ini_lines.append(f"load_sequence graphics\\scenery\\flare_{t_key}\\{t_key}- {seq_id} NOTANIM 92 310 -30 -15 30 10\n")

            scenery_db_entries.append({
                "id": f"flare_{t_key}",
                "name": f"{t_name} (Flare 3D)",
                "dmod_slug": "flare",
                "dmod_title": "Acervo Flare RPG (Definitive Edition)",
                "author": "Clint Bellanger / Flare RPG Team",
                "category": "scenery",
                "tags": ["flare_rpg", "natureza", "arvore", "floresta", "vegetacao", "3d"],
                "preview": rel_web,
                "width": 185,
                "height": 315,
                "total_frames": 1,
                "available_directions": ["1"],
                "default_action": "idle",
                "default_direction": "1",
                "actions": {
                    "idle": {
                        "key": "idle",
                        "label": "Árvore",
                        "icon": "🌲",
                        "directions": {
                            "1": {
                                "dir_name": "Fixo",
                                "frames": [rel_web],
                                "fps": 1,
                                "frame_count": 1,
                                "width": 185,
                                "height": 315,
                                "ini_info": f"load_sequence graphics\\scenery\\flare_{t_key}\\{t_key}- {seq_id} NOTANIM 92 310 -30 -15 30 10",
                                "preview": rel_web
                            }
                        }
                    }
                }
            })

    # -------------------------------------------------------------
    # 6. CONVERSÃO DE ADEREÇOS DE ACAMPAMENTO & BRASEIRO ANIMADO
    # -------------------------------------------------------------
    print("\n[6/6] Ingerindo Tenda, Toco de Machado & Braseiro Animado...")
    structs_sheet = fetch_cached(f"{GITHUB_ART_TILED}/grassland_structures.png", "grassland_structures.png")
    if structs_sheet and os.path.exists(structs_sheet):
        struct_configs = [
            ("tent", "Tenda de Acampamento de Aventureiro", 3, 0, 958, "Tenda rústica com lona impermeável para expedições."),
            ("stump_axe", "Toco com Machado de Lenhador", 1, 11, 959, "Toco de corte com machado cravado na madeira."),
            ("fence_wood", "Cerca Rural de Madeira", 1, 8, 960, "Trecho de cerca rústica para fazendas e divisórias.")
        ]

        for s_key, s_name, sr, sc, seq_id, s_desc in struct_configs:
            s_web_dir = os.path.join(WEB_SCENERY_DIR, "camp", s_key)
            s_dink_dir = os.path.join(DINK_SCENERY_DIR, f"flare_{s_key}")
            os.makedirs(s_web_dir, exist_ok=True)
            os.makedirs(s_dink_dir, exist_ok=True)

            web_png = os.path.join(s_web_dir, f"{s_key}-01.png")
            dink_bmp = os.path.join(s_dink_dir, f"{s_key}-01.bmp")
            dink_png = os.path.join(s_dink_dir, f"{s_key}-01.png")
            rel_web = f"research/web_assets/flare_scenery/camp/{s_key}/{s_key}-01.png"

            cmd_png = (
                f"magick '{structs_sheet}' -crop 192x384+{sc*192}+{sr*384} +repage -trim +repage "
                f"-resize 140x180\\> -gravity south -background none -extent 145x185 '{web_png}' && "
                f"cp '{web_png}' '{dink_png}'"
            )
            cmd_bmp = (
                f"magick '{web_png}' -background black -alpha remove -type truecolor bmp3:'{dink_bmp}'"
            )
            commands_to_run.append(f"{cmd_png} && {cmd_bmp}")

            ini_lines.append(f"; {s_name}")
            ini_lines.append(f"load_sequence graphics\\scenery\\flare_{s_key}\\{s_key}- {seq_id} NOTANIM 72 180 -35 -15 35 12\n")

            scenery_db_entries.append({
                "id": f"flare_{s_key}",
                "name": f"{s_name} (Flare 3D)",
                "dmod_slug": "flare",
                "dmod_title": "Acervo Flare RPG (Definitive Edition)",
                "author": "Clint Bellanger / Flare RPG Team",
                "category": "scenery",
                "tags": ["flare_rpg", "acampamento", "vila", "aderecos", "3d"],
                "preview": rel_web,
                "width": 145,
                "height": 185,
                "total_frames": 1,
                "available_directions": ["1"],
                "default_action": "idle",
                "default_direction": "1",
                "actions": {
                    "idle": {
                        "key": "idle",
                        "label": "Adereço",
                        "icon": "🏕️",
                        "directions": {
                            "1": {
                                "dir_name": "Fixo",
                                "frames": [rel_web],
                                "fps": 1,
                                "frame_count": 1,
                                "width": 145,
                                "height": 185,
                                "ini_info": f"load_sequence graphics\\scenery\\flare_{s_key}\\{s_key}- {seq_id} NOTANIM 72 180 -35 -15 35 12",
                                "preview": rel_web
                            }
                        }
                    }
                }
            })

    # Braseiro de Fogo Animado da Masmorra
    dungeon_tiles = fetch_cached(f"{GITHUB_FC_RAW}/images/tilesets/tileset_dungeon.png", "tileset_dungeon.png")
    if dungeon_tiles and os.path.exists(dungeon_tiles):
        br_web_dir = os.path.join(WEB_SCENERY_DIR, "dungeon", "brazier")
        br_dink_dir = os.path.join(DINK_SCENERY_DIR, "flare_brazier")
        os.makedirs(br_web_dir, exist_ok=True)
        os.makedirs(br_dink_dir, exist_ok=True)

        brazier_frames_web = []
        br_coords = [
            (0, 1612), (0, 1996), (0, 2380), (0, 2764),
            (0, 3148), (0, 3532), (619, 774), (811, 774)
        ]
        for i, (bx, by) in enumerate(br_coords):
            fn = i + 1
            web_png = os.path.join(br_web_dir, f"br-0{fn}.png")
            dink_bmp = os.path.join(br_dink_dir, f"br-0{fn}.bmp")
            dink_png = os.path.join(br_dink_dir, f"br-0{fn}.png")
            brazier_frames_web.append(f"research/web_assets/flare_scenery/dungeon/brazier/br-0{fn}.png")

            cmd_png = (
                f"magick '{dungeon_tiles}' -crop 192x384+{bx}+{by} +repage -trim +repage "
                f"-resize 75x120\\> -gravity south -background none -extent 80x125 '{web_png}' && "
                f"cp '{web_png}' '{dink_png}'"
            )
            cmd_bmp = (
                f"magick '{web_png}' -background black -alpha remove -type truecolor bmp3:'{dink_bmp}'"
            )
            commands_to_run.append(f"{cmd_png} && {cmd_bmp}")

        ini_lines.append("; Braseiro de Ferro Forjado com Chamas Vivas (8 frames animados de 66ms)")
        ini_lines.append("load_sequence graphics\\scenery\\flare_brazier\\br- 961 66 40 120 -20 -10 20 8\n")

        scenery_db_entries.append({
            "id": "flare_brazier",
            "name": "Braseiro de Ferro com Fogo Animado",
            "dmod_slug": "flare",
            "dmod_title": "Acervo Flare RPG (Definitive Edition)",
            "author": "Clint Bellanger / Flare RPG Team",
            "category": "scenery",
            "tags": ["flare_rpg", "dungeon", "fogo", "braseiro", "iluminacao", "animado", "3d"],
            "preview": "research/web_assets/flare_scenery/dungeon/brazier/br-01.png",
            "width": 80,
            "height": 125,
            "total_frames": 8,
            "available_directions": ["1"],
            "default_action": "burn",
            "default_direction": "1",
            "actions": {
                "burn": {
                    "key": "burn",
                    "label": "Fogo Crepitante",
                    "icon": "🔥",
                    "directions": {
                        "1": {
                            "dir_name": "Fixo",
                            "frames": brazier_frames_web,
                            "fps": 12,
                            "frame_count": 8,
                            "width": 80,
                            "height": 125,
                            "ini_info": "load_sequence graphics\\scenery\\flare_brazier\\br- 961 66 40 120 -20 -10 20 8",
                            "preview": "research/web_assets/flare_scenery/dungeon/brazier/br-01.png"
                        }
                    }
                }
            }
        })

    # -------------------------------------------------------------
    # EXECUÇÃO PARALELA DAS OPERAÇÕES DO IMAGEMAGICK
    # -------------------------------------------------------------
    print(f"\n[EXEC] Executando {len(commands_to_run)} operações de conversão via ImageMagick...")
    with ThreadPoolExecutor(max_workers=8) as pool:
        results = list(pool.map(lambda c: os.system(c), commands_to_run))
        failures = sum(1 for r in results if r != 0)
        if failures > 0:
            print(f"  [AVISO] {failures} comandos retornaram código diferente de zero.")

    # -------------------------------------------------------------
    # SALVANDO INI DE CENÁRIO
    # -------------------------------------------------------------
    scenery_ini_path = os.path.join(DATA_OUT_DIR, "flare_scenery.ini")
    with open(scenery_ini_path, "w", encoding="utf-8") as f:
        f.write("\n".join(ini_lines))
    print(f"\n[OK] INI de Cenários gerado: {scenery_ini_path} ({len(ini_lines)} linhas)")

    # -------------------------------------------------------------
    # ATUALIZANDO BANCO VISUAL (grouped_visual_database.json)
    # -------------------------------------------------------------
    print(f"\n[DB] Atualizando banco visual unificado ({GROUPED_DB_PATH})...")
    with open(GROUPED_DB_PATH, "r", encoding="utf-8") as f:
        db = json.load(f)

    existing_ids = {e["id"] for e in scenery_db_entries}
    db = [e for e in db if e.get("id") not in existing_ids]
    db = scenery_db_entries + db

    with open(GROUPED_DB_PATH, "w", encoding="utf-8") as f:
        json.dump(db, f, indent=2, ensure_ascii=False)
    print(f"[OK] Banco visual atualizado! Total de entidades no banco: {len(db)}")
    print(f"[OK] Novos objetos de cenário e loot adicionados: {len(scenery_db_entries)}")

if __name__ == "__main__":
    main()
