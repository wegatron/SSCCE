cmake_minimum_required(VERSION 3.10)
project(GraphSlam3DTool_V2)

set(CMAKE_CXX_STANDARD 14)

set(app_name GraphSlam3DTool_V2)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

include(cmake_self.cmake)
include(common.cmake)
set(CMAKE_DEBUG_POSTFIX _${COMPILER}_${BITS}d)
set(CMAKE_RELEASE_POSTFIX _${COMPILER}_${BITS})

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin)

set(root_src_dir ${CMAKE_CURRENT_SOURCE_DIR}/../..)

#for openmp
#find_package(OpenMP)
#if(OPENMP_FOUND)
#    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS} /MP")
#    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
#endif()

#boost
find_package(Boost COMPONENTS system filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

#eigen
include_directories(${EIGEN_INCLUDE_DIRS})

#qt
find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

#vtk
find_package(VTK REQUIRED)
include_directories(${VTK_INCLUDE_DIRS} SourceFile ${root_src_dir}/Sensor/)

#flann
find_package(FLANN REQUIRED)
include_directories(${FLANN_INCLUDE_DIRS})

#pcl
find_package(PCL 1.8 REQUIRED COMPONENTS common features filters kdtree ml octree registration io segmentation visualization)
include_directories(${PCL_INCLUDE_DIRS})
add_definitions(${PCL_DEFINITIONS})

#g2o
find_package(G2O REQUIRED)
include_directories(${G2O_INCLUDE_DIR})
include_directories(${G2O_INCLUDE_DIR}/g2o/EXTERNAL/csparse)

# utils libs
include(common_lib.cmake)

file(GLOB graph_build_h SourceFile/GraphBuild/*.h)
source_group(headers\\GraphBuild FILES ${graph_build_h})
file(GLOB graph_build_src SourceFile/GraphBuild/*.cpp)
source_group(src\\GraphBuild FILES ${graph_build_src})

add_executable(${app_name} ...)

target_link_libraries(${app_name}
ComUtils
PoseUtils
SensorDataFrame
${Boost_LIBRARIES}
${VTK_LIBRARIES}
${PCL_LIBRARIES}
${FLANN_LIBRARIES}
${G2O_LIBRARIES}
Qt5::Core Qt5::Gui Qt5::Widgets
)

set_target_properties(${app_name} PROPERTIES
DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX}
RELEASE_POSTFIX ${CMAKE_RELEASE_POSTFIX}
COMPILE_FLAGS "/MP")

# configure the project to set some debug parameters in VS
configure_file(${CMAKE_SOURCE_DIR}/vs.user.in ${app_name}.vcxproj.user)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${app_name})

install(TARGETS ${app_name} RUNTIME DESTINATION .)
install(CODE 
"include(BundleUtilities)
fixup_bundle(${CMAKE_INSTALL_PREFIX}/${app_name}_${COMPILER}_${BITS}.exe \"\" \"${Boost_LIBRARY_DIRS};${FLANN_ROOT}/bin;${G2O_ROOT}/bin;${ACTIVE_QT_DIR}/bin;D:/usr/pcl1.8.1/bin;d:/usr/Qhull/bin;D:/usr/OpenNI2/Tools\")")
