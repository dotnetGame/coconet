SET(LIB_NAME cotensor)
SET(LIB_OUTNAME coconet-${LIB_NAME})

SET(HEADER_PATH ${COCONET_PATH_HEADER}/tensor/${LIB_NAME})
SET(SOURCE_PATH ${COCONET_PATH_SOURCE}/tensor/${LIB_NAME})

SET(TENSOR_LIST
    ${HEADER_PATH}/index.h
    ${SOURCE_PATH}/index.cpp
    ${HEADER_PATH}/tensor.h
    ${SOURCE_PATH}/tensor.cpp
    ${HEADER_PATH}/storage.h
    ${SOURCE_PATH}/storage.cpp
)

ADD_LIBRARY(${LIB_OUTNAME} ${TENSOR_LIST})


