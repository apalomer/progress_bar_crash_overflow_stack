cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(progress_bar)

# Set output folder
set(CMAKE_BIN "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BIN})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BIN})

# Set Library options
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_SHARED_LIBRARY_SUFFIX .so)

# Include Qt
find_package(Qt REQUIRED)
INCLUDE         (${QT_USE_FILE})
ADD_DEFINITIONS (${QT_DEFINITIONS})

# Add bin and build dir to include
set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(${CMAKE_SOURCE_DIR}/src)

# Create threadedworker library
QT4_WRAP_CPP(threadedworker_moc   src/threadedworker.h)
add_library(threadedworker SHARED src/threadedworker.cpp ${threadedworker_moc} ${threadedworker_ui})
target_link_libraries(threadedworker ${QT_LIBRARIES})

# Create mainwindow library
QT4_WRAP_CPP(mainwindow_moc   src/mainwindow.h)
QT4_WRAP_UI(mainwindow_ui src/mainwindow.ui)
add_library(mainwindow SHARED src/mainwindow.cpp ${mainwindow_moc} ${mainwindow_ui})
target_link_libraries(mainwindow ${QT_LIBRARIES} threadedworker)

# Qcustomplot example
add_executable(progress_bar src/progress_bar_main.cpp)
target_link_libraries(progress_bar ${QT_LIBRARIES} mainwindow)
