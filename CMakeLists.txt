#------------------------------------------------------------------------------
# General Projects Settings
#------------------------------------------------------------------------------
cmake_minimum_required (VERSION 3.11)
set(PROJECT_NAME TEST_TASK)
project(${PROJECT_NAME}
        LANGUAGES CXX
)

#------------------------------------------------------------------------------
# The main executable
#------------------------------------------------------------------------------
add_executable(${PROJECT_NAME}
        src/main.cpp
        )

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE} Debug)
endif()

if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__DEBUG__")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__RELEASE__")
endif()

if(NOT BUILD_TYPE)
    set(BUILD_TYPE ${BUILD_TYPE} "desktop")
endif()

#------------------------------------------------------------------------------
# General dependencies.
#------------------------------------------------------------------------------
include(ExternalProject)

#find_package(Git)
#if(NOT GIT_FOUND)
#    message(FATAL_ERROR "Git not found!")
#endif()
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

#------------------------------------------------------------------------------
# Tests section
#------------------------------------------------------------------------------

enable_testing()
add_subdirectory(tests)
