
// C.f. https://numpy.org/doc/1.21/reference/c-api/array.html#importing-the-api
#define PY_ARRAY_UNIQUE_SYMBOL _cpp2py_ARRAY_API
#ifdef __clang__
#pragma clang diagnostic ignored "-W#warnings"
#endif
#include "tpl_derived.cpp"
#include "c2py/c2py.hpp"

using c2py::operator"" _a;

// ==================== Wrapped classes =====================

template <> inline constexpr bool c2py::is_wrapped<N::my_class> = true;

// ==================== enums =====================

// ==================== module classes =====================

template <> inline const std::string c2py::cpp_name<N::my_class>   = "N::my_class";
template <> inline constexpr auto c2py::tp_name<N::my_class>       = "tpl_derived.MyClass";
template <> inline constexpr const char *c2py::tp_doc<N::my_class> = R"DOC(   )DOC";

// The base classes which are to be merged
template <> struct c2py::merged_into<N::my_base> : c2py::merged_into<N::my_class> {};
template <> struct c2py::merged_into<N::my_base_templated<double>> : c2py::merged_into<N::my_class> {};
static auto init_0 =
   c2py::dispatcher_c_kw_t{c2py::c_constructor<N::my_class>(), c2py::c_constructor<N::my_class, int>("u")};
template <> constexpr initproc c2py::tp_init<N::my_class> = c2py::pyfkw_constructor<init_0>;
// f_base
static auto const fun_0 = c2py::dispatcher_f_kw_t{c2py::cfun(c2py::castm<int>(&N::my_class::f_base), "u")};

// get
static auto const fun_1   = c2py::dispatcher_f_kw_t{c2py::cfun(c2py::castmc<long>(&N::my_class::get), "i")};
static const auto doc_d_0 = fun_0.doc({R"DOC(   )DOC"});
static const auto doc_d_1 = fun_1.doc({R"DOC(   )DOC"});

// ----- Method table ----
template <>
PyMethodDef c2py::tp_methods<N::my_class>[] = {
   {"f_base", (PyCFunction)c2py::pyfkw<fun_0>, METH_VARARGS | METH_KEYWORDS, doc_d_0.c_str()},
   {"get", (PyCFunction)c2py::pyfkw<fun_1>, METH_VARARGS | METH_KEYWORDS, doc_d_1.c_str()},
   {nullptr, nullptr, 0, nullptr} // Sentinel
};

constexpr auto doc_member_0 = R"DOC()DOC";

// ----- Method table ----

template <>
constinit PyGetSetDef c2py::tp_getset<N::my_class>[] = {
   c2py::getsetdef_from_member<&N::my_class::i, N::my_class>("i", doc_member_0),

   {nullptr, nullptr, nullptr, nullptr, nullptr}};

// ==================== module functions ====================

//--------------------- module function table  -----------------------------

static PyMethodDef module_methods[] = {
   {nullptr, nullptr, 0, nullptr} // Sentinel
};

//--------------------- module struct & init error definition ------------

//// module doc directly in the code or "" if not present...
/// Or mandatory ?
static struct PyModuleDef module_def = {
   PyModuleDef_HEAD_INIT,
   "tpl_derived", /* name of module */
   "DOC MODULE",  /* module documentation, may be NULL */
   -1, /* size of per-interpreter state of the module, or -1 if the module keeps state in global variables. */
   module_methods,
   NULL,
   NULL,
   NULL,
   NULL};

//--------------------- module init function -----------------------------

extern "C" __attribute__((visibility("default"))) PyObject *PyInit_tpl_derived() {

  // import numpy iff 'numpy/arrayobject.h' included
#ifdef Py_ARRAYOBJECT_H
  import_array();
#endif

  PyObject *m;

  if (PyType_Ready(&c2py::py_type_object<c2py::py_range>) < 0) return NULL;
  if (PyType_Ready(&c2py::py_type_object<N::my_class>) < 0) return NULL;

  m = PyModule_Create(&module_def);
  if (m == NULL) return NULL;

  auto &conv_table = *c2py::conv_table_sptr.get();

  conv_table[std::type_index(typeid(c2py::py_range)).name()] = &c2py::py_type_object<c2py::py_range>;
  CLAIR_C2PY_ADD_TYPE_OBJECT(N::my_class, "MyClass");

  return m;
}
