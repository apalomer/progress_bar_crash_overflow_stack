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

#OPENMP
find_package(OpenMP REQUIRED)
if(OPENMP_FOUND)
 message("OPENMP FOUND")
 set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
 set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
 set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

# Create progress dialog library
add_library(progressdialog SHARED src/progressdialog.cpp src/progressdialog.h)
target_link_libraries(progressdialog Qt5::Core Qt5::Widgets )
target_compile_definitions(progressdialog PRIVATE PROGRESSDIALOG)

# Create threadedworker library
add_library(threadedworker SHARED src/threadedworker.cpp src/threadedworker.h src/fastthreadedworker.cpp src/fastthreadedworker.h)
target_link_libraries(threadedworker progressdialog)
target_compile_definitions(threadedworker PRIVATE THREADWORKER)

# Create mainwindow library
add_library(mainwindow SHARED src/mainwindow.cpp src/mainwindow.h src/mainwindow.ui)
target_link_libraries(mainwindow threadedworker)
target_compile_definitions(mainwindow PRIVATE MAINWINDOW)

# Executable example
add_executable(progress_bar src/progress_bar_main.cpp)
target_link_libraries(progress_bar mainwindow)
