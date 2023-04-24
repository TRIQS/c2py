MESSAGE( "EXEC ${clang_exe} -fsyntax-only -fcolor-diagnostics -Xclang -load -Xclang ${bin_dir}/src/plugins/c2py/libclplug_c2py.dylib -Xclang -plugin -Xclang c2py ${modulename}.cpp -fparse-all-comments -std=c++20  ${opt} -I${src_cur_dir}/ ")

execute_process(
 COMMAND cp ${src_cur_dir}/${modulename}.cpp  ${bin_cur_dir}
 COMMAND ${clang_exe} -fsyntax-only -fcolor-diagnostics -Xclang -load -Xclang ${bin_dir}/src/plugins/c2py/libclplug_c2py.dylib -Xclang -plugin -Xclang c2py ${modulename}.cpp -fparse-all-comments -std=c++20  ${opt} -I${src_cur_dir}/ 
 RESULT_VARIABLE command_failed
 ERROR_VARIABLE error
 OUTPUT_FILE ${modulename}.out
 ERROR_FILE ${modulename}.err
 WORKING_DIRECTORY ${bin_cur_dir}
 TIMEOUT 600
 )

if(command_failed)
  message(FATAL_ERROR "Error runing test '${modulename}'. Error output:\n ${error}")
endif()


# Compare the cxx file
execute_process(
 COMMAND diff -wB --strip-trailing-cr -I "^\\s*//" ${bin_cur_dir}/${modulename}.cxx ${src_cur_dir}/${refcxx}
 RESULT_VARIABLE not_successful
 OUTPUT_FILE ${modulename}.diff.out
 ERROR_FILE ${modulename}.diff.err
 OUTPUT_VARIABLE out
 ERROR_VARIABLE err
 )

if(not_successful)
  file(READ ${modulename}.diff.out fileOUT)
  # Status prints new line correctly, FATAL_ERROR does not ... 
  message(STATUS "File produced does not match with reference : \n${bin_cur_dir}/${modulename}.cxx \n${src_cur_dir}/${refcxx} \n ${fileOUT}")
  message(FATAL_ERROR "ERROR")
endif()


