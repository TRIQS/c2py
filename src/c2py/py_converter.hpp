// Copyright (c) 2017-2018 Commissariat à l'énergie atomique et aux énergies alternatives (CEA)
// Copyright (c) 2017-2018 Centre national de la recherche scientifique (CNRS)
// Copyright (c) 2018-2022 Simons Foundation
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0.txt
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// Authors: Philipp Dumitrescu, Olivier Parcollet, Nils Wentzell

#pragma once
#include "./pyref.hpp"
#include "./converter_table.hpp"
#include <type_traits>

// for backward compatibility layer below
namespace cpp2py {
  template <typename T> struct py_converter;
}

namespace c2py {

  //---------------------  py_converters -----------------------------

  template <typename T> struct py_converter;
#if 0
  // format of converters. NB do not uncomment, py_converter has no default implementation.
  //
  template <typename T> struct py_converter {
   
   // From C++ to python.
   // Can throw. ??? Really ?
   static PyObject *c2py(auto &&x);
   
   // Return true iif the object can A PRIORI be converted. 
   // It is a normally type check.
   // An error may still occurr in the conversion, e.g. int overflow. 
   // is_convertible is used for the dynamic dispatch of the function
   // raise_exception : in case of failure, it sets an error message as a python exception ...
   // FIXME  really ?
   static bool is_convertible(PyObject *ob, bool raise_exception) noexcept;
   
   // Convert. Assumes that is_convertible is true
   // Can still throw C++ exception.
   // Returns a T or a ref (for wrapped types).
   static [T & | T] py2c(PyObject *ob);
  
  };
#endif

  // This must be specialized for each wrapped type, whether it is wrapped
  // in the module being compiled or in another one ...
  template <typename T> static constexpr bool is_wrapped = false; // default

  //---------------------  py_converters -----------------------------

  template <typename T> struct merged_into {
    using type = T;
  }; // default

  //---------------------  Concept to check convertibility -----------------------------

  namespace concepts {

    template <typename U>
    concept IsConvertiblePy2C = requires() {
      { c2py::py_converter<std::decay_t<U>>::py2c((PyObject *)nullptr) } -> std::convertible_to<U>;
      { c2py::py_converter<std::decay_t<U>>::is_convertible((PyObject *)nullptr, false) } -> std::same_as<bool>;
    };

    template <typename U>
    concept IsConvertibleC2Py = requires(U x) {
      { c2py::py_converter<std::remove_const_t<U>>::c2py(x) } -> std::same_as<PyObject *>;
    };

    template <typename U>
    concept IsConvertible = IsConvertibleC2Py<U> and IsConvertiblePy2C<U>;

  } // namespace concepts
  //---------------------  Helper function -----------------------------

  // Return can be T, T&, T const &
  template <typename T> static decltype(auto) py2cxx(PyObject *x) { return py_converter<std::decay_t<T>>::py2c(x); }

  // New ref
  template <typename T> static PyObject *cxx2py(T &&x) { return py_converter<std::decay_t<T>>::c2py(std::forward<T>(x)); }

  template <typename T> static bool convertible(PyObject *ob, bool raise_exception) { return py_converter<T>::is_convertible(ob, raise_exception); }

  // ---------------------  Backward compatibility layer
  // with cpp2py. If the converters already exists in cpp2py, use them
  // FIXME in cpp2py : use only the converters, do NOT include cpp2py.hpp ... (which contains basic py_converters).

  namespace concepts {
    template <typename U>
    concept IsConvertibleCPP2Py_BACKWARD = requires(U x) {
      { cpp2py::py_converter<U>::c2py(x) } -> std::same_as<PyObject *>;
    } and not requires { typename cpp2py::py_converter<U>::is_wrapped_type; };
  }

  template <typename T>
    requires(concepts::IsConvertibleCPP2Py_BACKWARD<std::decay_t<T>>)
  struct py_converter<T> : ::cpp2py::py_converter<std::decay_t<T>> {};

  //---------------------  wrapped type -----------------------------

  template <typename T>
    requires(is_wrapped<T>) //std::decay_t<T>>)
  struct py_converter<T> {  // hence T , T &, T const & for T wrapped.

    using py_type = struct {
      PyObject_HEAD //
         T *_c;
    };

    using is_wrapped = void; // to recognize
    static_assert(not std::is_reference_v<T>, "Not implemented");

    template <typename U> static PyObject *c2py(U &&x) {
      PyTypeObject *p = get_type_ptr(typeid(T));
      if (p == nullptr) return nullptr;
      auto *self = (py_type *)p->tp_alloc(p, 0);
      if (self != NULL) { self->_c = new T{std::forward<U>(x)}; } // NOLINT
      return (PyObject *)self;
    }

    static T &py2c(PyObject *ob) {
      auto *_c = ((py_type *)ob)->_c;
      if (_c == NULL) {
        std::cerr << "Severe internal error : _c is null in py2c\n";
        std::terminate();
      }
      return *_c;
    }

    static bool is_convertible(PyObject *ob, bool raise_exception) {
      PyTypeObject *p = get_type_ptr(typeid(T));
      if (p == nullptr) return false;
      if (PyObject_TypeCheck(ob, p)) {
        if (((py_type *)ob)->_c != NULL) return true;
        auto err = std::string{"Severe internal error : Python object of "} + p->tp_name + " has a _c NULL pointer !!";
        if (raise_exception) PyErr_SetString(PyExc_TypeError, err.c_str());
        return false;
      }
      auto err = std::string{"Python object is not a "} + p->tp_name + " but a " + Py_TYPE(ob)->tp_name;
      if (raise_exception) PyErr_SetString(PyExc_TypeError, err.c_str());
      return false;
    }
  };

  //---------------------  convert by cast ------------------------------

  // A generic converter for type T, if
  // - T can be explicitly constructed from R
  // - T can be explicitly casted into R.
  // - R is convertible
  template <typename T, typename R> struct py_converter_generic_cast_construct {

    using conv_t = py_converter<R>;

    static PyObject *c2py(T const &x) { return conv_t::c2py(static_cast<R>(x)); }

    static bool is_convertible(PyObject *ob, bool raise_exception) {
      if (conv_t::is_convertible(ob, false)) return true;
      if (raise_exception) { PyErr_SetString(PyExc_TypeError, ("Cannot convert "s + to_string(ob) + " to ... failed"s).c_str()); }
      return false;
    }

    static T py2c(PyObject *ob) { return T{conv_t::py2c(ob)}; }
  };

  //---------------------  convert by cross construction ------------------------------
  // A generic converter for type T, if
  // - T can be explicitly constructed from R
  // - R can be explicitly constructed from T
  // - R is convertible
  // e.g. a view
  template <typename T, typename R> struct py_converter_generic_cross_construction {

    using conv_t = py_converter<R>;

    static PyObject *c2py(T const &x) { return conv_t::c2py(R{x}); }
    static PyObject *c2py(T &&x) { return conv_t::c2py(R{std::move(x)}); }

    static bool is_convertible(PyObject *ob, bool raise_exception) {
      if (conv_t::is_convertible(ob, false)) return true;
      if (raise_exception) { PyErr_SetString(PyExc_TypeError, ("Cannot convert "s + to_string(ob) + " to ... failed"s).c_str()); }
      return false;
    }

    static T py2c(PyObject *ob) { return T{conv_t::py2c(ob)}; }
  };

} // namespace c2py
