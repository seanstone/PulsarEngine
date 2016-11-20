add_subdirectory(example1)

# Copy data
if(NOT EMSCRIPTEN)
    file(COPY data DESTINATION ${CMAKE_BINARY_DIR})
endif()
