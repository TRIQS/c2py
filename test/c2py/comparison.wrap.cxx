
// C.f. https://numpy.org/doc/1.21/reference/c-api/array.html#importing-the-api
#define PY_ARRAY_UNIQUE_SYMBOL _cpp2py_ARRAY_API
#ifdef __clang__
#pragma clang diagnostic ignored "-W#warnings"
#endif
#include "comparison.cpp"
#include "c2py/c2py.hpp"

using c2py::operator"" _a;

// ==================== Wrapped classes =====================

template <> inline constexpr bool c2py::is_wrapped<N::cls_comp>   = true;
template <> inline constexpr bool c2py::is_wrapped<N::cls_equal>  = true;
template <> inline constexpr bool c2py::is_wrapped<N::cls_equal2> = true;

// ==================== enums =====================

// ==================== module classes =====================

template <> inline const std::string c2py::cpp_name<N::cls_comp>   = "N::cls_comp";
template <> inline constexpr auto c2py::tp_name<N::cls_comp>       = "comparison.ClsComp";
template <> inline constexpr const char *c2py::tp_doc<N::cls_comp> = R"DOC(   )DOC";

static auto init_0                                        = c2py::dispatcher_c_kw_t{c2py::c_constructor<N::cls_comp>()};
template <> constexpr initproc c2py::tp_init<N::cls_comp> = c2py::pyfkw_constructor<init_0>;

// ----- Method table ----
template <>
PyMethodDef c2py::tp_methods<N::cls_comp>[] = {

   {nullptr, nullptr, 0, nullptr} // Sentinel
};

constexpr auto doc_member_0 = R"DOC()DOC";

// ----- Method table ----

template <>
constinit PyGetSetDef c2py::tp_getset<N::cls_comp>[] = {c2py::getsetdef_from_member<&N::cls_comp::value, N::cls_comp>("value", doc_member_0),

                                                        {nullptr, nullptr, nullptr, nullptr, nullptr}};

template <> inline const std::string c2py::cpp_name<N::cls_equal>   = "N::cls_equal";
template <> inline constexpr auto c2py::tp_name<N::cls_equal>       = "comparison.ClsEqual";
template <> inline constexpr const char *c2py::tp_doc<N::cls_equal> = R"DOC(   )DOC";

static auto init_1                                         = c2py::dispatcher_c_kw_t{c2py::c_constructor<N::cls_equal>()};
template <> constexpr initproc c2py::tp_init<N::cls_equal> = c2py::pyfkw_constructor<init_1>;

// ----- Method table ----
template <>
PyMethodDef c2py::tp_methods<N::cls_equal>[] = {

   {nullptr, nullptr, 0, nullptr} // Sentinel
};

constexpr auto doc_member_1 = R"DOC()DOC";

// ----- Method table ----

template <>
constinit PyGetSetDef c2py::tp_getset<N::cls_equal>[] = {c2py::getsetdef_from_member<&N::cls_equal::value, N::cls_equal>("value", doc_member_1),

                                                         {nullptr, nullptr, nullptr, nullptr, nullptr}};

template <> inline const std::string c2py::cpp_name<N::cls_equal2>   = "N::cls_equal2";
template <> inline constexpr auto c2py::tp_name<N::cls_equal2>       = "comparison.ClsEqual2";
template <> inline constexpr const char *c2py::tp_doc<N::cls_equal2> = R"DOC(   )DOC";

static auto init_2                                          = c2py::dispatcher_c_kw_t{c2py::c_constructor<N::cls_equal2>()};
template <> constexpr initproc c2py::tp_init<N::cls_equal2> = c2py::pyfkw_constructor<init_2>;

// ----- Method table ----
template <>
PyMethodDef c2py::tp_methods<N::cls_equal2>[] = {

   {nullptr, nullptr, 0, nullptr} // Sentinel
};

constexpr auto doc_member_2 = R"DOC()DOC";

// ----- Method table ----

template <>
constinit PyGetSetDef c2py::tp_getset<N::cls_equal2>[] = {c2py::getsetdef_from_member<&N::cls_equal2::value, N::cls_equal2>("value", doc_member_2),

                                                          {nullptr, nullptr, nullptr, nullptr, nullptr}};

// ==================== module functions ====================

