#!/usr/bin/env python3
"""
convert_flare_heroes.py

Ingestion and Conversion Pipeline for Playable Heroes and Class Evolution:
Converts Flare RPG 3D modular characters into Dink Smallwood Definitive Edition assets.

Supports 6 Hero Classes / Tiers:
1. hero_male_peasant: Dink Camponês 3D (Classe Inicial / Fiel 1997)
2. hero_male_leather: Dink Caçador / Ladino (Armadura de Couro)
3. hero_male_soldier: Dink Guarda Real (Cota de Malha & Escudo)
4. hero_male_paladin: Dink Paladino Sagrado (Placas & Greatsword)
5. hero_female_peasant: Heroína Camponesa 3D (Classe Inicial)
6. hero_female_mage: Heroína Feiticeira / Maga Arcana (Roupas Místicas & Cajado)

Outputs:
- RGBA 32-bit PNGs in research/web_assets/flare/heroes/<hero_id>/<action>/
- Updates research/grouped_visual_database.json
- Updates research/visual_database.json
- Updates asset_database.html with dedicated filter pill
"""

import os
import re
import sys
import json
import subprocess
from concurrent.futures import ThreadPoolExecutor

BASE_DIR = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", ".."))
RESEARCH_DIR = os.path.join(BASE_DIR, "research")
WEB_ASSETS_DIR = os.path.join(RESEARCH_DIR, "web_assets", "flare", "heroes")
GROUPED_DB_PATH = os.path.join(RESEARCH_DIR, "grouped_visual_database.json")
VISUAL_DB_PATH = os.path.join(RESEARCH_DIR, "visual_database.json")
HTML_PATH = os.path.join(BASE_DIR, "asset_database.html")

MALE_BUILD_DIR = "/tmp/hero_showcase_build"
FEMALE_BUILD_DIR = "/tmp/female_build"

# Dink 8-direction mapping (Numpad) to Flare direction index
# 1=SW, 2=S, 3=SE, 4=W, 6=E, 7=NW, 8=N, 9=NE
DINK_DIR_TO_FLARE = {
    '1': (5, 'Sudoeste (↙)'),
    '2': (6, 'Sul (↓)'),
    '3': (4, 'Sudeste (↘)'),
    '4': (7, 'Oeste (←)'),
    '6': (3, 'Leste (→)'),
    '7': (0, 'Noroeste (↖)'),
    '8': (1, 'Norte (↑)'),
    '9': (2, 'Nordeste (↗)'),
}

ACTIONS = {
    'idle': ('stance', 's', 'Parado / Guarda', '🧍', 4, 10),
    'walk': ('run', 'w', 'Caminhando / Correndo', '🚶', 8, 12),
    'attack': ('swing', 'a', 'Ataque Melee / Espada', '⚔️', 4, 12),
    'die': ('die', 'd', 'Morte', '💀', 6, 8),
    'cast': ('cast', 'm', 'Magia / Conjuração', '✨', 4, 10),
}

