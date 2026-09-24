#!/usr/bin/env python3
"""
Download all 393 DMODs from dinknetwork.com into research/dmods/
Multi-threaded, resumable, with progress logging.
"""
import os, sys, json, time, urllib.request
from concurrent.futures import ThreadPoolExecutor, as_completed

TARGET_DIR = "research/dmods"
JSON_SOURCE = "switch/distribution/dmods_all.json"
MAX_WORKERS = 6

os.makedirs(TARGET_DIR, exist_ok=True)

dmods = json.load(open(JSON_SOURCE, "r", encoding="utf-8"))
total = len(dmods)

print(f"Iniciando download dos {total} DMODs para '{TARGET_DIR}' com {MAX_WORKERS} threads...")

completed_count = 0
failed = []
downloaded_bytes = 0

def download_item(item):
    title = item["title"]
    url = item["url"]
    filename = url.split("/")[-1]
    if not filename.endswith(".dmod"):
        filename += ".dmod"
    dest = os.path.join(TARGET_DIR, filename)
    
    # Check if already downloaded and has content
    expected_bytes = int(item["size"] * 1024 * 1024)
    if os.path.exists(dest) and os.path.getsize(dest) > 1000:
        actual_size = os.path.getsize(dest)
        # If within 5% of expected size or greater than 50KB, assume complete
        if actual_size >= expected_bytes * 0.9 or actual_size > 10000:
            return (True, title, filename, actual_size, True)
            
    for attempt in range(3):
        try:
            req = urllib.request.Request(url, headers={"User-Agent": "DinkHD-Research-Tool/1.0"})
            with urllib.request.urlopen(req, timeout=30) as response, open(dest, "wb") as out:
                data = response.read()
                out.write(data)
                return (True, title, filename, len(data), False)
        except Exception as e:
            if attempt == 2:
                return (False, title, filename, str(e), False)
            time.sleep(1.5)
            
    return (False, title, filename, "Unknown error", False)

start_time = time.time()

with ThreadPoolExecutor(max_workers=MAX_WORKERS) as executor:
    futures = {executor.submit(download_item, item): item for item in dmods}
    for future in as_completed(futures):
        success, title, filename, info, skipped = future.result()
        completed_count += 1
        if success:
            if skipped:
                print(f"[{completed_count}/{total}] [Já existe] {title} ({info/(1024*1024):.1f} MB)", flush=True)
            else:
                downloaded_bytes += info
                print(f"[{completed_count}/{total}] [Baixado] {title} ({info/(1024*1024):.1f} MB)", flush=True)
        else:
            failed.append((title, filename, info))
            print(f"[{completed_count}/{total}] [FALHA] {title}: {info}", flush=True)

elapsed = time.time() - start_time
print(f"\nConcluído em {elapsed:.1f}s!")
print(f"Sucessos: {total - len(failed)}/{total}")
if failed:
    print(f"Falhas ({len(failed)}):")
    for f in failed:
        print("  -", f[0], f[1], f[2])

# Write index
index_data = []
for item in dmods:
    url = item["url"]
    filename = url.split("/")[-1]
    if not filename.endswith(".dmod"):
        filename += ".dmod"
    dest = os.path.join(TARGET_DIR, filename)
    exists = os.path.exists(dest)
    sz = os.path.getsize(dest) if exists else 0
    index_data.append({
        "title": item["title"],
        "author": item["author"],
        "rating": item["rating"],
        "desc": item["desc"],
        "filename": filename,
        "path": dest,
        "size_bytes": sz,
        "downloaded": exists
    })

with open("research/dmods_index.json", "w", encoding="utf-8") as f:
    json.dump(index_data, f, indent=2, ensure_ascii=False)

print(f"Índice salvo em 'research/dmods_index.json'")
