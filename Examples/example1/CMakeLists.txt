project(example1)
add_executable(example1 "src/example.cpp")
target_link_libraries(example1 Pulsar)

if(EMSCRIPTEN)
    file(COPY index.html DESTINATION ${CMAKE_BINARY_DIR})
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --embed-file ${CMAKE_SOURCE_DIR}/Examples/data@/data")
endif()
