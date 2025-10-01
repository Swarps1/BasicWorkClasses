cmake_minimum_required(VERSION 3.10)
project(HexProject)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_library(hex
    src/hex_main.cpp
    src/hex_arith.cpp
    src/vector.cpp
)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(hex_test
    test/hex_test.cpp
)

target_link_libraries(hex_test hex ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} pthread)

add_executable(hex_demo
    test/main.cpp
)

target_link_libraries(hex_demo hex)