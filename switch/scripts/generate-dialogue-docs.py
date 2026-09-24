#!/usr/bin/env python3
"""
Generate complete markdown script documentation for Dink Smallwood HD:
- ROTEIRO_ORIGINAL_EN.md
- ROTEIRO_TRADUCAO_PTBR.md
- COMPARATIVO_TRADUCAO.md
"""
import os, glob, re

ORIG_DIR = "bin/dink/story"
PT_DIR = "bin/dink/story_pt"

SCRIPT_DESCRIPTIONS = {
    # Intro
    "start.c": "Inicialização do Jogo e Atributos Iniciais",
    "start-1.c": "Introdução: Abertura e Narração Inicial",
    "start-2.c": "Introdução: O Reino e os Perigos",
    "start-3.c": "Introdução: A Chegada a Stonebrook",
    
    # Chapter 1: Stonebrook
    "s1-mom.c": "Mãe de Dink no Vilarejo",
    "s1-h1-m.c": "Mãe dentro da Casa de Dink",
    "s1-pig.c": "Os Porcos de Dink no Chiqueiro",
    "s1-feed.c": "Ração dos Porcos",
    "s1-eth.c": "Dona Rita na Vila",
    "s1-ethp.c": "Casa da Dona Rita (O Pato Perdido)",
    "s1-duck.c": "O Pato Perdido de Rita (Quaquá)",
    "s1-duck2.c": "Pato no Chiqueiro",
    "s1-jack.c": "Jack (O Trapaceiro de Apostas)",
    "s1-wand.c": "Viajante na Estrada de Stonebrook",
    "s1-sign1.c": "Placa: Entrada de Stonebrook",
    "s1-sign2.c": "Placa: Caminho para Goodheart e Terris",
    "s1-sign3.c": "Placa: Chiqueiro dos Porcos",
    "s1-h2-o.c": "Vizinho Rabugento na Casa",
    "s1-h3-8.c": "Mulher na Casa dos Fundos",
    "s1-nut.c": "Coleta das Nozes de AlkTree na Floresta",
    "s1-fire.c": "Incêndio em Stonebrook: Ataque dos Monstros",
    "s1-deadm.c": "A Morte da Mãe de Dink nos Escombros",
    
    # Chapter 2: Terris
    "s2-cave.c": "Caverna: Prisioneiro Atrás da Estátua Mágica",
    "s2-cave2.c": "Caverna: Emboscada dos 3 Agentes do Cast e Morte do Prisioneiro",
    "s2-mdoor.c": "Porta do Mago em Terris (Pedindo Ajuda)",
    "s2-mh-m.c": "Mago dentro de Casa em Terris",
    "s2-bar.c": "Taberna de Terris (Boatos e Bebidas)",
    "s2-ca-g.c": "Guardas do Castelo Goodheart",
    "s2-ca-o.c": "Guarda do Portão do Castelo",
    "s2-signe.c": "Placa: Floresta Murkwood (Selada)",
    "s2-jack.c": "Jack em Terris (Novo Esquema)",
    "s2-auntp.c": "Tia de Dink em Terris",
    
    # Chapter 3: KernSin
    "s3-mayor.c": "Prefeito de KernSin e a Invasão do Cast",
    "s3-chick.c": "Garota das Galinhas / Fofocas de KernSin",
    "s3-bar.c": "Bar de KernSin",
    "s3-mog.c": "Confronto com o Emissário dos Goblins",
    "s3-sign1.c": "Placa Central de KernSin",
    
    # Chapter 4: Goblins
    "en-gmog.c": "Rei dos Goblins Mog no Santuário",
    "s4-sign1.c": "Placa: Território dos Goblins",
    
    # Chapter 5: Windemere
    "dam-icee.c": "Windemere: Resgate do Prisioneiro no Gelo",
    "s5-sign1.c": "Placa: Entrada de Windemere",
    
    # Chapter 6: Darklands
    "s6-st1p.c": "Encontro com Criaturas nas Terras Sombrias",
    "s6-vend.c": "Mercador Misterioso nas Terras Sombrias",
    
    # Chapter 7: Endgame
    "s7-mil.c": "Milder Flatstomp Ferido e a Revelação de Seth",
    "s7-boss.c": "Batalha Final contra o Grande Tirano Seth",
    "king.c": "Rei Daniel: Missão nas Terras Sombrias e Vitória Final",
}

