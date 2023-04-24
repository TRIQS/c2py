#pragma clang diagnostic ignored "-W#warnings"

#include <c2py/module.hpp>
#include <c2py/c2py.hpp>
#include <c2py/converters/pair.hpp>

int f1(int x) { return x * 3; }
int f1(double x) { return -x * 10; }

/** 
 * A doc for f(x)
 * 
 * @param x The doc of x
 */ 
int f(int x) { return x * 3; }

/** 
 * A doc for f(x,y)
 * 
 * @param x The doc of x
 * @param y The doc of y
 */ 
int f(int x, int y) { return x + 10 * y; }

int f(int x);

int g(int x, int y = 8) { return x * 10 + y; }

using return_t = double;
std::pair<return_t, double> ret_with_alias() { return std::make_pair(1.3, 2.0); }

static_assert(c2py::concepts::IsConvertibleC2Py<std::pair<return_t, double> >);

// attribute declaration must precede definition ! Cf clang message if reverse order.
C2PY_IGNORE int ignored(int x);
int ignored(int x) { return x * 3; }

namespace N {
  auto tpl(auto x) { return -2; }
  template <int N> int tplxx() { return 4; }

  auto h(auto x) { return x + 4; }

} // namespace N

// ==========  Declare the module ==========

namespace c2py_module {

  auto documentation = "Module documentation";

  namespace functions {
    //auto f  = c2py::dispatch<c2py::cast<int>(::f), c2py::cast<double>(::f)>;
    auto h  = c2py::dispatch<N::h<int>, N::h<double>>;
    auto hf = c2py::dispatch<c2py::cast<int>(::f1), N::h<double>>;

  } // namespace functions

} // namespace c2py_module
