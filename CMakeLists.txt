cmake_minimum_required(VERSION 3.24)
project(2048)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(SOURCES
        GameBoard.cpp GameBoard.hpp
        MainWindow.cpp MainWindow.h main.cpp)

add_executable(2048 ${SOURCES})

target_link_libraries(2048 Qt5::Widgets)

# Add the resource file to the target
# qt5_add_resources(2048_resources resources/2048.qrc)

# Link the resource file to the target
target_sources(2048 PRIVATE ${2048_resources})

# Copy the images folder to the build directory
# file(COPY resources/images DESTINATION ${CMAKE_BINARY_DIR}/resources)
