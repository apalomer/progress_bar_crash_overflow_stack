cmake_minimum_required(VERSION 3.0)

project(progress_bar)

if (UNIX)
  add_compile_options(-Wall -Wextra)
endif()

# Find LIbrary
find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets)
# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)

# Create threadedworker library
add_library(threadedworker SHARED src/threadedworker.cpp src/threadedworker.h)
target_link_libraries(threadedworker Qt5::Core Qt5::Widgets )
target_compile_definitions(threadedworker PRIVATE THREADWORKER)

# Create mainwindow library
add_library(mainwindow SHARED src/mainwindow.cpp src/mainwindow.h src/mainwindow.ui)
target_link_libraries(mainwindow threadedworker)
target_compile_definitions(mainwindow PRIVATE MAINWINDOW)

# Executable example
add_executable(progress_bar src/progress_bar_main.cpp)
target_link_libraries(progress_bar mainwindow)
