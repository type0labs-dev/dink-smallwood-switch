#!/usr/bin/env python3
"""
group_visual_database.py

Groups the 17,988 raw directional sequences in research/visual_database.json
into unified Creature / Character / Asset entities with multi-directional
support and action switching (Walk, Attack, Die, Idle).

Outputs:
  - research/grouped_visual_database.json
  - asset_database.html (with interactive 8-way D-pad & action selectors)
"""

import os
import re
import sys
import json
from collections import defaultdict

BASE_DIR = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", ".."))
IN_JSON_PATH = os.path.join(BASE_DIR, "research", "visual_database.json")
OUT_JSON_PATH = os.path.join(BASE_DIR, "research", "grouped_visual_database.json")
OUT_HTML_PATH = os.path.join(BASE_DIR, "asset_database.html")

DIR_MAP = {
    '1': 'Sudoeste (↙)',
    '2': 'Sul (⬇)',
    '3': 'Sudeste (↘)',
    '4': 'Oeste (⬅)',
    '6': 'Leste (➡)',
    '7': 'Noroeste (↖)',
    '8': 'Norte (⬆)',
    '9': 'Nordeste (↗)',
    'default': 'Padrão'
}

ACTION_LABELS = {
    'walk': ('Caminhar', '🚶'),
    'idle': ('Parado', '🧍'),
    'attack': ('Atacar', '⚔️'),
    'magic': ('Magia', '🔮'),
    'ranged': ('Disparo', '🏹'),
    'block': ('Bloqueio', '🛡️'),
    'hit': ('Ferido', '💥'),
    'die': ('Morte', '💀'),
    'spawn': ('Surgir', '🌱'),
    'default': ('Animação', '✨')
}

def clean_str(s):
    if not isinstance(s, str):
        return s
    return s.encode('utf-8', 'replace').decode('utf-8')

def parse_action_and_direction(raw, path, name):
    raw_l = raw.lower()
    path_l = path.lower()
    combined = f"{path_l}/{raw_l}"
    
    action = 'default'
    direction = 'default'
    creature_stem = raw
    
    # 1. Path-based action detection
    for act_kw in ['walk', 'attack', 'die', 'death', 'dead', 'hit', 'hurt', 'idle', 'stand', 'fly', 'push', 'jump', 'run', 'cast', 'magic', 'ranged', 'block', 'spawn']:
        if f'/{act_kw}' in path_l or path_l.endswith(f'/{act_kw}'):
            if act_kw in ('walk', 'run', 'fly'): action = 'walk'
            elif act_kw in ('attack', 'cast'): action = 'attack'
            elif act_kw in ('die', 'death', 'dead'): action = 'die'
            elif act_kw in ('hit', 'hurt'): action = 'hit'
            elif act_kw in ('idle', 'stand'): action = 'idle'
            elif act_kw == 'magic': action = 'magic'
            elif act_kw == 'ranged': action = 'ranged'
            elif act_kw == 'block': action = 'block'
            elif act_kw == 'spawn': action = 'spawn'
            break

    # 2. Filename-based action & direction detection (e.g. ds-w1, sp-a2, gob-w8, sk-m1, etc.)
    m = re.search(r'^(.*?)(?:[-_]?)([wWahdsfmrbp])([1-46-9])(?:[-_]?)(.*?)$', raw, re.IGNORECASE)
    if m:
        pfx = m.group(1).rstrip('-_')
        act_c = m.group(2).lower()
        direction = m.group(3)
        sfx = m.group(4).lstrip('-_')
        creature_stem = f"{pfx}_{sfx}".strip('_') if (pfx or sfx) else 'creature'
        if action == 'default':
            if act_c in ('w', 'f'): action = 'walk'
            elif act_c in ('s', 'i'): action = 'idle'
            elif act_c == 'a': action = 'attack'
            elif act_c == 'h': action = 'hit'
            elif act_c == 'd': action = 'die'
            elif act_c == 'm': action = 'magic'
            elif act_c == 'r': action = 'ranged'
            elif act_c == 'b': action = 'block'
            elif act_c == 'p': action = 'spawn'
    else:
        # Ending in digit 1-9
        m2 = re.search(r'^(.*?)(?:[-_]?)([1-46-9])$', raw)
        if m2:
            creature_stem = m2.group(1).rstrip('-_')
            direction = m2.group(2)
            if action == 'default':
                if any(k in combined for k in ['walk', 'run', 'move', 'andando']): action = 'walk'
                elif any(k in combined for k in ['att', 'hit', 'slash', 'atacando']): action = 'attack'
                elif any(k in combined for k in ['die', 'death', 'dead', 'morte']): action = 'die'
                elif any(k in combined for k in ['idle', 'stand', 'parado']): action = 'idle'
                else: action = 'walk'
        else:
            # Compass directions
            m3 = re.search(r'^(.*?)(?:[-_]?)(s|n|e|w|sw|se|nw|ne)$', raw, re.IGNORECASE)
            if m3:
                compass_map = {'s':'2','n':'8','e':'6','w':'4','sw':'1','se':'3','nw':'7','ne':'9'}
                creature_stem = m3.group(1).rstrip('-_')
                direction = compass_map.get(m3.group(2).lower(), 'default')
                if action == 'default': action = 'walk'
            else:
                creature_stem = raw
                if action == 'default':
                    if any(k in combined for k in ['walk', 'run', 'move']): action = 'walk'
                    elif any(k in combined for k in ['att', 'hit', 'slash']): action = 'attack'
                    elif any(k in combined for k in ['die', 'death', 'dead']): action = 'die'
                    elif any(k in combined for k in ['idle', 'stand']): action = 'idle'

    return creature_stem, action, direction

def strip_action_folder(path):
    parts = path.split('/')
    if parts and parts[-1].lower() in ('walk', 'attack', 'att', 'die', 'death', 'dead', 'hit', 'hurt', 'idle', 'stand', 'fly', 'push', 'jump', 'run', 'magic', 'ranged', 'block', 'spawn', 'cast'):
        return '/'.join(parts[:-1])
    return path

