#!/usr/bin/env bash
set -euo pipefail
ROOT="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")/../.." && pwd)"
REV=3f483048a63b022fca5b2636ade29f63a5a82c9f
if [[ ! -d "$ROOT/proton/.git" ]]; then
    git clone https://github.com/SethRobinson/proton.git "$ROOT/proton"
    git -C "$ROOT/proton" checkout --detach "$REV"
fi
[[ "$(git -C "$ROOT/proton" rev-parse HEAD)" == "$REV" ]] || {
    echo "Proton checkout must be at $REV; keep other work in a separate checkout." >&2
    exit 1
}
PATCH="$ROOT/switch/patches/proton-switch.patch"
if git -C "$ROOT/proton" apply --reverse --check "$PATCH" 2>/dev/null; then
    echo 'Switch patch already applied.'
else
    git -C "$ROOT/proton" apply --check "$PATCH"
    git -C "$ROOT/proton" apply "$PATCH"
fi
