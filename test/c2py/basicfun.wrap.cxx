
// C.f. https://numpy.org/doc/1.21/reference/c-api/array.html#importing-the-api
#define PY_ARRAY_UNIQUE_SYMBOL _cpp2py_ARRAY_API
#ifdef __clang__
#pragma clang diagnostic ignored "-W#warnings"
#endif
#include "basicfun.cpp"
#include "c2py/c2py.hpp"

using c2py::operator"" _a;

// ==================== Wrapped classes =====================

// ==================== enums =====================

// ==================== module classes =====================

// ==================== module functions ====================

// f
static auto const fun_0 =
   c2py::dispatcher_f_kw_t{c2py::cfun(c2py::cast<int>(&f), "x"), c2py::cfun(c2py::cast<int, int>(&f), "x", "y")};

// f1
static auto const fun_1 =
   c2py::dispatcher_f_kw_t{c2py::cfun(c2py::cast<int>(&f1), "x"), c2py::cfun(c2py::cast<double>(&f1), "x")};

// g
static auto const fun_2 = c2py::dispatcher_f_kw_t{c2py::cfun(c2py::cast<int, int>(&g), "x", "y"_a = 8)};

// h
static auto const fun_3 = c2py::dispatcher_f_kw_t{c2py::cfun(&N::h<int>, "x"), c2py::cfun(&N::h<double>, "x")};

// hf
static auto const fun_4 =
   c2py::dispatcher_f_kw_t{c2py::cfun(c2py::cast<int>(&f1), "x"), c2py::cfun(&N::h<double>, "x")};

// ret_with_alias
static auto const fun_5 = c2py::dispatcher_f_kw_t{c2py::cfun(c2py::cast<>(&ret_with_alias))};

static constexpr auto doc_f_0_0 = R"DOC(   A doc for f(x)
   
   Parameters
   ----------
   
   x: The doc of x)DOC";
static constexpr auto doc_f_0_1 = R"DOC(   A doc for f(x,y)
   
   Parameters
   ----------
   
   y: The doc of y
   x: The doc of x)DOC";
static const auto doc_d_0       = fun_0.doc({doc_f_0_0, doc_f_0_1});
static constexpr auto doc_f_1_0 = R"DOC(   )DOC";
static constexpr auto doc_f_1_1 = R"DOC(   )DOC";
static const auto doc_d_1       = fun_1.doc({doc_f_1_0, doc_f_1_1});
static const auto doc_d_2       = fun_2.doc({R"DOC(   )DOC"});
static constexpr auto doc_f_3_0 = R"DOC(   )DOC";
static constexpr auto doc_f_3_1 = R"DOC(   )DOC";
static const auto doc_d_3       = fun_3.doc({doc_f_3_0, doc_f_3_1});
static constexpr auto doc_f_4_0 = R"DOC(   )DOC";
static constexpr auto doc_f_4_1 = R"DOC(   )DOC";
static const auto doc_d_4       = fun_4.doc({doc_f_4_0, doc_f_4_1});
static const auto doc_d_5       = fun_5.doc({R"DOC(   )DOC"});
//--------------------- module function table  -----------------------------

static PyMethodDef module_methods[] = {
   {"f", (PyCFunction)c2py::pyfkw<fun_0>, METH_VARARGS | METH_KEYWORDS, doc_d_0.c_str()},
   {"f1", (PyCFunction)c2py::pyfkw<fun_1>, METH_VARARGS | METH_KEYWORDS, doc_d_1.c_str()},
   {"g", (PyCFunction)c2py::pyfkw<fun_2>, METH_VARARGS | METH_KEYWORDS, doc_d_2.c_str()},
   {"h", (PyCFunction)c2py::pyfkw<fun_3>, METH_VARARGS | METH_KEYWORDS, doc_d_3.c_str()},
   {"hf", (PyCFunction)c2py::pyfkw<fun_4>, METH_VARARGS | METH_KEYWORDS, doc_d_4.c_str()},
   {"ret_with_alias", (PyCFunction)c2py::pyfkw<fun_5>, METH_VARARGS | METH_KEYWORDS, doc_d_5.c_str()},
   {nullptr, nullptr, 0, nullptr} // Sentinel
};

//--------------------- module struct & init error definition ------------

//// module doc directly in the code or "" if not present...
/// Or mandatory ?
static struct PyModuleDef module_def = {
   PyModuleDef_HEAD_INIT,
   "basicfun",   /* name of module */
   "DOC MODULE", /* module documentation, may be NULL */
   -1,           /* size of per-interpreter state of the module, or -1 if the module keeps state in global variables. */
   module_methods,
   NULL,
   NULL,
   NULL,
   NULL};

//--------------------- module init function -----------------------------

extern "C" __attribute__((visibility("default"))) PyObject *PyInit_basicfun() {

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
