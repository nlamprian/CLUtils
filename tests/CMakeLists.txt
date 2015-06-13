if ( BUILD_TESTS )

    find_package ( Threads REQUIRED )

    include_directories ( ${GTEST_INCLUDE_DIRS}
                          ${COMMON_INCLUDES} )

    add_executable ( ${FNAME}_tests tests.cpp )

    add_dependencies ( ${FNAME}_tests googletest )

    target_link_libraries ( ${FNAME}_tests LINK_PUBLIC CLUtils
                                                       ${GTEST_BOTH_LIBRARIES}
                                                       ${CMAKE_THREAD_LIBS_INIT} )

    add_test ( NAME ${FNAME}_tests 
               COMMAND ${EXECUTABLE_OUTPUT_PATH}/${FNAME}_tests 
               WORKING_DIRECTORY ${CMAKE_BINARY_DIR} )

    add_custom_target ( check COMMAND ${CMAKE_CTEST_COMMAND} --verbose )

endif (  )
