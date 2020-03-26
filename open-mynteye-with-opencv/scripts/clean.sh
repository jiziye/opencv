#!/bin/bash

BASE_DIR="$(cd "$(dirname "$0")" && pwd)"
BASE_DIR=$(dirname "$BASE_DIR")

find "$BASE_DIR" -iname "build" -type d -print0 | while IFS= read -r -d "" subdir; do
    if [[ $subdir == $BASE_DIR* ]]; then
        echo "Remove $subdir"
        rm -rf "$subdir"
    fi
done
