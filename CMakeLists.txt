cmake_minimum_required(VERSION 3.15)
project(Calculator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_library(calculator_lib STATIC
    src/Tokenizer.cpp
    src/Parser.cpp
)

target_include_directories(calculator_lib PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

add_executable(calculator_cmd src/main.cpp)

target_link_libraries(calculator_cmd PRIVATE calculator_lib)

enable_testing()
add_subdirectory(test)