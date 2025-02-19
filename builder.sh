#!/bin/bash

./modulesBuilder.sh

mkdir build
cd build
cmake ..
make -j

