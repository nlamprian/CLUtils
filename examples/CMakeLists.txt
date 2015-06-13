add_executable ( ${FNAME}_vecAdd vecAdd.cpp )

target_link_libraries ( ${FNAME}_vecAdd CLUtils ${OPENCL_LIBRARIES} )
