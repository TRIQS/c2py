FILE(COPY ${CMAKE_SOURCE_DIR}/.clang-format DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

#find_package(sanitizer REQUIRED "asan")
MESSAGE("SANITIZER_RT_PRELOAD = ${SANITIZER_RT_PRELOAD}")

SET(MODULE_EXTENSION "wrap.cxx")

macro(add_test_py1 modulename module_extension) 

  Python_add_library( ${modulename} MODULE "${modulename}.${module_extension}")
  target_compile_options(${modulename} PRIVATE ${ARGN} -std=c++20)
  target_include_directories(${modulename} SYSTEM PRIVATE  ${CMAKE_SOURCE_DIR}/src)
  target_link_libraries(${modulename} PRIVATE c2py ${PROJECT_NAME}_warnings itertools::itertools_c Python::NumPy)

if(ASAN)
  target_link_libraries(${modulename}  PRIVATE $<BUILD_INTERFACE:asan>)
endif()
if(UBSAN)
  target_link_libraries(${modulename}  PRIVATE $<BUILD_INTERFACE:ubsan>)
endif()

  get_filename_component(test_name ${modulename} NAME_WE)
  get_filename_component(test_dir ${modulename} DIRECTORY)
  add_test(NAME ${modulename}_py COMMAND ${Python_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/${test_dir}/${modulename}_test.py WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${test_dir})
  set_property(TEST ${modulename}_py APPEND PROPERTY ENVIRONMENT PYTHONPATH=${h5_BINARY_DIR}/python:${CMAKE_CURRENT_BINARY_DIR}:$ENV{PYTHONPATH} ${SANITIZER_RT_PRELOAD})
endmacro()

macro(add_test_py modulename)
  add_test_py1(${modulename} ${MODULE_EXTENSION} ${PLUGIN_OPTION})
endmacro()

# ----------------------------
# Non generated test. Low level only
add_test_py1(cls "cxx" )

# Full tests
add_test_py(basicfun)
add_test_py(cls_basic)
add_test_py(comparison)
add_test_py(issue9)
add_test_py(callables)

add_test_py(itertool)
add_test_py(enumcxx)
add_test_py(synth_init)

add_test_py(tpl_cls)
add_test_py(tpl_derived)

#add_test_py(h5_storable)
#get_target_property(H5_INCDIR h5_c INTERFACE_INCLUDE_DIRECTORIES)
#target_include_directories(h5_storable SYSTEM PRIVATE  ${H5_INCDIR})
#target_link_libraries(h5_storable PRIVATE h5_c)
#add_dependencies(h5_storable _h5py)



