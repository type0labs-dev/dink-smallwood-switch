#!/usr/bin/env python3
"""
translate-scripts.py - Dink Smallwood DinkC script translator using DeepSeek AI.

Translates and adapts Dink Smallwood (.c) scripts into Brazilian Portuguese (PT-BR)
with natural colloquial dubbing humor, satire, slang and jokes, while preserving
100% of DinkC syntax, engine color codes (`#, `$, `6, etc.) and variables (&level, etc.).
"""

import os
import sys
import json
import re
import glob
import argparse
import urllib.request
import urllib.error
import time

AI_CONFIG_PATH = "/home/zero/Projects/gamevault/config/ai.json"
STORY_DIR = "bin/dink/story"
STORY_PT_DIR = "bin/dink/story_pt"

SYSTEM_PROMPT = """Você é o Diretor Criativo e Mestre de Dublagem da localização brasileira definitiva do clássico RPG satírico "Dink Smallwood".
O jogo original é uma paródia ácida e hilária de RPGs clássicos (estilo Zelda/Monkey Island/South Park). Dink é um anti-herói ranzinza, folgado, boca-suja e sarcástico que detesta o trabalho na fazenda e vive reclamando da vida.

DIRETRIZ PRINCIPAL DO PROJETO: "MUITO MAIS DIVERTIDO E COM CHEIRINHO BR!"
Esqueça traduções literais, neutras, formais ou mornas. Queremos o puro estilo da melhor dublagem brasileira (estilo Borderlands, The Witcher 3, South Park, dublagens clássicas da Cinevídeo/Herbert Richers e cultura gamer BR).

EXEMPLOS DE TRANSFORMAÇÃO (SIGA RIGOROSAMENTE ESTE ESPÍRITO):
- "Dink, it is getting late! No food until you feed the pigs!"
  -> "`#Dink, já tá anoitecendo e você não vai botar uma colher na boca até dar comida pra esses porcos!"
- "Mother, how do I feed the pigs? I forgot!"
  -> "Pô mãe, como é que alimenta os bichos mesmo? Esqueci essa parada!"
- "That is very amusing, Dink. You get the sack of feed, and you sprinkle it in the pig pen. And do not tease them!"
  -> "`#Muito engraçadinho, Dink. Pega a droga do saco de ração e joga no chiqueiro. E para de atazanar os porcos!"
- "I HATE YOU!"
  -> "EU TE ODEIO, SUA CHATA!"
- "You will get over it."
  -> "`#Engole o choro que passa."
- "Except to watch you work... Is pig farming fun?"
  -> "`6Só vim ver você ralar... Cuidar de porco é divertido, ô mané?"
- "I am NOT a pig farmer."
  -> "Eu NÃO sou criador de porco, seu babaca!"
- "Bawahahahah! See you around, squirt."
  -> "`6Mwahahaha! Falou e disse, pirralho zé ruela!"
- "I *HATE* that guy!"
  -> "Nossa, como eu *DETESTO* esse desgraçado!"
- "I am a bottle, not a duck. Even though I sound like one. Funny, eh?"
  -> "Que pato o que, bicho, eu sou uma garrafa! Embora eu grasne igualzinho. Mó viagem, né?"
- "What a gyp!"
  -> "Que sacanagem! Fui tapeado na cara dura!"
- "Die, strange machine that doesn't belong here!"
  -> "Morre, troço bizarro que não devia tá aqui!"
- "Get angry for no reason"
  -> "Ficar pistola sem motivo nenhum"
- "Ethel? She's old, isn't she?"
  -> "Ethel? Ela é mó véia, né?"
- "`#The villagers are very friendly."
  -> "`#O pessoal aqui da vila é mó gente boa."
- "I don't see anything here."
  -> "Não tô vendo nada nessa droga."
- "I'm fairly sure I can't talk to or use that."
  -> "Tenho quase certeza de que não dá pra bater papo nem usar esse troço."
- "I'm gesturing wildly to no avail!"
  -> "Tô aqui gesticulando que nem um idiota à toa!"

GÍRIAS, EXPRESSÕES E VOCABULÁRIO OBRIGATÓRIOS:
Use com naturalidade: "pô", "caraca", "zé ruela", "mané", "pirralho", "que saco", "tá de sacanagem", "nem a pau", "vai catar coquinho", "mó furada", "troço esquisito", "dar ruim", "não tanko", "bicho", "moleque", "engole o choro", "ficar pistola", "se liga", "papo reto", "tá moscando", "traste", "otário", "desgraçado", "bicho burro", "cretino", "babaca", "pestinha".
Adapte trocadilhos e piadas para fazer o jogador brasileiro rir alto!

REGRAS TÉCNICAS INEGOCIÁVEIS:
1. PRESERVE EXATAMENTE qualquer prefixo de formatação/cor no início da string (ex: `# `, `$ `, `6 `, `! `, `% `, `w `, `1 `, `3 `). A crase e o símbolo DEVEM continuar no início da string traduzida!
2. PRESERVE EXATAMENTE variáveis do jogo como &current_sprite, &level, &story, &old_result, &savegameinfo, &buttoninfo, &pig_story, etc. NUNCA altere nomes de variáveis com &!
3. Se a string for apenas uma variável como "&savegameinfo", NÃO ALTERE NADA.
4. Mantenha aspas normais escapadas se necessário, sem quebrar o formato JSON.
5. Retorne APENAS um objeto JSON com as chaves correspondentes aos IDs numéricos fornecidos.
"""

