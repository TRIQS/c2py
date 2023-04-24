#pragma once
#include "pytypes.hpp"

namespace c2py {

  // *********************************************
  //     py_range
  // *********************************************
  struct py_range {
    std::function<PyObject *(PyObject *)> lazy_iter;

    py_range()                            = delete;
    py_range(py_range const &)            = delete;
    py_range(py_range &&)                 = default;
    py_range &operator=(py_range const &) = delete;
    py_range &operator=(py_range &&)      = delete;
    ~py_range()                           = default;

    template <typename T>
    py_range(T &&x) : lazy_iter{[y = std::forward<T>(x)](PyObject *self) -> PyObject * { return make_iterator(y.begin(), y.end(), self); }} {}
  };

  // ------------- converter ---------------

  template <> inline constexpr bool is_wrapped<py_range> = true;
  template <> inline constexpr auto tp_name<py_range>    = "hidden_pyrange";

  struct py_converter_to_py_range {
    static PyObject *c2py(auto x) { return py_converter<py_range>::c2py(py_range{std::move(x)}); }
    static void py2c(PyObject *ob)                                 = delete;
    static bool is_convertible(PyObject *ob, bool raise_exception) = delete;
  };

  // ------------- tp_iter of py_range ---------------

  template <>
  inline constexpr getiterfunc tp_iter<py_range> = [](PyObject *self) -> PyObject * {
    decltype(auto) self_c = py2cxx<py_range>(self);
    return self_c.lazy_iter(self);
  };

} // namespace c2py
