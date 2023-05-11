#pragma once
#include <string>
#include "pretty_print.hpp"
#include "util.hpp"

namespace c2py {

  // ------------ cpp_name --------------
  // name of the c++ type for error messages and signatures
  // To be specialized along the converters.

  // FIXME : constexpr when implemented in clang 2b
  template <typename T> static inline const std::string cpp_name = trim(replacenl(std::string{type_name<T>()})); // typeid(T).name();
  //template <> inline const std::string cpp_name<int>                      = "int";
  //template <typename T> static inline const std::string cpp_name<T &>     = cpp_name<T> + '&';
  //template <typename T> static inline const std::string cpp_name<T const> = cpp_name<T> + " const ";

} // namespace c2py
