// Copyright (c) 2017-2018 Commissariat à l'énergie atomique et aux énergies alternatives (CEA)
// Copyright (c) 2017-2018 Centre national de la recherche scientifique (CNRS)
// Copyright (c) 2018-2020 Simons Foundation
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

#include "./backwd/get_module.hpp"
#include "./macros.hpp"
#include "./pyref.hpp"

#include <string>
#include <complex>
#include <map>
#include <memory>
#include <typeindex>
#include <iostream>

// silence warning on intel
#ifndef __INTEL_COMPILER
#pragma clang diagnostic ignored "-Wdeprecated-writable-strings"
#endif
#pragma GCC diagnostic ignored "-Wwrite-strings"

// A global table of PyTypeObject to be stored at the top of interpreter
// so that each module can retrieve the PyTypeObject of types wrapped by other modules.

// FIXME : move to cpp ??

namespace c2py {

  // Table : c++ type name (demangled ??) -> PyTypeObject *
  using conv_table_t = std::map<std::string, PyTypeObject *>;

  // Fetch the pointer to the converter table from __main__
  inline std::shared_ptr<conv_table_t> get_conv_table_from_main() {
    // Fetch __main__ module
    pyref str_main = PyUnicode_FromString("__main__");
    pyref mod      = PyImport_GetModule(str_main);
    if (mod == nullptr) {
      PyErr_SetString(PyExc_RuntimeError, "Severe internal error : can not load __main__");
      throw std::runtime_error("Severe internal error : can not load __main__");
    }

    // Return ptr from __cpp2py_table attribute if available
    if (not PyObject_HasAttrString(mod, "__cpp2py_table")) return {};
    pyref capsule = PyObject_GetAttrString(mod, "__cpp2py_table");
    if (capsule.is_null()) throw std::runtime_error("Severe internal error : can not load __main__.__cpp2py_table");
    void *ptr = PyCapsule_GetPointer(capsule, "__main__.__cpp2py_table");
    return {*static_cast<std::shared_ptr<conv_table_t> *>(ptr)};
  }

  // Destructor used to clean the capsule containing the converter table pointer
  inline void _table_destructor(PyObject *capsule) {
    auto *p = static_cast<std::shared_ptr<conv_table_t> *>(PyCapsule_GetPointer(capsule, "__main__.__cpp2py_table"));
    delete p; //NOLINT
  }

  // Get the converter table, initialize it if necessary
  inline static std::shared_ptr<conv_table_t> get_conv_table() {
    if (not Py_IsInitialized()) return {}; // do it later
    std::shared_ptr<conv_table_t> sptr = get_conv_table_from_main();

    // Init map if pointer in main is null
    if (not sptr) {
      sptr = std::make_shared<conv_table_t>();

      // Now register the pointer in __main__
      PyObject *mod = PyImport_GetModule(PyUnicode_FromString("__main__"));
      auto *p       = new std::shared_ptr<conv_table_t>{sptr}; //NOLINT
      pyref c       = PyCapsule_New((void *)p, "__main__.__cpp2py_table", (PyCapsule_Destructor)_table_destructor);
      pyref s       = PyUnicode_FromString("__cpp2py_table");
      int err       = PyObject_SetAttr(mod, s, c);
      if (err) {
        PyErr_SetString(PyExc_RuntimeError, "Can not add the __cpp2py_table to main");
        throw std::runtime_error("Can not add the __cpp2py_table to main");
      }
    }
    return sptr;
  }

  // Each translation holds a shared pointer to the converter table
  static std::shared_ptr<conv_table_t> conv_table_sptr = get_conv_table(); //NOLINT
  // get the PyTypeObject from the table in __main__.
  // if the type was not wrapped, return nullptr and set up a Python exception
  inline PyTypeObject *get_type_ptr(std::type_index const &ind) {
    conv_table_t &conv_table = *conv_table_sptr.get();
    //PyTypeObject *r          = nullptr;

    auto it = conv_table.find(ind.name());
    if (it != conv_table.end()) return it->second;

    std::string s = std::string{"The type "} + ind.name() + " can not be converted";
    PyErr_SetString(PyExc_RuntimeError, s.c_str());
    return nullptr;
  }

} // namespace c2py
