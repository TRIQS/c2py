// Copyright (c) 2022 Simons Foundation
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
// Authors: Olivier Parcollet

#pragma once
#include "./macros_general.hpp"

// --- Stringify macros -----

#define CLAIR_AS_STRING(...) CLAIR_AS_STRING2(__VA_ARGS__)
#define CLAIR_AS_STRING2(...) #__VA_ARGS__

#define AS_STRING(...) AS_STRING2(__VA_ARGS__)
#define AS_STRING2(...) #__VA_ARGS__

#define CLAIR_PRINT(X) std::cerr << AS_STRING(X) << " = " << X << "      at " << __FILE__ << ":" << __LINE__ << '\n'

#define CLAIR_C2PY_ADD_TYPE_OBJECT(CLS, PYNAME)                                                                                                      \
  Py_INCREF(&c2py::py_type_object<CLS>);                                                                                                             \
  PyModule_AddObject(m, PYNAME, (PyObject *)&c2py::py_type_object<CLS>);                                                                             \
  conv_table[std::type_index(typeid(CLS)).name()] = &c2py::py_type_object<CLS>;
