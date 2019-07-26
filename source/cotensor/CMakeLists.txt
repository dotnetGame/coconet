SET(LIB_NAME cotensor)
SET(LIB_OUTNAME coconet-${LIB_NAME})

SET(HEADER_PATH ${COCONET_PATH_HEADER}/${LIB_NAME})
SET(SOURCE_PATH ${COCONET_PATH_SOURCE}/${LIB_NAME})

SET(TENSOR_LIST
    ${HEADER_PATH}/tensor.h
    ${SOURCE_PATH}/tensor.cpp
    ${HEADER_PATH}/storage.h
    ${SOURCE_PATH}/storage.cpp
)

ADD_LIBRARY(${LIB_OUTNAME} ${TENSOR_LIST})

target_link_libraries(${LIB_OUTNAME} coconet-tensor)
target_link_libraries(${LIB_OUTNAME} coconet-util)

