add_subdirectory(cmake)

if(NOT CMAKE_INSTALL_PREFIX STREQUAL TRIQS_ROOT AND NOT IS_SUBPROJECT)

  configure_file(${PROJECT_NAME}.modulefile.in ${PROJECT_NAME}.modulefile @ONLY)
  configure_file(${PROJECT_NAME}vars.sh.in ${PROJECT_NAME}vars.sh @ONLY)

  install(
    FILES
      ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.modulefile
      ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}vars.sh
    DESTINATION share
  )
 
  message(STATUS "***************************************************************")
  message(STATUS "* Custom install Location. Use:                                ")
  message(STATUS "*                                                              ")
  message(STATUS "*   source ${CMAKE_INSTALL_PREFIX}/share/${PROJECT_NAME}vars.sh      ")
  message(STATUS "*                                                              ")
  message(STATUS "* to set up the environment variables                          ")
  message(STATUS "***************************************************************")

endif()
