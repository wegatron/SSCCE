cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)

include(common.cmake)

set(CMAKE_DEBUG_POSTFIX _${COMPILER}_${BITS}d)
set(CMAKE_RELEASE_POSTFIX _${COMPILER}_${BITS})

add_executable(test_io zsw_clock.h main.cpp)

set_target_properties(test_io PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX}
RELEASE_POSTFIX ${CMAKE_RELEASE_POSTFIX}
)