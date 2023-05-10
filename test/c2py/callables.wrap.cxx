
// C.f. https://numpy.org/doc/1.21/reference/c-api/array.html#importing-the-api
#define PY_ARRAY_UNIQUE_SYMBOL _cpp2py_ARRAY_API
#ifdef __clang__
#pragma clang diagnostic ignored "-W#warnings"
#endif
#include "callables.cpp"
#include "c2py/c2py.hpp"

using c2py::operator"" _a;

// ==================== Wrapped classes =====================

// ==================== enums =====================

// ==================== module classes =====================

// ==================== module functions ====================

// call1
static auto const fun_0 = c2py::dispatcher_f_kw_t{c2py::cfun(c2py::cast<const std::function<int(int, int)> &>(&call1), "f")};

// call2
static auto const fun_1 = c2py::dispatcher_f_kw_t{c2py::cfun(c2py::cast<std::function<int(int, int)>>(&call2), "f")};

// call3
static auto const fun_2 = c2py::dispatcher_f_kw_t{c2py::cfun(c2py::cast<const std::function<int(std::pair<int, int>)> &>(&call3), "f")};

// call4
static auto const fun_3 = c2py::dispatcher_f_kw_t{c2py::cfun(c2py::cast<std::function<int(std::pair<int, int>)>>(&call4), "f")};

// call5
static auto const fun_4 = c2py::dispatcher_f_kw_t{c2py::cfun(c2py::cast<std::function<int(const std::pair<int, int> &)>>(&call5), "f")};

// callback
static auto const fun_5 = c2py::dispatcher_f_kw_t{c2py::cfun(c2py::cast<>(&callback))};

// make_f
static auto const fun_6 = c2py::dispatcher_f_kw_t{c2py::cfun(c2py::cast<>(&make_f))};

// make_f2
static auto const fun_7 = c2py::dispatcher_f_kw_t{c2py::cfun(c2py::cast<>(&make_f2))};

static const auto doc_d_0 = fun_0.doc({R"DOC(   )DOC"});
static const auto doc_d_1 = fun_1.doc({R"DOC(   )DOC"});
static const auto doc_d_2 = fun_2.doc({R"DOC(   )DOC"});
static const auto doc_d_3 = fun_3.doc({R"DOC(   )DOC"});
static const auto doc_d_4 = fun_4.doc({R"DOC(   )DOC"});
static const auto doc_d_5 = fun_5.doc({R"DOC(   )DOC"});
static const auto doc_d_6 = fun_6.doc({R"DOC(   )DOC"});
static const auto doc_d_7 = fun_7.doc({R"DOC(   )DOC"});
//--------------------- module function table  -----------------------------

static PyMethodDef module_methods[] = {
   {"call1", (PyCFunction)c2py::pyfkw<fun_0>, METH_VARARGS | METH_KEYWORDS, doc_d_0.c_str()},
   {"call2", (PyCFunction)c2py::pyfkw<fun_1>, METH_VARARGS | METH_KEYWORDS, doc_d_1.c_str()},
   {"call3", (PyCFunction)c2py::pyfkw<fun_2>, METH_VARARGS | METH_KEYWORDS, doc_d_2.c_str()},
   {"call4", (PyCFunction)c2py::pyfkw<fun_3>, METH_VARARGS | METH_KEYWORDS, doc_d_3.c_str()},
   {"call5", (PyCFunction)c2py::pyfkw<fun_4>, METH_VARARGS | METH_KEYWORDS, doc_d_4.c_str()},
   {"callback", (PyCFunction)c2py::pyfkw<fun_5>, METH_VARARGS | METH_KEYWORDS, doc_d_5.c_str()},
   {"make_f", (PyCFunction)c2py::pyfkw<fun_6>, METH_VARARGS | METH_KEYWORDS, doc_d_6.c_str()},
   {"make_f2", (PyCFunction)c2py::pyfkw<fun_7>, METH_VARARGS | METH_KEYWORDS, doc_d_7.c_str()},
   {nullptr, nullptr, 0, nullptr} // Sentinel
};

//--------------------- module struct & init error definition ------------

//// module doc directly in the code or "" if not present...
/// Or mandatory ?
static struct PyModuleDef module_def = {PyModuleDef_HEAD_INIT,
                                        "callables",  /* name of module */
                                        "DOC MODULE", /* module documentation, may be NULL */
                                        -1, /* size of per-interpreter state of the module, or -1 if the module keeps state in global variables. */
                                        module_methods,
                                        NULL,
                                        NULL,
                                        NULL,
                                        NULL};

//--------------------- module init function -----------------------------

extern "C" __attribute__((visibility("default"))) PyObject *PyInit_callables() {

  // import numpy iff 'numpy/arrayobject.h' included
#ifdef Py_ARRAYOBJECT_H
  import_array();
#endif

  PyObject *m;

  if (PyType_Ready(&c2py::py_type_object<c2py::py_range>) < 0) return NULL;

  m = PyModule_Create(&module_def);
  if (m == NULL) return NULL;

  auto &conv_table = *c2py::conv_table_sptr.get();

  conv_table[std::type_index(typeid(c2py::py_range)).name()] = &c2py::py_type_object<c2py::py_range>;

  return m;
}
