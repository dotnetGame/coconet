project(coconet)

cmake_minimum_required(VERSION 3.14)

set(COCONET_PATH ${PROJECT_SOURCE_DIR} CACHE STRING "Adds a path to coconet" FORCE)
set(COCONET_PATH_INCLUDE ${COCONET_PATH}/include CACHE STRING "Adds a path to coconet header" FORCE)
set(COCONET_PATH_HEADER ${COCONET_PATH}/include/coconet CACHE STRING "Adds a path to coconet header" FORCE)
set(COCONET_PATH_SOURCE ${COCONET_PATH}/source CACHE STRING "Adds a path to coconet source" FORCE)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


option(COCONET_OPENMP "openmp support" OFF)

add_subdirectory(source)
add_subdirectory(examples)