HERO_DEFINITIONS = [
    {
        'id': 'hero_male_peasant',
        'prefix': 'hmp',
        'name': 'Dink Camponês 3D (Classe Inicial)',
        'class_title': 'Camponês Inicial',
        'gender': 'male',
        'tier': 0,
        'desc': 'Visual clássico de Dink Smallwood de 1997 em CGI 3D de alta fidelidade. Túnica de linho verde, calça simples e espada básica.',
        'tags': ['jogador', 'heroi', 'male', 'campones', '3d', 'alta_fidelidade', 'classe_inicial', 'flare_rpg', 'flare_hero'],
        'layers': [
            (f'{MALE_BUILD_DIR}/default_feet.txt', f'{MALE_BUILD_DIR}/default_feet.png'),
            (f'{MALE_BUILD_DIR}/default_legs.txt', f'{MALE_BUILD_DIR}/default_legs.png'),
            (f'{MALE_BUILD_DIR}/default_hands.txt', f'{MALE_BUILD_DIR}/default_hands.png'),
            (f'{MALE_BUILD_DIR}/default_chest.txt', f'{MALE_BUILD_DIR}/default_chest.png'),
            (f'{MALE_BUILD_DIR}/cloth_pants.txt', f'{MALE_BUILD_DIR}/cloth_pants.png'),
            (f'{MALE_BUILD_DIR}/cloth_shirt.txt', f'{MALE_BUILD_DIR}/cloth_shirt.png'),
            (f'{MALE_BUILD_DIR}/head_short.txt', f'{MALE_BUILD_DIR}/head_short.png'),
            (f'{MALE_BUILD_DIR}/longsword.txt', f'{MALE_BUILD_DIR}/longsword.png'),
        ],
        'actions': ['idle', 'walk', 'attack', 'die'],
    },
    {
        'id': 'hero_male_leather',
        'prefix': 'hml',
        'name': 'Dink Caçador / Ladino (Armadura de Couro)',
        'class_title': 'Caçador / Ladino (Tier 1)',
        'gender': 'male',
        'tier': 1,
        'desc': 'Evolução ágil com capuz de patrulheiro, colete e calças de couro batido reforçado e espada de caçador.',
        'tags': ['jogador', 'heroi', 'male', 'ladino', 'cacador', 'couro', '3d', 'alta_fidelidade', 'flare_rpg', 'flare_hero'],
        'layers': [
            (f'{MALE_BUILD_DIR}/leather_boots.txt', f'{MALE_BUILD_DIR}/leather_boots.png'),
            (f'{MALE_BUILD_DIR}/leather_pants.txt', f'{MALE_BUILD_DIR}/leather_pants.png'),
            (f'{MALE_BUILD_DIR}/default_hands.txt', f'{MALE_BUILD_DIR}/default_hands.png'),
            (f'{MALE_BUILD_DIR}/default_chest.txt', f'{MALE_BUILD_DIR}/default_chest.png'),
            (f'{MALE_BUILD_DIR}/leather_chest.txt', f'{MALE_BUILD_DIR}/leather_chest.png'),
            (f'{MALE_BUILD_DIR}/leather_hood.txt', f'{MALE_BUILD_DIR}/leather_hood.png'),
            (f'{MALE_BUILD_DIR}/longsword.txt', f'{MALE_BUILD_DIR}/longsword.png'),
        ],
        'actions': ['idle', 'walk', 'attack', 'die'],
    },
    {
        'id': 'hero_male_soldier',
        'prefix': 'hms',
        'name': 'Dink Guarda Real (Cota de Malha & Escudo)',
        'class_title': 'Guarda Real (Tier 2)',
        'gender': 'male',
        'tier': 2,
        'desc': 'Defensor de elite do Castelo de Goodheart. Cota de malha polida, peitoral e grevas de aço, escudo de pipa e espada longa.',
        'tags': ['jogador', 'heroi', 'male', 'guerreiro', 'soldado', 'escudo', 'cota_malha', '3d', 'alta_fidelidade', 'flare_rpg', 'flare_hero'],
        'layers': [
            (f'{MALE_BUILD_DIR}/leather_boots.txt', f'{MALE_BUILD_DIR}/leather_boots.png'),
            (f'{MALE_BUILD_DIR}/plate_greaves.txt', f'{MALE_BUILD_DIR}/plate_greaves.png'),
            (f'{MALE_BUILD_DIR}/plate_gauntlets.txt', f'{MALE_BUILD_DIR}/plate_gauntlets.png'),
            (f'{MALE_BUILD_DIR}/default_chest.txt', f'{MALE_BUILD_DIR}/default_chest.png'),
            (f'{MALE_BUILD_DIR}/plate_cuirass.txt', f'{MALE_BUILD_DIR}/plate_cuirass.png'),
            (f'{MALE_BUILD_DIR}/head_short.txt', f'{MALE_BUILD_DIR}/head_short.png'),
            (f'{MALE_BUILD_DIR}/kite_shield.txt', f'{MALE_BUILD_DIR}/kite_shield.png'),
            (f'{MALE_BUILD_DIR}/longsword.txt', f'{MALE_BUILD_DIR}/longsword.png'),
        ],
        'actions': ['idle', 'walk', 'attack', 'die'],
    },
    {
        'id': 'hero_male_paladin',
        'prefix': 'hmpal',
        'name': 'Dink Paladino Sagrado (Placas & Greatsword)',
        'class_title': 'Paladino / Campeão (Tier 3 - Endgame)',
        'gender': 'male',
        'tier': 3,
        'desc': 'Guerreiro lendário em armadura de placas completa polida, elmo com viseira e montante de duas mãos com runas brilhantes.',
        'tags': ['jogador', 'heroi', 'male', 'paladino', 'cavaleiro', 'placas', 'greatsword', 'endgame', '3d', 'alta_fidelidade', 'flare_rpg', 'flare_hero'],
        'layers': [
            (f'{MALE_BUILD_DIR}/leather_boots.txt', f'{MALE_BUILD_DIR}/leather_boots.png'),
            (f'{MALE_BUILD_DIR}/plate_greaves.txt', f'{MALE_BUILD_DIR}/plate_greaves.png'),
            (f'{MALE_BUILD_DIR}/plate_gauntlets.txt', f'{MALE_BUILD_DIR}/plate_gauntlets.png'),
            (f'{MALE_BUILD_DIR}/default_chest.txt', f'{MALE_BUILD_DIR}/default_chest.png'),
            (f'{MALE_BUILD_DIR}/plate_cuirass.txt', f'{MALE_BUILD_DIR}/plate_cuirass.png'),
            (f'{MALE_BUILD_DIR}/plate_helm.txt', f'{MALE_BUILD_DIR}/plate_helm.png'),
            (f'{MALE_BUILD_DIR}/greatsword.txt', f'{MALE_BUILD_DIR}/greatsword.png'),
        ],
        'actions': ['idle', 'walk', 'attack', 'die'],
    },
    {
        'id': 'hero_female_peasant',
        'prefix': 'hfp',
        'name': 'Heroína Camponesa 3D (Classe Inicial)',
        'class_title': 'Camponesa Inicial Feminina',
        'gender': 'female',
        'tier': 0,
        'desc': 'Protagonista feminina inicial para modos de jogo com heroína ou DMODs customizados. Vestimenta rústica e adaga.',
        'tags': ['jogador', 'heroi', 'female', 'camponesa', '3d', 'alta_fidelidade', 'classe_inicial', 'flare_rpg', 'flare_hero'],
        'layers': [
            (f'{FEMALE_BUILD_DIR}/female_default_feet.txt', f'{FEMALE_BUILD_DIR}/female_default_feet.png'),
            (f'{FEMALE_BUILD_DIR}/female_default_hands.txt', f'{FEMALE_BUILD_DIR}/female_default_hands.png'),
            (f'{FEMALE_BUILD_DIR}/female_default_chest.txt', f'{FEMALE_BUILD_DIR}/female_default_chest.png'),
            (f'{FEMALE_BUILD_DIR}/female_cloth_pants.txt', f'{FEMALE_BUILD_DIR}/female_cloth_pants.png'),
            (f'{FEMALE_BUILD_DIR}/female_cloth_shirt.txt', f'{FEMALE_BUILD_DIR}/female_cloth_shirt.png'),
            (f'{FEMALE_BUILD_DIR}/female_head_long.txt', f'{FEMALE_BUILD_DIR}/female_head_long.png'),
            (f'{FEMALE_BUILD_DIR}/female_dagger.txt', f'{FEMALE_BUILD_DIR}/female_dagger.png'),
        ],
        'actions': ['idle', 'walk', 'attack', 'die'],
    },
    {
        'id': 'hero_female_mage',
        'prefix': 'hfm',
        'name': 'Heroína Feiticeira / Maga Arcana',
        'class_title': 'Maga / Conjuradora Arcana',
        'gender': 'female',
        'tier': 2,
        'desc': 'Mestra das artes mágicas com túnica e saia místicas talhadas e cajado de conjuração com joia de esmeralda.',
        'tags': ['jogador', 'heroi', 'female', 'maga', 'feiticeira', 'magia', 'cajado', '3d', 'alta_fidelidade', 'flare_rpg', 'flare_hero'],
        'layers': [
            (f'{FEMALE_BUILD_DIR}/female_default_feet.txt', f'{FEMALE_BUILD_DIR}/female_default_feet.png'),
            (f'{FEMALE_BUILD_DIR}/female_default_hands.txt', f'{FEMALE_BUILD_DIR}/female_default_hands.png'),
            (f'{FEMALE_BUILD_DIR}/female_default_chest.txt', f'{FEMALE_BUILD_DIR}/female_default_chest.png'),
            (f'{FEMALE_BUILD_DIR}/female_mage_skirt.txt', f'{FEMALE_BUILD_DIR}/female_mage_skirt.png'),
            (f'{FEMALE_BUILD_DIR}/female_mage_vest.txt', f'{FEMALE_BUILD_DIR}/female_mage_vest.png'),
            (f'{FEMALE_BUILD_DIR}/female_head_long.txt', f'{FEMALE_BUILD_DIR}/female_head_long.png'),
            (f'{FEMALE_BUILD_DIR}/female_staff.txt', f'{FEMALE_BUILD_DIR}/female_staff.png'),
        ],
        'actions': ['idle', 'walk', 'attack', 'die', 'cast'],
    },
]

