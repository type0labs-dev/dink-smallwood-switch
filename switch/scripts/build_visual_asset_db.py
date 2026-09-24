#!/usr/bin/env python3
"""
build_visual_asset_database.py

Scans base game and all 392 DMODs in research/dmods/, extracts visual assets (BMP/PNG/INI),
groups frames into animation sequences (walk, attack, die, cast, idle, effects),
reads dimensions, categorizes by type (monsters, dink/heroes, npcs, items, magic, scenery),
and outputs:
  - research/visual_database.json (complete indexed database)
  - asset_database.html (interactive web viewer with flipbook animation player)
"""

import os
import re
import sys
import json
import glob
import struct
import tarfile
from collections import defaultdict
from concurrent.futures import ThreadPoolExecutor

BASE_DIR = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", ".."))
DMODS_DIR = os.path.join(BASE_DIR, "research", "dmods")
INDEX_PATH = os.path.join(BASE_DIR, "research", "dmods_index.json")
OUT_ASSETS_DIR = os.path.join(BASE_DIR, "research", "web_assets")
BASE_GAME_DIR = os.path.join(OUT_ASSETS_DIR, "base_game")
OUT_JSON_PATH = os.path.join(BASE_DIR, "research", "visual_database.json")
OUT_HTML_PATH = os.path.join(BASE_DIR, "asset_database.html")

def get_bmp_size(filepath):
    """Read BMP width and height directly from the 26-byte header."""
    try:
        with open(filepath, 'rb') as f:
            header = f.read(26)
            if len(header) >= 26 and header[:2] == b'BM':
                w, h = struct.unpack('<ii', header[18:26])
                return w, abs(h)
    except Exception:
        pass
    return None, None

