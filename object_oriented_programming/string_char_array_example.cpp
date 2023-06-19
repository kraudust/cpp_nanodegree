// #include <cassert>
// #include <stdexcept>
#include <string>
#include <iostream>

// class StringCharTest
// {
// public:
//   /**
//    * @brief Pyramid constructor
//    *
//    * @param[in] length: sets the length of the pyramid
//    * @param[in] width: sets the width of the pyramid
//    * @param[in] height: sets the height of the pyramid
//    * 
//    * @throws invalid_argument exception if values passed in <= 0
//    */
//   StringCharTest(std::string string_ex, char* char_array);

//   // Accessors
//   int Length() const
//   {
//     return length_;
//   }
//   int Width() const
//   {
//     return width_;
//   }
//   int Height() const
//   {
//     return height_;
//   }

//   // Mutators
//   /**
//    * @brief length_ mutator
//    *
//    * @param[in] length: sets the length of the pyramid
//    * 
//    * @throws invalid_argument exception if value passed in <= 0
//    */
//   void Length(int length);

//   // Compute Volume
//   /**
//    * @brief Computes and returns the volume of the pyramid
//    *
//    * @return Float containing the volume of the pyramid
//    */
//   float Volume();

// private:
//   int length_;
//   int width_;
//   int height_;
// };

// StringCharTest::StringCharTest(int length, int width, int height)
// {
//   Length(length);
//   Width(width);
//   Height(height);
// }
// void StringCharTest::Length(int length)
// {
//   if (length > 0) {
//     length_ = length;
//   } else {
//     throw std::invalid_argument("Value must be greater than 0.");
//   }
// }

// Test
int main() {
  // std::cout << will print a char array until it hits a null character

  // Char Array First (C-String)
  char char_test1[] = "oranges"; // automatically adds null character, length is 1 longer than string
  // Equivalent to: char char_test1a[8] = "oranges";
  std::cout << "char_test1------------------" << std::endl;
  std::cout << char_test1 << std::endl; // prints oranges
  std::cout << *char_test1 << std::endl;
  std::cout << &char_test1 << std::endl; // prints address of char_test1

  int array_test[] = {1,2,3,4,5,6,7};
  std::cout << "array_test------------------" << std::endl;
  std::cout << array_test << std::endl;
  std::cout << *array_test << std::endl;
  std::cout << &array_test << std::endl;

  char char_test2[] = {'a', 'p', 'p', 'l', 'e', 's'}; // no null character, results in unexpected behavior
  std::cout << "char_test2------------------" << std::endl;
  std::cout << char_test2 << std::endl; // prints applesoranges (since oranges happens to be next in memory, and terminates in a null character)
   std::cout << *char_test2 << std::endl;
  std::cout << &char_test2 << std::endl;

  char char_test3[] = {'b', 'a', 'n', 'a', 'n', 'a', 's', '\0'}; // null character added at end (ejquivalent to: char char_test3[8])
  std::cout << "char_test3------------------" << std::endl;
  std::cout << char_test3 << std::endl;
  std::cout << *char_test3 << std::endl;
  std::cout << &char_test3 << std::endl;

  const char* char_test4 = "cherries";
  std::cout << "char_test4------------------" << std::endl;
  std::cout << char_test4 << std::endl;
  std::cout << *char_test4 << std::endl;
  std::cout << &char_test4 << std::endl;

  // C++ Strings TODO: Continue experimenting
  std::string string_test1 = "oranges";
}
