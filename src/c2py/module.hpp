#pragma once

// The front end (user facing) part of c2py library

// Annotations
#define C2PY_IGNORE __attribute__((annotate("c2py_ignore")))
#define C2PY_NOGIL __attribute__((annotate("c2py_nogil")))
#define C2PY_METHODS_AS_PROPERTY __attribute__((annotate("c2py_methods_as_property")))

namespace c2py_module {
  template <typename T> struct wrap_info {};
  template <typename T> struct add_methods_to {};
} // namespace c2py_module

namespace c2py {

  template <auto... T> struct dispatch_t {};
  template <auto... T> constexpr dispatch_t<T...> dispatch = {};

  template <typename... A> static constexpr auto cast = []<typename R>(R (*f)(A...)) { return f; };

  template <typename... A> static constexpr auto castm = []<typename R, typename C>(R (C::*f)(A...)) { return f; };

  template <typename... A> static constexpr auto castmc = []<typename R, typename C>(R (C::*f)(A...) const) { return f; };

  // For each type with an explicit converter
  // specialize, and give the name of the includer to be used.
  // template <typename T> static constexpr char *has_converter = nullptr;

  // FIXME : namespace module is not GREAT .... c2py_module ??
  namespace concepts {

    //---------------- Serialize-------------------
    // to force instantiation of the struct inside
    // FIXME RENAME
    template <typename T>
    concept fake_force_instantiation = requires {
      { c2py_module::wrap_info<T>{} };
      { c2py_module::add_methods_to<T>{} };
    };

    //---------------- Serialize-------------------

    struct fake_archive {};
    template <typename T> void operator&(fake_archive, T) {}

    template <typename T>
    concept HasSerializeLikeBoost = requires(T x, fake_archive ar) {
      { x.serialize(ar, 0) };
    };

  } // namespace concepts

} // namespace c2py
