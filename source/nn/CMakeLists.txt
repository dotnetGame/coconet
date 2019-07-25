set(LIB_NAME nn)
set(LIB_OUTNAME coconet-${LIB_NAME})

set(HEADER_PATH ${COCONET_PATH_HEADER}/${LIB_NAME})
set(SOURCE_PATH ${COCONET_PATH_SOURCE}/${LIB_NAME})

set(NN_LIST
    ${HEADER_PATH}/function.h
    ${SOURCE_PATH}/function.cpp
    ${HEADER_PATH}/operation.h
    ${SOURCE_PATH}/operation.cpp
    ${HEADER_PATH}/variable.h
    ${SOURCE_PATH}/variable.cpp
)

add_library(${LIB_OUTNAME} ${NN_LIST})