def clean_code(text):
    if len(text) >= 2 and text[0] == '`':
        return text[2:].strip()
    return text.strip()

def get_speaker(target, text, filename, lang="pt"):
    t = target.strip()
    if t == '1':
        return "Dink"
    if '&evil' in t:
        return "Agente do Cast" if lang == "pt" else "Cast Agent"
    if '&dude' in t:
        if 'cave' in filename:
            return "Prisioneiro" if lang == "pt" else "Prisoner"
        return "Aldeão" if lang == "pt" else "Townsperson"
    
    fn = filename.lower()
    if 'mom' in fn or 'h1-m' in fn or 'deadm' in fn:
        return "Mãe" if lang == "pt" else "Mother"
    if 'king' in fn:
        return "Rei Daniel" if lang == "pt" else "King Daniel"
    if 'sign' in fn or 'post' in fn or 'vil2' in fn:
        return "Placa" if lang == "pt" else "Sign"
    if 'duck' in fn:
        return "Pato" if lang == "pt" else "Duck"
    if 'pig' in fn:
        return "Porco" if lang == "pt" else "Pig"
    if 'eth' in fn:
        return "Dona Rita" if lang == "pt" else "Aunt Ethel"
    if 'jack' in fn:
        return "Jack"
    if 'bar' in fn or 'vend' in fn or 'store' in fn or 'shop' in fn or 'boot' in fn:
        return "Comerciante / Taberneiro" if lang == "pt" else "Shopkeeper / Barkeep"
    if 'wiz' in fn or 'mh-m' in fn or 'mdoor' in fn:
        return "Mago" if lang == "pt" else "Wizard"
    if 'boss' in fn or ('s7-mil' in fn and '`%' in text):
        return "Seth"
    if 'mil' in fn:
        return "Milder Flatstomp"
    if 'mog' in fn:
        return "Rei Goblin Mog" if lang == "pt" else "Goblin King Mog"
    if 'mayor' in fn:
        return "Prefeito" if lang == "pt" else "Mayor"
    if 'guard' in fn or 'ca-g' in fn or 'ca-o' in fn:
        return "Guarda" if lang == "pt" else "Guard"
    
    # Fallback to color code
    if text.startswith("`#"):
        return "Mulher / Mãe" if lang == "pt" else "Woman / Mother"
    if text.startswith("`0"):
        return "Mago / Ancião" if lang == "pt" else "Wizard / Elder"
    if text.startswith("`2"):
        return "Guarda / Cavaleiro" if lang == "pt" else "Guard / Knight"
    if text.startswith("`4"):
        return "Vilão / Inimigo" if lang == "pt" else "Villain / Enemy"
    if text.startswith("`5"):
        return "Aldeão" if lang == "pt" else "Villager"
    if text.startswith("`6"):
        return "Nobre / Narrador" if lang == "pt" else "Noble / Narrator"
    if text.startswith("`%"):
        return "Narrador / Placa" if lang == "pt" else "Narrator / Sign"
    
    return "NPC"

def parse_script_dialogues(path):
    if not os.path.exists(path):
        return []
    lines = open(path, "r", encoding="utf-8", errors="replace").readlines()
    entries = []
    in_choice = False
    choice_options = []
    for l in lines:
        code = l.split("//")[0].strip()
        if "choice_start" in code:
            in_choice = True
            choice_options = []
            continue
        if "choice_end" in code:
            in_choice = False
            entries.append(("CHOICE", choice_options, ""))
            continue
        if in_choice:
            m = re.search(r"\"([^\"]+)\"", code)
            if m:
                choice_options.append(m.group(1))
            continue
        
        m = re.search(r"(?:say|say_stop|say_xy|say_stop_xy)\s*\(\s*\"([^\"]*)\"(?:\s*,\s*([^);]+))?\)", code)
        if m:
            text = m.group(1)
            target = m.group(2).strip() if m.group(2) else ""
            entries.append(("SAY", text, target))
    return entries

