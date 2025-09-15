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

# ignore BOOST deprecated messages
add_definitions("-DBOOST_ALLOW_DEPRECATED_HEADERS")

# Include directories
include_directories(include)

file(GLOB_RECURSE UI_SOURCE_FILES
    src/ui/*.cpp
    src/ui/algorithms_settings/*.cpp
    # Needed here to trigger the MOC for Q_OBJECT Macro
    include/ui/*.hpp
    include/ui/algorithms_settings/*.hpp
)

file(GLOB_RECURSE UTILS_SOURCES
    src/utils/*.cpp
)

file(GLOB_RECURSE CORE_SOURCES
    src/core/*.cpp
)

# Create the executable
add_executable(${PROJECT_NAME} ${UTILS_SOURCES} ${UI_SOURCE_FILES} ${CORE_SOURCES})

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Debug mode enabled")
    target_compile_definitions(${PROJECT_NAME} PRIVATE DEBUG_MODE=1)
endif()

# Link Qt5 if needed
target_link_libraries(${PROJECT_NAME} Qt5::Widgets)
