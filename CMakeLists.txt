cmake_minimum_required(VERSION 3.10)
project(HexProject)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR}/include)

# Основная программа
add_executable(hex test/main.cpp src/hex.cpp)

# Для тестов
find_package(GTest REQUIRED)
add_executable(hex_tests test/hex_test.cpp src/hex.cpp)
target_link_libraries(hex_tests GTest::GTest pthread)
enable_testing()
add_test(NAME HexTests COMMAND hex_tests)