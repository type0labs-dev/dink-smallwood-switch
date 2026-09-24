#!/usr/bin/env python3
"""
Sync edits made in COMPARATIVO_TRADUCAO.md back into bin/dink/story_pt/*.c,
preserving engine color codes (`#, `0, `2, `4, etc.) and applying requested name changes.
"""
import re, os, glob

COMP_FILE = "COMPARATIVO_TRADUCAO.md"
PT_DIR = "bin/dink/story_pt"

NAME_MAP = [
    (r"\bQuackers\b", "Quaquá"),
    (r"\bQUACKERS\b", "QUAQUÁ"),
    (r"\bEthel\b", "Rita"),
    (r"\bETHEL\b", "RITA"),
]

def apply_names(text):
    for pattern, repl in NAME_MAP:
        text = re.sub(pattern, repl, text)
    return text

def main():
    comp = open(COMP_FILE, "r", encoding="utf-8").read()
    sections = re.split(r"^## 📁 `([^`]+)`", comp, flags=re.M)
    
    updated_files = 0
    total_strings_updated = 0
    
    for i in range(1, len(sections), 2):
        fn = sections[i].strip()
        sec_content = sections[i+1]
        
        pt_parts = sec_content.split("#### 🇧🇷 Tradução PT-BR (Dublagem)")
        if len(pt_parts) < 2:
            continue
        pt_block = pt_parts[1]
        
        pt_lines = []
        for l in pt_block.strip().splitlines():
            l = l.strip()
            if l.startswith("> **") and ":**" in l:
                if "> **[Escolha do Jogador]:**" in l:
                    continue
                m = re.search(r"^>\s*\*\*([^*]+):\*\*\s*(.*)", l)
                if m:
                    text = m.group(2).rstrip()
                    pt_lines.append(apply_names(text))
            elif l.startswith("> - `"):
                m = re.search(r"\*\"([^\"]+)\"\*", l)
                if m:
                    text = m.group(1).rstrip()
                    pt_lines.append(apply_names(text))
        
        pt_file = os.path.join(PT_DIR, fn)
        if not os.path.exists(pt_file):
            continue
            
        file_lines = open(pt_file, "r", encoding="utf-8", errors="replace").readlines()
        new_file_lines = []
        file_idx = 0
        in_choice = False
        file_changed = False
        
        for line in file_lines:
            code = line.split("//")[0]
            if "choice_start" in code:
                in_choice = True
                new_file_lines.append(line)
                continue
            if "choice_end" in code:
                in_choice = False
                new_file_lines.append(line)
                continue
            if in_choice:
                m = re.search(r"(\"[^\"]+\")", line)
                if m and file_idx < len(pt_lines):
                    target_text = pt_lines[file_idx]
                    file_idx += 1
                    curr_quote = m.group(1)
                    curr_text = curr_quote[1:-1]
                    target_text = apply_names(target_text)
                    if curr_text != target_text:
                        line = line.replace(curr_quote, f"\"{target_text}\"")
                        file_changed = True
                        total_strings_updated += 1
                new_file_lines.append(line)
                continue
            
            # Match say/say_stop/say_xy/say_stop_xy
            m = re.search(r"((?:say|say_stop|say_xy|say_stop_xy)\s*\(\s*\")([^\"]*)(\"[^);]*\);?)", line)
            if m and file_idx < len(pt_lines):
                prefix = m.group(1)
                curr_text = m.group(2)
                suffix = m.group(3)
                target_text = pt_lines[file_idx]
                file_idx += 1
                
                # Preserve color code
                color = ""
                if len(curr_text) >= 2 and curr_text[0] == "`":
                    color = curr_text[:2]
                
                # Apply name replacements
                target_text = apply_names(target_text)
                
                # Strip duplicate color if present in target_text
                if len(target_text) >= 2 and target_text[0] == "`":
                    new_text = target_text
                else:
                    new_text = color + target_text
                
                if curr_text != new_text:
                    line = line.replace(f"{prefix}{curr_text}{suffix}", f"{prefix}{new_text}{suffix}")
                    file_changed = True
                    total_strings_updated += 1
            new_file_lines.append(line)
            
        if file_changed:
            with open(pt_file, "w", encoding="utf-8") as f_out:
                f_out.writelines(new_file_lines)
            updated_files += 1
            print(f"  [Atualizado] {fn}")
            
    print(f"\nSincronização concluída: {updated_files} arquivos atualizados, {total_strings_updated} falas modificadas.")

if __name__ == "__main__":
    main()
