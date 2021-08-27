cmake_minimum_required(VERSION 3.5)
project(SharedPointerTest)

file(GLOB SOURCES "*.cc")

add_executable(test ${SOURCES})
target_include_directories(test PUBLIC "..")
target_link_libraries(test gtest pthread)