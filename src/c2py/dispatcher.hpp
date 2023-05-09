#pragma once
#include <algorithm>
#include "pycfun_kw.hpp"
namespace c2py {

  // =============== dynamic dispatcher ========================

  // Gather a set of overload and handle the calls and error reporting
  template <typename Eraser, bool Constructors = false> struct dispatcher_t {
    std::vector<std::unique_ptr<Eraser>> ov_list;

    template <typename... U> dispatcher_t(U &&...u) { ((void)ov_list.push_back(std::forward<U>(u)), ...); }

    private:
    // impl detail of ()
    PyObject *call_impl(PyObject *self, PyObject *args, PyObject *kwargs) const {

      for (auto const &ov : ov_list)
        if (ov->is_callable(self, args, kwargs)) return ov->operator()(self, args, kwargs);

      // The call has failed. We rerun, but raising the exception in each case, and report
      std::stringstream err;
      err << "[c2py] Can not call the function with the arguments\n";
      if (self) err << "  - " << PyUnicode_AsUTF8(pyref{PyObject_Str(self)}) << "\n";
      if (args) err << "  - " << PyUnicode_AsUTF8(pyref{PyObject_Str(args)}) << "\n";
      if (kwargs) err << "  - " << PyUnicode_AsUTF8(pyref{PyObject_Str(kwargs)}) << "\n";
      int c = 0;
      for (auto const &ov : ov_list) {
        ++c;
        ov->is_callable(self, args, kwargs, true);

        PyObject *error_msg = nullptr, *ptype = nullptr, *ptraceback = nullptr;
        PyErr_Fetch(&ptype, &error_msg, &ptraceback);
        if (error_msg and PyUnicode_Check(error_msg)) err << "[" << c << "] " << ov->signature() << "\n   " << PyUnicode_AsUTF8(error_msg) << "\n";
        Py_XDECREF(ptype);
        Py_XDECREF(ptraceback);
        Py_XDECREF(error_msg);
      }
      PyErr_SetString(PyExc_TypeError, err.str().c_str());
      return nullptr;
    }

    public:
    // Call each overload. The first available is used.
    // if not is ok, we recall the is_callable to build a proper error with the exceptions
    auto operator()(PyObject *self, PyObject *args, PyObject *kwargs = nullptr) const {
      PyObject *r = call_impl(self, args, kwargs);
      if constexpr (not Constructors)
        return r;
      else
        return int(r == nullptr ? -1 : 0);
    }

    //
    [[nodiscard]] std::string signatures() const {
      std::stringstream fs;
      for (auto const &ov : ov_list) fs << ov->signature() << "\n";
      return fs.str();
    }

    // overload doc (string) in case only one overload ...
    // FIXME : to make generated code simpler in most cases.
    [[nodiscard]] std::string doc(std::initializer_list<const char *> const &docs) const {
      assert(docs.size() == ov_list.size()); // by construction for the automated tool
      std::stringstream fs;
      fs << "Dispatched C++ function\n";
      int i = 0;
      // FIXME : use format when in std
      for (auto const &x : docs) fs << "[" << i + 1 << "]  " << ov_list[i++]->signature() << "\n\n" << x << "\n\n";
      return fs.str();
    }
  };

  // ==============================

  using dispatcher_f_kw_t = dispatcher_t<pycfun_kw, false>;
  using dispatcher_c_kw_t = dispatcher_t<pycfun_kw, true>;

} // namespace c2py
