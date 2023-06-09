#pragma clang diagnostic ignored "-W#warnings"
#include <vector>
#include <c2py/module.hpp>
#include <c2py/c2py.hpp>


namespace N {

  template <typename T> struct my_base_templated {
    my_base_templated() = default;
    
    // FIXME 
    //T f_base_tpl(int u) { return u + 0.5; }

    using index_t = long;
    // FIXME 
    //index_t get(index_t i) const { return i; }
    long get(long i) const { return i; }
  };

  struct my_base {
    int f_base(int u) { return 10*u;}
  };

  struct my_private_base {
    void f_private_base(int u) {}
  };

  struct my_class : private my_private_base, public my_base, public my_base_templated<double> {

    int i;
    my_class() = default;
    my_class(int u) { i = u; }

  };

} // namespace N

// =============== Declare module ===========================

namespace c2py_module {

  auto cls_reject = "N::my_private_base";
  
  template <> struct wrap_info<N::my_class> {

    // List of bases class to merge 
    using bases_to_merge = std::tuple<N::my_base, N::my_base_templated<double>>;
  };

} // namespace c2py_module
