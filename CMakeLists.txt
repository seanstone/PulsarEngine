cmake_minimum_required (VERSION 2.6)

option(DEBUG_MODE off)
option(EMSCRIPTEN off)
option(ENABLE_ASSIMP off)

# Check if Emscripten
if(${CMAKE_SYSTEM} STREQUAL Emscripten-1)
	option(EMSCRIPTEN on)
	option(ENABLE_ASSIMP off)
endif()

# Include directories
include_directories(Pulsar/include)
include_directories(lib)

# Output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
if(EMSCRIPTEN)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
else()
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
endif()

# Compile flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}-std=c++14 -fopenmp -Wall")
if(DEBUG_MODE)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O -g")
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -ffast-math")
endif()
if(EMSCRIPTEN)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s USE_SDL=2 -s USE_LIBPNG=1")
	if(NOT DEBUG_MODE)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --closure 1")
	endif()
endif()

# Switches
if(ENABLE_ASSIMP)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DENABLE_ASSIMP")
endif()

add_subdirectory(Pulsar)
add_subdirectory(Examples)
