# Intro to the C++ Language
- To compile a file: g++ \<filename\>, then to run it: ./a.out
- Offline documentation: [https://zealdocs.org/](https://zealdocs.org/)

## Coding Standards
- Follow the [ROS C++ Style Guide](https://docs.ros.org/en/rolling/The-ROS2-Project/Contributing/Code-Style-Language-Versions.html)
- My notes on coding style are [here](coding_standards.md)
- Linting: source ros2, and then run ament_cpplint and ament_uncrustify. Example below.
	- ament_cpplint board.cpp
	- ament_uncrustify board.cpp

## Basics of a Program
- The \#include statement is a preprocessor command which is executed before the code is compiled. It searches for the iostream header file and pastes its contents into the program. iostream contains the declarations for the input/output stream objects.
- Namespaces are a way in C++ to group identifiers (names) together. They provide context for identifiers to avoid naming collisions. The std namespace is the namespace used for the standard library.
- The using command adds std::cout to the global scope of the program. This way you can use cout in your code instead of having to write std::cout.
	- using std::cout;
	- I prefer to not use using statements so it is clear what namespace I am using for something
- Coding statements end with a semicolon in C++. The \#include statement is a preprocessor command, so it doesn't need one.
- std::cout << "Hello!" << "\n";
	- In this line, the code is using cout to send output to the notebook. The << operator is the stream insertion operator, and it writes what's on the right side of the operator to the left side. So in this case, "Message here" is written to the output stream cout.

## C++ Types and Data Structures
Primitive types are things like string and int. You must define types for variables, but can use auto to do automatic type inference.

**vector**

```cpp
#include <iostream>
#include <vector>
using std::vector;
using std::cout;

int main() {
    // Three ways of declaring and initializing vectors.
    vector<int> v_1{0, 1, 2};
    vector<int> v_2 = {3, 4, 5};
    vector<int> v_3;
    v_3 = {6};
    // Push 6 to the back of the vector
    v_2.push_back(6);
    // Creating a 2D vector.
    vector<vector<int>> v {{1,2}, {3,4}};
    cout << "Great! A 2D vector has been created." << "\n";
    cout << "Everything worked!" << "\n";
}
```
**enum**
```cpp
#include <iostream>
using std::cout; 

int main()
{
	enum class Direction {kUp, kDown, kLeft, kRight};
	Direction a = Direction::kUp;
	switch (a) {
	  case Direction::kUp : cout << "Going up!" << "\n";
		break;
	  case Direction::kDown : cout << "Going down!" << "\n";
		break;
	  case Direction::kLeft : cout << "Going left!" << "\n";
		break;
	  case Direction::kRight : cout << "Going right!" << "\n";
		break;
	}
}
```
**Pointers**

At this point, you might be wondering why the same symbol & can be used to both access memory addresses and, as you've seen before, pass references into a function. This is a great thing to wonder about. The overloading of the ampersand symbol & and the * symbol probably contribute to much of the confusion around pointers.

The symbols & and * have a different meaning, depending on which side of an equation they appear.

This is extremely important to remember. For the & symbol, if it appears on the left side of an equation (e.g. when declaring a variable), it means that the variable is declared as a reference. If the & appears on the right side of an equation, or before a previously defined variable, it is used to return a memory address, as in the example above.

Ex.: 
```cpp
int i = 5;
// A pointer pointer_to_i is declared and initialized to the address of i.
int * pointer_to_i = &i;
```

Once you have a pointer, you may want to retrieve the object it is pointing to. In this case, the `*` symbol can be used again. This time, however, it will appear on the right hand side of an equation or in front of an already-defined variable, so the meaning is different. In this case, it is called the "dereferencing operator", and it returns the object being pointed to.

**unordered_map**
- A map is basically a dictionary with key value pairs
- Also known as a hash table
- Include <unordered_map> header
- Syntax: ```unordered_map <key_type, value_type> variable_name;```
- In the code below, we check if the key is in the unordered_map using the .find() method. If the key does not exist in the map, then .find() returns an unordered_map::end() type. Otherwise, .find() returns a [C++ iterator](http://www.cplusplus.com/reference/iterator/), which is a pointer that points to the beginning of the iterable key-value pair.
- We haven't covered iterators in this course, and you won't need them for this project, but they are a lot like pointers that can "iterate" forward or backward through a range.
```cpp
int main() {
    // Create strings to use in the hash table.
    string key = "word";
    string def_1 = "a unit of language, consisting of one or more spoken sounds or their written representation, that functions as a principal carrier of meaning";
    string def_2 = "speech or talk: to express one's emotion in words";
    string def_3 = "a short talk or conversation: 'Marston, I'd like a word with you.'";
    string def_4 = "an expression or utterance: a word of warning";
    unordered_map <string, vector<string>> my_dictionary;
    
    // Check if key is in the hash table.
    if (my_dictionary.find(key) == my_dictionary.end()) {
        cout << "The key 'word' is not in the dictionary." << "\n";
        cout << "Inserting a key-value pair into the dictionary." << "\n\n";
        // Set the value for the key.
        my_dictionary[key] = vector<string> {def_1, def_2, def_3, def_4};
    }
    // The key should now be in the hash table. You can access the
    // value corresponding to the key with square brackets [].
    // Here, the value my_dictionary[key] is a vector of strings.
    // We iterate over the vector and print the strings.
    cout << key << ": \n";
    auto definitions = my_dictionary[key];
    for (string definition : definitions) {
        cout << definition << "\n";
    }
}
```

Another example of how to initialize:
```cpp
std::unordered_map<int, std::string> mymap {
     {5, "a"},
     {6, "b"},
     {7, "c"} 
 };
```
**Lambda Functions**

Used when a function needs a function handle passed to it for a simple function. For example:
```cpp
std::sort(open_list.begin(), open_list.end(),
            [](RouteModel::Node *node1, RouteModel::Node *node2)
	            {return node1->g_value + node1->h_value > node2->g_value + node2->h_value;});
```

## Comments
// You can use two forward slashes for single line comments.
/\*
For longer comments, you can enclose the text with an opening
slash-star and closing star-slash.
\*/

## Loops
### Post vs. Pre Increment Operator
```cpp
#include <iostream>
using std::cout;

int main() {
    auto i = 1;
    // Post-increment assigns i to c and then increments i.
    auto c = i++;
    cout << "Post-increment example:" << "\n";
    cout << "The value of c is: " << c << "\n"; // 1
    cout << "The value of i is: " << i << "\n"; // 2
    cout << "\n";
    // Reset i to 1.
    i = 1;

    // Pre-increment increments i, then assigns to c.
    c = ++i;
    cout << "Pre-increment example:" << "\n";
    cout << "The value of c is: " << c << "\n"; // 2
    cout << "The value of i is: " << i << "\n"; // 2
    cout << "\n";
    
    // Decrement i;
    i--;
    cout << "Decrement example:" << "\n";
    cout << "The value of i is: " << i << "\n"; // 1
}
```

### Index vs. Range Based For Loops
**Index based for loop**
```cpp
for(int i = -3; i <= 10; i++) {
    }
```
**Range based for loops**
```cpp
vector<int> a {1, 2, 3, 4, 5};
for (int i: a) {
  cout << i << "\n";
}
```

```cpp
int main() {
  vector<vector<int>> b {{1, 2}, {3, 4}, {5, 6}};
  for (vector<int> i: b){
    for (int j: i) {
	  cout << j << "\n";
	}
  }
}
```
## File Input Streams
- Header is \<fstream>
- std::ifstream object to handle input file streams
- Example:
```cpp
#include <fstream>
#include <iostream>
#include <string>

int main()
{
  std::ifstream my_file;
  my_file.open("files/1.board");
  if (my_file) {
    std::cout << "The file stream has been created!" << "\n";
    std::string line;
    while (getline(my_file, line)) {
      std::cout << line << "\n";
    }
  }    
}
```
**Streaming Strings to Ints**
```cpp
#include <iostream>
#include <sstream>
#include <string>

using std::istringstream;
using std::string;
using std::cout;

int main () {
    string a("1 2 3");

    istringstream my_stream(a);
    
    int n;
    
    while (my_stream >> n) {
      cout << "That stream was successful: " << n << "\n";
    }
    cout << "The stream has failed." << "\n";
    
}
```
**Strings with mixed types**

In the example above the string only had whitespaces and characters which could be converted to int. If the string has mixed types, more care is needed to process the string. In the following example, the type char is used, which is a type that can hold only a single ASCII character.

In the following example, note that 3 won't be printed because it is trying to stream an int followed by a char, but since there is no char after the 3, the stream fails and the while loop exits.
```cpp
#include <iostream>
#include <sstream>
#include <string>

using std::istringstream;
using std::string;
using std::cout;

int main() 
{
    string b("1,2,3");

    istringstream my_stream(b);

    char c;
    int n;

    while (my_stream >> n >> c) {
      cout << "That stream was successful:" << n << " " << c << "\n";
    }
    cout << "The stream has failed." << "\n";
}
```
## const vs. constexpr
C++ supports two notions of immutability:
- const: meaning roughly " I promise not to change this value."...The compiler enforces the promise made by const....
- constexpr: meaning roughly "to be evaluated at compile time." This is used primarily to specify constants...

Example:
```cpp
int main()
{
    int i;
    std::cout << "Enter an integer value for i: ";
    std::cin >> i;
    constexpr int j = i * 2;  // "j can only be evaluated at run time."
                              // "constexpr must be evaluated at compile time."
                              // "So this code will produce a compilation error."
}
```

When in doubt, use const, it’s much more common. When passing by reference, set variables passed in that aren’t to be changed to const
```cpp
int sum(const std::vector<int> & v)
```

# Writing Multi-file Programs
## Including your own .h files

The \#include statement for the header used quotes " " around the file name, and not angle brackets <>. We have stored the header in the same directory as the .cpp file, and the quotes tell the preprocessor to look for the file in the same directory as the current file - not in the usual set of directories where libraries are typically stored

## Include Guards

```cpp
#ifndef HEADER_EXAMPLE_H
#define HEADER_EXAMPLE_H
class ...
#endif //(at end of program)
```

This is called an "include guard". Since the header will be included into another file, and \#include just pastes contents into a file, the include guard prevents the same file from being pasted multiple times into another file. This might happen if multiple files include the same header, and then are all included into the same main.cpp, for example. The ifndef checks if HEADER_EXAMPLE_H has not been defined in the file already. If it has not been defined yet, then it is defined with \#define HEADER_EXAMPLE_H, and the rest of the header is used. If HEADER_EXAMPLE_H has already been defined, then the preprocessor does not enter the ifndef block. Note: There are other ways to do this. Another common way is to use an \#pragma oncepreprocessor directive, but we won't cover that in detail here.

## CMake and Make

When you compile a project with g++, g++ actually performs several distinct tasks:
1. The preprocessor runs and executes any statement beginning with a hash symbol: #, such as \#include statements. This ensures all code is in the correct location and ready to compile.
2. Each file in the source code is compiled into an "object file" (a .o file). Object files are platform-specific machine code that will be used to create an executable.
3. The object files are "linked" together to make a single executable. In the examples you have seen so far, this executable is a.out, but you can specify whatever name you want.
    

It is possible to have g++ perform each of the steps separately by using the -c flag. For example:
```
g++ -c main.cpp
```

will produce a main.o file, and that file can be converted to an executable with
```
g++ main.o
```

You can do this with multiple files as well with:
```
g++ *.cpp or g++ -c *.cpp g++ *.o
```

It’s better to use cross platform build systems for this though.

**CMake and Make**

CMake is an open-source, platform-independent build system. CMake uses text documents, denoted as CMakeLists.txt files, to manage build environments, like make. A comprehensive tutorial on CMake would require an entire course, but you can learn the basics of CMake here, so you'll be ready to use it in the upcoming projects.

**CMakeLists.txt**

CMakeList.txt files are simple text configuration files that tell CMake how to build your project. There can be multiple CMakeLists.txt files in a project. In fact, one CMakeList.txt file can be included in each directory of the project, indicating how the files in that directory should be built.

These files can be used to specify the locations of necessary packages, set build flags and environment variables, specify build target names and locations, and other actions.

The first lines that you'll want in your CMakeLists.txt are lines that specifies the minimum versions of cmake and C++ required to build the project. Add the following lines to your CMakeLists.txt and save the file:

```
cmake_minimum_required(VERSION 3.5.1)
set(CMAKE_CXX_STANDARD 14)
```

These lines set the minimum cmake version required to 3.5.1 and set the environment variable CMAKE_CXX_STANDARD so CMake uses C++ 14. On your own computer, if you have a recent g++ compiler, you could use C++ 17 instead.

CMake requires that we name the project, so you should choose a name for the project and then add the following line to CMakeLists.txt:

```
project(<your_project_name>)
```

You can choose any name you want, but be sure to change <your_project_name> to the actual name of the project!

Next, we want to add an executable to this project. You can do that with the add_executable command by specifying the executable name, along with the locations of all the source files that you will need. CMake has the ability to automatically find source files in a directory, but for now, you can just specify each file needed:

```
add_executable(your_executable_name  path_to_file_1  path_to_file_2 ...)
```

Hint: The source files you need are the three .cpp files in the src/ directory. You can specify the path relative to the CMakeLists.txt file, so src/main.cpp would work, for example.

A typical CMake project will have a build directory in the same place as the top-level CMakeLists.txt. Make a build directory in the /home/workspace/cmake_example folder:

```
root@abc123defg:/home/workspace/cmake_example# mkdir build
root@abc123defg:/home/workspace/cmake_example# cd build
```

From within the build directory, you can now run CMake as follows:
```
root@abc123defg:/home/workspace/cmake_example/build# cmake ..
root@abc123defg:/home/workspace/cmake_example/build# make
```

The first line directs the cmake command at the top-level CMakeLists.txt file with ... This command uses the CMakeLists.txt to configure the project and create a Makefile in the build directory.

In the second line, make finds the Makefile and uses the instructions in the Makefile to build the project.

Now that your project builds correctly, try modifying one of the files. When you are ready to run the project again, you'll only need to run the make command from the build folder, and only that file will be compiled again. Try it now!

In general, CMake only needs to be run once for a project, unless you are changing build options (e.g. using different build flags or changing where you store your files).

Make will be able to keep track of which files have changed and compile only those that need to be compiled before building.

Note: If you do re-run CMake, or if you are having problems with your build, it can be helpful to delete your build directory and start from scratch. Otherwise, some environment variables may not be reset correctly.

## Classes

Examples of class:

car.h
```cpp
#ifndef CAR_H
#define CAR_H

#include <string>
using std::string;
using std::cout;

class Car {
  public:
    void PrintCarData();
    void IncrementDistance();
    // Using a constructor list in the constructor:
    Car(string c, int n) : color(c), number(n) {}
  // The variables do not need to be accessed outside of
  // functions from this class, so we can set them to private.
  private:
    string color;
    int distance = 0;
    int number;
};
#endif
```

car.cpp

```cpp

#include <iostream>
#include "car.h"

// Method definitions for the Car class.
void Car::PrintCarData() 
{
    cout << "The distance that the " << color << " car " << number << " has traveled is: " << distance << "\n";
}

void Car::IncrementDistance() 
{
    distance++;
}
```

Note: Arrow operator -> dereferences a pointer to an object and accesses an attribute or method. The following are equivalent:
```cpp
car_pointer->IncrementDistance();
(*car_pointer).IncrementDistance();
```

### This Pointer

When working with classes it is often helpful to be able to refer to the current class instance or object. Example:

```cpp
// The Car class
class Car {
  public:
    // Method to print data.
    void PrintCarData() {
        cout << "The distance that the " << this->color << " car " << this->number << " has traveled is: " << this->distance << "\n";
    }

    // Method to increment the distance travelled.
    void IncrementDistance() {
        this->distance++;
    }

    // Class/object attributes
    string color;
    int distance = 0;
    int number;
};
```

### Inheritance

It is possible for a class to use methods and attributes from another class using class inheritance. For example, if you wanted to make a Sedan class with additional attributes or methods not found in the generic Car class, you could create a Sedan class that inherited from the Car by using the colon notation:

```cpp
class Sedan : public Car {
    // Sedan class declarations/definitions here.
};
```

By doing this, each Sedan class instance will have access to any of the public methods and attributes of Car. In the code above, these are IncrementDistance() and PrintCarData(). You can add additional features to the Sedan class as well. In the example above, Car is often referred to as the parent class, and Sedan as the child or derived class.

## Project - OpenStreetMap Route Planner
[Notes for project are here](osm_project_notes.md)
