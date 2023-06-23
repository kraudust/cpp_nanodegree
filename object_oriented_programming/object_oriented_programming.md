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
	13. [Polymorphism and Inheritance](#polymorphism-and-inheritance)
		1. [Inheritance](#inheritance)
			1. [Inherited Access Specifiers](#inherited-access-specifiers)
		2. [Composition](#composition)
		3. [Friends](#friends)
		4. [Polymorphism Overloading](#polymorphism-overloading)
		5. [Polymorphism Operator Overloading](#polymorphism-operator-overloading)
		6. [Polymorphism Overriding](#polymorphism-overriding)
		7. [Virtual Functions](#virtual-functions)
		8. [Multiple Inheritance](#multiple-inheritance)
3. [Generic Programming (Templates)](#generic-programming-templates)
	1. [Template Deduction](#template-deduction)
	2. [Class Templates](#class-templates)
4. [System Monitor Project](CppND-System-Monitor/README.md)

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
  const std::string name;
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

## Polymorphism and Inheritance
### Inheritance

- Top level class is parent class or base class. 
- Class that inherits from it is called derived class or child class.

Syntax Example:
```cpp
#include <iostream>
#include <string>
using std::string;

class Vehicle {
public:
    int wheels = 0;
    string color = "blue";
    string make  = "generic";
    
    void Print() const
    {
        std::cout << "This " << color << " " << make << " vehicle has " << wheels << " wheels!\n";
    }
};

class Car : public Vehicle {
public:
    bool sunroof = false;
};

// Example of multi-level inheritance
class Sedan : public Car {
public:
    int doors{4};
};

class Bicycle : public Vehicle {
public:
    bool kickstand = true;
};

class Scooter : public Vehicle {
public:
    bool electric = false;
};

int main() 
{
    Scooter scooter;
    scooter.wheels = 2;
    scooter.Print();
};
```

#### Inherited Access Specifiers

Just as access specifiers (i.e. `public`, `protected`, and `private`) define which class members _users_ can access, the same access modifiers also define which class members _users of a derived classes_ can access.

[Public inheritance:](https://en.cppreference.com/w/cpp/language/derived_class#Public_inheritance) the public and protected members of the base class listed after the specifier keep their member access in the derived class

[Protected inheritance:](https://en.cppreference.com/w/cpp/language/derived_class#Protected_inheritance) the public and protected members of the base class listed after the specifier are protected members of the derived class

[Private inheritance:](https://en.cppreference.com/w/cpp/language/derived_class#Private_inheritance) the public and protected members of the base class listed after the specifier are private members of the derived class

Example:

```cpp
// This example demonstrates the privacy levels
// between parent and child classes
#include <iostream>
#include <string>
using std::string;

class Vehicle {
public:
    int wheels = 0;
    string color = "blue";
    
    void Print() const
    {
        std::cout << "This " << color << " vehicle has " << wheels << " wheels!\n";
    }
};

class Car : public Vehicle {
public:
    bool sunroof = false;
};

class Bicycle : protected Vehicle {
public:
    bool kickstand = true;
};

class Scooter : private Vehicle {
public:
    bool electric = false;
};

int main() 
{
    Car car;
    car.wheels = 4;
	// The following will produce errors and won't compile
    //Bicycle bicycle;
    //bicycle.wheels = 2;
    //Scooter scooter;
    //scooter.wheels = 1;
};
```

### Composition

[Composition](https://en.wikipedia.org/wiki/Composition_over_inheritance) is a closely related alternative to inheritance. Composition involves constructing ("composing") classes from other classes, instead of inheriting traits from a parent class.

A common way to distinguish "composition" from "inheritance" is to think about what an object can do, rather than what it is. This is often expressed as [**"has a"**](https://en.wikipedia.org/wiki/Has-a) versus [**"is a"**](https://en.wikipedia.org/wiki/Is-a).

From the standpoint of composition, a cat "has a" head and "has a" set of paws and "has a" tail.

From the standpoint of inheritance, a cat "is a" mammal.

There is [no hard and fast rule](https://www.google.com/search?q=when+to+use+composition+and+when+to+use+inheritance&oq=when+to+use+composition+and+when+to+use+inheritance) about when to prefer composition over inheritance. In general, if a class needs only extend a small amount of functionality beyond what is already offered by another class, it makes sense to **inherit** from that other class. However, if a class needs to contain functionality from a variety of otherwise unrelated classes, it makes sense to **compose** the class from those other classes.

Example:

```cpp
#include <iostream>
#include <cmath>
#include <assert.h>

// Define LineSegment struct
struct LineSegment {
// Define protected attribute length
public:
    double length;
};

// Define Circle class
public:
    Circle(LineSegment& radius);
    double Area();

private:
    LineSegment& radius_;
};

// Declare Circle class
Circle::Circle(LineSegment& radius) : radius_(radius) {}

double Circle::Area() 
{
    return pow(Circle::radius_.length, 2) * M_PI;
}

// Test in main()
int main() 
{
    LineSegment radius {3};
    Circle circle(radius);
    assert(int(circle.Area()) == 28);
}
```

### Friends

In C++, `friend` classes provide an alternative inheritance mechanism to derived classes. The main difference between classical inheritance and friend inheritance is that a `friend` class can access private members of the base class, which isn't the case for classical inheritance. In classical inheritance, a derived class can only access public and protected members of the base class.

Example:
```cpp
#include <cassert>

class Heart {
private:
	int rate{80};
	friend class Human;
};

class Human {
public:
	Heart heart;
	void Exercise() {heart.rate = 150;}
	int HeartRate() {return heart.rate;}
};

int main() {
	Human human;
	assert(human.HeartRate() == 80);
	human.Exercise();
	assert(human.HeartRate() == 150);
}
```

### Polymorphism Overloading

[Polymorphism](https://www.merriam-webster.com/dictionary/polymorphism) is means "assuming many forms".

In the context of object-oriented programming, [polymorphism](https://en.wikipedia.org/wiki/Polymorphism_(computer_science)) describes a paradigm in which a function may behave differently depending on how it is called. In particular, the function will perform differently based on its inputs.

Polymorphism can be achieved in two ways in C++: overloading and [overriding](#polymorphism-overriding). In this exercise we will focus on overloading.

In C++, you can write two (or more) versions of a function with the same name. This is called ["overloading"](https://en.wikipedia.org/wiki/Function_overloading). Overloading requires that we leave the function name the same, but we modify the function signature. For example, we might define the same function name with multiple different configurations of input arguments.

Example:

```cpp
#include <cassert>
#include <string>

class Water {};
class Alcohol {};
class Coffee {};

class Human{
public:
	std::string condition{"happy"};
	void Drink(Water water){condition = "hydrated";}
	void Drink(Alcohol alcohol){condition = "impaired";}
	void Drink(Soda soda){condition = "cavities";}
};

int main() {
	Human david;
	assert(david.condition == "happy");
	david.Drink(Water());
	assert(david.condition == "hydrated");
	david.Drink(Alcohol());
	assert(david.condition == "impaired");
	david.Drink(Soda());
	assert(david.condition == "cavities");
}
```

### Polymorphism Operator Overloading

In this exercise you'll see how to achieve polymorphism with [operator overloading](https://en.cppreference.com/w/cpp/language/operators). You can choose any operator from the ASCII table and give it your own set of rules!

Operator overloading can be useful for many things. Consider the `+` operator. We can use it to add `int`s, `double`s, `float`s, or even `std::string`s.

Imagine vector addition. You might want to perform vector addition on a pair of points to add their x and y components. The compiler won't recognize this type of operation on its own, because this data is user defined. However, you can overload the `+` operator so it performs the action that you want to implement.

Example:

```cpp
#include <assert.h>

class Point {
public:
    Point(int x, int y) : x_(x), y_(y) {}
    
    Point operator+(const Point& p2)
    {
        return Point(x_ + p2.x_, y_ + p2.y_);
    }
    int x_;
    int y_;
};

// Test in main()
int main() {
  Point p1(10, 5), p2(2, 4);
  Point p3 = p1 + p2; // An example call to "operator +";
  assert(p3.x_ == p1.x_ + p2.x_);
  assert(p3.y_ == p1.y_ + p2.y_);
}
```

### Polymorphism Overriding

Overriding a function occurs when:
1. A base class declares a [virtual function](#virtual-functions).
2. A derived class overrides that virtual function by defining its own implementation with an identical function signature.

See [example](#virtual_func_overriding_ex) in virtual functions section. 

**`override` keyword**

This specification tells both the compiler and the human programmer that the purpose of this function is to override a virtual function. The compiler will verify that a function specified as `override` does indeed override some other virtual function, or otherwise the compiler will generate an error.

Specifying a function as `override` is [good practice](http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rh-override), as it empowers the compiler to verify the code, and communicates the intention of the code to future users.

For example:
```cpp
class Shape {
public:
  virtual double Area() const = 0;
  virtual double Perimeter() const = 0;
};

class Circle : public Shape {
public:
  Circle(double radius) : radius_(radius) {}
  double Area() const override { return pow(radius_, 2) * PI; } // specified as an override function
  double Perimeter() const override { return 2  *radius_*  PI; } // specified as an override function

private:
  double radius_;
};
```


**Function Hiding**

Function hiding is [closely related, but distinct from](https://stackoverflow.com/questions/19736281/what-are-the-differences-between-overriding-virtual-functions-and-hiding-non-vir), overriding.

A derived class hides a base class function, as opposed to overriding it, if the base class function is not specified to be `virtual`.

```cpp
class Cat {
public:
  std::string Talk() const { return std::string("Meow"); }
};

class Lion : public Cat {
public:
  std::string Talk() const { return std::string("Roar"); }
};
```

In this example, `Cat` is the base class and `Lion` is the derived class. Both `Cat` and `Lion` have `Talk()` member functions.

When an object of type `Lion` calls `Talk()`, the object will run `Lion::Talk()`, not `Cat::Talk()`.

In this situation, `Lion::Talk()` is _hiding_ `Cat::Talk()`. If `Cat::Talk()` were `virtual`, then `Lion::Talk()` would _override_ `Cat::Talk()`, instead of _hiding_ it. _Overriding_ requires a `virtual` function in the base class.

The distinction between _overriding_ and _hiding_ is subtle and not terribly significant, but in certain situations _hiding_ [can lead to bizarre errors](https://isocpp.org/wiki/faq/strange-inheritance), particularly when the two functions have slightly different function signatures.



### Virtual Functions

Virtual functions are a polymorphic feature. These functions are declared (and possibly defined) in a base class, and can be overridden by derived classes.

This approach declares an [interface](http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#S-glossary) at the base level, but delegates the implementation of the interface to the derived classes.

In this exercise, `class Shape` is the base class. Geometrical shapes possess both an area and a perimeter. `Area()` and `Perimeter()` should be virtual functions of the base class interface. Append `= 0` to each of these functions in order to declare them to be "pure" virtual functions.

A [pure virtual function](http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#S-glossary) is a [virtual function](http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#S-glossary) that the base class [declares](http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#S-glossary) but does not [define](http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#S-glossary).

A pure virtual function has the side effect of making its class [abstract](http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#S-glossary). This means that the class cannot be instantiated. Instead, only classes that derive from the abstract class and override the pure virtual function can be instantiated.

<a name="virtual_func_overriding_ex"></a>Example:

```cpp
#include <assert.h>
#include <cmath>

class Shape
{
public:
    virtual float Area() const = 0;
    virtual float Perimeter() const = 0;
};

class Rectangle: public Shape
{
public:
    Rectangle(float width, float height) : width_(width), height_(height) {}
    float Area() const {return width_ * height_;}
    float Perimeter() const{return width_ * 2.0f + height_ * 2.0f;}
private:
    float width_;
    float height_;
};

class Circle : public Shape
{
public:
    Circle(float radius) : radius_(radius) {}
    float Area() const {return M_PI * radius_ * radius_;}
    float Perimeter() const {return 2.0f * M_PI * radius_;}
private:
    float radius_;
};

// Test in main()
int main() {
  double epsilon = 0.1; // useful for floating point equality
  // Test circle
  Circle circle(12.31);
  assert(abs(circle.Perimeter() - 77.35) < epsilon);
  assert(abs(circle.Area() - 476.06) < epsilon);
  // Test rectangle
  Rectangle rectangle(10, 6);
  assert(rectangle.Perimeter() == 32);
  assert(rectangle.Area() == 60);
}
```

### Multiple Inheritance

The Core Guidelines have some worthwhile recommendations about how and when to use multiple inheritance:

- ["Use multiple inheritance to represent multiple distinct interfaces"](http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#c135-use-multiple-inheritance-to-represent-multiple-distinct-interfaces)
- ["Use multiple inheritance to represent the union of implementation attributes"](http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#c136-use-multiple-inheritance-to-represent-the-union-of-implementation-attributes)

Example:
```cpp
#include <cassert>
#include <iostream>

class Car {
public:
	std::string Drive() {return "I'm driving!";}
};

class Boat {
public:
	std::string Drive() {return "I'm cruising!";}
};

class AmphibiousCar : public Boat, public Car {};

int main() {
	Car car;
	Boat boat;
	AmphibiousCar duck;
	assert(duck.Drive() = car.Drive());
	assert(duck.Cruise() == boat.Cruise());
}
```

## Generic Programming (Templates)

An example of generic programming is the vector class. You can create a vector of any type of object (string, int, custom user defined class, etc.).

Templates enable generic programming by generalizing a function to apply to any class. Specifically, templates use _types_ as parameters so that the same implementation can operate on different data types.

For example, you might need a function to accept many different data types. The function acts on those arguments, perhaps dividing them or sorting them or something else. Rather than writing and maintaining the multiple function declarations, each accepting slightly different arguments, you can write one function and pass the argument types as parameters. At compile time, the compiler then expands the code using the types that are passed as parameters.

Example:

```cpp
template <typename Type> Type Sum(Type a, Type b) { return a + b; }

int main() {
	std::cout << Sum<double>(20.0, 13.7) << "\n";
}
```

Because `Sum()` is defined with a template, when the program calls `Sum()` with `double`s as parameters, the function expands to become:
```cpp
double Sum(double a, double b) {
    return a+b;
}
```

Or in this case:

```cpp
std::cout << Sum<char>(‘Z’, ’j’) << "\n";
```

The program expands to become:
```cpp
char Sum(char a, char b) {
    return a+b;
}
```

We use the keyword `template` to specify which function is generic. Generic code is the term for code that is independent of types. It is mandatory to put the `template<>` tag before the function signature, to specify and mark that the declaration is generic.

Besides `template`, the keyword `typename` (or, alternatively, `class`) specifies the generic type in the function prototype. The parameters that follow `typename` (or `class`) represent generic types in the function declaration.

In order to instantiate a templatized class, use a templatized constructor, for example: `Sum<double>(20.0, 13.7)`. You might recognize this form as the same form used to construct a `vector`. That's because `vector`s are indeed a generic class!

See [template_example.cpp](template_example.cpp) for more examples of how to use.

### Template Deduction

The compiler determines the type for a template automatically without us having to specify it.

Example:

```cpp
template <typename T> 
T Max(T a, T b) {
    return a > b ? a : b;
}

// These are equivalent
std::cout << Max(5.7, 1.436246) << std::endl;
std::cout << Max<double>(5.7, 1.436246) << std::endl;
```

### Class Templates

Classes are the building blocks of object oriented programming in C++. Templates support the creation of generic classes!

Class templates can declare and implement generic attributes for use by generic methods. These templates can be very useful when building classes that will serve multiple purposes.

Example:
```cpp
#include <assert.h>
#include <string>
#include <sstream>

template <typename KeyType, typename ValueType>
class Mapping {
public:
  Mapping(KeyType key, ValueType value) : key(key), value(value) {}
  std::string Print() const {
    std::ostringstream stream;
    stream << key << ": " << value;
    return stream.str();
  }
  KeyType key;
  ValueType value;
};

// Test
int main() {
  Mapping<std::string, int> mapping("age", 20);
  assert(mapping.Print() == "age: 20");
}
```





