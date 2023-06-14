#include <iostream>

class Foo {
 public:
  static int count;
  Foo() { Foo::count += 1; }
};

int Foo::count{0};

int main() {
  Foo f;
  std::cout << f.count << std::endl; // 1
  Foo f2;
  std::cout << f.count << ", " << f2.count << std::endl; // 2, 2
  Foo f3;
  std::cout << f.count << ", " << f2.count << ", " << f3.count << std::endl; // 3, 3, 3
  std::cout << &(f.count) << ", " << &(f2.count) << ", " << &(f3.count) << std::endl; // same address!
  std::cout << Foo::count << std::endl; // Can access the static data member without a class instantiation
  std::cout << Foo::count << std::endl; // 3
}