cmake_minimum_required(VERSION 3.10)
project(test_cpp)

set(app_name test_cpp)

set(CMAKE_CXX_STANDARD 11)

#include($ENV{HOME}/usr/cmake_modules/cmake_self.cmake)
#include($ENV{HOME}/usr/cmake_modules/common.cmake)

# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/lib)
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/lib)
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin)
# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/lib)
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/lib)
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin)

# find_package(Boost COMPONENTS system filesystem REQUIRED)
# include_directories(${Boost_INCLUDE_DIRS})
# link_directories(${Boost_LIBRARY_DIRS})

# include_directories(${EIGEN_INCLUDE_DIRS})

file(GLOB headers *.h *.hpp)
file(GLOB src *.cpp)

add_executable(${app_name}
${headers}
${src}
)

# target_link_libraries(${app_name} ${Boost_LIBRARIES})

# 可执行程序的后缀需要额外设置
# set_target_properties(${app_name} PROPERTIES
# DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX}
# RELEASE_POSTFIX ${CMAKE_RELEASE_POSTFIX}
# COMPILE_FLAGS "/MP")

# configure the project to set some debug parameters in VS
# configure_file(${CMAKE_SOURCE_DIR}/vs.user.in ${app_name}.vcxproj.user)

# 设置启动项目, 必须在最外层的CMAKELists.txt中设置
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${app_name})