def build_grouped_database():
    print("Loading raw visual database...")
    with open(IN_JSON_PATH, 'r', encoding='utf-8', errors='replace') as f:
        raw_db = json.load(f)

    print(f"Loaded {len(raw_db)} raw sequences. Grouping by creature / entity...")
    entities = {}

    for item in raw_db:
        slug = item['dmod_slug']
        raw = item['raw_name']
        orig_path = os.path.dirname(item['preview'])
        parent_path = strip_action_folder(orig_path)
        name = item['name']
        cat = item['category']

        stem, act, dir_code = parse_action_and_direction(raw, orig_path, name)
        
        # Entity identifier
        if slug == 'flare':
            folder_creature = parent_path.split('/')[-1]
            ent_id = f"flare_{folder_creature}".lower()
        else:
            ent_id = f"{slug}_{parent_path}_{stem}".replace('/', '_').replace('\\', '_').replace(' ', '_').lower()
        
        if ent_id not in entities:
            # Clean name from direction / action labels
            clean_title = re.sub(r'\s*\((Caminhando|Atacando|Morte|Parado|Animação|Sul|Norte|Leste|Oeste|Direção.*)\)', '', name).strip()
            if slug == 'flare':
                flare_names = {
                    'skeleton': 'Esqueleto Guerreiro (Flare 3D)',
                    'skeleton_weak': 'Esqueleto Frágil (Flare 3D)',
                    'skeleton_archer': 'Esqueleto Arqueiro (Flare 3D)',
                    'skeleton_mage': 'Esqueleto Necromante (Flare 3D)',
                    'skeleton_knight_boss': 'Lorde Cavaleiro da Morte (Flare 3D)',
                    'skeleton_mage_boss': 'Lorde Lich Necromante (Flare 3D)',
                    'skeleton_mage_fire': 'Lich Piromante Infernal (Flare 3D)',
                    'skeleton_mage_ice': 'Lich Criomante Glacial (Flare 3D)',
                    'skeleton_mage_high_boss': 'Arquilich Ancião Soberano (Flare 3D)',
                    'antlion': 'Aranha Gigante das Cavernas (Flare 3D)',
                    'antlion_small': 'Aranha Filhote do Enxame (Flare 3D)',
                    'antlion_armored': 'Aranha Blindada de Aço (Flare 3D)',
                    'antlion_fossilized': 'Aranha Fóssil de Pedra (Flare 3D)',
                    'fire_ant': 'Formiga de Fogo Flamejante (Flare 3D)',
                    'ice_ant': 'Formiga de Gelo Cristalina (Flare 3D)',
                    'goblin': 'Goblin Saqueador (Flare 3D)',
                    'goblin_runner': 'Goblin Rastreador Ágil (Flare 3D)',
                    'goblin_elite': 'Goblin Guerreiro de Elite (Flare 3D)',
                    'goblin_elite_runner': 'Goblin Assassino das Sombras (Flare 3D)',
                    'goblin_minecart': 'Goblin Demolidor do Carrinho (Flare 3D)',
                    'hobgoblin': 'Hobgoblin Brutal (Flare 3D)',
                    'hobgoblin_archer': 'Hobgoblin Franco-Atirador (Flare 3D)',
                    'minotaur': 'Minotauro Brutal (Flare 3D)',
                    'boulder': 'Golem de Pedra Viva (Flare 3D)',
                    'wyvern': 'Wyvern Alado (Flare 3D)',
                    'wyvern_air': 'Wyvern das Tempestades (Flare 3D)',
                    'wyvern_fire': 'Wyvern Vulcânico Infernal (Flare 3D)',
                    'wyvern_water': 'Wyvern Glacial das Profundezas (Flare 3D)',
                    'wyvern_air_boss': 'Rei Dragão Tempestuoso Soberano (Flare 3D)',
                    'zombie': 'Zumbi Putrefato (Flare 3D)',
                    'frozen_zombie': 'Zumbi Congelado (Flare 3D)',
                    'zombie_dark': 'Zumbi das Sombras (Flare 3D)',
                    'zombie_ghost': 'Espectro / Alma Penada (Flare 3D)',
                    'cursed_grave': 'Tumba Amaldiçoada (Flare 3D)',
                    'cursed_grave_fire': 'Tumba das Chamas Eternas (Flare 3D)',
                    'cursed_grave_ice': 'Tumba do Inverno Eterno (Flare 3D)',
                    'knight': 'Cavaleiro Nobre Real (Flare 3D)',
                    'peasant_man1': 'Camponês Trabalhador (Flare 3D)',
                    'peasant_man2': 'Fazendeiro da Vila (Flare 3D)',
                    'peasant_woman1': 'Aldeã Camponesa (Flare 3D)',
                    'peasant_woman2': 'Matrona da Vila (Flare 3D)',
                    'guild_man': 'Mestre da Guilda / Alquimista (Flare 3D)',
                    'wandering_trader': 'Mercador da Caravana (Flare 3D)',
                    'peddler_goblin': 'Goblin Mascate Pacífico (Flare 3D)',
                    'return_obelisk1': 'Monólito Mágico de Retorno (Flare 3D)',
                }
                folder_creature = parent_path.split('/')[-1]
                clean_title = flare_names.get(folder_creature, f"{folder_creature.capitalize()} (Flare 3D)")
                if folder_creature in ['knight', 'peasant_man1', 'peasant_man2', 'peasant_woman1', 'peasant_woman2', 'guild_man', 'wandering_trader', 'peddler_goblin']:
                    cat = 'npcs'
                elif folder_creature in ['return_obelisk1', 'cursed_grave', 'cursed_grave_fire', 'cursed_grave_ice']:
                    cat = 'scenery'
                else:
                    cat = 'monsters'
            elif not clean_title or clean_title == 'Asset:':
                clean_title = stem.replace('_', ' ').replace('-', ' ').title()
                
            entities[ent_id] = {
                'id': clean_str(ent_id),
                'name': clean_str(clean_title),
                'dmod_slug': clean_str(slug),
                'dmod_title': clean_str(item['dmod_title']),
                'author': clean_str(item['author']),
                'category': cat,
                'tags': set(item.get('tags', [])),
                'actions': defaultdict(dict),
                'preview': item['preview'],
                'width': item.get('width', 64),
                'height': item.get('height', 64)
            }

        ent = entities[ent_id]
        ent['tags'].update(item.get('tags', []))
        
        ent['actions'][act][dir_code] = {
            'frames': item['frames'],
            'fps': item.get('fps', 10),
            'frame_count': item.get('frame_count', len(item['frames'])),
            'width': item.get('width', 64),
            'height': item.get('height', 64),
            'ini_info': item.get('ini_info'),
            'preview': item.get('preview')
        }
        
        # Best preview: South (2) or East (6) or walk
        if dir_code == '2' or (dir_code == '6' and '2' not in ent['actions'][act]) or (dir_code == 'default' and act == 'walk'):
            ent['preview'] = item['preview']

    print(f"Grouped into {len(entities)} unique creatures/entities!")

    # Format into final serializable structure
    output_entities = []
    for ent_id, ent in entities.items():
        actions_dict = {}
        all_dirs = set()
        total_frames = 0
        
        # Action ordering preference
        act_order = ['walk', 'idle', 'attack', 'magic', 'ranged', 'block', 'hit', 'die', 'spawn', 'default']
        ordered_acts = sorted(ent['actions'].keys(), key=lambda a: act_order.index(a) if a in act_order else 99)
        
        for act in ordered_acts:
            dirs = ent['actions'][act]
            act_label, act_icon = ACTION_LABELS.get(act, (act.capitalize(), '✨'))
            
            dir_dict = {}
            for d, data in dirs.items():
                all_dirs.add(d)
                total_frames += data['frame_count']
                dir_dict[d] = {
                    'dir_name': DIR_MAP.get(d, 'Padrão'),
                    'frames': data['frames'],
                    'fps': data['fps'],
                    'frame_count': data['frame_count'],
                    'width': data['width'],
                    'height': data['height'],
                    'ini_info': data['ini_info'],
                    'preview': data['preview']
                }
            
            actions_dict[act] = {
                'key': act,
                'label': act_label,
                'icon': act_icon,
                'directions': dir_dict
            }

        # Default action & direction
        default_act = ordered_acts[0] if ordered_acts else 'default'
        act_dirs = actions_dict.get(default_act, {}).get('directions', {})
        if '2' in act_dirs:
            default_dir = '2'
        elif '6' in act_dirs:
            default_dir = '6'
        elif act_dirs:
            default_dir = list(act_dirs.keys())[0]
        else:
            default_dir = 'default'

        sorted_dirs = sorted([d for d in all_dirs if d != 'default'], key=lambda x: int(x) if x.isdigit() else 99)
        if 'default' in all_dirs:
            sorted_dirs.append('default')

        output_entities.append({
            'id': ent['id'],
            'name': ent['name'],
            'dmod_slug': ent['dmod_slug'],
            'dmod_title': ent['dmod_title'],
            'author': ent['author'],
            'category': ent['category'],
            'tags': sorted(list(ent['tags'])),
            'preview': ent['preview'],
            'width': ent['width'],
            'height': ent['height'],
            'total_frames': total_frames,
            'available_directions': sorted_dirs,
            'default_action': default_act,
            'default_direction': default_dir,
            'actions': actions_dict
        })

    # Sort entities by category, then by name
    cat_order = ['monsters', 'dink_heroes', 'npcs', 'items_weapons', 'magic_fx', 'scenery', 'tiles', 'other']
    output_entities.sort(key=lambda x: (cat_order.index(x['category']) if x['category'] in cat_order else 99, x['name']))

    print(f"Writing {OUT_JSON_PATH}...")
    with open(OUT_JSON_PATH, 'w', encoding='utf-8') as f:
        json.dump(output_entities, f, ensure_ascii=False, indent=2)

    print("Generating updated asset_database.html with interactive D-pad...")
    generate_html(output_entities)
    print("Done!")

