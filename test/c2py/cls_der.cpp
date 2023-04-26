#include <vector>
#include <iostream>

struct B {
  int ib = 12;
  int b(int u) { return u + 2; }
};

struct A : B {
  int a(int i, int j) { return i + j; }
};