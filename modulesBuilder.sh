#!/bin/bash

cd Source
if ! [ -d Modules ]; then
    mkdir Modules
fi

cd Modules

STL_MODULES=("algorithm"
             "chrono"
             "concepts"
             "fstream"
             "iostream"
             "memory"
             "ranges"
             "string"
             "stdexcept"
             "thread"
             "tuple"
             "type_traits"
             "utility"
             "vector")

for module in "${STL_MODULES[@]}"; do
    pcm_file="${module}.pcm"

    if ! [ -f "$pcm_file" ]; then
        echo "Building STL $module module..."
        clang++ -std=c++20 -fmodules -xc++-system-header "$module" -o "$pcm_file"
    fi
done
cd ..

echo Finished building modules

