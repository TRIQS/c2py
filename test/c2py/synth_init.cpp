#pragma clang diagnostic ignored "-W#warnings"
#include <vector>
#include <string>
#include <c2py/module.hpp>
#include <c2py/c2py.hpp>
#include <c2py/converters/vector.hpp>

namespace N1 {

  struct A_ndc {
    int u; 
    A_ndc(int i): u(i) {}
    bool operator==(A_ndc const &) const = default;
  };
  
  struct params {

    /// An int
    int i;

    /// A double
    double x = 10;

    /// A vector of int
    std::vector<int> v;

    std::vector<int> w = {1,2,3};

    //std::vector<int> get() { return v;}
  };

  // Same with some non default constructible members...
  struct params_ndc {

    /// An int
    int i;

    /// A double
    double x = 10;

    /// A non default constructible object 
    A_ndc ndc1;

    /// A non default constructible object with a default init
    A_ndc ndc2 = A_ndc{9};

    /// A vector of int
    std::vector<int> v;

    std::vector<int> w = {1,2,3};
    
 };

  // double pr(params const &p) { return p.x; }


} // namespace N1


// =============== Declare module ===========================

namespace c2py_module {
  
   template<> struct wrap_info<N1::params> {
     static constexpr auto synthetize_init_from_pydict = true;
     static constexpr auto synthetize_dict_attribute = true;
   };


   template<> struct wrap_info<N1::params_ndc> {
     static constexpr auto synthetize_init_from_pydict = true;
     static constexpr auto synthetize_dict_attribute = true;
   };

}

