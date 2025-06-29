cmake_minimum_required(VERSION 3.22)

project(PathPlannerApp)

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable AUTOMOC to handle Q_OBJECT macros
set(CMAKE_AUTOMOC ON)

find_package(
    Qt5 REQUIRED COMPONENTS Widgets # Qt5 For the ui
)

# Include directories
include_directories(include)

# UI Source files
set(UI_SOURCE_FILES
    src/ui/graphics_scene.cpp
    src/ui/main_window.cpp
    src/ui/main.cpp
    # Needed here to trigger the MOC for Q_OBJECT Macro
    include/ui/main_window.hpp
    include/ui/graphics_scene.hpp
)

# Create the executable
add_executable(${PROJECT_NAME} ${UI_SOURCE_FILES})

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Debug mode enabled")
    target_compile_definitions(${PROJECT_NAME} PRIVATE DEBUG_MODE=1)
endif()

# Link Qt5 if needed
target_link_libraries(${PROJECT_NAME} Qt5::Widgets)
