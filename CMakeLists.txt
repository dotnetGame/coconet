project(coconet)

cmake_minimum_required(VERSION 3.14)

set(COCONET_PATH ${PROJECT_SOURCE_DIR} CACHE STRING "Adds a path to coconet" FORCE)
set(COCONET_PATH_INCLUDE ${COCONET_PATH}/include CACHE STRING "Adds a path to coconet header" FORCE)
set(COCONET_PATH_HEADER ${COCONET_PATH}/include/coconet CACHE STRING "Adds a path to coconet header" FORCE)
set(COCONET_PATH_SOURCE ${COCONET_PATH}/source CACHE STRING "Adds a path to coconet source" FORCE)
set(COCONET_PATH_CONTRIB ${COCONET_PATH}/contrib CACHE STRING "Adds a path to coconet contrib" FORCE)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


# option(COCONET_OPENMP "openmp support" OFF)

option(COCONET_FEATURE_SIMD "SIMD support" ON)
option(COCONET_FEATURE_MULTI_THREAD "multi thread support" ON)

if(COCONET_FEATURE_SIMD)
    add_compile_definitions(COCONET_FEATURE_SIMD)
endif()

if(COCONET_FEATURE_MULTI_THREAD)
    add_compile_definitions(COCONET_FEATURE_MULTI_THREAD)
endif()

add_subdirectory(contrib)
add_subdirectory(source)
add_subdirectory(examples)