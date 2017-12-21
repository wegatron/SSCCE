cmake_minimum_required(VERSION 3.5)

project(boost_asio_demo)
set(CMAKE_DEBUG_POSTFIX "d" CACHE STRING "add a postfix usually d on windows")

find_package(Boost 1.65 COMPONENTS system)
set(Boost_USE_STATIC_LIBS        OFF)

add_executable(server server.cpp)

add_executable(client client.cpp)

set_target_properties(server PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})

set_target_properties(client PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})