def generate_html(entities):
    # Generates the responsive web application with D-pad & action controls
    html = """<!DOCTYPE html>
<html lang="pt-BR">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Dink Smallwood Complete Edition — Catálogo de Criaturas & Assets</title>
    <link rel="preconnect" href="https://fonts.googleapis.com">
    <link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
    <link href="https://fonts.googleapis.com/css2?family=Cinzel:wght@600;700;800;900&family=Inter:wght@400;500;600;700&display=swap" rel="stylesheet">
    <style>
        :root {
            --bg-base: #0a0c10;
            --bg-card: #131720;
            --bg-card-hover: #1c2230;
            --bg-player: #08090d;
            --border-color: #262f40;
            --border-gold: #c29947;
            --accent-gold: #e5b95c;
            --accent-green: #2ecc71;
            --accent-blue: #3498db;
            --accent-purple: #9b59b6;
            --accent-red: #e74c3c;
            --text-main: #e6edf3;
            --text-muted: #8b949e;
        }
        * {
            box-sizing: border-box;
            margin: 0;
            padding: 0;
        }
        body {
            background: var(--bg-base);
            color: var(--text-main);
            font-family: 'Inter', sans-serif;
            min-height: 100vh;
            display: flex;
            flex-direction: column;
        }
        header {
            background: linear-gradient(180deg, #181d28 0%, #0e1118 100%);
            border-bottom: 2px solid var(--border-gold);
            padding: 1.1rem 2rem;
            display: flex;
            justify-content: space-between;
            align-items: center;
            position: sticky;
            top: 0;
            z-index: 100;
            box-shadow: 0 4px 20px rgba(0,0,0,0.5);
        }
        .header-title {
            display: flex;
            align-items: center;
            gap: 1rem;
        }
        .header-title h1 {
            font-family: 'Cinzel', serif;
            font-size: 1.45rem;
            color: var(--accent-gold);
            letter-spacing: 1px;
            text-shadow: 0 0 10px rgba(229,185,92,0.3);
        }
        .header-badge {
            background: rgba(194, 153, 71, 0.15);
            border: 1px solid var(--border-gold);
            color: var(--accent-gold);
            padding: 0.25rem 0.6rem;
            border-radius: 999px;
            font-size: 0.8rem;
            font-weight: 600;
        }
        .header-links {
            display: flex;
            align-items: center;
            gap: 1rem;
        }
        .header-btn {
            background: #1e2638;
            border: 1px solid var(--border-color);
            color: var(--text-main);
            padding: 0.5rem 1rem;
            border-radius: 6px;
            font-size: 0.85rem;
            font-weight: 600;
            text-decoration: none;
            cursor: pointer;
            display: flex;
            align-items: center;
            gap: 0.5rem;
            transition: all 0.2s;
        }
        .header-btn:hover {
            background: var(--border-gold);
            color: #0a0c10;
        }
        .cart-badge {
            background: var(--accent-red);
            color: #fff;
            padding: 0.1rem 0.45rem;
            border-radius: 999px;
            font-size: 0.75rem;
            margin-left: 0.3rem;
        }

        /* Workspace Layout */
        .workspace {
            display: flex;
            flex: 1;
            height: calc(100vh - 72px);
            overflow: hidden;
            position: relative;
        }

        .loading-overlay {
            position: absolute;
            inset: 0;
            background: rgba(10, 12, 16, 0.95);
            z-index: 50;
            display: flex;
            flex-direction: column;
            align-items: center;
            justify-content: center;
            gap: 1.25rem;
        }
        .loading-spinner {
            width: 50px;
            height: 50px;
            border: 4px solid #202738;
            border-top-color: var(--accent-gold);
            border-radius: 50%;
            animation: spin 0.8s linear infinite;
        }
        @keyframes spin {
            to { transform: rotate(360deg); }
        }
        .loading-text {
            font-family: 'Cinzel', serif;
            font-size: 1.15rem;
            color: var(--accent-gold);
        }

        /* Catalog Pane */
        .catalog-pane {
            flex: 1;
            display: flex;
            flex-direction: column;
            border-right: 1px solid var(--border-color);
            overflow: hidden;
        }

        .filter-toolbar {
            background: #10141d;
            border-bottom: 1px solid var(--border-color);
            padding: 1rem 1.5rem;
            display: flex;
            flex-direction: column;
            gap: 0.8rem;
        }

        .search-row {
            display: flex;
            gap: 0.75rem;
        }
        .search-input {
            flex: 1;
            background: #171d2a;
            border: 1px solid var(--border-color);
            border-radius: 6px;
            padding: 0.6rem 1rem;
            color: #fff;
            font-size: 0.9rem;
            outline: none;
            transition: border-color 0.2s;
        }
        .search-input:focus {
            border-color: var(--border-gold);
        }
        .select-filter {
            background: #171d2a;
            border: 1px solid var(--border-color);
            border-radius: 6px;
            padding: 0.6rem 1rem;
            color: #fff;
            font-size: 0.9rem;
            outline: none;
            cursor: pointer;
            max-width: 280px;
        }

        .category-pills {
            display: flex;
            gap: 0.5rem;
            overflow-x: auto;
            padding-bottom: 0.2rem;
        }
        .cat-pill {
            background: #182030;
            border: 1px solid var(--border-color);
            color: var(--text-muted);
            padding: 0.35rem 0.8rem;
            border-radius: 999px;
            font-size: 0.8rem;
            font-weight: 600;
            cursor: pointer;
            white-space: nowrap;
            transition: all 0.2s;
            user-select: none;
        }
        .cat-pill:hover {
            color: #fff;
            border-color: #485b7f;
        }
        .cat-pill.active {
            background: rgba(229, 185, 92, 0.2);
            border-color: var(--accent-gold);
            color: var(--accent-gold);
        }

        .assets-grid-container {
            flex: 1;
            overflow-y: auto;
            padding: 1.5rem;
            display: flex;
            flex-direction: column;
        }
        .assets-grid {
            display: grid;
            grid-template-columns: repeat(auto-fill, minmax(190px, 1fr));
            gap: 1rem;
        }
        .asset-card {
            background: var(--bg-card);
            border: 1px solid var(--border-color);
            border-radius: 8px;
            padding: 0.85rem;
            display: flex;
            flex-direction: column;
            align-items: center;
            cursor: pointer;
            transition: all 0.2s;
            position: relative;
        }
        .asset-card:hover {
            background: var(--bg-card-hover);
            border-color: var(--border-gold);
            transform: translateY(-2px);
            box-shadow: 0 6px 15px rgba(0,0,0,0.4);
        }
        .asset-card.selected {
            border-color: var(--accent-gold);
            box-shadow: 0 0 14px rgba(229,185,92,0.45);
        }
        .asset-thumb-box {
            width: 100%;
            height: 125px;
            background: #080a0f;
            border: 1px solid #1a202c;
            border-radius: 6px;
            display: flex;
            align-items: center;
            justify-content: center;
            overflow: hidden;
            margin-bottom: 0.6rem;
            position: relative;
        }
        .asset-thumb-img {
            max-width: 90%;
            max-height: 90%;
            object-fit: contain;
            image-rendering: pixelated;
        }
        .dir-badge {
            position: absolute;
            bottom: 5px;
            right: 5px;
            background: rgba(0,0,0,0.85);
            border: 1px solid #444;
            color: var(--accent-gold);
            padding: 0.1rem 0.4rem;
            border-radius: 4px;
            font-size: 0.68rem;
            font-weight: 700;
        }
        .actions-badge {
            position: absolute;
            top: 6px;
            left: 6px;
            background: rgba(0,0,0,0.8);
            border: 1px solid #333;
            color: #79c0ff;
            padding: 0.1rem 0.35rem;
            border-radius: 4px;
            font-size: 0.65rem;
            font-weight: 600;
        }
        .asset-title {
            font-size: 0.88rem;
            font-weight: 600;
            color: #fff;
            text-align: center;
            white-space: nowrap;
            overflow: hidden;
            text-overflow: ellipsis;
            width: 100%;
            margin-bottom: 0.2rem;
        }
        .asset-dmod {
            font-size: 0.72rem;
            color: var(--text-muted);
            text-align: center;
            white-space: nowrap;
            overflow: hidden;
            text-overflow: ellipsis;
            width: 100%;
        }
        .card-select-star {
            position: absolute;
            top: 6px;
            right: 6px;
            background: rgba(0,0,0,0.65);
            border: 1px solid #444;
            border-radius: 4px;
            padding: 2px 6px;
            font-size: 0.8rem;
            color: #888;
            cursor: pointer;
            transition: all 0.2s;
            z-index: 2;
        }
        .card-select-star:hover, .card-select-star.active {
            color: var(--accent-gold);
            border-color: var(--accent-gold);
            background: rgba(229,185,92,0.25);
        }

        .load-more-btn {
            margin: 1.5rem auto 0;
            background: #182030;
            border: 1px solid var(--border-color);
            color: #fff;
            padding: 0.75rem 2rem;
            border-radius: 6px;
            font-size: 0.9rem;
            font-weight: 600;
            cursor: pointer;
            transition: all 0.2s;
        }
        .load-more-btn:hover {
            background: var(--border-gold);
            color: #000;
        }

        /* Right Side: Player & D-Pad Controls */
        .player-pane {
            width: 460px;
            background: #11151e;
            display: flex;
            flex-direction: column;
            overflow-y: auto;
        }
        .player-header {
            padding: 1rem 1.25rem;
            border-bottom: 1px solid var(--border-color);
            background: #151a26;
        }
        .player-header h2 {
            font-family: 'Cinzel', serif;
            font-size: 1.18rem;
            color: var(--accent-gold);
            margin-bottom: 0.2rem;
            white-space: nowrap;
            overflow: hidden;
            text-overflow: ellipsis;
        }
        .player-header p {
            font-size: 0.8rem;
            color: var(--text-muted);
            white-space: nowrap;
            overflow: hidden;
            text-overflow: ellipsis;
        }

        /* Action selector pills */
        .action-selector-section {
            padding: 0.8rem 1.25rem;
            border-bottom: 1px solid var(--border-color);
            background: #131822;
            display: flex;
            align-items: center;
            gap: 0.5rem;
            overflow-x: auto;
        }
        .action-btn {
            background: #1a2233;
            border: 1px solid var(--border-color);
            color: var(--text-main);
            padding: 0.35rem 0.75rem;
            border-radius: 6px;
            font-size: 0.8rem;
            font-weight: 600;
            cursor: pointer;
            white-space: nowrap;
            transition: all 0.2s;
            display: flex;
            align-items: center;
            gap: 0.35rem;
        }
        .action-btn:hover {
            border-color: var(--border-gold);
        }
        .action-btn.active {
            background: rgba(229, 185, 92, 0.2);
            border-color: var(--accent-gold);
            color: var(--accent-gold);
        }

        .stage-container {
            padding: 1.25rem;
            display: flex;
            flex-direction: column;
            align-items: center;
            background: var(--bg-player);
            border-bottom: 1px solid var(--border-color);
        }
        .stage-canvas-box {
            width: 320px;
            height: 240px;
            border: 2px solid var(--border-color);
            border-radius: 8px;
            display: flex;
            align-items: center;
            justify-content: center;
            position: relative;
            box-shadow: inset 0 0 20px rgba(0,0,0,0.8);
            transition: background 0.3s;
            overflow: hidden;
        }
        .stage-canvas-box.bg-black { background: #000; }
        .stage-canvas-box.bg-grid {
            background-color: #1a1e27;
            background-image: linear-gradient(45deg, #131720 25%, transparent 25%),
                              linear-gradient(-45deg, #131720 25%, transparent 25%),
                              linear-gradient(45deg, transparent 75%, #131720 75%),
                              linear-gradient(-45deg, transparent 75%, #131720 75%);
            background-size: 20px 20px;
            background-position: 0 0, 0 10px, 10px -10px, -10px 0px;
        }
        .stage-canvas-box.bg-grass { background: #23581c; }
        .stage-canvas-box.bg-dirt { background: #4a341f; }

        .player-sprite {
            max-width: 90%;
            max-height: 90%;
            image-rendering: pixelated;
            transform-origin: center center;
            transition: transform 0.1s ease;
        }

        /* Directional D-Pad Section */
        .dpad-section {
            padding: 1rem 1.25rem;
            border-bottom: 1px solid var(--border-color);
            background: #141924;
            display: flex;
            flex-direction: column;
            align-items: center;
            gap: 0.6rem;
        }
        .dpad-title {
            font-size: 0.75rem;
            text-transform: uppercase;
            letter-spacing: 1px;
            color: var(--accent-gold);
            font-weight: 700;
            display: flex;
            align-items: center;
            gap: 0.5rem;
        }
        .dpad-grid {
            display: grid;
            grid-template-columns: repeat(3, 44px);
            grid-template-rows: repeat(3, 44px);
            gap: 5px;
        }
        .dpad-btn {
            background: #1a2233;
            border: 1px solid #2d3748;
            border-radius: 6px;
            color: #e6edf3;
            font-size: 1.1rem;
            cursor: pointer;
            display: flex;
            align-items: center;
            justify-content: center;
            transition: all 0.15s;
            user-select: none;
        }
        .dpad-btn:hover:not(:disabled) {
            background: #25334d;
            border-color: var(--accent-gold);
            color: var(--accent-gold);
            transform: scale(1.05);
        }
        .dpad-btn.active {
            background: var(--accent-gold);
            border-color: #fff;
            color: #000;
            box-shadow: 0 0 10px rgba(229, 185, 92, 0.6);
            font-weight: 800;
        }
        .dpad-btn:disabled {
            opacity: 0.2;
            cursor: not-allowed;
            border-color: #222;
        }
        .dpad-center {
            background: #10141d;
            border: 1px dashed #333;
            border-radius: 6px;
            color: var(--text-muted);
            font-size: 0.75rem;
            display: flex;
            align-items: center;
            justify-content: center;
        }
        .dpad-hint {
            font-size: 0.72rem;
            color: var(--text-muted);
            text-align: center;
        }

        /* Playback Controls */
        .player-controls {
            width: 100%;
            margin-top: 1rem;
            display: flex;
            flex-direction: column;
            gap: 0.75rem;
        }
        .controls-row {
            display: flex;
            justify-content: center;
            align-items: center;
            gap: 0.5rem;
        }
        .ctrl-btn {
            background: #1e2638;
            border: 1px solid var(--border-color);
            color: #fff;
            padding: 0.4rem 0.8rem;
            border-radius: 6px;
            font-size: 0.85rem;
            cursor: pointer;
            transition: all 0.2s;
        }
        .ctrl-btn:hover {
            background: var(--border-gold);
            color: #000;
        }
        .ctrl-btn.active {
            background: var(--accent-gold);
            color: #000;
            border-color: var(--accent-gold);
        }

        .slider-row {
            display: flex;
            align-items: center;
            justify-content: space-between;
            font-size: 0.8rem;
            color: var(--text-muted);
            padding: 0 0.5rem;
        }
        .slider-row input[type="range"] {
            flex: 1;
            margin: 0 0.75rem;
            accent-color: var(--accent-gold);
        }

        /* Frame Strip */
        .frame-strip-section {
            padding: 1rem 1.25rem;
            border-bottom: 1px solid var(--border-color);
        }
        .frame-strip-label {
            font-size: 0.75rem;
            text-transform: uppercase;
            letter-spacing: 1px;
            color: var(--text-muted);
            margin-bottom: 0.5rem;
        }
        .frame-strip {
            display: flex;
            gap: 0.5rem;
            overflow-x: auto;
            padding-bottom: 0.5rem;
        }
        .frame-strip-thumb {
            width: 50px;
            height: 50px;
            background: #000;
            border: 1px solid var(--border-color);
            border-radius: 4px;
            display: flex;
            align-items: center;
            justify-content: center;
            cursor: pointer;
            flex-shrink: 0;
            transition: all 0.2s;
        }
        .frame-strip-thumb:hover {
            border-color: #fff;
        }
        .frame-strip-thumb.active {
            border-color: var(--accent-gold);
            box-shadow: 0 0 8px rgba(229,185,92,0.5);
        }
        .frame-strip-thumb img {
            max-width: 90%;
            max-height: 90%;
            image-rendering: pixelated;
        }

        /* Details */
        .details-section {
            padding: 1.25rem;
            display: flex;
            flex-direction: column;
            gap: 0.8rem;
            font-size: 0.85rem;
        }
        .detail-row {
            display: flex;
            justify-content: space-between;
            padding-bottom: 0.4rem;
            border-bottom: 1px solid #1a2233;
        }
        .detail-label {
            color: var(--text-muted);
        }
        .detail-val {
            color: #fff;
            font-weight: 500;
            text-align: right;
        }
        .ini-code-box {
            background: #080a0f;
            border: 1px solid #202738;
            border-radius: 6px;
            padding: 0.75rem;
            font-family: monospace;
            font-size: 0.75rem;
            color: #79c0ff;
            word-break: break-all;
        }
        .tags-box {
            display: flex;
            flex-wrap: wrap;
            gap: 0.35rem;
            margin-top: 0.3rem;
        }
        .tag-pill {
            background: rgba(52, 152, 219, 0.15);
            border: 1px solid rgba(52, 152, 219, 0.3);
            color: #58a6ff;
            padding: 0.15rem 0.45rem;
            border-radius: 4px;
            font-size: 0.7rem;
        }

        .action-btns {
            margin-top: 0.5rem;
            display: flex;
            flex-direction: column;
            gap: 0.5rem;
        }
        .btn-integrate {
            background: linear-gradient(180deg, #d4a037 0%, #a4761b 100%);
            border: 1px solid #e5b95c;
            color: #000;
            font-weight: 700;
            padding: 0.75rem;
            border-radius: 6px;
            cursor: pointer;
            font-size: 0.9rem;
            transition: all 0.2s;
            text-align: center;
        }
        .btn-integrate:hover {
            filter: brightness(1.15);
            transform: translateY(-1px);
        }

        /* Cart Drawer */
        .cart-modal {
            position: fixed;
            top: 0;
            right: -450px;
            width: 450px;
            height: 100vh;
            background: #11151e;
            border-left: 2px solid var(--border-gold);
            z-index: 200;
            box-shadow: -10px 0 30px rgba(0,0,0,0.8);
            transition: right 0.3s cubic-bezier(0.16, 1, 0.3, 1);
            display: flex;
            flex-direction: column;
        }
        .cart-modal.open {
            right: 0;
        }
        .cart-modal-header {
            padding: 1.25rem 1.5rem;
            border-bottom: 1px solid var(--border-color);
            display: flex;
            justify-content: space-between;
            align-items: center;
            background: #161c28;
        }
        .cart-modal-body {
            flex: 1;
            overflow-y: auto;
            padding: 1.25rem;
            display: flex;
            flex-direction: column;
            gap: 0.75rem;
        }
        .cart-item {
            background: #171d2a;
            border: 1px solid var(--border-color);
            border-radius: 6px;
            padding: 0.6rem 0.8rem;
            display: flex;
            align-items: center;
            gap: 0.8rem;
        }
        .cart-item-img {
            width: 40px;
            height: 40px;
            object-fit: contain;
            background: #000;
            border-radius: 4px;
            image-rendering: pixelated;
        }
        .cart-item-info {
            flex: 1;
            overflow: hidden;
        }
        .cart-item-title {
            font-size: 0.85rem;
            font-weight: 600;
            color: #fff;
            white-space: nowrap;
            overflow: hidden;
            text-overflow: ellipsis;
        }
        .cart-item-dmod {
            font-size: 0.75rem;
            color: var(--text-muted);
        }
        .cart-modal-footer {
            padding: 1.25rem;
            border-top: 1px solid var(--border-color);
            background: #161c28;
            display: flex;
            flex-direction: column;
            gap: 0.5rem;
        }
    </style>
</head>
<body>

    <header>
        <div class="header-title">
            <h1>Dink Smallwood Complete Edition</h1>
            <span class="header-badge">Catálogo de Criaturas & Sprites</span>
        </div>
        <div class="header-links">
            <a href="complete_edition.html" class="header-btn">🏛️ Voltar ao Dashboard</a>
            <button class="header-btn" id="btnOpenCart">
                ⭐ Selecionados <span class="cart-badge" id="cartCount">0</span>
            </button>
        </div>
    </header>

    <div class="workspace">
        <div class="loading-overlay" id="loadingOverlay">
            <div class="loading-spinner"></div>
            <div class="loading-text">Carregando acervo de criaturas e assets agrupados...</div>
        </div>

        <div class="catalog-pane">
            <div class="filter-toolbar">
                <div class="search-row">
                    <input type="text" id="searchInput" class="search-input" placeholder="Buscar por criatura, NPC (#aranha, #robô, #escudo, #vaca), DMOD...">
                    <select id="dmodFilter" class="select-filter">
                        <option value="">Todos os D-MODs & Jogo Base</option>
                    </select>
                </div>
                <div class="category-pills">
                    <div class="cat-pill active" data-cat="all">Todas as Criaturas (<span id="countAll">0</span>)</div>
                    <div class="cat-pill flare-pill" data-cat="flare" style="background: linear-gradient(135deg, #065f46, #059669); color: #fff; font-weight: bold; border-color: #34d399;">🌟 Acervo Flare RPG 3D (<span id="countFlare">0</span>)</div>
                    <div class="cat-pill" data-cat="monsters">👾 Monstros & Inimigos (<span id="countMonsters">0</span>)</div>
                    <div class="cat-pill" data-cat="dink_heroes">🛡️ Dink & Heróis (<span id="countDink">0</span>)</div>
                    <div class="cat-pill" data-cat="npcs">👥 NPCs & Animais (<span id="countNpcs">0</span>)</div>
                    <div class="cat-pill" data-cat="items_weapons">⚔️ Armas & Itens (<span id="countItems">0</span>)</div>
                    <div class="cat-pill" data-cat="magic_fx">✨ Magias & VFX (<span id="countMagic">0</span>)</div>
                    <div class="cat-pill" data-cat="scenery">🏰 Cenários & Barcos (<span id="countScenery">0</span>)</div>
                    <div class="cat-pill" data-cat="tiles">🧱 Tilesets (<span id="countTiles">0</span>)</div>
                </div>
            </div>

            <div class="assets-grid-container" id="gridContainer">
                <div class="assets-grid" id="assetsGrid"></div>
                <button class="load-more-btn" id="btnLoadMore" style="display: none;">Carregar mais criaturas...</button>
            </div>
        </div>

        <div class="player-pane">
            <div class="player-header">
                <h2 id="insTitle">Selecione uma criatura ou NPC</h2>
                <p id="insSubtitle">Clique em qualquer criatura no catálogo para inspecionar direções e ações</p>
            </div>

            <!-- Action Pill Selector -->
            <div class="action-selector-section" id="actionSelector">
                <!-- Injected action buttons: Walk, Attack, Die, Idle -->
            </div>

            <div class="stage-container">
                <div class="stage-canvas-box bg-grid" id="stageBox">
                    <img id="playerImg" class="player-sprite" src="" alt="Sprite">
                </div>

                <div class="player-controls">
                    <div class="controls-row">
                        <button class="ctrl-btn" id="btnPrevFrame" title="Frame anterior">⏮️</button>
                        <button class="ctrl-btn active" id="btnPlayPause" title="Play/Pause">⏸️ Pausar</button>
                        <button class="ctrl-btn" id="btnNextFrame" title="Próximo frame">⏭️</button>
                    </div>

                    <div class="slider-row">
                        <span>Velocidade:</span>
                        <input type="range" id="fpsSlider" min="1" max="30" value="10">
                        <span id="fpsVal">10 FPS</span>
                    </div>

                    <div class="slider-row">
                        <span>Zoom:</span>
                        <input type="range" id="zoomSlider" min="1" max="5" value="2">
                        <span id="zoomVal">2x</span>
                    </div>

                    <div class="controls-row" style="margin-top: 0.3rem;">
                        <span style="font-size: 0.75rem; color: var(--text-muted);">Fundo:</span>
                        <button class="ctrl-btn" data-bg="bg-grid">Xadrez</button>
                        <button class="ctrl-btn" data-bg="bg-black">Preto</button>
                        <button class="ctrl-btn" data-bg="bg-grass">Grama</button>
                        <button class="ctrl-btn" data-bg="bg-dirt">Terra</button>
                    </div>
                </div>
            </div>

            <!-- 8-WAY DIRECTIONAL CONTROLLER (D-PAD) -->
            <div class="dpad-section">
                <div class="dpad-title">
                    <span>🧭 Controle de Direções</span>
                    <span id="dirNameLabel" style="color: #fff; text-transform: none; font-weight: 500; font-size: 0.8rem;">Sul (⬇)</span>
                </div>

                <div class="dpad-grid" id="dpadGrid">
                    <button class="dpad-btn" data-dir="7" title="Noroeste (7 / ↖)">↖</button>
                    <button class="dpad-btn" data-dir="8" title="Norte (8 / ⬆)">⬆</button>
                    <button class="dpad-btn" data-dir="9" title="Nordeste (9 / ↗)">↗</button>

                    <button class="dpad-btn" data-dir="4" title="Oeste (4 / ⬅)">⬅</button>
                    <div class="dpad-center" id="dpadCenter">⏺</div>
                    <button class="dpad-btn" data-dir="6" title="Leste (6 / ➡)">➡</button>

                    <button class="dpad-btn" data-dir="1" title="Sudoeste (1 / ↙)">↙</button>
                    <button class="dpad-btn active" data-dir="2" title="Sul (2 / ⬇)">⬇</button>
                    <button class="dpad-btn" data-dir="3" title="Sudeste (3 / ↘)">↘</button>
                </div>

                <div class="dpad-hint">
                    💡 Dica: Use as <b>Setas do Teclado</b> ou <b>Numpad (1-9)</b> para virar a criatura!
                </div>
            </div>

            <div class="frame-strip-section">
                <div class="frame-strip-label">Frames da Animação Atual (<span id="stripFrameCount">0</span>)</div>
                <div class="frame-strip" id="frameStrip"></div>
            </div>

            <div class="details-section">
                <div class="detail-row">
                    <span class="detail-label">Origem:</span>
                    <span class="detail-val" id="detDmod">—</span>
                </div>
                <div class="detail-row">
                    <span class="detail-label">Autor:</span>
                    <span class="detail-val" id="detAuthor">—</span>
                </div>
                <div class="detail-row">
                    <span class="detail-label">Resolução:</span>
                    <span class="detail-val" id="detResolution">—</span>
                </div>
                <div class="detail-row">
                    <span class="detail-label">Ações Disponíveis:</span>
                    <span class="detail-val" id="detActionsCount">—</span>
                </div>
                <div class="detail-row">
                    <span class="detail-label">Direções Suportadas:</span>
                    <span class="detail-val" id="detDirsCount">—</span>
                </div>

                <div id="iniBoxContainer" style="display: none;">
                    <span class="detail-label" style="display: block; margin-bottom: 0.3rem;">Definição em dink.ini:</span>
                    <div class="ini-code-box" id="detIni">—</div>
                </div>

                <div>
                    <span class="detail-label" style="display: block; margin-bottom: 0.3rem;">Tags & Características:</span>
                    <div class="tags-box" id="detTags"></div>
                </div>

                <div class="action-btns">
                    <button class="btn-integrate" id="btnToggleStash">⭐ Adicionar Criatura à Complete Edition</button>
                </div>
            </div>
        </div>
    </div>

    <!-- Cart Drawer -->
    <div class="cart-modal" id="cartModal">
        <div class="cart-modal-header">
            <h3 style="font-family: 'Cinzel', serif; color: var(--accent-gold);">Minha Seleção de Criaturas & Assets</h3>
            <button class="ctrl-btn" id="btnCloseCart">✕ Fechar</button>
        </div>
        <div class="cart-modal-body" id="cartBody"></div>
        <div class="cart-modal-footer">
            <button class="btn-integrate" id="btnExportCart">💾 Exportar Lista para Integração (JSON)</button>
            <button class="ctrl-btn" id="btnClearCart" style="color: #ff7b72;">Limpar Seleção</button>
        </div>
    </div>

    <script>
        let DATABASE = [];
        let filteredItems = [];
        let currentLimit = 120;

        let currentCategory = 'all';
        let searchQuery = '';
        let selectedDmod = '';
        let currentItem = null;
        let currentActionKey = 'walk';
        let currentDirKey = '2';

        let isPlaying = true;
        let currentFrameIdx = 0;
        let playInterval = null;
        let currentFps = 10;
        let currentZoom = 2;
        let selectedStash = new Set(JSON.parse(localStorage.getItem('dink_complete_assets') || '[]'));

        const DIR_NAMES = {
            '1': 'Sudoeste (↙)',
            '2': 'Sul (⬇)',
            '3': 'Sudeste (↘)',
            '4': 'Oeste (⬅)',
            '6': 'Leste (➡)',
            '7': 'Noroeste (↖)',
            '8': 'Norte (⬆)',
            '9': 'Nordeste (↗)',
            'default': 'Padrão'
        };

        const loadingOverlay = document.getElementById('loadingOverlay');
        const assetsGrid = document.getElementById('assetsGrid');
        const searchInput = document.getElementById('searchInput');
        const dmodFilter = document.getElementById('dmodFilter');
        const btnLoadMore = document.getElementById('btnLoadMore');
        const playerImg = document.getElementById('playerImg');
        const stageBox = document.getElementById('stageBox');
        const actionSelector = document.getElementById('actionSelector');
        const dpadGrid = document.getElementById('dpadGrid');
        const dirNameLabel = document.getElementById('dirNameLabel');
        const btnPlayPause = document.getElementById('btnPlayPause');
        const btnPrevFrame = document.getElementById('btnPrevFrame');
        const btnNextFrame = document.getElementById('btnNextFrame');
        const fpsSlider = document.getElementById('fpsSlider');
        const fpsVal = document.getElementById('fpsVal');
        const zoomSlider = document.getElementById('zoomSlider');
        const zoomVal = document.getElementById('zoomVal');
        const frameStrip = document.getElementById('frameStrip');
        const cartCount = document.getElementById('cartCount');
        const cartModal = document.getElementById('cartModal');
        const btnOpenCart = document.getElementById('btnOpenCart');
        const btnCloseCart = document.getElementById('btnCloseCart');
        const cartBody = document.getElementById('cartBody');
        const btnToggleStash = document.getElementById('btnToggleStash');
        const btnExportCart = document.getElementById('btnExportCart');
        const btnClearCart = document.getElementById('btnClearCart');

        // Fetch grouped visual database
        fetch('research/grouped_visual_database.json')
            .then(res => res.json())
            .then(data => {
                DATABASE = data;
                loadingOverlay.style.display = 'none';
                setupFilters();
                updateCartBadge();
                filterAndRender(true);
                if (DATABASE.length > 0) {
                    selectItem(DATABASE[0]);
                }
            })
            .catch(err => {
                loadingOverlay.innerHTML = `<div style="color: #ff7b72; font-family: 'Cinzel', serif;">Erro ao carregar banco de dados: ${err.message}</div>`;
            });

        function setupFilters() {
            const dmods = new Set();
            const counts = {
                all: DATABASE.length,
                flare: 0,
                monsters: 0,
                dink_heroes: 0,
                npcs: 0,
                items_weapons: 0,
                magic_fx: 0,
                scenery: 0,
                tiles: 0
            };

            DATABASE.forEach(item => {
                dmods.add(item.dmod_title);
                if (item.dmod_slug === 'flare' || (item.tags || []).includes('flare_rpg')) {
                    counts.flare++;
                }
                if (counts[item.category] !== undefined) {
                    counts[item.category]++;
                }
            });

            document.getElementById('countAll').textContent = counts.all;
            document.getElementById('countFlare').textContent = counts.flare;
            document.getElementById('countMonsters').textContent = counts.monsters;
            document.getElementById('countDink').textContent = counts.dink_heroes;
            document.getElementById('countNpcs').textContent = counts.npcs;
            document.getElementById('countItems').textContent = counts.items_weapons;
            document.getElementById('countMagic').textContent = counts.magic_fx;
            document.getElementById('countScenery').textContent = counts.scenery;
            document.getElementById('countTiles').textContent = counts.tiles;

            Array.from(dmods).sort().forEach(d => {
                const opt = document.createElement('option');
                opt.value = d;
                opt.textContent = d;
                dmodFilter.appendChild(opt);
            });
        }

        function filterAndRender(resetLimit = true) {
            if (resetLimit) currentLimit = 120;
            const q = searchQuery.toLowerCase().trim();

            filteredItems = DATABASE.filter(item => {
                if (currentCategory === 'flare') {
                    if (item.dmod_slug !== 'flare' && !(item.tags || []).includes('flare_rpg')) return false;
                } else if (currentCategory !== 'all' && item.category !== currentCategory) {
                    return false;
                }
                if (selectedDmod && item.dmod_title !== selectedDmod) return false;
                if (q) {
                    const matchText = (item.name + ' ' + item.dmod_title + ' ' + item.author + ' ' + (item.tags || []).join(' ')).toLowerCase();
                    if (!matchText.includes(q)) return false;
                }
                return true;
            });

            renderCards();
        }

        function renderCards() {
            assetsGrid.innerHTML = '';
            const slice = filteredItems.slice(0, currentLimit);

            slice.forEach(item => {
                const card = document.createElement('div');
                card.className = `asset-card ${currentItem && currentItem.id === item.id ? 'selected' : ''}`;
                
                const isStashed = selectedStash.has(item.id);
                const isFlare = item.dmod_slug === 'flare' || (item.tags || []).includes('flare_rpg');
                const dirsCount = (item.available_directions || []).filter(d => d !== 'default').length;
                const dirsText = dirsCount > 0 ? `${dirsCount} direções 🧭` : 'Estático';
                const actKeys = Object.keys(item.actions || {});
                const actsText = actKeys.length > 1 ? `${actKeys.length} ações` : '';

                card.innerHTML = `
                    <div class="card-select-star ${isStashed ? 'active' : ''}" title="Adicionar à Complete Edition">★</div>
                    <div class="asset-thumb-box">
                        <img class="asset-thumb-img" src="${item.preview}" alt="${item.name}" loading="lazy">
                        ${isFlare ? `<span class="flare-badge" style="position:absolute; top:6px; left:6px; background:linear-gradient(135deg, #059669, #10b981); color:#fff; font-size:9px; font-weight:bold; padding:2px 6px; border-radius:4px; border:1px solid #34d399; box-shadow:0 2px 8px rgba(16,185,129,0.4); z-index:2;">🌟 3D FLARE</span>` : ''}
                        <span class="dir-badge">${dirsText}</span>
                        ${actsText ? `<span class="actions-badge">${actsText}</span>` : ''}
                    </div>
                    <div class="asset-title" title="${item.name}">${item.name}</div>
                    <div class="asset-dmod" title="${item.dmod_title}">${item.dmod_title}</div>
                `;

                const star = card.querySelector('.card-select-star');
                star.addEventListener('click', (e) => {
                    e.stopPropagation();
                    toggleStash(item);
                });

                card.addEventListener('click', () => {
                    selectItem(item);
                });

                assetsGrid.appendChild(card);
            });

            if (filteredItems.length === 0) {
                assetsGrid.innerHTML = `<div style="grid-column: 1/-1; text-align: center; color: var(--text-muted); padding: 3rem;">Nenhuma criatura ou asset encontrado com os filtros atuais.</div>`;
                btnLoadMore.style.display = 'none';
            } else if (currentLimit < filteredItems.length) {
                btnLoadMore.style.display = 'block';
                btnLoadMore.textContent = `Carregar mais criaturas... (${currentLimit} de ${filteredItems.length})`;
            } else {
                btnLoadMore.style.display = 'none';
            }
        }

        btnLoadMore.addEventListener('click', () => {
            currentLimit += 120;
            renderCards();
        });

        // Select Creature
        function selectItem(item) {
            currentItem = item;
            currentActionKey = item.default_action || Object.keys(item.actions)[0] || 'default';
            currentDirKey = item.default_direction || '2';
            currentFrameIdx = 0;

            document.getElementById('insTitle').textContent = item.name;
            document.getElementById('insSubtitle').textContent = `${item.dmod_title} por ${item.author}`;
            document.getElementById('detDmod').textContent = item.dmod_title;
            document.getElementById('detAuthor').textContent = item.author;
            document.getElementById('detResolution').textContent = `${item.width} × ${item.height} px`;

            const actList = Object.values(item.actions).map(a => `${a.icon} ${a.label}`).join(', ');
            document.getElementById('detActionsCount').textContent = actList || 'Padrão';

            const dirsClean = (item.available_directions || []).filter(d => d !== 'default');
            document.getElementById('detDirsCount').textContent = dirsClean.length > 0 ? `${dirsClean.length} direções (${dirsClean.join(', ')})` : 'Direção única';

            const detTags = document.getElementById('detTags');
            detTags.innerHTML = '';
            (item.tags || []).forEach(t => {
                const span = document.createElement('span');
                span.className = 'tag-pill';
                span.textContent = '#' + t;
                detTags.appendChild(span);
            });

            // Build action selector pills
            renderActionSelector();

            // Setup D-pad & active direction
            updateDpad();

            // Load current frames & start playback
            loadCurrentSequence();

            updateStashBtn();
            renderCards();
        }

        function renderActionSelector() {
            actionSelector.innerHTML = '';
            const acts = currentItem ? currentItem.actions : {};
            const actKeys = Object.keys(acts);

            actKeys.forEach(k => {
                const act = acts[k];
                const btn = document.createElement('button');
                btn.className = `action-btn ${k === currentActionKey ? 'active' : ''}`;
                btn.innerHTML = `<span>${act.icon}</span> <span>${act.label}</span>`;
                btn.addEventListener('click', () => {
                    currentActionKey = k;
                    // If current direction not in this action, fallback
                    const availableDirs = Object.keys(act.directions);
                    if (!availableDirs.includes(currentDirKey)) {
                        currentDirKey = availableDirs[0] || 'default';
                    }
                    currentFrameIdx = 0;
                    renderActionSelector();
                    updateDpad();
                    loadCurrentSequence();
                });
                actionSelector.appendChild(btn);
            });
        }

        function updateDpad() {
            if (!currentItem) return;
            const currentActData = currentItem.actions[currentActionKey];
            const availableDirs = currentActData ? Object.keys(currentActData.directions) : [];

            // Update D-Pad buttons
            dpadGrid.querySelectorAll('.dpad-btn').forEach(btn => {
                const d = btn.dataset.dir;
                if (availableDirs.includes(d)) {
                    btn.disabled = false;
                    if (d === currentDirKey) {
                        btn.classList.add('active');
                    } else {
                        btn.classList.remove('active');
                    }
                } else {
                    btn.disabled = true;
                    btn.classList.remove('active');
                }
            });

            dirNameLabel.textContent = DIR_NAMES[currentDirKey] || 'Padrão';
        }

        function setDirection(d) {
            if (!currentItem) return;
            const currentActData = currentItem.actions[currentActionKey];
            if (!currentActData) return;

            if (currentActData.directions[d]) {
                currentDirKey = d;
                currentFrameIdx = 0;
                updateDpad();
                loadCurrentSequence();
            }
        }

        function loadCurrentSequence() {
            if (!currentItem) return;
            const actData = currentItem.actions[currentActionKey];
            if (!actData) return;

            let seqData = actData.directions[currentDirKey];
            if (!seqData) {
                // Fallback to first available direction
                const firstD = Object.keys(actData.directions)[0];
                if (firstD) {
                    currentDirKey = firstD;
                    seqData = actData.directions[firstD];
                    updateDpad();
                }
            }

            if (!seqData) return;

            currentFps = seqData.fps || 10;
            fpsSlider.value = currentFps;
            fpsVal.textContent = `${currentFps} FPS`;

            const iniBoxContainer = document.getElementById('iniBoxContainer');
            if (seqData.ini_info) {
                iniBoxContainer.style.display = 'block';
                document.getElementById('detIni').textContent = seqData.ini_info;
            } else {
                iniBoxContainer.style.display = 'none';
            }

            // Build Frame Strip
            frameStrip.innerHTML = '';
            document.getElementById('stripFrameCount').textContent = seqData.frame_count;
            seqData.frames.forEach((fUrl, idx) => {
                const thumb = document.createElement('div');
                thumb.className = `frame-strip-thumb ${idx === 0 ? 'active' : ''}`;
                thumb.innerHTML = `<img src="${fUrl}" alt="Frame ${idx + 1}">`;
                thumb.addEventListener('click', () => {
                    currentFrameIdx = idx;
                    showCurrentFrame();
                    stopAnimation();
                });
                frameStrip.appendChild(thumb);
            });

            showCurrentFrame();
            startAnimation();
        }

        function getCurrentFrames() {
            if (!currentItem) return [];
            const actData = currentItem.actions[currentActionKey];
            if (!actData) return [];
            const seqData = actData.directions[currentDirKey];
            return seqData ? seqData.frames : [];
        }

        function showCurrentFrame() {
            const frames = getCurrentFrames();
            if (!frames.length) return;
            currentFrameIdx = Math.min(currentFrameIdx, frames.length - 1);
            playerImg.src = frames[currentFrameIdx];

            const thumbs = frameStrip.querySelectorAll('.frame-strip-thumb');
            thumbs.forEach((t, i) => {
                if (i === currentFrameIdx) t.classList.add('active');
                else t.classList.remove('active');
            });
        }

        function startAnimation() {
            stopAnimation();
            const frames = getCurrentFrames();
            if (frames.length <= 1) return;
            isPlaying = true;
            btnPlayPause.textContent = '⏸️ Pausar';
            btnPlayPause.classList.add('active');

            const delay = Math.max(25, 1000 / currentFps);
            playInterval = setInterval(() => {
                const f = getCurrentFrames();
                if (!f.length) return;
                currentFrameIdx = (currentFrameIdx + 1) % f.length;
                showCurrentFrame();
            }, delay);
        }

        function stopAnimation() {
            if (playInterval) {
                clearInterval(playInterval);
                playInterval = null;
            }
            isPlaying = false;
            btnPlayPause.textContent = '▶️ Reproduzir';
            btnPlayPause.classList.remove('active');
        }

        // D-Pad Click Events
        dpadGrid.querySelectorAll('.dpad-btn').forEach(btn => {
            btn.addEventListener('click', () => {
                setDirection(btn.dataset.dir);
            });
        });

        // Keyboard Controls for Directions (Arrows, Numpad, WASD)
        window.addEventListener('keydown', (e) => {
            // Ignore if typing in search input
            if (document.activeElement === searchInput) return;

            const key = e.key;
            let targetDir = null;

            if (key === 'ArrowUp' || key === '8' || key.toLowerCase() === 'w') targetDir = '8';
            else if (key === 'ArrowDown' || key === '2' || key.toLowerCase() === 's') targetDir = '2';
            else if (key === 'ArrowLeft' || key === '4' || key.toLowerCase() === 'a') targetDir = '4';
            else if (key === 'ArrowRight' || key === '6' || key.toLowerCase() === 'd') targetDir = '6';
            else if (key === '7' || key.toLowerCase() === 'q') targetDir = '7';
            else if (key === '9' || key.toLowerCase() === 'e') targetDir = '9';
            else if (key === '1' || key.toLowerCase() === 'z') targetDir = '1';
            else if (key === '3' || key.toLowerCase() === 'c') targetDir = '3';
            else if (key === ' ') {
                e.preventDefault();
                if (isPlaying) stopAnimation(); else startAnimation();
            }

            if (targetDir) {
                setDirection(targetDir);
            }
        });

        function toggleStash(item) {
            if (selectedStash.has(item.id)) {
                selectedStash.delete(item.id);
            } else {
                selectedStash.add(item.id);
            }
            localStorage.setItem('dink_complete_assets', JSON.stringify(Array.from(selectedStash)));
            updateCartBadge();
            updateStashBtn();
            renderCards();
            renderCartModal();
        }

        function updateCartBadge() {
            cartCount.textContent = selectedStash.size;
        }

        function updateStashBtn() {
            if (!currentItem) return;
            if (selectedStash.has(currentItem.id)) {
                btnToggleStash.textContent = '✓ Criatura Adicionada (Clique para Remover)';
                btnToggleStash.style.background = '#238636';
                btnToggleStash.style.borderColor = '#2ea043';
                btnToggleStash.style.color = '#fff';
            } else {
                btnToggleStash.textContent = '⭐ Adicionar Criatura à Complete Edition';
                btnToggleStash.style.background = 'linear-gradient(180deg, #d4a037 0%, #a4761b 100%)';
                btnToggleStash.style.borderColor = '#e5b95c';
                btnToggleStash.style.color = '#000';
            }
        }

        function renderCartModal() {
            cartBody.innerHTML = '';
            if (selectedStash.size === 0) {
                cartBody.innerHTML = `<p style="color: var(--text-muted); font-size: 0.85rem; text-align: center;">Nenhuma criatura selecionada ainda.<br>Clique na estrela ⭐ dos cards para selecionar.</p>`;
                return;
            }

            selectedStash.forEach(id => {
                const item = DATABASE.find(x => x.id === id);
                if (!item) return;
                const div = document.createElement('div');
                div.className = 'cart-item';
                div.innerHTML = `
                    <img class="cart-item-img" src="${item.preview}" alt="">
                    <div class="cart-item-info">
                        <div class="cart-item-title">${item.name}</div>
                        <div class="cart-item-dmod">${item.dmod_title} (${item.total_frames} frames totais)</div>
                    </div>
                    <button class="ctrl-btn" style="color: #ff7b72; padding: 2px 6px;">✕</button>
                `;
                div.querySelector('button').addEventListener('click', () => {
                    toggleStash(item);
                });
                cartBody.appendChild(div);
            });
        }

        searchInput.addEventListener('input', (e) => {
            searchQuery = e.target.value;
            filterAndRender(true);
        });

        dmodFilter.addEventListener('change', (e) => {
            selectedDmod = e.target.value;
            filterAndRender(true);
        });

        document.querySelectorAll('.cat-pill').forEach(pill => {
            pill.addEventListener('click', () => {
                document.querySelectorAll('.cat-pill').forEach(p => p.classList.remove('active'));
                pill.classList.add('active');
                currentCategory = pill.dataset.cat;
                filterAndRender(true);
            });
        });

        btnPlayPause.addEventListener('click', () => {
            if (isPlaying) stopAnimation();
            else startAnimation();
        });

        btnPrevFrame.addEventListener('click', () => {
            stopAnimation();
            const f = getCurrentFrames();
            if (!f.length) return;
            currentFrameIdx = (currentFrameIdx - 1 + f.length) % f.length;
            showCurrentFrame();
        });

        btnNextFrame.addEventListener('click', () => {
            stopAnimation();
            const f = getCurrentFrames();
            if (!f.length) return;
            currentFrameIdx = (currentFrameIdx + 1) % f.length;
            showCurrentFrame();
        });

        fpsSlider.addEventListener('input', (e) => {
            currentFps = parseInt(e.target.value);
            fpsVal.textContent = `${currentFps} FPS`;
            if (isPlaying) startAnimation();
        });

        zoomSlider.addEventListener('input', (e) => {
            currentZoom = parseInt(e.target.value);
            zoomVal.textContent = `${currentZoom}x`;
            playerImg.style.transform = `scale(${currentZoom})`;
        });

        document.querySelectorAll('[data-bg]').forEach(btn => {
            btn.addEventListener('click', () => {
                stageBox.className = `stage-canvas-box ${btn.dataset.bg}`;
            });
        });

        btnToggleStash.addEventListener('click', () => {
            if (currentItem) toggleStash(currentItem);
        });

        btnOpenCart.addEventListener('click', () => {
            renderCartModal();
            cartModal.classList.add('open');
        });

        btnCloseCart.addEventListener('click', () => {
            cartModal.classList.remove('open');
        });

        btnClearCart.addEventListener('click', () => {
            selectedStash.clear();
            localStorage.removeItem('dink_complete_assets');
            updateCartBadge();
            updateStashBtn();
            renderCards();
            renderCartModal();
        });

        btnExportCart.addEventListener('click', () => {
            const selectedItems = Array.from(selectedStash).map(id => DATABASE.find(x => x.id === id)).filter(Boolean);
            const dataStr = "data:text/json;charset=utf-8," + encodeURIComponent(JSON.stringify(selectedItems, null, 2));
            const downloadAnchor = document.createElement('a');
            downloadAnchor.setAttribute("href", dataStr);
            downloadAnchor.setAttribute("download", "dink_complete_edition_selected_creatures.json");
            document.body.appendChild(downloadAnchor);
            downloadAnchor.click();
            downloadAnchor.remove();
        });
    </script>
</body>
</html>
"""
    with open(OUT_HTML_PATH, 'w', encoding='utf-8') as f:
        f.write(html)
    print(f"Generated updated HTML at {OUT_HTML_PATH}")

if __name__ == '__main__':
    build_grouped_database()