FRAME_CACHE = {}

def get_frame(txt_path, action, frame_idx, dir_idx):
    cache_key = (txt_path, action, frame_idx, dir_idx)
    if cache_key in FRAME_CACHE:
        return FRAME_CACHE[cache_key]
    
    if not os.path.exists(txt_path):
        FRAME_CACHE[cache_key] = None
        return None
        
    with open(txt_path) as f:
        content = f.read()
        
    m = re.search(r'\[' + action + r'\](.*?)(\n\[|$)', content, re.DOTALL)
    if not m:
        FRAME_CACHE[cache_key] = None
        return None
    sec = m.group(1)
    
    pat = rf'frame={frame_idx},{dir_idx},(\d+),(\d+),(\d+),(\d+),(-?\d+),(-?\d+)'
    mf = re.search(pat, sec)
    if not mf:
        FRAME_CACHE[cache_key] = None
        return None
    res = [int(x) for x in mf.groups()]
    FRAME_CACHE[cache_key] = res
    return res

def render_single_frame(task):
    hero_id, action_key, dink_dir, flare_dir, frame_idx, out_png, layers = task
    
    canvas_w, canvas_h = 240, 240
    ox_base, oy_base = 120, 180
    
    cmd = ['magick', '-size', f'{canvas_w}x{canvas_h}', 'xc:none', '-colorspace', 'sRGB', '-define', 'png:color-type=6']
    
    flare_act_name = ACTIONS[action_key][0]
    
    has_layers = False
    for txt_path, png_path in layers:
        coords = get_frame(txt_path, flare_act_name, frame_idx, flare_dir)
        if not coords:
            continue
        has_layers = True
        x, y, w, h, ox, oy = coords
        dest_x = ox_base - ox
        dest_y = oy_base - oy
        cmd += ['(', png_path, '-crop', f'{w}x{h}+{x}+{y}', '+repage', ')', '-geometry', f'+{dest_x}+{dest_y}', '-composite']
        
    if not has_layers:
        return None
        
    cmd += [out_png]
    subprocess.run(cmd, check=True)
    return out_png

