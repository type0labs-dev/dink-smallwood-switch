import urllib.request, re, json, time

CATS = [
    "epic", "quest", "romp", "development", "addon", 
    "graphics", "music", "cheat", "source"
]

cat_map = {}

for c in CATS:
    page = 1
    cat_map[c] = []
    while True:
        if page == 1:
            url = f"https://www.dinknetwork.com/files/category_{c}/"
        else:
            url = f"https://www.dinknetwork.com/files/category_{c}/sort_title-asc/page_{page}/"
        req = urllib.request.Request(url, headers={"User-Agent": "Mozilla/5.0"})
        try:
            html = urllib.request.urlopen(req, timeout=10).read().decode("utf-8", errors="replace")
        except Exception as e:
            print(f"Error fetching {url}: {e}")
            break
            
        matches = re.findall(r"<a href=\"/file/([^\"]+)/\">([^<]+)</td>", html)
        if not matches:
            break
        for slug, title in matches:
            cat_map[c].append({"slug": slug, "title": title.strip()})
            
        # Check if there is a next page link
        if f"/page_{page+1}/" not in html:
            break
        page += 1
        time.sleep(0.15)
        
    print(f"Category [{c}]: {len(cat_map[c])} files found across {page} pages.")

with open("switch/distribution/dmod_categories.json", "w", encoding="utf-8") as f:
    json.dump(cat_map, f, indent=2, ensure_ascii=False)
