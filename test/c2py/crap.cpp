int f(int x) { return x * 3; }
int f(int x, int y) { return x + 10 * y; }

int f(int x);

int g(int x, int y=8) { return x * 10 + y; }

void hello() { } //std::cout << "Hello" << std::endl;}

namespace N {
auto tpl(auto x) { return -2;}
template<int N> int tplxx() { return 4;}

int h(auto x) 
{ return x + 4;}

}
// ==========  wrapping code ==========
// Declare the module

namespace c2py { 
//template<auto ...T> constexpr bool WRAP=false;
//template<typename ...T> constexpr int dispatch1(T...) { return 1;}
template<auto ...T> struct dispatch_t{};
template<auto ...T> constexpr dispatch_t dispatch = {};
}

namespace c2py::modules {

  using namespace N;

  auto module_name = "basicfun";

  auto documentation = "Module documentation";

}

 //std::string s = "Ee";
 int y = 2;
 myvar<double>;

}
