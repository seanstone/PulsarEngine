project(example1)
add_executable(example1 "src/example.cpp")
target_link_libraries(example1 Pulsar)

if(EMSCRIPTEN)
    file(COPY index.html DESTINATION ${CMAKE_BINARY_DIR})
endif()
