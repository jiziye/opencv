#!/bin/bash

build() {
    local clean="$1"; shift
    if [[ -n $clean && -e build ]]; then
        echo "Delete $(pwd)/build"
        rm -rf build
    fi
    echo "CMake in $(pwd)/build"
    if [[ ! -e build ]]; then
        mkdir build
    fi
    cd build
    cmake .. -DCMAKE_BUILD_TYPE=Release
    make
    cd ..
}

BASE_DIR="$(cd "$(dirname "$0")" && pwd)"
BASE_DIR=$(dirname "$BASE_DIR")

BUILD_CLEAN=$1

cd $BASE_DIR
build $BUILD_CLEAN
