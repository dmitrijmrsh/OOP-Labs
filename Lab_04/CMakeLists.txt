cmake_minimum_required(VERSION 3.10)

project(Lab_04)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(main main.cpp)

enable_testing()
add_executable(testing test/test.cpp)
target_link_libraries(testing ${GTEST_LIBRARIES})
add_test(NAME BASIC COMMAND testing)