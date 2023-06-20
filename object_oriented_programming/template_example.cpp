#include <cmath>
#include <iostream>

// TODO: Create a generic function Product that multiplies two parameters
template <typename T> T Product (T a, T b)
{
    return a * b;
}

template <typename T> T Max(T a, T b) {
    return a > b ? a : b;
}

int main() {
  double var = 0.01;
  std::cout << Product<int>(10, 2) << std::endl;
  std::cout << Product<double>(10., 2.) << std::endl; 
  std::cout << Product<float>(10.f, 2.f) << std::endl;
  std::cout << Product(10.f, 2.f) << std::endl; // can call without the <type> as well
  int a = 2;
  double d = 10.1;
  std::cout << Product<int>(d, a) << std::endl; // casts the double to an int inherently
  std::cout << Product<double>(d, a) << std::endl; // casts the int to a double inherently
  // std::cout << Product(d, a) << std::endl; // no casting occurs and won't compile due to d and a being different types
  std::cout << "-------------------------" << std::endl;
  std::cout << Max<int>(10, 50) << std::endl;
  std::cout << Max<int>(5.7, 1.436246) << std::endl; // Returns 5 since this casts to ints
  std::cout << Max(5.7, 1.436246) << std::endl; // Returns 5.7 since it knows these are doubles
}