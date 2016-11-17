#/bin/bash
mkdir -p build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=/usr/lib/emscripten/cmake/Modules/Platform/Emscripten.cmake
