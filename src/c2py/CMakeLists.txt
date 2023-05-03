add_library(c2py_obj OBJECT pycfun_kw.cpp signal_handler.cpp numpy_proxy.cpp)

set_property(TARGET c2py_obj PROPERTY POSITION_INDEPENDENT_CODE 1)

target_compile_options(c2py_obj PRIVATE -std=c++20 -fPIC) # -fvisibility=hidden)

target_include_directories(c2py_obj
  PUBLIC
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_PREFIX}/include>
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
  )

target_link_libraries(c2py_obj PRIVATE ${PROJECT_NAME}_warnings itertools::itertools_c )
target_link_libraries(c2py_obj PUBLIC Python::NumPy Python::Python)

# shared and static libraries built from the same object files
add_library(c2py_dyn SHARED $<TARGET_OBJECTS:c2py_obj>)
add_library(c2py STATIC $<TARGET_OBJECTS:c2py_obj>)
add_library(c2py::c2py ALIAS c2py)

target_include_directories(c2py
  PUBLIC
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_PREFIX}/include>
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
  )


target_link_libraries(c2py_dyn PUBLIC Python::NumPy Python::Python)
target_link_libraries(c2py PUBLIC Python::NumPy Python::Python)


# Install the library in lib and export the c2py target
install(TARGETS c2py c2py_dyn EXPORT c2py-targets DESTINATION lib)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION include FILES_MATCHING PATTERN "*.hpp" PATTERN "*.h")

# Install the exported targets
install(EXPORT c2py-targets NAMESPACE c2py:: DESTINATION lib/cmake/c2py)