def categorize_sequence(rel_path, seq_name, dmod_slug):
    """Classify an animation sequence or static sprite into category & tags."""
    text = f"{rel_path} {seq_name} {dmod_slug}".lower()
    
    # 1. Monsters & Bosses
    monster_keywords = [
        ('spider', 'Aranha Gigante', ['aranha', 'monstro', 'veneno', 'aracnídeo']),
        ('wasp', 'Vespa Assassina', ['vespa', 'inseto', 'voador', 'ferrão']),
        ('pill', 'Piolho Gigante', ['piolho', 'inseto', 'carapaça', 'monstro']),
        ('slayer', 'Slayer / Carrasco', ['slayer', 'carrasco', 'demônio']),
        ('bonca', 'Bonca Selvagem', ['bonca', 'fera', 'chifres']),
        ('goblin', 'Goblin / Trasgo', ['goblin', 'humanoide', 'clã']),
        ('dragon', 'Dragão Alado', ['dragão', 'réptil', 'fogo', 'chefe']),
        ('robot', 'Robô / Autômato', ['robô', 'vapor', 'laser', 'mecânico']),
        ('bot', 'Robô / Autômato', ['robô', 'mecânico']),
        ('skeleton', 'Esqueleto Vivo', ['esqueleto', 'morto-vivo', 'ossos']),
        ('skel', 'Esqueleto Vivo', ['esqueleto', 'morto-vivo']),
        ('zombie', 'Zumbi Putrefato', ['zumbi', 'morto-vivo']),
        ('demon', 'Demônio Infernal', ['demônio', 'infernal', 'chefe']),
        ('wolf', 'Lobo Selvagem', ['lobo', 'fera', 'selva']),
        ('beast', 'Besta Monstruosa', ['besta', 'monstro']),
        ('slime', 'Gosma / Slime', ['slime', 'gosma', 'veneno']),
        ('puddle', 'Gosma Ácida', ['gosma', 'ácido']),
        ('larva', 'Larva Gigante', ['larva', 'inseto']),
        ('rat', 'Rato das Sombras', ['rato', 'esgoto', 'roedor']),
        ('stonegnt', 'Gigante de Pedra', ['gigante', 'pedra', 'golem']),
        ('spike', 'Monstro Espinhoso', ['espinhos', 'monstro']),
        ('boss', 'Chefe / Boss', ['chefe', 'monstro']),
        ('foe', 'Inimigo Hostil', ['inimigo', 'monstro']),
        ('enemy', 'Inimigo Hostil', ['inimigo', 'monstro']),
    ]
    for kw, label, tags in monster_keywords:
        if kw in text:
            action = "Animação"
            if any(k in text for k in ['walk', 'w1', 'w2', 'w3', 'w4', 'w6', 'w7', 'w8', 'w9', 'run']):
                action = "Caminhando"
                tags.append("movimento")
            elif any(k in text for k in ['att', 'a1', 'a2', 'a3', 'a4', 'a6', 'a7', 'a8', 'a9', 'hit', 'slash', 'punch']):
                action = "Atacando"
                tags.append("combate")
            elif any(k in text for k in ['die', 'death', 'dead', 'd1', 'd2', 'd3', 'd4']):
                action = "Morte"
                tags.append("morte")
            elif 'idle' in text or 'stand' in text:
                action = "Parado"
                tags.append("idle")
            return 'monsters', f"{label} ({action})", tags

    # 2. Dink & Protagonists
    dink_keywords = [
        ('shield', 'Dink com Escudo', ['dink', 'escudo', 'defesa', 'off-hand']),
        ('axe', 'Dink com Machado', ['dink', 'machado', 'combate']),
        ('lantern', 'Dink com Lanterna', ['dink', 'lanterna', 'luz', 'exploração']),
        ('shovel', 'Dink com Pá / Coveiro', ['dink', 'pá', 'coveiro', 'escavação']),
        ('bow', 'Dink com Arco e Flecha', ['dink', 'arco', 'flecha', 'longo-alcance']),
        ('alex', 'Alex (Protagonista)', ['alex', 'protagonista', 'herói']),
        ('lyna', 'Lyna (Protagonista)', ['lyna', 'protagonista', 'heroína']),
        ('karg', 'Karg (Guerreiro)', ['karg', 'bárbaro', 'guerreiro']),
        ('dink', 'Dink Smallwood', ['dink', 'protagonista']),
        ('hero', 'Herói', ['herói', 'protagonista']),
    ]
    for kw, label, tags in dink_keywords:
        if kw in text:
            action = "Animação"
            if any(k in text for k in ['walk', 'w1', 'w2', 'w3', 'w4', 'w6', 'w7', 'w8', 'w9']):
                action = "Caminhando"
                tags.append("movimento")
            elif any(k in text for k in ['att', 'a1', 'a2', 'a3', 'hit', 'slash', 'punch']):
                action = "Atacando"
                tags.append("combate")
            elif any(k in text for k in ['die', 'death', 'dead']):
                action = "Morte"
                tags.append("morte")
            return 'dink_heroes', f"{label} ({action})", tags

    # 3. Weapons, Items & Shields
    item_keywords = [
        ('sword', 'Espada', ['espada', 'arma', 'lâmina']),
        ('shield', 'Escudo', ['escudo', 'defesa']),
        ('axe', 'Machado', ['machado', 'arma']),
        ('bow', 'Arco e Flecha', ['arco', 'arma']),
        ('potion', 'Poção / Elixir', ['poção', 'cura', 'item']),
        ('chest', 'Baú de Tesouro', ['baú', 'tesouro', 'item']),
        ('coin', 'Moedas de Ouro', ['ouro', 'moeda', 'economia']),
        ('gold', 'Ouro / Riqueza', ['ouro', 'tesouro']),
        ('key', 'Chave Especial', ['chave', 'porta', 'item']),
        ('wand', 'Varinha Mágica', ['varinha', 'magia', 'item']),
        ('bomb', 'Bomba Explosiva', ['bomba', 'explosivo', 'arma']),
        ('scroll', 'Pergaminho Antigo', ['pergaminho', 'lore', 'magia']),
        ('item', 'Item / Artefato', ['item', 'inventário']),
    ]
    for kw, label, tags in item_keywords:
        if kw in text:
            return 'items_weapons', label, tags

    # 4. Magic, VFX & Projectiles
    magic_keywords = [
        ('fire', 'Bola de Fogo / Labareda', ['fogo', 'magia', 'projétil']),
        ('plasma', 'Campo de Plasma', ['plasma', 'energia', 'magia']),
        ('ice', 'Magia de Gelo', ['gelo', 'frio', 'congelamento']),
        ('water', 'Jato d\'Água', ['água', 'fluido', 'magia']),
        ('blood', 'Sangue / Efeito de Dano', ['sangue', 'combate', 'gore']),
        ('splode', 'Explosão Impactante', ['explosão', 'impacto', 'vfx']),
        ('spark', 'Faíscas Mágicas', ['faíscas', 'magia', 'energia']),
        ('smoke', 'Fumaça / Névoa', ['fumaça', 'ambiente', 'vfx']),
        ('lightning', 'Relâmpago / Raio', ['raio', 'eletricidade', 'magia']),
        ('bolt', 'Disparo Mágico', ['projétil', 'magia']),
        ('magic', 'Efeito Mágico', ['magia', 'vfx']),
        ('spell', 'Encantamento', ['feitiço', 'magia']),
    ]
    for kw, label, tags in magic_keywords:
        if kw in text:
            return 'magic_fx', label, tags

    # 5. NPCs & Peaceful Creatures
    npc_keywords = [
        ('cow', 'Vaca Leiteira', ['vaca', 'animal', 'fazenda', 'empurrar']),
        ('duck', 'Pato Quaquá', ['pato', 'animal', 'fazenda']),
        ('pig', 'Porco', ['porco', 'animal']),
        ('rabbit', 'Coelho', ['coelho', 'animal']),
        ('girl', 'Moça / Aldeã', ['aldeã', 'npc', 'vila']),
        ('maiden', 'Donzela / Camponesa', ['donzela', 'npc']),
        ('peasant', 'Camponês', ['camponês', 'npc']),
        ('oldman', 'Ancião / Velho Sábio', ['ancião', 'npc', 'sábio']),
        ('knight', 'Cavaleiro Real', ['cavaleiro', 'guarda', 'soldado']),
        ('soldier', 'Soldado da Guarda', ['soldado', 'guarda']),
        ('guard', 'Guarda do Castelo', ['guarda', 'reino']),
        ('merchant', 'Mercador / Vendedor', ['mercador', 'loja', 'comércio']),
        ('king', 'Rei de Cast', ['rei', 'realeza']),
        ('queen', 'Rainha', ['rainha', 'realeza']),
        ('fairy', 'Fada Encantada', ['fada', 'mística', 'npc']),
        ('people', 'Habitante da Vila', ['habitante', 'npc']),
    ]
    for kw, label, tags in npc_keywords:
        if kw in text:
            return 'npcs', label, tags

    # 6. Scenery, Vehicles & Doodads
    scenery_keywords = [
        ('boat', 'Barco / Embarcação', ['barco', 'marítimo', 'transporte']),
        ('ship', 'Navio', ['navio', 'marítimo']),
        ('house', 'Construção / Cabana', ['casa', 'edifício', 'cenário']),
        ('cabin', 'Cabana de Madeira', ['cabana', 'cenário']),
        ('castle', 'Castelo Real', ['castelo', 'fortaleza', 'cenário']),
        ('bridge', 'Ponte', ['ponte', 'cenário']),
        ('portal', 'Portal Mágico', ['portal', 'viagem', 'místico']),
        ('tree', 'Árvore / Floresta', ['árvore', 'natureza', 'floresta']),
        ('bush', 'Arbusto', ['natureza', 'vegetação']),
        ('rock', 'Rocha / Pedra', ['rocha', 'cenário']),
        ('statue', 'Estátua Monumental', ['estátua', 'monumento']),
        ('door', 'Porta Interativa', ['porta', 'acesso']),
        ('struct', 'Estrutura Arquitetônica', ['estrutura', 'cenário']),
    ]
    for kw, label, tags in scenery_keywords:
        if kw in text:
            return 'scenery', label, tags

    # 7. Tilesets
    if 'tile' in text:
        return 'tiles', f"Tileset ({seq_name})", ['tileset', 'terreno', 'mapa']

    return 'other', f"Asset: {seq_name}", ['comunidade', 'dmod']

