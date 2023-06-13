# Table of Contents
1. [Structures](#structures)
2. [Classes](#classes)
	1. [Constructors](#constructors)

# Structures

Allows developers to create their own types to aggregate data relevant to their needs.
```cpp
struct Date {
  int day{1};
  int month{1};
  int year{0};
};
// Create an instance of the Date structure
Date date;
// Initialize the attributes of Date
date.day = 1;
date.month = 10;
date.year = 2019;
```

By default members of a struct are public, and you can set them (for example data.day = 1). Can use private: and public: in struct to change user access.

```cpp
#include <cassert>
#include <iostream>

struct Date {
 public:
  int Day() { return day; }
  void Day(int day) { this->day = day; }
  int Month() { return month; }
  void Month(int month) { this->month = month; }
  int Year() { return year; }
  void Year(int year) { this->year = year; }

 private:
  int day{1};
  int month{1};
  int year{0};
};

int main() {
  Date date;
  date.Day(29);
  date.Month(8);
  date.Year(1981);
  assert(date.Day() == 29);
  assert(date.Month() == 8);
  assert(date.Year() == 1981);
  std::cout << date.Day() << "/" << date.Month() << "/" << date.Year() << "\n";
}
```

Sometimes accessors are not necessary, or even advisable. The [C++ Core Guidelines](https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md#Rh-get) recommend, "A trivial getter or setter adds no semantic value; the data item could just as well be public."

# Classes

Classes, like structures, provide a way for C++ programmers to aggregate data together in a way that makes sense in the context of a specific program. By convention, programmers use structures when member variables are independent of each other, and [use classes when member variables are related by an "invariant"](http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#c2-use-class-if-the-class-has-an-invariant-use-struct-if-the-data-members-can-vary-independently).
- An "invariant" is a rule that limits the values of member variables. For example, in a Date class, an invariant would specify that the member variable day cannot be less than 0. Another invariant would specify that the value of day cannot exceed 28, 29, 30, or 31, depending on the month and year. Yet another invariant would limit the value of month to the range of 1 to 12.
- By default struct members are public, but by default, class members are private.
- As a general rule, member data subject to an invariant should be specified private, in order to enforce the invariant before updating the member's value.

## Constructors
```cpp
class Date {
 public:
  Date(int d, int m, int y) {  // This is a constructor.
    Day(d);
  }
  
  int Day() { return day; }
  void Day(int d) {
    if (d >= 1 && d <= 31) day = d;
  }

  int Month() { return month; }
  void Month(int m) {
    if (m >= 1 && m <= 12) month = m;
  }

  int Year() { return year_; }
  void Year(int y) { year = y; }

 private:
  int day{1};
  int month{1};
  int year{0};
};
```



