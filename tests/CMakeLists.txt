if ( BUILD_TESTS )

    # find_package ( GTest REQUIRED )
    find_package ( Threads REQUIRED )

    include_directories ( ${GTEST_INCLUDE_DIRS}
                          ${COMMON_INCLUDES} )

    add_executable ( clUtils_tests tests.cpp )

    add_dependencies ( clUtils_tests googletest )

    target_link_libraries ( clUtils_tests LINK_PUBLIC CLUtils
                                                      ${GTEST_BOTH_LIBRARIES}
                                                      ${CMAKE_THREAD_LIBS_INIT} )

    add_test ( NAME clUtils_tests 
               COMMAND ${EXECUTABLE_OUTPUT_PATH}/clUtils_tests 
               WORKING_DIRECTORY ${CMAKE_BINARY_DIR} )

    add_custom_target ( check COMMAND ${CMAKE_CTEST_COMMAND} --verbose )

endif (  )