def scan_base_game():
    """Index canonical original Dink 1.08 sprites from unpacked base_game."""
    records = []
    if not os.path.exists(BASE_GAME_DIR):
        return records

    # Read base dink.ini
    ini_sequences = {}
    base_ini = os.path.join(BASE_DIR, "bin", "dink", "dink.ini")
    if os.path.exists(base_ini):
        with open(base_ini, 'r', encoding='latin-1', errors='ignore') as f:
            for line in f:
                line_s = line.strip()
                if line_s.lower().startswith(('load_sequence', 'load_sequence_now')):
                    parts = line_s.split()
                    if len(parts) >= 3:
                        pfx = parts[1].replace('\\', '/').lower()
                        ini_sequences[pfx] = {'seq_num': parts[2], 'delay': parts[3] if len(parts) > 3 else "75", 'line': line_s}

    seq_groups = defaultdict(list)
    regex = re.compile(r'^(.*?)(?:[\-_]?)([0-9]{1,3})\.(bmp|png)$', re.IGNORECASE)

    for root, _, files in os.walk(BASE_GAME_DIR):
        for fname in sorted(files):
            if not fname.lower().endswith(('.bmp', '.png')):
                continue
            abs_path = os.path.join(root, fname)
            rel_dir = os.path.relpath(root, BASE_GAME_DIR)
            m = regex.match(fname)
            if m:
                base_prefix = m.group(1).rstrip('-_')
                fnum = int(m.group(2))
                key = (rel_dir, base_prefix) if base_prefix else (rel_dir, 'frame')
                seq_groups[key].append((fnum, abs_path))
            else:
                bname = os.path.splitext(fname)[0]
                seq_groups[(rel_dir, bname)].append((1, abs_path))

    for (rel_dir, base_prefix), frames in seq_groups.items():
        frames.sort(key=lambda x: x[0])
        web_frames = [os.path.relpath(f[1], BASE_DIR) for f in frames]
        first_abs = frames[0][1]
        w, h = get_bmp_size(first_abs)
        
        seq_name = base_prefix if base_prefix else os.path.basename(rel_dir)
        cat, friendly_title, tags = categorize_sequence(rel_dir, seq_name, "base_game")
        tags.append("original_1997")
        
        fps = 10
        ini_info = None
        for p, data in ini_sequences.items():
            if base_prefix.lower() in p or p.endswith(base_prefix.lower()):
                ini_info = data['line']
                try:
                    d = int(data['delay'])
                    if d > 0: fps = max(1, min(30, int(1000 / d)))
                except ValueError:
                    pass
                break

        seq_id = f"base_{rel_dir}_{seq_name}".replace('/', '_').replace('\\', '_').replace(' ', '_').lower()
        records.append({
            'id': seq_id,
            'dmod_slug': 'base_game',
            'dmod_title': 'Dink Smallwood (Original 1.08)',
            'author': 'RTsoft (Seth Robinson)',
            'category': cat,
            'name': friendly_title,
            'raw_name': seq_name,
            'frame_count': len(frames),
            'fps': fps,
            'width': w or 64,
            'height': h or 64,
            'frames': web_frames,
            'preview': web_frames[0],
            'tags': list(set(tags)),
            'ini_info': ini_info
        })

    return records

def process_dmod(archive_path, meta_dict):
    """Extract visual files and index sequences for a single DMOD."""
    slug = os.path.splitext(os.path.basename(archive_path))[0]
    dmod_meta = meta_dict.get(os.path.basename(archive_path), {
        'title': slug,
        'author': 'Comunidade Dink',
        'desc': '',
        'rating': 0.0
    })
    
    extracted_images = []
    dink_ini_lines = []
    target_dmod_dir = os.path.join(OUT_ASSETS_DIR, slug)

    try:
        t = tarfile.open(archive_path, 'r:bz2', errorlevel=0, ignore_zeros=True)
        while True:
            try:
                m = t.next()
                if m is None:
                    break
                m_lower = m.name.lower()
                
                # Check for images or ini
                if m_lower.endswith(('.bmp', '.png')):
                    t.extract(m, target_dmod_dir)
                    extracted_images.append(m.name)
                elif m_lower.endswith('dink.ini'):
                    f = t.extractfile(m)
                    if f:
                        dink_ini_lines = f.read().decode('latin-1', errors='ignore').splitlines()
            except Exception:
                break
        t.close()
    except Exception as e:
        return []

    if not extracted_images:
        return []

    # Parse INI sequences if any
    ini_sequences = {}
    for line in dink_ini_lines:
        line_s = line.strip()
        if line_s.lower().startswith(('load_sequence', 'load_sequence_now')):
            parts = line_s.split()
            if len(parts) >= 3:
                prefix = parts[1].replace('\\', '/').lower()
                seq_num = parts[2]
                delay = parts[3] if len(parts) > 3 else "75"
                ini_sequences[prefix] = {'seq_num': seq_num, 'delay': delay, 'line': line_s}

    # Group extracted images by sequence
    seq_groups = defaultdict(list)
    regex = re.compile(r'^(.*?)(?:[\-_]?)([0-9]{1,3})\.(bmp|png)$', re.IGNORECASE)

    for img_rel in extracted_images:
        abs_img = os.path.join(target_dmod_dir, img_rel)
        fname = os.path.basename(img_rel)
        dir_rel = os.path.dirname(img_rel)
        
        m = regex.match(fname)
        if m:
            base_prefix = m.group(1).rstrip('-_')
            frame_num = int(m.group(2))
            seq_key = (dir_rel, base_prefix) if base_prefix else (dir_rel, 'frame')
            seq_groups[seq_key].append((frame_num, img_rel, abs_img))
        else:
            base_name = os.path.splitext(fname)[0]
            seq_groups[(dir_rel, base_name)].append((1, img_rel, abs_img))

    # Build sequence records
    records = []
    for (dir_rel, base_prefix), frames in seq_groups.items():
        frames.sort(key=lambda x: x[0])
        frame_rel_paths = [os.path.join('research', 'web_assets', slug, f[1]) for f in frames]
        first_abs = frames[0][2]
        w, h = get_bmp_size(first_abs)
        
        seq_name = base_prefix if base_prefix else os.path.basename(dir_rel)
        category, friendly_title, tags = categorize_sequence(dir_rel, seq_name, slug)
        
        fps = 10
        full_prefix = (dir_rel + '/' + base_prefix).lower()
        ini_info = None
        for p, data in ini_sequences.items():
            if p.endswith(base_prefix.lower()) or base_prefix.lower() in p:
                ini_info = data['line']
                try:
                    delay_ms = int(data['delay'])
                    if delay_ms > 0:
                        fps = max(1, min(30, int(1000 / delay_ms)))
                except ValueError:
                    pass
                break

        seq_id = f"{slug}_{dir_rel}_{seq_name}".replace('/', '_').replace('\\', '_').replace(' ', '_').lower()
        
        records.append({
            'id': seq_id,
            'dmod_slug': slug,
            'dmod_title': dmod_meta['title'],
            'author': dmod_meta['author'],
            'category': category,
            'name': friendly_title,
            'raw_name': seq_name,
            'frame_count': len(frames),
            'fps': fps,
            'width': w or 64,
            'height': h or 64,
            'frames': frame_rel_paths,
            'preview': frame_rel_paths[0],
            'tags': list(set(tags)),
            'ini_info': ini_info
        })

    return records

