add_executable ( clUtils_vecAdd vecAdd.cpp )

target_link_libraries ( clUtils_vecAdd CLUtils
                                       ${OPENCL_LIBRARIES} )
