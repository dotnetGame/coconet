set(LIB_NAME core)
set(LIB_OUTNAME coconet-${LIB_NAME})

set(HEADER_PATH ${COCONET_PATH_HEADER}/${LIB_NAME})
set(SOURCE_PATH ${COCONET_PATH_SOURCE}/${LIB_NAME})

set(CORE_LIST
    ${HEADER_PATH}/type.h
    ${HEADER_PATH}/variable.h
    ${SOURCE_PATH}/variable.cpp
)

add_library(${LIB_OUTNAME} ${CORE_LIST})
