#!/bin/bash
git commit -am "$(date '+%F %H:%M:%S')"
cmake -B build
if [ $? -eq 0 ]; then
    cmake --build build
    if [ $? -eq 0 ]; then
        build/gpu-collision-detection
    fi
fi