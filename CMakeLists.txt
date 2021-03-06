cmake_minimum_required (VERSION 2.6)
project(PulsarEngine)

option(DEBUG_MODE off)
option(EMSCRIPTEN off)
option(ENABLE_ASSIMP off)

# Check if Emscripten
if(${CMAKE_SYSTEM} STREQUAL Emscripten-1)
	option(EMSCRIPTEN on)
	option(ENABLE_ASSIMP off)
endif()

# Include directories
include_directories(include)
include_directories(lib)
include_directories(lib/glm)

# Output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Compile flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -fopenmp -Wall")
if(DEBUG_MODE)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O -g")
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -ffast-math")
endif()
if(EMSCRIPTEN)
	# see https://github.com/kripken/emscripten/blob/master/src/settings.js
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --llvm-lto 0 -s NO_EXIT_RUNTIME=1 -s USE_SDL=2 -s USE_LIBPNG=1 -s USE_ZLIB=1")
	if(NOT DEBUG_MODE)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --closure 1")
	endif()
endif()

# Switches
if(ENABLE_ASSIMP)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DENABLE_ASSIMP")
endif()

file(GLOB SOURCES "src/*.cpp")
add_library(Pulsar SHARED ${SOURCES})
target_link_libraries(Pulsar GL)
if(EMSCRIPTEN)
    set_target_properties(Pulsar PROPERTIES SUFFIX .bc)
else()
    target_link_libraries(Pulsar GLEW SDL2 png)
endif()
if(ENABLE_ASSIMP)
    target_link_libraries(Pulsar assimp)
endif()
