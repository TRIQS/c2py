#pragma clang diagnostic ignored "-W#warnings"

#include <vector>
#include <iostream>
#include <c2py/module.hpp>
#include <c2py/c2py.hpp>

/**
 Brief description of A

 A long description of A.
 with multiple lines
*/
struct A {
  int k                 = 12;
  const int k_immutable = 23;
  std::vector<int> v    = {1, 2, 3, 5};

  A() = default;
  A(int i) : k(i) {}

  auto f(int x) { return x * 2; }
  int f(int x) const { return x * 2; }

  //int const & get_k() const { return k;}

  using index_t = long;
  index_t f_w_alias(index_t i) const { return 2 * i; }

  friend int a_friend(A const &a) { return -a.k; }

  double tpl(auto x) { return 256 + x; }

  int prop1() const { return k; }

  void no_prop() { k *= 10; }

  //C2PY_PROPERTY("p")
  //int get_prop() const { return k; }
  //C2PY_PROPERTY_SETTER("p")
  //void set_prop(int i) { k = i; }

  int &operator[](int i) { return v[i]; }
  int operator[](int i) const { return v[i]; }
  int size() const { return v.size(); }

  int operator()(int i) { return k + i; }
  int operator()(int i, int j) const { return k + i + 10 * j; }

  auto begin() const { return std::begin(v); }
  auto end() const { return std::end(v); }

  bool operator==(A const &) const = default;

  //int const & bad() { return v[0];}

  template <typename Ar> void serialize(Ar &ar, int) {
    ar &k;
    ar &v;
  }
};

std::ostream &operator<<(std::ostream &out, A const &a) { return out << "A : k = " << a.k << "\n"; }

bool operator<(A const &x, A const &y) { return x.k < y.k; }

// Additional method
//C2PY_METHOD_OF(A)
int hhh(A const &a, int j) { return j + 20; }

// maker into a constructor
A maker_A(int i) {
  std::cout << " I am the A maker" << std::endl;
  return A{i};
}

// To check the filter : it should not compile if hidden is filtered out
struct hidden {};
void fff(hidden h) {}

/// test implementation outside of class

struct dummy_class {
  double do_thing(double x);
};
double dummy_class::do_thing(double x) { return 3 * x; }

// =============== Declare module ===========================

namespace c2py_module {

  constexpr auto regex_exclude = "hidden";
  constexpr auto regex_exclude_fun = "fff";

  constexpr auto get_set_as_properties = true;
  auto module_init                     = []() { std::cout << "Starting module" << std::endl; };

  template <> struct add_methods_to<A> {
    static constexpr auto h = c2py::dispatch<hhh>;
  };

} // namespace c2py_module
