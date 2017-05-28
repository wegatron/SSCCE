cmake_minimum_required(VERSION 3.0)

project(test_qml)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_DEBUG_POSTFIX "d" CACHE STRING "add a postfix, usually d on windows")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib) # static library
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib) # dynamic library
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin) # executable

set(qt_dir D:/win_exe/qt/5.8/msvc2015_64)
set(CMAKE_PREFIX_PATH ${qt_dir})

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Find the Qt libraries for Qt Quick/QML
find_package(Qt5Core CONFIG REQUIRED Qml Quick Gui)
find_package(Qt5Quick)
find_package(Qt5OpenGL)
find_package(Qt5Qml)
find_package(Qt5Gui)

include_directories(${Qt5Core_INCLUDE_DIRS})
include_directories(${Qt5OpenGL_INCLUDE_DIRS})
include_directories(${Qt5Quick_INCLUDE_DIRS})
include_directories(${Qt5Network_INCLUDE_DIRS})

file(GLOB headers *.h)
file(GLOB sources *.cpp)
file(GLOB qml_files *.qml)
file(GLOB resources *.qrc)

add_executable(test_qml ${headers} ${sources} ${qml_files} ${resources})

target_link_libraries(test_qml
Qt5::Core
Qt5::Qml
Qt5::Quick
)