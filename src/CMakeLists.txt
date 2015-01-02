add_library ( CLUtils STATIC CLUtils.cpp )

target_link_libraries ( CLUtils ${OPENCL_LIBRARIES} )

target_include_directories ( CLUtils PUBLIC ${COMMON_INCLUDES} )

install ( TARGETS CLUtils DESTINATION lib )
install ( FILES ${COMMON_INCLUDES}/CLUtils.hpp DESTINATION include )
