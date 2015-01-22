cmake_minimum_required(VERSION 2.6)
set( CMAKE_AUTOMOC ON )
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package( Qt4 REQUIRED QtCore QtGui QtOpenGL)

include( ${QT_USE_FILE} )

set(ui_forms mainwindow.ui)

qt4_wrap_ui(ui_forms_header ${ui_forms})

file(GLOB source *.cpp)
file(GLOB header *.h)

add_executable(test_qt ${header} ${source} ${ui_forms_header})

target_link_libraries( test_qt
  ${QT_LIBRARIES}
  )