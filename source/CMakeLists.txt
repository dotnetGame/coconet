INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include)
include_directories(${COCONET_PATH_CONTRIB}/taskflow)
include_directories(${COCONET_PATH_CONTRIB}/xsimd/include)

add_subdirectory(core)
add_subdirectory(util)
add_subdirectory(tensor)
add_subdirectory(cotensor)
add_subdirectory(nn)