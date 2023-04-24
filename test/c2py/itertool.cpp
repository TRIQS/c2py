#pragma clang diagnostic ignored "-W#warnings"

#include <itertools/itertools.hpp>
#include <functional> // FIXME This should be automatic in the CXX

#include <c2py/module.hpp>
#include <c2py/c2py.hpp>

template <typename T, typename L>
struct c2py::py_converter<itertools::detail::transformed<T, L>> : c2py::py_converter_to_py_range{};

static_assert(c2py::concepts::IsConvertibleC2Py<itertools::detail::transformed<std::vector<int>, decltype([](auto &&x) { return x * x; })>>);

struct a_class {
  std::vector<int> v;
  a_class() : v{1, 2, 3, 4} {}

  auto values() const {
    return itertools::transform(v, [](auto &&x) { return x * x; });
  }
};

auto trf(int n) {
  std::vector<int> v(n);
  for (int i = 0; i < n; ++i) v[i] = i + 1;
  return itertools::transform(std::move(v), [](auto &&x) { return x * x; });
}