def get_chapter(fn):
    if fn.startswith("start") or fn.startswith("intro") or fn.startswith("title"):
        return "00_intro", "Prólogo e Introdução"
    if fn.startswith("s1-"):
        return "01_stonebrook", "Capítulo 1: Stonebrook (A Vila de Dink)"
    if fn.startswith("s2-"):
        return "02_terris", "Capítulo 2: Terris, Caverna e Castelo Goodheart"
    if fn.startswith("s3-") or fn.startswith("ch3"):
        return "03_kernsin", "Capítulo 3: KernSin e o Culto do Cast"
    if fn.startswith("s4-") or fn.startswith("en-g") or "mog" in fn:
        return "04_goblins", "Capítulo 4: Santuário dos Goblins"
    if fn.startswith("s5-") or fn.startswith("dam-"):
        return "05_windemere", "Capítulo 5: Windemere e Montanhas de Gelo"
    if fn.startswith("s6-"):
        return "06_darklands", "Capítulo 6: As Terras Sombrias (Darklands)"
    if fn.startswith("s7-") or fn == "king.c":
        return "07_endgame", "Capítulo 7: Castelo da Perdição, Seth e Epílogo"
    if fn.startswith("s8-"):
        return "08_eastereggs", "Capítulo 8: Segredos e Easter Eggs"
    if fn.startswith("item-") or fn.startswith("get-"):
        return "09_items", "Itens e Magias"
    return "10_outros", "Cenários e NPCs Secundários"

