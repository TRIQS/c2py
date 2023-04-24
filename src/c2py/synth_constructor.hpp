#pragma once
#include "py_converter.hpp"
#include "converters/basic_types.hpp"
#include "pytypes.hpp"
namespace c2py {

  using namespace std::string_literals;

  // FIXME : split pydict ...

  struct pydict : pyref {
    pydict() : pyref{PyDict_New()} {}
    pydict(PyObject *ob) : pyref{borrowed(ob)} { assert(PyDict_Check(ob)); }
    pydict(pyref p) : pyref{p} {}

    struct proxy {
      PyObject *self;
      const char *key;
      proxy &operator=(auto &x) {
        PyDict_SetItemString(self, key, c2py::pyref{c2py::cxx2py(x)}); // PyDict_SetItemString does NOT steal a reference to val
        return *this;
      }
      operator PyObject *() const { return PyDict_GetItemString(self, key); } // BORROWED
    };
    proxy operator[](const char *key) { return proxy{*this, key}; }
    proxy const operator[](const char *key) const { return proxy{*this, key}; }
    //PyObject *operator[](const char * key) const { return PyDict_GetItemString(self, key);}

    bool contains(const char *key) const { return PyDict_GetItemString(*this, key) != nullptr; }
  };

  // --------

  template <> struct py_converter<pydict> {
    static PyObject *c2py(pydict d) { return d.new_ref(); }
    static bool is_convertible(PyObject *ob, bool raise_exception) {
      bool r = PyDict_Check(ob);
      if (r) return true;
      if (raise_exception) PyErr_SetString(PyExc_TypeError, ("Object is not a dictionary"));
      return false;
    }
    static pydict py2c(PyObject *ob) { return {borrowed(ob)}; }
  };

  // --------------------

  class pydict_extractor {

    pydict dic;
    std::stringstream err;
    std::vector<std::string> used_keys;

    public:
    pydict_extractor(PyObject *kw) : dic((kw ? c2py::borrowed(kw) : c2py::pyref{PyDict_New()})) {}

    private:
    std::string make_error_mandatory(PyObject *obj, const char *var_name, std::string const &var_cpp_type_name) {
      std::stringstream out;
      out << "\n The parameter " << var_name << " does not have the right type : expecting " << var_cpp_type_name << " in C++, but got '"
          << Py_TYPE(obj)->tp_name << "' in Python.";
      return out.str();
    }

    template <typename T> void call_impl(const char *varname, T &x, PyObject *pyarg) {
      used_keys.emplace_back(varname);
      if (py_converter<T>::is_convertible(pyarg, false))
        x = py2cxx<T>(pyarg);
      else {
        err << make_error_mandatory(pyarg, varname, cpp_name<T>);
        py_converter<T>::is_convertible(pyarg, true); // raise exception
        if (PyErr_Occurred()) {
          PyObject *error_msg = nullptr, *ptype = nullptr, *ptraceback = nullptr;
          PyErr_Fetch(&ptype, &error_msg, &ptraceback);
          if (error_msg and PyUnicode_Check(error_msg)) err << "   Explanation: " << PyUnicode_AsUTF8(error_msg) << "\n";
          Py_XDECREF(ptype);
          Py_XDECREF(ptraceback);
          Py_XDECREF(error_msg);
        }
      }
    }

    public:
    void operator()(const char *varname, auto &x, bool is_optional = false) {
      PyObject *pyarg = dic[varname];
      if (pyarg)
        call_impl(varname, x, pyarg);
      else if (not is_optional)
        err << "\n Mandatory parameter '" << varname << "' is missing. \n";
    }

    // Mandatory get
    template <typename T> T get(const char *varname) {
      PyObject *pyarg = dic[varname];
      if (not pyarg) throw std::runtime_error("The mandatory parameter '"s + varname + "' is missing");
      used_keys.emplace_back(varname);
      if (not py_converter<T>::is_convertible(pyarg, true)) throw std::runtime_error(make_error_mandatory(pyarg, varname, cpp_name<T>));
      return py2cxx<T>(pyarg);
    }

    /* void operator()(const char *varname, auto &x, auto &default_value) {*/
    //pyref pyarg = PyDict_GetItemString(dic, varname);
    //if (pyarg.is_null()) {
    //x = default_value;
    //return;
    //}
    //call_impl(varname, x, pyarg);
    /*}*/

    std::string report(bool report_unknown_keys = true) {
      std::sort(used_keys.begin(), used_keys.end());
      if (report_unknown_keys) {
        pyref keys         = PyDict_Keys(dic);                 // new ref
        PyListObject *list = (PyListObject *)(PyObject *)keys; //NOLINT
        int l              = PySequence_Fast_GET_SIZE(list);
        for (int i = 0; i < l; ++i) {
          PyObject *k   = PySequence_Fast_GET_ITEM(list, i); // borrowed
          std::string s = PyUnicode_AsUTF8(k);
          if (not std::binary_search(begin(used_keys), end(used_keys), s)) err << "\n The parameter '" << s << "' is not recognized.";
        }
      }
      return err.str();
    }

    int check() {
      auto s     = report();
      bool error = not s.empty();
      if (error) PyErr_SetString(PyExc_RuntimeError, s.c_str());
      return (error ? -1 : 0);
    }
  };

} // namespace c2py
