# Table of Contents
1. [Structures](#structures)
2. [Classes](#classes)
	1. [Constructors](#constructors)
	2. [Scope Resolution](#scope-resolution)
	3. [Namespaces](#namespaces)
	4. [Initializer Lists](#initializer-lists)
		1. [Use initializer lists to set constants](#use-initializer-lists-to-set-constants)
	5. [Encapsulation](#encapsulation)
	6. [Accessors](#accessors)
	7. [Mutators](#mutators)
	8. [Access Modifiers](#access-modifiers)
	9. [Abstraction](#abstraction)
	10. [Static Members](#static-members)
	11. [Static Methods](#static-methods)
	12. [Const Data Members](#const-data-members)
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

## Encapsulation

[Encapsulation](https://en.wikipedia.org/wiki/Encapsulation_(computer_programming%29)) is the grouping together of data and logic into a single unit. In object-oriented programming, classes encapsulate data and functions that operate on that data.

This can be a delicate balance, because on the one hand we want to group together relevant data and functions, but on the hand we want to [limit member functions to only those functions that need direct access to the representation of a class](http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#c4-make-a-function-a-member-only-if-it-needs-direct-access-to-the-representation-of-a-class).

In the context of a `Date` class, a function `Date Tomorrow(Date const & date)` probably does not need to be encapsulated as a class member. It can exist outside the `Date` class.

However, a function that calculates the number of days in a month probably should be encapsulated with the class, because the class needs this function in order to operate correctly.

More Date class example of functions that could be captured in this class:
```cpp
#include <cassert>

class Date {
public:
  Date(int day, int month, int year);
  int Day() const { return day_; }
  void Day(int day);
  int Month() const { return month_; }
  void Month(int month);
  int Year() const { return year_; }
  void Year(int year);

private:
  bool LeapYear(int year) const;
  int DaysInMonth(int month, int year) const;
  int day_{1};
  int month_{1};
  int year_{0};
};

Date::Date(int day, int month, int year) {
  Year(year);
  Month(month);
  Day(day);
}

bool Date::LeapYear(int year) const {
    if(year % 4 != 0)
        return false;
    else if(year % 100 != 0)
        return true;
    else if(year % 400 != 0)
        return false;
    else
        return true;
}

int Date::DaysInMonth(int month, int year) const {
    if(month == 2)
        return LeapYear(year) ? 29 : 28;
    else if(month == 4 || month == 6 || month == 9 || month == 11)
        return 30;
    else
        return 31;
}

void Date::Day(int day) {
  if (day >= 1 && day <= DaysInMonth(Month(), Year()))
    day_ = day;
}

void Date::Month(int month) {
  if (month >= 1 && month <= 12)
    month_ = month;
}

void Date::Year(int year) { year_ = year; }

// Test
int main() {
  Date date(29, 2, 2016);
  assert(date.Day() == 29);
  assert(date.Month() == 2);
  assert(date.Year() == 2016);
    
  Date date2(29, 2, 2019);
  assert(date2.Day() != 29);
  assert(date2.Month() == 2);
  assert(date2.Year() == 2019);
}
```

## Accessors

Accessor functions are public member functions that allow users to access an object's data, albeit indirectly.

Accessors should only retrieve data. They should not change the data stored in the object.

The main role of the `const` specifier in accessor methods is to protect member data. When you specify a member function as `const`, the compiler will prohibit that function from changing any of the object's member data.

Using the same Date class from above, the following is an example of a accessor (getter).

```cpp
int Day() const { return day_; }
```

## Mutators

A mutator ("setter") function can apply logic ("invariants") when updating member data. Keeps users from setting member data to an invalid state.

Example from Date class above:
```cpp
void Day(int day);
void Date::Day(int day) {
  if (day >= 1 && day <= DaysInMonth(Month(), Year()))
    day_ = day;
}
```

## Access Modifiers

- Public: access to anyone
- Private: access only within the class
- Protected: access only within friend classes (and the class) 

Learn more [here](https://www.tutorialspoint.com/cplusplus/cpp_class_access_modifiers.htm)

## Abstraction

Abstraction refers to the separation of a class's interface from the details of its implementation. The interface provides a way to interact with an object, while hiding the details and implementation of how the class works.

The `String()` function within this `Date` class is an example of abstraction.

```cpp
class Date {
 public:
  ...
  std::string String() const;
  ...
};
```

The user is able to interact with the `Date` class through the `String()` function, but the user does not need to know about the implementation of either `Date` or `String()`.

For example, the user does not know, or need to know, that this object internally contains three `int` member variables. The user can just call the `String()` method to get data.

If the designer of this class ever decides to change how the data is stored internally -- using a vector of `int`s instead of three separate `int`s, for example -- the user of the `Date` class will not need to know.

See [sphere_class_example](sphere_class_example.cpp) for another example of abstraction.

## Static Members

Class members can be declared `static`, which means that the member belongs to the entire class, instead of to a specific instance of the class. More specifically, a `static` member is created only once and then shared by all instances (i.e. objects) of the class. All instances of that class will refer to the same memory location for that static variable. That means that if the `static` member gets changed, either by a user of the class or within a member function of the class itself, then all members of the class will see that change the next time they access the `static` member.

`static` members are **declared** within their `class` (often in a header file) but in most cases they must be **defined** within the global scope. That's because memory is allocated for `static` variables immediately when the program begins, at the same time any global variables are initialized.

Here is an example:
```cpp
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
```

An exception to the global definition of `static` members is if such members can be marked as [`constexpr`](https://en.cppreference.com/w/cpp/language/constexpr). In that case, the `static` member variable can be both declared and defined within the `class` definition:

```cpp
struct Kilometer {
  static constexpr int meters{1000};
};
```

## Static Methods

In addition to `static` member variables, C++ supports `static` member functions (or "methods"). Just like `static` member variables, `static` member functions are instance-independent: they belong to the class, not to any particular instance of the class.

One corollary to this is that we can method invoke a `static` member function _without ever creating an instance of the class_. Static member functions can not access instance member variables. Static member functions are for static member variables only.

```cpp
#include <cassert>
#include <cmath>
#include <stdexcept>

class Sphere {
public:
  static float Volume(int radius) {
    return pi_ * 4/3 * pow(radius,3);
  }

private:
  static float constexpr pi_{3.14159};
};

// Test
int main(void)
{
  assert(abs(Sphere::Volume(5) - 523.6) < 1);
}
```

## Const Data Members

Data that shouldn't be changed should be declared as const. 

There are 2 ways to initialize const data members.
- Initialize in the class
- From outside the class using an initializer list

Example:
```cpp
#include <iostream>

class Phone
{
public:
	Phone(std::string str) : phone_name(str) {}
	std::string GetPhoneName() {return phone_name;}
	std::string GetPhoneMake() {return phone_make;}
private:
	const std::string phone_name;
	const std::string phone_make = "Motorola";
};

int main()
{
	Phone p1("Moto G4");
	std::cout << p1.getPhoneName() << std::endl;
	std::cout << p1.getPhoneMake() << std::endl;
	return 0;
}
```