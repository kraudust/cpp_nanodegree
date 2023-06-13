# Table of Contents
1. [Structures](#structures)
2. [Classes](#classes)
	1. [Constructors](#constructors)
	2. [Scope Resolution](#scope-resolution)
	3. [Namespaces](#namespaces)
	4. [Initializer Lists](#initializer-lists)
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

## Scope Resolution

C++ allows different identifiers (variable and function names) to have the same name, as long as they have different scope. For example, two different functions can each declare the variable int i, because each variable only exists within the scope of its parent function.

In some cases, scopes can overlap, in which case the compiler may need assistance in determining which identifier the programmer means to use. The process of determining which identifier to use is called "scope resolution".

```::``` is the scope resolution operator. This specifies which namespace or class to search in order to resolve an identifier. 

```cpp
Person::move(); \\ Call the move the function, member of Person class 
std::map m; \\ Initialize the map container from the C++ Standard Library
```

Each Class provides in own scope. Use scope resolution operator to separate class declaration from class definition.

```cpp
#include <cassert>
class Date {
 public:
  int Day() { return day; }
  void Day(int day);
  int Month() { return month; }
  void Month(int month);
  int Year() { return year; }
  void Year(int year);

 private:
  int day{1};
  int month{1};
  int year{0};
};

void Date::Day(int day) {
    if(day >= 1 && day <= 31)
        Date::day = day;
}

void Date::Month(int month) {
    if(month >= 1 && month <= 12)
        Date::month = month;
}

void Date::Year(int year) { Date::year = year; }

// Test in main
int main() {
  Date date;
  date.Day(29);
  date.Month(8);
  date.Year(1981);
  assert(date.Day() == 29);
  assert(date.Month() == 8);
  assert(date.Year() == 1981);
}
```

## Namespaces

[Namespaces](https://en.cppreference.com/w/cpp/language/namespace) allow programmers to group logically related variables and functions together. Namespaces also help to avoid conflicts between to variables that have the same name in different parts of a program.

```cpp
namespace English {
void Hello() { std::cout << "Hello, World!\n"; }
}  // namespace English

namespace Spanish {
void Hello() { std::cout << "Hola, Mundo!\n"; }
}  // namespace Spanish

int main() {
  English::Hello();
  Spanish::Hello();
}
```

### std Namespace
You are already familiar with the `std` namespace, even if you didn't realize quite what it was. `std` is the namespace used by the [C++ Standard Library](https://en.wikipedia.org/wiki/C%2B%2B_Standard_Library).

Classes like [`std::vector`](https://en.cppreference.com/w/cpp/container/vector) and functions like [`std::sort`](https://en.cppreference.com/w/cpp/algorithm/sort) are defined within the `std` namespace.

## Initializer Lists

[Initializer lists](https://en.cppreference.com/w/cpp/language/initializer_list) initialize member variables to specific values, just before the class constructor runs. This initialization ensures that class members are automatically initialized when an instance of the class is created.

```cpp
Date::Date(int day, int month, int year) : year_(y) {
  Day(day);
  Month(month);
}
```

In this example, the member value `year` is initialized through the initializer list, while `day` and `month` are assigned from within the constructor. Assigning `day` and `month` allows us to apply the invariants set in the mutator.

In general, [prefer initialization to assignment](http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#c49-prefer-initialization-to-assignment-in-constructors). Initialization sets the value as soon as the object exists, whereas assignment sets the value only after the object comes into being. This means that assignment creates an opportunity to accidentally use a variable before its value is set.

In fact, initialization lists ensure that member variables are initialized _before_ the object is created. This is why class member variables can be declared `const`, but only if the member variable is initialized through an initialization list. Trying to initialize a `const` class member within the body of the constructor will not work.

### Use initializer lists to set constants

Initializer lists exist for a number of reasons. First, the compiler can optimize initialization faster from an initialization list than from within the constructor.

A second reason is a bit of a technical paradox. If you have a `const` class attribute, you can only initialize it using an initialization list. Otherwise, you would violate the `const` keyword simply by initializing the member in the constructor!

The third reason is that attributes defined as [references](http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#S-glossary) must use initialization lists.

This exercise showcases several advantages of initializer lists.

```cpp
#include <assert.h>
#include <string>

struct Person {
public:
  Person(std::string name) : name(name) {}
  std::string const name;
};

// Test
int main() {
  Person alice("Alice");
  Person bob("Bob");
  assert(alice.name != bob.name);
}
```