def generate_web_database_html(database):
    """Generate the complete interactive web page with flipbook animation player."""
    db_json_str = json.dumps(database, ensure_ascii=False)
    
    html = f"""<!DOCTYPE html>
<html lang="pt-BR">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Dink Smallwood Complete Edition — Catálogo Visual de Assets & Animações</title>
    <link rel="preconnect" href="https://fonts.googleapis.com">
    <link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
    <link href="https://fonts.googleapis.com/css2?family=Cinzel:wght@600;700;800;900&family=Inter:wght@400;500;600;700&display=swap" rel="stylesheet">
    <style>
        :root {{
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
        }}
        * {{
            box-sizing: border-box;
            margin: 0;
            padding: 0;
        }}
        body {{
            background: var(--bg-base);
            color: var(--text-main);
            font-family: 'Inter', sans-serif;
            min-height: 100vh;
            display: flex;
            flex-direction: column;
        }}
        header {{
            background: linear-gradient(180deg, #181d28 0%, #0e1118 100%);
            border-bottom: 2px solid var(--border-gold);
            padding: 1.25rem 2rem;
            display: flex;
            justify-content: space-between;
            align-items: center;
            position: sticky;
            top: 0;
            z-index: 100;
            box-shadow: 0 4px 20px rgba(0,0,0,0.5);
        }}
        .header-title {{
            display: flex;
            align-items: center;
            gap: 1rem;
        }}
        .header-title h1 {{
            font-family: 'Cinzel', serif;
            font-size: 1.5rem;
            color: var(--accent-gold);
            letter-spacing: 1px;
            text-shadow: 0 0 10px rgba(229,185,92,0.3);
        }}
        .header-badge {{
            background: rgba(194, 153, 71, 0.15);
            border: 1px solid var(--border-gold);
            color: var(--accent-gold);
            padding: 0.25rem 0.6rem;
            border-radius: 999px;
            font-size: 0.8rem;
            font-weight: 600;
        }}
        .header-links {{
            display: flex;
            align-items: center;
            gap: 1rem;
        }}
        .header-btn {{
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
        }}
        .header-btn:hover {{
            background: var(--border-gold);
            color: #0a0c10;
        }}
        .cart-badge {{
            background: var(--accent-red);
            color: #fff;
            padding: 0.1rem 0.45rem;
            border-radius: 999px;
            font-size: 0.75rem;
            margin-left: 0.3rem;
        }}

        .workspace {{
            display: flex;
            flex: 1;
            height: calc(100vh - 75px);
            overflow: hidden;
        }}

        .catalog-pane {{
            flex: 1;
            display: flex;
            flex-direction: column;
            border-right: 1px solid var(--border-color);
            overflow: hidden;
        }}

        .filter-toolbar {{
            background: #10141d;
            border-bottom: 1px solid var(--border-color);
            padding: 1rem 1.5rem;
            display: flex;
            flex-direction: column;
            gap: 0.8rem;
        }}

        .search-row {{
            display: flex;
            gap: 0.75rem;
        }}
        .search-input {{
            flex: 1;
            background: #171d2a;
            border: 1px solid var(--border-color);
            border-radius: 6px;
            padding: 0.6rem 1rem;
            color: #fff;
            font-size: 0.9rem;
            outline: none;
            transition: border-color 0.2s;
        }}
        .search-input:focus {{
            border-color: var(--border-gold);
        }}
        .select-filter {{
            background: #171d2a;
            border: 1px solid var(--border-color);
            border-radius: 6px;
            padding: 0.6rem 1rem;
            color: #fff;
            font-size: 0.9rem;
            outline: none;
            cursor: pointer;
            max-width: 260px;
        }}

        .category-pills {{
            display: flex;
            gap: 0.5rem;
            overflow-x: auto;
            padding-bottom: 0.2rem;
        }}
        .cat-pill {{
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
        }}
        .cat-pill:hover {{
            color: #fff;
            border-color: #485b7f;
        }}
        .cat-pill.active {{
            background: rgba(229, 185, 92, 0.2);
            border-color: var(--accent-gold);
            color: var(--accent-gold);
        }}

        .assets-grid-container {{
            flex: 1;
            overflow-y: auto;
            padding: 1.5rem;
        }}
        .assets-grid {{
            display: grid;
            grid-template-columns: repeat(auto-fill, minmax(180px, 1fr));
            gap: 1rem;
        }}
        .asset-card {{
            background: var(--bg-card);
            border: 1px solid var(--border-color);
            border-radius: 8px;
            padding: 0.75rem;
            display: flex;
            flex-direction: column;
            align-items: center;
            cursor: pointer;
            transition: all 0.2s;
            position: relative;
        }}
        .asset-card:hover {{
            background: var(--bg-card-hover);
            border-color: var(--border-gold);
            transform: translateY(-2px);
            box-shadow: 0 6px 15px rgba(0,0,0,0.4);
        }}
        .asset-card.selected {{
            border-color: var(--accent-gold);
            box-shadow: 0 0 12px rgba(229,185,92,0.4);
        }}
        .asset-thumb-box {{
            width: 100%;
            height: 120px;
            background: #0d1017;
            border: 1px solid #1a202c;
            border-radius: 6px;
            display: flex;
            align-items: center;
            justify-content: center;
            overflow: hidden;
            margin-bottom: 0.6rem;
            position: relative;
        }}
        .asset-thumb-img {{
            max-width: 90%;
            max-height: 90%;
            object-fit: contain;
            image-rendering: pixelated;
        }}
        .frame-badge {{
            position: absolute;
            bottom: 6px;
            right: 6px;
            background: rgba(0,0,0,0.8);
            border: 1px solid #333;
            color: #fff;
            padding: 0.1rem 0.4rem;
            border-radius: 4px;
            font-size: 0.7rem;
            font-weight: 700;
        }}
        .asset-title {{
            font-size: 0.85rem;
            font-weight: 600;
            color: #fff;
            text-align: center;
            white-space: nowrap;
            overflow: hidden;
            text-overflow: ellipsis;
            width: 100%;
            margin-bottom: 0.2rem;
        }}
        .asset-dmod {{
            font-size: 0.75rem;
            color: var(--text-muted);
            text-align: center;
            white-space: nowrap;
            overflow: hidden;
            text-overflow: ellipsis;
            width: 100%;
        }}
        .card-select-star {{
            position: absolute;
            top: 6px;
            right: 6px;
            background: rgba(0,0,0,0.6);
            border: 1px solid #444;
            border-radius: 4px;
            padding: 2px 5px;
            font-size: 0.8rem;
            color: #888;
            cursor: pointer;
            transition: all 0.2s;
        }}
        .card-select-star:hover, .card-select-star.active {{
            color: var(--accent-gold);
            border-color: var(--accent-gold);
            background: rgba(229,185,92,0.2);
        }}

        .player-pane {{
            width: 440px;
            background: #11151e;
            display: flex;
            flex-direction: column;
            overflow-y: auto;
        }}
        .player-header {{
            padding: 1rem 1.25rem;
            border-bottom: 1px solid var(--border-color);
            background: #151a26;
        }}
        .player-header h2 {{
            font-family: 'Cinzel', serif;
            font-size: 1.15rem;
            color: var(--accent-gold);
            margin-bottom: 0.2rem;
        }}
        .player-header p {{
            font-size: 0.8rem;
            color: var(--text-muted);
        }}

        .stage-container {{
            padding: 1.25rem;
            display: flex;
            flex-direction: column;
            align-items: center;
            background: var(--bg-player);
            border-bottom: 1px solid var(--border-color);
        }}
        .stage-canvas-box {{
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
        }}
        .stage-canvas-box.bg-black {{ background: #000; }}
        .stage-canvas-box.bg-grid {{
            background-color: #1a1e27;
            background-image: linear-gradient(45deg, #131720 25%, transparent 25%),
                              linear-gradient(-45deg, #131720 25%, transparent 25%),
                              linear-gradient(45deg, transparent 75%, #131720 75%),
                              linear-gradient(-45deg, transparent 75%, #131720 75%);
            background-size: 20px 20px;
            background-position: 0 0, 0 10px, 10px -10px, -10px 0px;
        }}
        .stage-canvas-box.bg-grass {{ background: #23581c; }}
        .stage-canvas-box.bg-dirt {{ background: #4a341f; }}

        .player-sprite {{
            max-width: 90%;
            max-height: 90%;
            image-rendering: pixelated;
            transform-origin: center center;
            transition: transform 0.1s ease;
        }}

        .player-controls {{
            width: 100%;
            margin-top: 1rem;
            display: flex;
            flex-direction: column;
            gap: 0.75rem;
        }}
        .controls-row {{
            display: flex;
            justify-content: center;
            align-items: center;
            gap: 0.5rem;
        }}
        .ctrl-btn {{
            background: #1e2638;
            border: 1px solid var(--border-color);
            color: #fff;
            padding: 0.4rem 0.8rem;
            border-radius: 6px;
            font-size: 0.85rem;
            cursor: pointer;
            transition: all 0.2s;
        }}
        .ctrl-btn:hover {{
            background: var(--border-gold);
            color: #000;
        }}
        .ctrl-btn.active {{
            background: var(--accent-gold);
            color: #000;
            border-color: var(--accent-gold);
        }}

        .slider-row {{
            display: flex;
            align-items: center;
            justify-content: space-between;
            font-size: 0.8rem;
            color: var(--text-muted);
            padding: 0 0.5rem;
        }}
        .slider-row input[type="range"] {{
            flex: 1;
            margin: 0 0.75rem;
            accent-color: var(--accent-gold);
        }}

        .frame-strip-section {{
            padding: 1rem 1.25rem;
            border-bottom: 1px solid var(--border-color);
        }}
        .frame-strip-label {{
            font-size: 0.75rem;
            text-transform: uppercase;
            letter-spacing: 1px;
            color: var(--text-muted);
            margin-bottom: 0.5rem;
        }}
        .frame-strip {{
            display: flex;
            gap: 0.5rem;
            overflow-x: auto;
            padding-bottom: 0.5rem;
        }}
        .frame-strip-thumb {{
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
        }}
        .frame-strip-thumb:hover {{
            border-color: #fff;
        }}
        .frame-strip-thumb.active {{
            border-color: var(--accent-gold);
            box-shadow: 0 0 8px rgba(229,185,92,0.5);
        }}
        .frame-strip-thumb img {{
            max-width: 90%;
            max-height: 90%;
            image-rendering: pixelated;
        }}

        .details-section {{
            padding: 1.25rem;
            display: flex;
            flex-direction: column;
            gap: 0.8rem;
            font-size: 0.85rem;
        }}
        .detail-row {{
            display: flex;
            justify-content: space-between;
            padding-bottom: 0.4rem;
            border-bottom: 1px solid #1a2233;
        }}
        .detail-label {{
            color: var(--text-muted);
        }}
        .detail-val {{
            color: #fff;
            font-weight: 500;
            text-align: right;
        }}
        .ini-code-box {{
            background: #080a0f;
            border: 1px solid #202738;
            border-radius: 6px;
            padding: 0.75rem;
            font-family: monospace;
            font-size: 0.75rem;
            color: #79c0ff;
            word-break: break-all;
        }}
        .tags-box {{
            display: flex;
            flex-wrap: wrap;
            gap: 0.35rem;
            margin-top: 0.3rem;
        }}
        .tag-pill {{
            background: rgba(52, 152, 219, 0.15);
            border: 1px solid rgba(52, 152, 219, 0.3);
            color: #58a6ff;
            padding: 0.15rem 0.45rem;
            border-radius: 4px;
            font-size: 0.7rem;
        }}

        .action-btns {{
            margin-top: 0.5rem;
            display: flex;
            flex-direction: column;
            gap: 0.5rem;
        }}
        .btn-integrate {{
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
        }}
        .btn-integrate:hover {{
            filter: brightness(1.15);
            transform: translateY(-1px);
        }}

        .cart-modal {{
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
        }}
        .cart-modal.open {{
            right: 0;
        }}
        .cart-modal-header {{
            padding: 1.25rem 1.5rem;
            border-bottom: 1px solid var(--border-color);
            display: flex;
            justify-content: space-between;
            align-items: center;
            background: #161c28;
        }}
        .cart-modal-body {{
            flex: 1;
            overflow-y: auto;
            padding: 1.25rem;
            display: flex;
            flex-direction: column;
            gap: 0.75rem;
        }}
        .cart-item {{
            background: #171d2a;
            border: 1px solid var(--border-color);
            border-radius: 6px;
            padding: 0.6rem 0.8rem;
            display: flex;
            align-items: center;
            gap: 0.8rem;
        }}
        .cart-item-img {{
            width: 40px;
            height: 40px;
            object-fit: contain;
            background: #000;
            border-radius: 4px;
            image-rendering: pixelated;
        }}
        .cart-item-info {{
            flex: 1;
            overflow: hidden;
        }}
        .cart-item-title {{
            font-size: 0.85rem;
            font-weight: 600;
            color: #fff;
            white-space: nowrap;
            overflow: hidden;
            text-overflow: ellipsis;
        }}
        .cart-item-dmod {{
            font-size: 0.75rem;
            color: var(--text-muted);
        }}
        .cart-modal-footer {{
            padding: 1.25rem;
            border-top: 1px solid var(--border-color);
            background: #161c28;
            display: flex;
            flex-direction: column;
            gap: 0.5rem;
        }}
    </style>
</head>
<body>

    <header>
        <div class="header-title">
            <h1>Dink Smallwood Complete Edition</h1>
            <span class="header-badge">Acervo Visual & Animações</span>
        </div>
        <div class="header-links">
            <a href="complete_edition.html" class="header-btn">🏛️ Voltar ao Dashboard</a>
            <button class="header-btn" id="btnOpenCart">
                ⭐ Selecionados <span class="cart-badge" id="cartCount">0</span>
            </button>
        </div>
    </header>

    <div class="workspace">
        <!-- Catalog List -->
        <div class="catalog-pane">
            <div class="filter-toolbar">
                <div class="search-row">
                    <input type="text" id="searchInput" class="search-input" placeholder="Buscar por nome, tag (#aranha, #robô, #escudo), DMOD...">
                    <select id="dmodFilter" class="select-filter">
                        <option value="">Todos os D-MODs & Jogo Base</option>
                    </select>
                </div>
                <div class="category-pills">
                    <div class="cat-pill active" data-cat="all">Todos (<span id="countAll">0</span>)</div>
                    <div class="cat-pill" data-cat="monsters">👾 Monstros & Inimigos (<span id="countMonsters">0</span>)</div>
                    <div class="cat-pill" data-cat="dink_heroes">🛡️ Dink & Protagonistas (<span id="countDink">0</span>)</div>
                    <div class="cat-pill" data-cat="npcs">👥 NPCs & Animais (<span id="countNpcs">0</span>)</div>
                    <div class="cat-pill" data-cat="items_weapons">⚔️ Armas & Itens (<span id="countItems">0</span>)</div>
                    <div class="cat-pill" data-cat="magic_fx">✨ Magias & VFX (<span id="countMagic">0</span>)</div>
                    <div class="cat-pill" data-cat="scenery">🏰 Cenários & Barcos (<span id="countScenery">0</span>)</div>
                    <div class="cat-pill" data-cat="tiles">🧱 Tilesets (<span id="countTiles">0</span>)</div>
                </div>
            </div>

            <div class="assets-grid-container">
                <div class="assets-grid" id="assetsGrid"></div>
            </div>
        </div>

        <!-- Right Side: Player & Inspector -->
        <div class="player-pane">
            <div class="player-header">
                <h2 id="insTitle">Selecione uma animação</h2>
                <p id="insSubtitle">Clique em qualquer asset no catálogo para reproduzir e inspecionar</p>
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

            <div class="frame-strip-section">
                <div class="frame-strip-label">Frames da Animação (<span id="stripFrameCount">0</span>)</div>
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
                    <span class="detail-label">Identificador Técnico:</span>
                    <span class="detail-val" id="detRawName" style="font-family: monospace; font-size: 0.75rem;">—</span>
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
                    <button class="btn-integrate" id="btnToggleStash">⭐ Adicionar à Minha Seleção Complete Edition</button>
                </div>
            </div>
        </div>
    </div>

    <!-- Selection Cart Drawer -->
    <div class="cart-modal" id="cartModal">
        <div class="cart-modal-header">
            <h3 style="font-family: 'Cinzel', serif; color: var(--accent-gold);">Minha Seleção de Assets</h3>
            <button class="ctrl-btn" id="btnCloseCart">✕ Fechar</button>
        </div>
        <div class="cart-modal-body" id="cartBody"></div>
        <div class="cart-modal-footer">
            <button class="btn-integrate" id="btnExportCart">💾 Exportar Lista para Integração (JSON)</button>
            <button class="ctrl-btn" id="btnClearCart" style="color: #ff7b72;">Limpar Seleção</button>
        </div>
    </div>

    <script>
        const DATABASE = {db_json_str};

        let currentCategory = 'all';
        let searchQuery = '';
        let selectedDmod = '';
        let currentItem = null;
        let isPlaying = true;
        let currentFrameIdx = 0;
        let playInterval = null;
        let currentFps = 10;
        let currentZoom = 2;
        let selectedStash = new Set(JSON.parse(localStorage.getItem('dink_complete_assets') || '[]'));

        const assetsGrid = document.getElementById('assetsGrid');
        const searchInput = document.getElementById('searchInput');
        const dmodFilter = document.getElementById('dmodFilter');
        const playerImg = document.getElementById('playerImg');
        const stageBox = document.getElementById('stageBox');
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

        function setupFilters() {{
            const dmods = new Set();
            const counts = {{
                all: DATABASE.length,
                monsters: 0,
                dink_heroes: 0,
                npcs: 0,
                items_weapons: 0,
                magic_fx: 0,
                scenery: 0,
                tiles: 0
            }};

            DATABASE.forEach(item => {{
                dmods.add(item.dmod_title);
                if (counts[item.category] !== undefined) {{
                    counts[item.category]++;
                }}
            }});

            document.getElementById('countAll').textContent = counts.all;
            document.getElementById('countMonsters').textContent = counts.monsters;
            document.getElementById('countDink').textContent = counts.dink_heroes;
            document.getElementById('countNpcs').textContent = counts.npcs;
            document.getElementById('countItems').textContent = counts.items_weapons;
            document.getElementById('countMagic').textContent = counts.magic_fx;
            document.getElementById('countScenery').textContent = counts.scenery;
            document.getElementById('countTiles').textContent = counts.tiles;

            Array.from(dmods).sort().forEach(d => {{
                const opt = document.createElement('option');
                opt.value = d;
                opt.textContent = d;
                dmodFilter.appendChild(opt);
            }});
        }}

        function renderCards() {{
            assetsGrid.innerHTML = '';
            const q = searchQuery.toLowerCase().trim();

            const filtered = DATABASE.filter(item => {{
                if (currentCategory !== 'all' && item.category !== currentCategory) return false;
                if (selectedDmod && item.dmod_title !== selectedDmod) return false;
                if (q) {{
                    const matchText = (item.name + ' ' + item.dmod_title + ' ' + item.author + ' ' + item.raw_name + ' ' + item.tags.join(' ')).toLowerCase();
                    if (!matchText.includes(q)) return false;
                }}
                return true;
            }});

            filtered.slice(0, 400).forEach(item => {{
                const card = document.createElement('div');
                card.className = `asset-card ${{currentItem && currentItem.id === item.id ? 'selected' : ''}}`;
                
                const isStashed = selectedStash.has(item.id);

                card.innerHTML = `
                    <div class="card-select-star ${{isStashed ? 'active' : ''}}" title="Adicionar à Complete Edition">★</div>
                    <div class="asset-thumb-box">
                        <img class="asset-thumb-img" src="${{item.preview}}" alt="${{item.name}}" loading="lazy">
                        <span class="frame-badge">${{item.frame_count}} frames</span>
                    </div>
                    <div class="asset-title" title="${{item.name}}">${{item.name}}</div>
                    <div class="asset-dmod" title="${{item.dmod_title}}">${{item.dmod_title}}</div>
                `;

                const star = card.querySelector('.card-select-star');
                star.addEventListener('click', (e) => {{
                    e.stopPropagation();
                    toggleStash(item);
                }});

                card.addEventListener('click', () => {{
                    selectItem(item);
                }});

                assetsGrid.appendChild(card);
            }});

            if (filtered.length === 0) {{
                assetsGrid.innerHTML = `<div style="grid-column: 1/-1; text-align: center; color: var(--text-muted); padding: 3rem;">Nenhum asset encontrado com os filtros atuais.</div>`;
            }}
        }}

        function selectItem(item) {{
            currentItem = item;
            currentFrameIdx = 0;
            currentFps = item.fps || 10;
            fpsSlider.value = currentFps;
            fpsVal.textContent = `${{currentFps}} FPS`;

            document.getElementById('insTitle').textContent = item.name;
            document.getElementById('insSubtitle').textContent = `${{item.dmod_title}} por ${{item.author}}`;
            document.getElementById('detDmod').textContent = item.dmod_title;
            document.getElementById('detAuthor').textContent = item.author;
            document.getElementById('detResolution').textContent = `${{item.width}} × ${{item.height}} px`;
            document.getElementById('detRawName').textContent = item.raw_name;

            const iniBoxContainer = document.getElementById('iniBoxContainer');
            if (item.ini_info) {{
                iniBoxContainer.style.display = 'block';
                document.getElementById('detIni').textContent = item.ini_info;
            }} else {{
                iniBoxContainer.style.display = 'none';
            }}

            const detTags = document.getElementById('detTags');
            detTags.innerHTML = '';
            item.tags.forEach(t => {{
                const span = document.createElement('span');
                span.className = 'tag-pill';
                span.textContent = '#' + t;
                detTags.appendChild(span);
            }});

            frameStrip.innerHTML = '';
            document.getElementById('stripFrameCount').textContent = item.frame_count;
            item.frames.forEach((fUrl, idx) => {{
                const thumb = document.createElement('div');
                thumb.className = `frame-strip-thumb ${{idx === 0 ? 'active' : ''}}`;
                thumb.innerHTML = `<img src="${{fUrl}}" alt="Frame ${{idx + 1}}">`;
                thumb.addEventListener('click', () => {{
                    currentFrameIdx = idx;
                    showCurrentFrame();
                    stopAnimation();
                }});
                frameStrip.appendChild(thumb);
            }});

            updateStashBtn();
            showCurrentFrame();
            startAnimation();
            renderCards();
        }}

        function showCurrentFrame() {{
            if (!currentItem || !currentItem.frames.length) return;
            playerImg.src = currentItem.frames[currentFrameIdx];

            const thumbs = frameStrip.querySelectorAll('.frame-strip-thumb');
            thumbs.forEach((t, i) => {{
                if (i === currentFrameIdx) t.classList.add('active');
                else t.classList.remove('active');
            }});
        }}

        function startAnimation() {{
            stopAnimation();
            if (!currentItem || currentItem.frames.length <= 1) return;
            isPlaying = true;
            btnPlayPause.textContent = '⏸️ Pausar';
            btnPlayPause.classList.add('active');

            const delay = Math.max(25, 1000 / currentFps);
            playInterval = setInterval(() => {{
                currentFrameIdx = (currentFrameIdx + 1) % currentItem.frames.length;
                showCurrentFrame();
            }}, delay);
        }}

        function stopAnimation() {{
            if (playInterval) {{
                clearInterval(playInterval);
                playInterval = null;
            }}
            isPlaying = false;
            btnPlayPause.textContent = '▶️ Reproduzir';
            btnPlayPause.classList.remove('active');
        }}

        function toggleStash(item) {{
            if (selectedStash.has(item.id)) {{
                selectedStash.delete(item.id);
            }} else {{
                selectedStash.add(item.id);
            }}
            localStorage.setItem('dink_complete_assets', JSON.stringify(Array.from(selectedStash)));
            updateCartBadge();
            updateStashBtn();
            renderCards();
            renderCartModal();
        }}

        function updateCartBadge() {{
            cartCount.textContent = selectedStash.size;
        }}

        function updateStashBtn() {{
            if (!currentItem) return;
            if (selectedStash.has(currentItem.id)) {{
                btnToggleStash.textContent = '✓ Adicionado à Seleção (Clique para Remover)';
                btnToggleStash.style.background = '#238636';
                btnToggleStash.style.borderColor = '#2ea043';
                btnToggleStash.style.color = '#fff';
            }} else {{
                btnToggleStash.textContent = '⭐ Adicionar à Minha Seleção Complete Edition';
                btnToggleStash.style.background = 'linear-gradient(180deg, #d4a037 0%, #a4761b 100%)';
                btnToggleStash.style.borderColor = '#e5b95c';
                btnToggleStash.style.color = '#000';
            }}
        }}

        function renderCartModal() {{
            cartBody.innerHTML = '';
            if (selectedStash.size === 0) {{
                cartBody.innerHTML = `<p style="color: var(--text-muted); font-size: 0.85rem; text-align: center;">Nenhum asset selecionado ainda.<br>Clique na estrela ⭐ dos cards para selecionar.</p>`;
                return;
            }}

            selectedStash.forEach(id => {{
                const item = DATABASE.find(x => x.id === id);
                if (!item) return;
                const div = document.createElement('div');
                div.className = 'cart-item';
                div.innerHTML = `
                    <img class="cart-item-img" src="${{item.preview}}" alt="">
                    <div class="cart-item-info">
                        <div class="cart-item-title">${{item.name}}</div>
                        <div class="cart-item-dmod">${{item.dmod_title}} (${{item.frame_count}} frames)</div>
                    </div>
                    <button class="ctrl-btn" style="color: #ff7b72; padding: 2px 6px;">✕</button>
                `;
                div.querySelector('button').addEventListener('click', () => {{
                    toggleStash(item);
                }});
                cartBody.appendChild(div);
            }});
        }}

        searchInput.addEventListener('input', (e) => {{
            searchQuery = e.target.value;
            renderCards();
        }});

        dmodFilter.addEventListener('change', (e) => {{
            selectedDmod = e.target.value;
            renderCards();
        }});

        document.querySelectorAll('.cat-pill').forEach(pill => {{
            pill.addEventListener('click', () => {{
                document.querySelectorAll('.cat-pill').forEach(p => p.classList.remove('active'));
                pill.classList.add('active');
                currentCategory = pill.dataset.cat;
                renderCards();
            }});
        }});

        btnPlayPause.addEventListener('click', () => {{
            if (isPlaying) stopAnimation();
            else startAnimation();
        }});

        btnPrevFrame.addEventListener('click', () => {{
            stopAnimation();
            if (!currentItem || !currentItem.frames.length) return;
            currentFrameIdx = (currentFrameIdx - 1 + currentItem.frames.length) % currentItem.frames.length;
            showCurrentFrame();
        }});

        btnNextFrame.addEventListener('click', () => {{
            stopAnimation();
            if (!currentItem || !currentItem.frames.length) return;
            currentFrameIdx = (currentFrameIdx + 1) % currentItem.frames.length;
            showCurrentFrame();
        }});

        fpsSlider.addEventListener('input', (e) => {{
            currentFps = parseInt(e.target.value);
            fpsVal.textContent = `${{currentFps}} FPS`;
            if (isPlaying) startAnimation();
        }});

        zoomSlider.addEventListener('input', (e) => {{
            currentZoom = parseInt(e.target.value);
            zoomVal.textContent = `${{currentZoom}}x`;
            playerImg.style.transform = `scale(${{currentZoom}})`;
        }});

        document.querySelectorAll('[data-bg]').forEach(btn => {{
            btn.addEventListener('click', () => {{
                stageBox.className = `stage-canvas-box ${{btn.dataset.bg}}`;
            }});
        }});

        btnToggleStash.addEventListener('click', () => {{
            if (currentItem) toggleStash(currentItem);
        }});

        btnOpenCart.addEventListener('click', () => {{
            renderCartModal();
            cartModal.classList.add('open');
        }});

        btnCloseCart.addEventListener('click', () => {{
            cartModal.classList.remove('open');
        }});

        btnClearCart.addEventListener('click', () => {{
            selectedStash.clear();
            localStorage.removeItem('dink_complete_assets');
            updateCartBadge();
            updateStashBtn();
            renderCards();
            renderCartModal();
        }});

        btnExportCart.addEventListener('click', () => {{
            const selectedItems = Array.from(selectedStash).map(id => DATABASE.find(x => x.id === id)).filter(Boolean);
            const dataStr = "data:text/json;charset=utf-8," + encodeURIComponent(JSON.stringify(selectedItems, null, 2));
            const downloadAnchor = document.createElement('a');
            downloadAnchor.setAttribute("href", dataStr);
            downloadAnchor.setAttribute("download", "dink_complete_edition_selected_assets.json");
            document.body.appendChild(downloadAnchor);
            downloadAnchor.click();
            downloadAnchor.remove();
        }});

        setupFilters();
        updateCartBadge();
        renderCards();

        if (DATABASE.length > 0) {{
            selectItem(DATABASE[0]);
        }}
    </script>
</body>
</html>
"""
    with open(OUT_HTML_PATH, 'w', encoding='utf-8') as f:
        f.write(html)
    print(f"Generated web visual database at {OUT_HTML_PATH}")

