project(example1)
add_executable(example1 "src/example.cpp")
target_link_libraries(example1 Pulsar)

if(EMSCRIPTEN)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --preload-file ${CMAKE_SOURCE_DIR}/Examples/data@/data")
endif()
