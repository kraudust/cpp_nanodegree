#include <iostream>

class DummyClass
{
public:
  DummyClass(int a, int b) : num1_(a), num2_(b) {}
  int add(const int& num1, int& num2) const
  {
    // num1_ = 5; // This produces a compilation error due to the function being const
    // num1 = 8; // This produces a compilation error due to the num1 reference being const
    num2 = 9;
    return num1 +  num2;
  }

  int num1_;
  int num2_;
};

int main()
{
  DummyClass dummy_class(7, 3);
  int first_num{1};
  int second_num{2};
  int output = dummy_class.add(first_num, second_num);
  std::cout << first_num << ", " << second_num << std::endl;
  std::cout << dummy_class.num1_ << ", " << dummy_class.num2_ << std::endl;

}