def load_api_key():
    if os.path.exists(AI_CONFIG_PATH):
        try:
            with open(AI_CONFIG_PATH, "r") as f:
                cfg = json.load(f)
                return cfg.get("apiKey"), cfg.get("model", "deepseek-chat")
        except Exception as e:
            print(f"Erro ao carregar {AI_CONFIG_PATH}: {e}", file=sys.stderr)
    key = os.environ.get("DEEPSEEK_API_KEY")
    if key:
        return key, "deepseek-chat"
    return None, None

def call_deepseek(strings_dict, api_key, model="deepseek-chat", max_retries=3):
    url = "https://api.deepseek.com/chat/completions"
    user_prompt = "Traduza e adapte os seguintes diálogos/textos mantendo os IDs intactos:\n" + json.dumps(strings_dict, ensure_ascii=False, indent=2)

    payload = {
        "model": model,
        "messages": [
            {"role": "system", "content": SYSTEM_PROMPT},
            {"role": "user", "content": user_prompt}
        ],
        "response_format": {"type": "json_object"},
        "temperature": 0.7
    }

    for attempt in range(1, max_retries + 1):
        try:
            req = urllib.request.Request(
                url,
                data=json.dumps(payload).encode("utf-8"),
                headers={
                    "Content-Type": "application/json",
                    "Authorization": f"Bearer {api_key}"
                }
            )
            with urllib.request.urlopen(req, timeout=45) as resp:
                data = json.loads(resp.read().decode("utf-8"))
                content = data["choices"][0]["message"]["content"]
                parsed = json.loads(content)
                return parsed
        except Exception as e:
            print(f"  [Tentativa {attempt}/{max_retries}] Erro ao chamar DeepSeek: {e}", file=sys.stderr)
            if attempt < max_retries:
                time.sleep(2 * attempt)
            else:
                raise e

def is_translatable(s):
    s_strip = s.strip()
    if not s_strip:
        return False
    # Check if purely a variable like &savegameinfo
    if re.match(r"^&[a-zA-Z0-9_-]+$", s_strip):
        return False
    # Check if a file path or engine asset
    if "/" in s_strip or "\\" in s_strip:
        return False
    if re.search(r"\.(mid|bmp|rttex|wav|c|d)$", s_strip, re.IGNORECASE):
        return False
    if s_strip.startswith("load_sequence_now"):
        return False
    # Has letters?
    if not re.search(r"[a-zA-Z]", s_strip):
        return False
    return True

