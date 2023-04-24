// Annotation

C2PY_IGNORE  void f(); // do not wrap
C2PY_NOGIL  void f(); // do not wrap

// ==========  Module declaration ==========

// Put the configuration information
// in the namespace c2py_module
// One module per file only
//
//  * Only the following variables, declarations, are authorized in this namespace,
//       anything not recognized is an error (except "using namespace" clauses).
//
namespace c2py_module {

  // Name of the module : default is the filename
  auto module_name = "MyModule";

  // Name of the package : default is ""
  auto package_name = "A.B";

  // The documentation string of the module [default = ""]
  auto documentation = "Module documentation";

  // Namespace to restrict search // TODO : add list of string ?
  auto ns = "N"; // [string = ""]

  // Rules to restrict the functions of the module
  // [string] a space separated list of regex. Any function matching one of them is accepted.
  // Default ".*" (i.e. anything).
  auto fun_accept_only = "f";
  auto fun_reject      = "f";

  // Rules to restrict the functions of the module
  // [string] a space separated list of regex. Any function matching one of them is accepted.
  // Default ".*" (i.e. anything).
  auto cls_accept_only = "...";
  auto cls_reject      = "f";

  // [Optional] An init function to be called at the module importation
  // should be () -> void
  auto module_init = []() {};

  // ----- Functions explicitly wrapped ----
  namespace functions {

    // The name of the alias is the Python name of the function
    // The Python function is a dynamic dispatch of the list of function (ordinary or template instantiation)
    // e.g.
    auto fg = c2py::dispatch<N::f, N::g>;
    auto h  = c2py::dispatch<N::h<int>, N::h<double>>;

    // Clang find other function with the Rules above and implicitly add other dispatch, e.g.
    // using f = c2py::dispatch< all f overloads found after filter>
    // if f was used explicitly, and some functions are orphans, they are ignored, maybe with warning

    // This allows to :
    // - rename a function in Python
    // - group some functions in the same dispatch at will
    // - use template instantiation
    // NB : dispatch is an empty struct, it is just there to list the functions...

  } // namespace functions

  // ----- Wrapped classes --------
  using ClsPythonName = ClsCppName;
  // .e.g
  using A  = N::A;
  using Bi = N::B<int>;

  // Clang find classes according to the Rules above and implicitly add
  //using C = C

  // Contains some optional information on the wrapping of 
  // e.g. A . Also works for template with partial spe.
  template <> struct wrap_info<A> {

    // Base class [Optional] NOT IMPLEMENTED.
    using base = B;

    // List of bases class to merge [optional]
    using bases_to_merge = std::tuple<...>;

    // Regex to select some methods. NOT IMPLEMENTED.
    static constexpr auto meth_regex = "";

    // For simple struct (no constructor), synthetize a construction from a pydict
    auto synthetize_constructor = true; //

  };

  /// Declaration of arithmetic operations
  template <> auto arithmetic<A> = c2py::arithmetic<Op<"+", A, A, R>, ...>; // variable template

  /// Additional methods to add to the Python class
  /// e.g. method template instantiation, or new injected function h
  template <> struct add_methods_to<A> {
    static constexpr auto h  = c2py::dispatch<&N::A<int>::h<int>, N::h<double>>;
    static constexpr auto h1 = c2py::dispatch_static<&N::A<int>::h<int>, N::h<double>>;
  };


} // namespace c2py::module