def main():
    os.makedirs(OUT_ASSETS_DIR, exist_ok=True)
    
    meta_dict = {}
    if os.path.exists(INDEX_PATH):
        with open(INDEX_PATH, 'r', encoding='utf-8') as f:
            meta_list = json.load(f)
            for m in meta_list:
                fname = m.get('filename')
                if fname:
                    meta_dict[fname] = m

    all_sequences = []

    # 1. Base Game Sprites
    print("Indexing base game canonical sprites...")
    base_seqs = scan_base_game()
    print(f"Base game: {len(base_seqs)} animation sequences indexed.")
    all_sequences.extend(base_seqs)

    # 2. DMOD Archives
    dmod_files = sorted(glob.glob(os.path.join(DMODS_DIR, "*.dmod")))
    print(f"Processing {len(dmod_files)} community D-MODs...")

    completed = 0
    total = len(dmod_files)

    def worker(path):
        return process_dmod(path, meta_dict)

    with ThreadPoolExecutor(max_workers=8) as executor:
        for dmod_seqs in executor.map(worker, dmod_files):
            completed += 1
            if dmod_seqs:
                all_sequences.extend(dmod_seqs)
            if completed % 25 == 0 or completed == total:
                print(f"Progress: [{completed}/{total}] DMODs processed... Total sequences so far: {len(all_sequences)}")

    print(f"Extraction & categorization complete! Grand total sequences indexed: {len(all_sequences)}")

    with open(OUT_JSON_PATH, 'w', encoding='utf-8') as f:
        json.dump(all_sequences, f, ensure_ascii=False, indent=2)
    print(f"Saved visual database to {OUT_JSON_PATH}")

    generate_web_database_html(all_sequences)

if __name__ == '__main__':
    main()