def extract_strings_from_script(code):
    """
    Finds translatable dialogue and choice strings, returning list of (start_idx, end_idx, raw_text).
    """
    entries = []

    # 1. say(...) / say_stop(...) / say_stop_npc(...) / say_stop_xy(...) / say_xy(...)
    say_pattern = re.compile(r"""(say(?:_stop|_stop_npc|_stop_xy|_xy)?\s*\(\s*)(")(.*?)(")""", re.IGNORECASE)
    for m in say_pattern.finditer(code):
        text = m.group(3)
        if is_translatable(text):
            entries.append({
                "type": "say",
                "start": m.start(3),
                "end": m.end(3),
                "text": text
            })

    # 2. choice_start() ... choice_end() blocks
    choice_blocks = list(re.finditer(r"""choice_start\s*\(\s*\);?(.*?)choice_end\s*\(\s*\);?""", code, re.DOTALL | re.IGNORECASE))
    for cb in choice_blocks:
        block_text = cb.group(1)
        block_offset = cb.start(1)

        # Title blocks inside choice
        for tb in re.finditer(r"""(title_start\s*\(\s*\);?\s*)(.*?)(\s*title_end\s*\(\s*\);?)""", block_text, re.DOTALL | re.IGNORECASE):
            raw_title = tb.group(2)
            if is_translatable(raw_title):
                entries.append({
                    "type": "title",
                    "start": block_offset + tb.start(2),
                    "end": block_offset + tb.end(2),
                    "text": raw_title
                })

        # Options: "Option text"
        for opt in re.finditer(r"""(")(.*?)(")""", block_text):
            opt_text = opt.group(2)
            if is_translatable(opt_text):
                entries.append({
                    "type": "choice",
                    "start": block_offset + opt.start(2),
                    "end": block_offset + opt.end(2),
                    "text": opt_text
                })

    # Sort entries by start offset in ascending order
    entries.sort(key=lambda x: x["start"])

    # Filter any potential overlaps
    filtered = []
    last_end = -1
    for e in entries:
        if e["start"] >= last_end:
            filtered.append(e)
            last_end = e["end"]

    return filtered

def preserve_formatting(original, translated):
    """
    Ensures engine color codes like `#, `$, `6 are kept at the start if present in original.
    """
    m_orig = re.match(r"^(`[#$!%w0-9])", original)
    if m_orig:
        prefix = m_orig.group(1)
        # If translated doesn't start with the same prefix, attach it
        m_trans = re.match(r"^(`[#$!%w0-9])", translated)
        if not m_trans:
            translated = prefix + translated
        elif m_trans.group(1) != prefix:
            translated = prefix + translated[len(m_trans.group(1)):]
    return translated

def translate_file(input_path, output_path, api_key, model="deepseek-chat", force=False):
    base_name = os.path.basename(input_path)
    if os.path.exists(output_path) and not force:
        print(f"  [Pular] {base_name} já traduzido em {output_path}")
        return True

    with open(input_path, "r", encoding="latin-1") as f:
        code = f.read()

    entries = extract_strings_from_script(code)
    if not entries:
        # Script has no translatable dialogue (pure logic). Just copy as-is!
        with open(output_path, "w", encoding="utf-8") as f:
            f.write(code)
        print(f"  [Cópia] {base_name} não contém falas (apenas lógica de jogo). Copiado direto.")
        return True

    print(f"  [Traduzindo] {base_name}: {len(entries)} falas encontradas...")
    strings_dict = {str(i): e["text"] for i, e in enumerate(entries)}

    translated_dict = call_deepseek(strings_dict, api_key, model)

    # Reconstruct code from back to front to preserve offsets
    new_code = code
    for i in reversed(range(len(entries))):
        e = entries[i]
        key = str(i)
        if key in translated_dict:
            trans_text = translated_dict[key]
            # Preserve engine color tags
            trans_text = preserve_formatting(e["text"], trans_text)
            # Make sure no unescaped inner double quotes break C syntax
            if e["type"] in ("say", "choice"):
                trans_text = trans_text.replace('"', '\\"')
            new_code = new_code[:e["start"]] + trans_text + new_code[e["end"]:]

    # Write translated file
    os.makedirs(os.path.dirname(output_path), exist_ok=True)
    with open(output_path, "w", encoding="utf-8") as f:
        f.write(new_code)

    print(f"  [Concluído] {base_name} salvo em {output_path}")
    return True

