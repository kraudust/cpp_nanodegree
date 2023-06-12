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