// operator<
static auto const fun_0 = c2py::dispatcher_f_kw_t{c2py::cfun([](N::cls_comp x, const N::cls_comp &y) { return operator<(x, y); }, "x", "y")};

// operator<=
static auto const fun_1 = c2py::dispatcher_f_kw_t{c2py::cfun([](N::cls_comp x, const N::cls_comp &y) { return operator<=(x, y); }, "x", "y")};

// operator==
static auto const fun_2 = c2py::dispatcher_f_kw_t{c2py::cfun([](N::cls_equal x, const N::cls_equal &y) { return operator==(x, y); }, "x", "y")};

// operator>
static auto const fun_3 = c2py::dispatcher_f_kw_t{c2py::cfun([](N::cls_comp x, const N::cls_comp &y) { return operator>(x, y); }, "x", "y")};

// operator>=
static auto const fun_4 = c2py::dispatcher_f_kw_t{c2py::cfun([](N::cls_comp x, const N::cls_comp &y) { return operator>=(x, y); }, "x", "y")};

static const auto doc_d_0 = fun_0.doc({R"DOC(   )DOC"});
static const auto doc_d_1 = fun_1.doc({R"DOC(   )DOC"});
static const auto doc_d_2 = fun_2.doc({R"DOC(   )DOC"});
static const auto doc_d_3 = fun_3.doc({R"DOC(   )DOC"});
static const auto doc_d_4 = fun_4.doc({R"DOC(   )DOC"});
//--------------------- module function table  -----------------------------

static PyMethodDef module_methods[] = {
   {"operator<", (PyCFunction)c2py::pyfkw<fun_0>, METH_VARARGS | METH_KEYWORDS, doc_d_0.c_str()},
   {"operator<=", (PyCFunction)c2py::pyfkw<fun_1>, METH_VARARGS | METH_KEYWORDS, doc_d_1.c_str()},
   {"operator==", (PyCFunction)c2py::pyfkw<fun_2>, METH_VARARGS | METH_KEYWORDS, doc_d_2.c_str()},
   {"operator>", (PyCFunction)c2py::pyfkw<fun_3>, METH_VARARGS | METH_KEYWORDS, doc_d_3.c_str()},
   {"operator>=", (PyCFunction)c2py::pyfkw<fun_4>, METH_VARARGS | METH_KEYWORDS, doc_d_4.c_str()},
   {nullptr, nullptr, 0, nullptr} // Sentinel
};

//--------------------- module struct & init error definition ------------

//// module doc directly in the code or "" if not present...
/// Or mandatory ?
static struct PyModuleDef module_def = {PyModuleDef_HEAD_INIT,
                                        "comparison", /* name of module */
                                        "DOC MODULE", /* module documentation, may be NULL */
                                        -1, /* size of per-interpreter state of the module, or -1 if the module keeps state in global variables. */
                                        module_methods,
                                        NULL,
                                        NULL,
                                        NULL,
                                        NULL};

//--------------------- module init function -----------------------------

extern "C" __attribute__((visibility("default"))) PyObject *PyInit_comparison() {

  // import numpy iff 'numpy/arrayobject.h' included
#ifdef Py_ARRAYOBJECT_H
  import_array();
#endif

  PyObject *m;

  if (PyType_Ready(&c2py::py_type_object<c2py::py_range>) < 0) return NULL;
  if (PyType_Ready(&c2py::py_type_object<N::cls_comp>) < 0) return NULL;
  if (PyType_Ready(&c2py::py_type_object<N::cls_equal>) < 0) return NULL;
  if (PyType_Ready(&c2py::py_type_object<N::cls_equal2>) < 0) return NULL;

  m = PyModule_Create(&module_def);
  if (m == NULL) return NULL;

  auto &conv_table = *c2py::conv_table_sptr.get();

  conv_table[std::type_index(typeid(c2py::py_range)).name()] = &c2py::py_type_object<c2py::py_range>;
  CLAIR_C2PY_ADD_TYPE_OBJECT(N::cls_comp, "ClsComp");
  CLAIR_C2PY_ADD_TYPE_OBJECT(N::cls_equal, "ClsEqual");
  CLAIR_C2PY_ADD_TYPE_OBJECT(N::cls_equal2, "ClsEqual2");

  return m;
}
