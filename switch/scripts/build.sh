#!/usr/bin/env bash
set -euo pipefail
ROOT="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")/../.." && pwd)"
: "${DEVKITPRO:=/opt/devkitpro}"
export DEVKITPRO
if [[ -d "$ROOT/proton/.git" ]]; then
    "$ROOT/switch/scripts/prepare-proton.sh"
fi
cmake -S "$ROOT" -B "$ROOT/build-switch" \
    -DCMAKE_TOOLCHAIN_FILE="$DEVKITPRO/cmake/Switch.cmake" \
    -DCMAKE_BUILD_TYPE=Release
cmake --build "$ROOT/build-switch" --parallel "${JOBS:-2}"
