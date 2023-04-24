#pragma once
#include <string>

namespace c2py {

  // ------------ cpp_name --------------
  // name of the c++ type for error messages and signatures
  // To be specialized along the converters.

  // FIXME : constexpr when implemented in clang 2b
  template <typename T> static inline const std::string cpp_name = "TYPE";
  template <> inline const std::string cpp_name<int>             = "int";

} // namespace c2py