def main():
    parser = argparse.ArgumentParser(description="Tradutor de scripts Dink Smallwood via DeepSeek")
    parser.add_argument("--file", help="Traduzir um script específico (ex: bin/dink/story/s1-h1-m.c)")
    parser.add_argument("--pattern", help="Padrão de arquivos para traduzir (ex: 's1-*.c')")
    parser.add_argument("--system", action="store_true", help="Traduzir scripts de sistema e menus (escape, dinfo, lraise, savebot, etc.)")
    parser.add_argument("--chapter1", action="store_true", help="Traduzir todo o Capítulo 1: Stonebrook (s1-*.c, duck, etc.)")
    parser.add_argument("--all", action="store_true", help="Traduzir todos os scripts com falas do jogo")
    parser.add_argument("--force", action="store_true", help="Sobrescrever traduções existentes")
    args = parser.parse_args()

    api_key, model = load_api_key()
    if not api_key:
        print("ERRO: Nenhuma chave de API do DeepSeek encontrada!", file=sys.stderr)
        print("Configure em /home/zero/Projects/gamevault/config/ai.json ou defina DEEPSEEK_API_KEY.", file=sys.stderr)
        sys.exit(1)

    print(f"=== Dink Smallwood - Tradutor PT-BR (DeepSeek: {model}) ===")

    targets = []
    if args.file:
        targets.append(args.file)
    elif args.system:
        system_files = [
            "escape.c", "dinfo.c", "lraise.c", "savebot.c", "button6.c",
            "item-fst.c", "item-pig.c", "item-axe.c", "item-sw1.c", "item-sw2.c",
            "item-sw3.c", "item-b1.c", "item-b2.c", "item-b3.c", "item-fb.c",
            "item-sfb.c", "item-ice.c", "item-nut.c", "item-bom.c", "item-eli.c"
        ]
        for sf in system_files:
            p = os.path.join(STORY_DIR, sf)
            if os.path.exists(p):
                targets.append(p)
    elif args.chapter1:
        s1_files = sorted(glob.glob(os.path.join(STORY_DIR, "s1-*.c")))
        extra = ["duck.c", "findduck.c", "treeduck.c", "escape.c", "dinfo.c", "lraise.c", "savebot.c", "newgame.c"]
        for ef in extra:
            p = os.path.join(STORY_DIR, ef)
            if p not in s1_files and os.path.exists(p):
                s1_files.append(p)
        targets = s1_files
    elif args.pattern:
        targets = sorted(glob.glob(os.path.join(STORY_DIR, args.pattern)))
    elif args.all:
        targets = sorted(glob.glob(os.path.join(STORY_DIR, "*.c")))
    else:
        print("Especifique --file, --pattern, --system, --chapter1 ou --all.")
        sys.exit(1)

    print(f"Total de scripts para processar: {len(targets)}")
    success_count = 0
    for idx, t in enumerate(targets, 1):
        rel = os.path.basename(t)
        out_p = os.path.join(STORY_PT_DIR, rel)
        print(f"\n[{idx}/{len(targets)}] Processando {rel}...")
        try:
            if translate_file(t, out_p, api_key, model, force=args.force):
                success_count += 1
        except Exception as e:
            print(f"  ERRO em {rel}: {e}", file=sys.stderr)

    print(f"\nConcluído! {success_count}/{len(targets)} scripts traduzidos com sucesso em '{STORY_PT_DIR}'.")

if __name__ == "__main__":
    main()
