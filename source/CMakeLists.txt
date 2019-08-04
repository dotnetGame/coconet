include_directories(${PROJECT_SOURCE_DIR}/include)

if(COCONET_FEATURE_MULTI_THREAD)
    include_directories(${COCONET_PATH_CONTRIB}/taskflow)
endif()
if(COCONET_FEATURE_SIMD)
    include_directories(${COCONET_PATH_CONTRIB}/xsimd/include)
endif()

add_subdirectory(core)
add_subdirectory(util)
add_subdirectory(tensor)
add_subdirectory(cotensor)
add_subdirectory(nn)