def main():
    print("=== Iniciando Ingestão de Heróis e Classes Flare RPG ===")
    os.makedirs(WEB_ASSETS_DIR, exist_ok=True)
    
    render_tasks = []
    hero_json_entries = []
    visual_db_entries = []
    
    for hero in HERO_DEFINITIONS:
        hero_id = hero['id']
        prefix = hero['prefix']
        hero_dir = os.path.join(WEB_ASSETS_DIR, hero_id)
        os.makedirs(hero_dir, exist_ok=True)
        
        print(f"Preparando tarefas para: {hero['name']}...")
        
        grouped_actions = {}
        total_hero_frames = 0
        preview_rel_path = None
        
        for action_key in hero['actions']:
            flare_act, act_code, act_label, act_icon, frame_count, fps = ACTIONS[action_key]
            act_dir = os.path.join(hero_dir, action_key)
            os.makedirs(act_dir, exist_ok=True)
            
            action_directions = {}
            
            for dink_dir, (flare_dir, dir_name) in DINK_DIR_TO_FLARE.items():
                dir_frames = []
                for f_idx in range(frame_count):
                    frame_num_str = f"{f_idx+1:02d}"
                    out_filename = f"{prefix}-{act_code}{dink_dir}-{frame_num_str}.png"
                    out_path = os.path.join(act_dir, out_filename)
                    rel_web_path = os.path.relpath(out_path, BASE_DIR)
                    
                    render_tasks.append((
                        hero_id, action_key, dink_dir, flare_dir, f_idx, out_path, hero['layers']
                    ))
                    dir_frames.append(rel_web_path)
                    total_hero_frames += 1
                    
                    if action_key == 'idle' and dink_dir == '1' and f_idx == 0:
                        preview_rel_path = rel_web_path
                
                action_directions[dink_dir] = {
                    'dir_name': dir_name,
                    'frames': dir_frames
                }
                
                # Also create entry for visual_database.json
                v_entry_id = f"flare_{hero_id}_{action_key}_{prefix}-{act_code}{dink_dir}"
                visual_db_entries.append({
                    'id': v_entry_id,
                    'dmod_slug': 'flare',
                    'dmod_title': 'Acervo Flare RPG (Definitive Edition)',
                    'author': 'Clint Bellanger / Flare RPG Team',
                    'category': 'dink_heroes',
                    'name': f"{hero['name']} ({act_label} - {dir_name})",
                    'raw_name': f"{prefix}-{act_code}{dink_dir}",
                    'frame_count': frame_count,
                    'fps': fps,
                    'width': 240,
                    'height': 240,
                    'frames': dir_frames,
                    'preview': dir_frames[0],
                    'tags': hero['tags'] + [action_key],
                    'ini_info': None
                })
            
            grouped_actions[action_key] = {
                'key': action_key,
                'label': act_label,
                'icon': act_icon,
                'directions': action_directions
            }
            
        if not preview_rel_path:
            preview_rel_path = f"research/web_assets/flare/heroes/{hero_id}/idle/{prefix}-s1-01.png"
            
        hero_json_entries.append({
            'id': f"flare_{hero_id}",
            'name': hero['name'],
            'dmod_slug': 'flare',
            'dmod_title': 'Acervo Flare RPG (Definitive Edition)',
            'author': 'Clint Bellanger / Flare RPG Team',
            'category': 'dink_heroes',
            'tags': hero['tags'],
            'preview': preview_rel_path,
            'width': 240,
            'height': 240,
            'total_frames': total_hero_frames,
            'available_directions': ['1', '2', '3', '4', '6', '7', '8', '9'],
            'default_action': 'idle',
            'default_direction': '1',
            'actions': grouped_actions
        })

    print(f"Executando {len(render_tasks)} tarefas de renderização com multithreading...")
    
    # Run renders in parallel
    completed = 0
    with ThreadPoolExecutor(max_workers=8) as executor:
        for res in executor.map(render_single_frame, render_tasks):
            completed += 1
            if completed % 100 == 0 or completed == len(render_tasks):
                print(f"Renderizado: {completed}/{len(render_tasks)} quadros...")
                
    print("Renderização concluída com sucesso!")
    
    # Update grouped_visual_database.json
    print(f"Atualizando {GROUPED_DB_PATH}...")
    with open(GROUPED_DB_PATH, 'r', encoding='utf-8') as f:
        grouped_db = json.load(f)
        
    # Remove any existing flare_hero_* entries to avoid duplicates
    existing_ids = {h['id'] for h in hero_json_entries}
    grouped_db = [item for item in grouped_db if item.get('id') not in existing_ids]
    # Prepend new heroes to top of grouped DB so they show up prominently
    grouped_db = hero_json_entries + grouped_db
    
    with open(GROUPED_DB_PATH, 'w', encoding='utf-8') as f:
        json.dump(grouped_db, f, indent=2, ensure_ascii=False)
        
    print(f"Atualizando {VISUAL_DB_PATH}...")
    with open(VISUAL_DB_PATH, 'r', encoding='utf-8') as f:
        visual_db = json.load(f)
        
    v_existing_ids = {v['id'] for v in visual_db_entries}
    visual_db = [item for item in visual_db if item.get('id') not in v_existing_ids]
    visual_db = visual_db_entries + visual_db
    
    with open(VISUAL_DB_PATH, 'w', encoding='utf-8') as f:
        json.dump(visual_db, f, indent=2, ensure_ascii=False)
        
    print("Bancos de dados JSON atualizados com sucesso!")
    
    # Update asset_database.html
    update_html()
    print("=== Pipeline de Heróis Finalizado com Sucesso! ===")

