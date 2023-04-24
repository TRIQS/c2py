#ifdef H5_INTERFACE_INCLUDED

#include <h5/serialization.hpp>

namespace c2py {

  /// hdf5 is not defined for this object, we still but a function + exception for a clear and early error message.
  template <typename Cls> static PyObject *tpxx_write_h5(PyObject *self, PyObject *args) {
    static auto l                = [](Cls const &self_c, h5::group g, const char *key) { h5_write(g, key, self_c); };
    static dispatcher_f_kw_t ovs = {cmethod(+l, "cls", "g", "key")}; // lambda FIXME for method : take self : change the call ?
    return ovs(self, args, nullptr);
  }

  template <typename T> std::function<PyObject *(PyObject *, std::string)> make_py_h5_reader(const char *) {

    auto reader = [](PyObject *h5_gr, std::string const &name) -> PyObject * {
      auto gr = py2cxx<h5::group>(h5_gr);
      try {
        // Now call the proper h5_read
        // If T is a view type grab the regular_t of it
        if constexpr (requires { typename T::regular_type; })
          return cxx2py(T{h5::h5_read<typename T::regular_type>(gr, name)});
        else
          return cxx2py(T{h5::h5_read<T>(gr, name)});
      } catch (std::exception const &e) {
        auto err = std::string(".. Error  : \n") + e.what() + "\nin h5 reading of object of type " + typeid(T).name();
        PyErr_SetString(PyExc_RuntimeError, err.c_str());
      }
    };
    return {reader};
  }

  template <typename T> void register_h5_type(pyref const &register_class) {
    pyref h5_reader = cxx2py(make_py_h5_reader<T>(tp_name<T>));
    pyref ds        = cxx2py(h5::get_hdf5_format<T>());
    pyref res = PyObject_CallFunctionObjArgs(register_class, (PyObject *)(&py_type_object<T>), Py_None, (PyObject *)h5_reader, (PyObject *)ds, NULL);
  }

  // *****************************************************************
  //  Serialization via hdf5
  // *****************************************************************

  // ---------------   getstate_h5 ----------------------------
  // Returns a tuple with the function to call, the tuple
  //
  template <typename T>
  static constexpr PyCFunction getstate_h5 = [](PyObject *self, PyObject *) -> PyObject * {
    auto &self_c = py_converter<T>::py2c(self);
    return cxx2py(h5::serialize(self_c));
  };

  // ---------------  setstate_h5  ----------------------------
  // deserialize_h5, deserialize_repr, ....
  //
  template <typename T>
  static constexpr PyCFunction setstate_h5 = [](PyObject *self, PyObject *state) -> PyObject * {
    try {
      auto a                   = py2cxx<std::vector<std::byte>>(state);
      ((py_type<T> *)self)->_c = new T{h5::deserialize<T>(a)};
      Py_RETURN_NONE;
    } catch (std::exception const &e) {
      PyErr_SetString(PyExc_RuntimeError, ("in deserialization of object "s + tp_name<T>).c_str());
      return nullptr;
    }
  };

} // namespace c2py

#endif
