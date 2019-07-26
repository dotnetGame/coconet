set(LIB_NAME core)
set(LIB_OUTNAME coconet-${LIB_NAME})

set(HEADER_PATH ${COCONET_PATH_HEADER}/${LIB_NAME})
set(SOURCE_PATH ${COCONET_PATH_SOURCE}/${LIB_NAME})

set(CORE_LIST
    ${HEADER_PATH}/type.h
    ${HEADER_PATH}/allocator.h
    ${SOURCE_PATH}/allocator.cpp
)

add_library(${LIB_OUTNAME} STATIC ${CORE_LIST})

target_link_libraries(${LIB_OUTNAME} coconet-util)
target_link_libraries(${LIB_OUTNAME} coconet-tensor)
target_link_libraries(${LIB_OUTNAME} coconet-cotensor)
