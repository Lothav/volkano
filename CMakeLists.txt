cmake_minimum_required(VERSION 3.7.0 FATAL_ERROR)
project(volkano)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake-modules")

# FIND VULKAN
find_package(Vulkan)
IF (NOT Vulkan_FOUND)
    message(FATAL_ERROR "Vulkan not find!")
ENDIF()
message(STATUS "Vulkan lib path: " ${Vulkan_LIBRARY})

# FIND XCB
find_package(XCB REQUIRED)
IF (NOT XCB_FOUND)
    message(FATAL_ERROR "XCB not find!")
ENDIF()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DVK_USE_PLATFORM_XCB_KHR")
message(STATUS "XCB libs paths: " ${XCB_LIBRARIES})

# INCLUD DIRECTORIES
include_directories(include engine/)
include_directories(include external/)

# SOURCE FILES
set(CORE_MAIN_FILE src/main.cpp)
file(GLOB_RECURSE CORE_HEADER_FILES src/engine/*)
file(GLOB_RECURSE EXTERNAL_HEADER_FILES external/*)

# ADD EXEC AND LINK LIBS
add_executable(volkano ${CORE_MAIN_FILE} ${CORE_HEADER_FILES} ${EXTERNAL_HEADER_FILES})
target_link_libraries(volkano ${XCB_LIBRARIES} ${Vulkan_LIBRARY})