
// C.f. https://numpy.org/doc/1.21/reference/c-api/array.html#importing-the-api
#define PY_ARRAY_UNIQUE_SYMBOL _cpp2py_ARRAY_API
#ifdef __clang__
#pragma clang diagnostic ignored "-W#warnings"
#endif
#include "itertool.cpp"
#include "c2py/c2py.hpp"

using c2py::operator"" _a;

// ==================== Wrapped classes =====================

template <> inline constexpr bool c2py::is_wrapped<a_class> = true;

// ==================== enums =====================

// ==================== module classes =====================

template <> inline const std::string c2py::cpp_name<a_class>   = "a_class";
template <> inline constexpr auto c2py::tp_name<a_class>       = "itertool.AClass";
template <> inline constexpr const char *c2py::tp_doc<a_class> = R"DOC(   )DOC";

static auto init_0                                    = c2py::dispatcher_c_kw_t{c2py::c_constructor<a_class>()};
template <> constexpr initproc c2py::tp_init<a_class> = c2py::pyfkw_constructor<init_0>;
// values
static auto const fun_0   = c2py::dispatcher_f_kw_t{c2py::cfun(c2py::castmc<>(&a_class::values))};
static const auto doc_d_0 = fun_0.doc({R"DOC(   )DOC"});

// ----- Method table ----
template <>
PyMethodDef c2py::tp_methods<a_class>[] = {
   {"values", (PyCFunction)c2py::pyfkw<fun_0>, METH_VARARGS | METH_KEYWORDS, doc_d_0.c_str()},
   {nullptr, nullptr, 0, nullptr} // Sentinel
};

constexpr auto doc_member_0 = R"DOC()DOC";

// ----- Method table ----

template <>
constinit PyGetSetDef c2py::tp_getset<a_class>[] = {
   c2py::getsetdef_from_member<&a_class::v, a_class>("v", doc_member_0),

   {nullptr, nullptr, nullptr, nullptr, nullptr}};

// ==================== module functions ====================

// trf
static auto const fun_1 = c2py::dispatcher_f_kw_t{c2py::cfun(c2py::cast<int>(&trf), "n")};

static const auto doc_d_1 = fun_1.doc({R"DOC(   )DOC"});
//--------------------- module function table  -----------------------------

static PyMethodDef module_methods[] = {
   {"trf", (PyCFunction)c2py::pyfkw<fun_1>, METH_VARARGS | METH_KEYWORDS, doc_d_1.c_str()},
   {nullptr, nullptr, 0, nullptr} // Sentinel
};

//--------------------- module struct & init error definition ------------

//// module doc directly in the code or "" if not present...
/// Or mandatory ?
static struct PyModuleDef module_def = {
   PyModuleDef_HEAD_INIT,
   "itertool",   /* name of module */
   "DOC MODULE", /* module documentation, may be NULL */
   -1,           /* size of per-interpreter state of the module, or -1 if the module keeps state in global variables. */
   module_methods,
   NULL,
   NULL,
   NULL,
   NULL};

//--------------------- module init function -----------------------------

extern "C" __attribute__((visibility("default"))) PyObject *PyInit_itertool() {

  // import numpy iff 'numpy/arrayobject.h' included
#ifdef Py_ARRAYOBJECT_H
  import_array();
#endif

  PyObject *m;

  if (PyType_Ready(&c2py::py_type_object<c2py::py_range>) < 0) return NULL;
  if (PyType_Ready(&c2py::py_type_object<a_class>) < 0) return NULL;

  m = PyModule_Create(&module_def);
  if (m == NULL) return NULL;

  auto &conv_table = *c2py::conv_table_sptr.get();

  conv_table[std::type_index(typeid(c2py::py_range)).name()] = &c2py::py_type_object<c2py::py_range>;
  CLAIR_C2PY_ADD_TYPE_OBJECT(a_class, "AClass");

  return m;
}
