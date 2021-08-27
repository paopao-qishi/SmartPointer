cmake_minimum_required(VERSION 3.5)
project(SharedPointer)

option(DEBUG "Enable debug mode build." OFF)
option(RELEASE "Enable release mode build." OFF)

set(CMAKE_CXX_FLAGS "-m64 -std=c++17 -Wall -Werror")

if (NOT DEBUG AND NOT RELEASE)
    message("*** Enabling DEBUG mode by default ***")
    set(DEBUG ON)
endif ()

if (DEBUG)
    message("*** Building in DEBUG mode ***")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0")
elseif (RELEASE)
    message("*** Building in RELEASE mode ***")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -DNDEBUG")
endif ()

add_subdirectory(test)