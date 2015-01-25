cmake_minimum_required(VERSION 2.8)

project(Plugin)

set(APP custom_plugin )

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_definitions(-DQT_PLUGIN)
add_definitions(-DQT_NO_DEBUG)
add_definitions(-DQT_SHARED)
add_definitions(-DQDESIGNER_EXPORT_WIDGETS)

find_package(Qt4 REQUIRED QtCore QtGui QtOpenGL QtDesigner)

include( ${QT_USE_FILE} )

include_directories(${CMAKE_CURRENT_BINARY_DIR})

file(GLOB source *.cpp)
file(GLOB header *.h)

add_library(${APP} SHARED ${source} ${header})

target_link_libraries(${APP} ${QT_LIBRARIES})

# install(TARGETS ${APP} LIBRARY
#   DESTINATION ~/tmpt)