def main():
    files = sorted(glob.glob(f"{ORIG_DIR}/*.c"))
    chapters = {}
    
    for f in files:
        fn = os.path.basename(f)
        orig_entries = parse_script_dialogues(f)
        if not orig_entries:
            continue
        pt_entries = parse_script_dialogues(os.path.join(PT_DIR, fn))
        
        c_id, c_title = get_chapter(fn)
        if c_id not in chapters:
            chapters[c_id] = (c_title, [])
        chapters[c_id][1].append((fn, orig_entries, pt_entries))

    # 1. Generate ROTEIRO_TRADUCAO_PTBR.md
    with open("ROTEIRO_TRADUCAO_PTBR.md", "w", encoding="utf-8") as f_pt:
        f_pt.write("# 🇧🇷 Dink Smallwood HD — Roteiro Completo Traduzido (Estilo Dublagem BR)\n\n")
        f_pt.write("> **Guia de Leitura e Revisão**:\n")
        f_pt.write("> Todos os diálogos, placas e opções do jogo traduzidos com humor, sátira e gírias brasileiras de dublagem clássica.\n")
        f_pt.write("> Para alterar qualquer fala, anote o nome do arquivo (ex: `s2-cave2.c`) e a sugestão!\n\n")
        
        for c_id in sorted(chapters):
            c_title, scripts = chapters[c_id]
            f_pt.write(f"\n---\n\n# {c_title}\n\n")
            for fn, orig_entries, pt_entries in scripts:
                desc = SCRIPT_DESCRIPTIONS.get(fn, "")
                header = f"### 📁 `{fn}`" + (f" — {desc}" if desc else "")
                f_pt.write(f"{header}\n\n")
                
                for entry in pt_entries:
                    kind = entry[0]
                    if kind == "CHOICE":
                        f_pt.write("> **[Escolha do Jogador]:**\n")
                        for idx, opt in enumerate(entry[1], 1):
                            f_pt.write(f"> - `{idx}`: *\"{clean_code(opt)}\"*\n")
                        f_pt.write(">\n")
                    elif kind == "SAY":
                        text = entry[1]
                        target = entry[2] if len(entry) > 2 else ""
                        speaker = get_speaker(target, text, fn, lang="pt")
                        clean = clean_code(text)
                        if clean:
                            f_pt.write(f"> **{speaker}:** {clean}  \n")
                f_pt.write("\n")

    # 2. Generate ROTEIRO_ORIGINAL_EN.md
    with open("ROTEIRO_ORIGINAL_EN.md", "w", encoding="utf-8") as f_en:
        f_en.write("# 🇺🇸 Dink Smallwood HD — Complete Original Dialogue Script (English)\n\n")
        f_en.write("> **Reference Script**:\n")
        f_en.write("> The original 1997 Seth Robinson dialogue lines and choices for comparison.\n\n")
        
        for c_id in sorted(chapters):
            c_title, scripts = chapters[c_id]
            f_en.write(f"\n---\n\n# {c_title}\n\n")
            for fn, orig_entries, pt_entries in scripts:
                desc = SCRIPT_DESCRIPTIONS.get(fn, "")
                header = f"### 📁 `{fn}`" + (f" — {desc}" if desc else "")
                f_en.write(f"{header}\n\n")
                
                for entry in orig_entries:
                    kind = entry[0]
                    if kind == "CHOICE":
                        f_en.write("> **[Player Choice]:**\n")
                        for idx, opt in enumerate(entry[1], 1):
                            f_en.write(f"> - `{idx}`: *\"{clean_code(opt)}\"*\n")
                        f_en.write(">\n")
                    elif kind == "SAY":
                        text = entry[1]
                        target = entry[2] if len(entry) > 2 else ""
                        speaker = get_speaker(target, text, fn, lang="en")
                        clean = clean_code(text)
                        if clean:
                            f_en.write(f"> **{speaker}:** {clean}  \n")
                f_en.write("\n")

    # 3. Generate COMPARATIVO_TRADUCAO.md
    with open("COMPARATIVO_TRADUCAO.md", "w", encoding="utf-8") as f_comp:
        f_comp.write("# 🔄 Dink Smallwood HD — Comparativo Completo (Original vs Dublagem BR)\n\n")
        f_comp.write("> **Formato Comparativo Cena a Cena**:\n")
        f_comp.write("> Cada cena traz primeiro o bloco em inglês original e logo abaixo o bloco traduzido em estilo dublagem brasileira.\n\n")
        
        for c_id in sorted(chapters):
            c_title, scripts = chapters[c_id]
            f_comp.write(f"\n---\n\n# {c_title}\n\n")
            for fn, orig_entries, pt_entries in scripts:
                desc = SCRIPT_DESCRIPTIONS.get(fn, "")
                header = f"## 📁 `{fn}`" + (f" — {desc}" if desc else "")
                f_comp.write(f"{header}\n\n")
                
                f_comp.write("#### 🇺🇸 Original (Inglês)\n")
                for entry in orig_entries:
                    kind = entry[0]
                    if kind == "CHOICE":
                        f_comp.write("> **[Player Choice]:**\n")
                        for idx, opt in enumerate(entry[1], 1):
                            f_comp.write(f"> - `{idx}`: *\"{clean_code(opt)}\"*\n")
                        f_comp.write(">\n")
                    elif kind == "SAY":
                        text = entry[1]
                        target = entry[2] if len(entry) > 2 else ""
                        speaker = get_speaker(target, text, fn, lang="en")
                        clean = clean_code(text)
                        if clean:
                            f_comp.write(f"> **{speaker}:** {clean}  \n")
                
                f_comp.write("\n#### 🇧🇷 Tradução PT-BR (Dublagem)\n")
                for entry in pt_entries:
                    kind = entry[0]
                    if kind == "CHOICE":
                        f_comp.write("> **[Escolha do Jogador]:**\n")
                        for idx, opt in enumerate(entry[1], 1):
                            f_comp.write(f"> - `{idx}`: *\"{clean_code(opt)}\"*\n")
                        f_comp.write(">\n")
                    elif kind == "SAY":
                        text = entry[1]
                        target = entry[2] if len(entry) > 2 else ""
                        speaker = get_speaker(target, text, fn, lang="pt")
                        clean = clean_code(text)
                        if clean:
                            f_comp.write(f"> **{speaker}:** {clean}  \n")
                f_comp.write("\n")

    print("Gerados com sucesso:")
    print(" - ROTEIRO_TRADUCAO_PTBR.md")
    print(" - ROTEIRO_ORIGINAL_EN.md")
    print(" - COMPARATIVO_TRADUCAO.md")

if __name__ == "__main__":
    main()
