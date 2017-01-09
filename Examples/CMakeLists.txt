add_subdirectory(example1)

# Copy data
if(EMSCRIPTEN)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --preload-file ${CMAKE_SOURCE_DIR}/Examples/data@/data")
endif()