def update_html():
    print(f"Injetando aba de heróis em {HTML_PATH}...")
    with open(HTML_PATH, 'r', encoding='utf-8') as f:
        html = f.read()
        
    # 1. Add hero pill if not present
    if 'data-cat="flare_heroes"' not in html:
        old_pill = '<div class="cat-pill active" data-cat="all">Todos os Assets (<span id="countAll">0</span>)</div>'
        new_pill = old_pill + '\n                    <div class="cat-pill" data-cat="flare_heroes" style="background: rgba(168, 85, 247, 0.2); border-color: #a855f7; color: #e9d5ff; font-weight: bold;">🛡️ Heróis & Classes 3D (<span id="countFlareHeroes">0</span>)</div>'
        html = html.replace(old_pill, new_pill)
        
    # 2. Add countFlareHeroes in counts object
    if 'flare_heroes: 0,' not in html:
        html = html.replace('flare: 0,', 'flare: 0,\n                flare_heroes: 0,')
        
    # 3. Add increment in counts
    if 'counts.flare_heroes++;' not in html:
        target = "if (item.category === 'scenery') {"
        replacement = "if (item.tags && item.tags.includes('flare_hero')) {\n                        counts.flare_heroes++;\n                    } else if (item.category === 'scenery') {"
        html = html.replace(target, replacement)
        
    # 4. Update count in UI
    if "document.getElementById('countFlareHeroes')" not in html:
        target = "document.getElementById('countFlare').textContent = counts.flare;"
        replacement = "document.getElementById('countFlare').textContent = counts.flare;\n            const chEl = document.getElementById('countFlareHeroes'); if (chEl) chEl.textContent = counts.flare_heroes;"
        html = html.replace(target, replacement)
        
    # 5. Filter logic
    if "currentCategory === 'flare_heroes'" not in html:
        target = "if (currentCategory === 'flare') {"
        replacement = "if (currentCategory === 'flare_heroes') {\n                    if (!isFlare || !(item.tags || []).includes('flare_hero')) return false;\n                } else if (currentCategory === 'flare') {"
        html = html.replace(target, replacement)
        
    with open(HTML_PATH, 'w', encoding='utf-8') as f:
        f.write(html)
    print("asset_database.html atualizado!")

if __name__ == '__main__':
    main()
