cmake_minimum_required(VERSION 3.7.0 FATAL_ERROR)
project(volkano)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake-modules")

# ENABLE DEBUG
add_definitions(-DDEBUG)

# FIND VULKAN
find_package(Vulkan REQUIRED)
IF (NOT Vulkan_FOUND)
    message(FATAL_ERROR "Vulkan not find!")
ENDIF()
message(STATUS "Vulkan lib path: " ${Vulkan_LIBRARY})

# FIND SDL2
find_package(SDL2 REQUIRED)
IF (NOT SDL2_FOUND)
    message(FATAL_ERROR "SDL2 not find!")
ENDIF()

# INCLUDE DIRECTORIES
include_directories(src/engine/ ${SDL2_INCLUDE_DIR})

# SOURCE FILES
set(CORE_MAIN_FILE src/main.cpp src/Volkano.hpp src/Volkano.cpp)
file(GLOB_RECURSE CORE_HEADER_FILES src/engine/*)
file(GLOB_RECURSE EXTERNAL_HEADER_FILES external/*)

# ADD EXEC AND LINK LIBS
add_executable(volkano ${CORE_MAIN_FILE} ${CORE_HEADER_FILES} ${EXTERNAL_HEADER_FILES})
target_link_libraries(volkano ${SDL2_LIBRARY} ${Vulkan_LIBRARY})

# BUILD SDL2 DEPENDENCY
add_dependencies(volkano ${SDL2_BUILD_COMMAND})