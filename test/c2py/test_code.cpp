int f(int x) {
  std::cout << "f: x = " << x << std::endl;
  return x * 3;
}
int f(int x, int y) {
  std::cout << "f: x ,y = " << x << "  " << y << std::endl;
  return x + 10 * y;
}

int g(int x, int y) {
  std::cout << "x, y = " << x << "  " << y << std::endl;
  return x * 10 + y;
}

struct A {
  int k              = 12;
  std::vector<int> v = {1, 2, 3, 5};

  int f(int x) { return x * 2; }
  int size() const { return 10; }
  int operator[](int i) { return -i; }
  std::function<int(int)> make() {
    return [](int i) { return i + 100; };
  }
  int eval(std::function<int(int)> const &f) { return f(1000); }

  bool operator==(A const &) const = default;

  friend int a_friend(A const &a) { return -a.k; }

  int get_prop() const { return k; }
  void set_prop(int i) { k = i; }

  auto begin() const { return std::begin(v); }
  auto end() const { return std::end(v); }

  template <typename Ar> void serialize(Ar &ar, int) {
    ar &k;
    ar &v;
  }
};
std::ostream &operator<<(std::ostream &out, A const &a) { return out << "A : k = " << a.k << "\n"; }
bool operator<(A const &x, A const &y) { return x.k < y.k; }
A operator+(A const &x, A const &y) { return A{x.k + y.k}; }
A operator+(A const &x, int y) { return A{x.k + y}; }

// maker into a constructo
// \py A constructor
A maker_A(int i) {
  std::cout << " I am the A maker" << std::endl;
  return A{i};
}

template <typename T> struct B {
  T x;
  B(T y) : x{y} {}
  T f(T x) { return x * 2; }
};

template <typename T> std::ostream &operator<<(std::ostream &out, B<T> const &b) { return out << "Bi(" << b.x << ")"; }

// ===============  enum =====================

enum class MyEnum { A, B, C };
MyEnum test_enum(MyEnum x) { return x; }

// ===============  simple struct =====================
namespace N1 {

  struct params {

    /// An int
    int i;

    /// A double
    double x = 10;

    /// A vector of int
    std::vector<int> v;

    std::vector<int> w = {1, 2, 3};

    std::vector<int> &get() { return v; }
  };

  double pr(params const &p) { return p.x; }

} // namespace N1
