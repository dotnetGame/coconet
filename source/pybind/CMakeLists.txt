set(LIB_NAME pybind)
set(LIB_OUTNAME coconet-${LIB_NAME})

set(HEADER_PATH ${COCONET_PATH_HEADER}/${LIB_NAME})
set(SOURCE_PATH ${COCONET_PATH_SOURCE}/${LIB_NAME})

set(CORE_LIST
    ${HEADER_PATH}/coconet.h
    ${SOURCE_PATH}/coconet.cpp
)

add_library(${LIB_OUTNAME} SHARED ${CORE_LIST})

target_link_libraries(${LIB_OUTNAME} coconet-core)
target_link_libraries(${LIB_OUTNAME} coconet-util)
target_link_libraries(${LIB_OUTNAME} coconet-tensor)
target_link_libraries(${LIB_OUTNAME} coconet-cotensor)
target_link_libraries(${LIB_OUTNAME} coconet-autograd)
target_link_libraries(${LIB_OUTNAME} coconet-nn)

# include_directories(${PYTHON_INCLUDE_DIRS})
target_link_libraries(${LIB_OUTNAME}  ${PYTHON_LIBRARIES})
target_link_libraries(${LIB_OUTNAME} pybind11)
