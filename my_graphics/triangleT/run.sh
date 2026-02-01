#!/bin/bash -


FILE="shader/shader.frag.spv"

if [ -f "$FILE" ]; then
    echo "shader spv exists"
else
    glslc shaders/shader.vert -o shaders/shader.vert.spv
    glslc shaders/shader.frag -o shaders/shader.frag.spv
fi



BUILD="build"

if [ -d "$BUILD" ]; then
	cd build && make && cd ..
else
	mkdir build && cd build && cmake .. && make && cd ..
fi

./build/res