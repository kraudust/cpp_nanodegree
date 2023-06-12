# Documentation
Source code files need to contain the following Doxygen-style comment block describing the purpose of the file and example usage. This is used for generating API documentation.

```cpp
/**
 * @file <File name>
 * @brief <Purpose of this file>
 *
 * <Optional detailed description of this file>
 *
 * Usage: <Example usage of this module>
 */
```

Functions and classes should be headed by the following Doxygen style comment block to allow API doc generation

```cpp
/**
 * @brief This is a long description that seems to give a lot of detail
 *
 * @param[in/out] name: Description
 *
 * @return Description
 */
```

# Style
## Spacing
- Max line length: 100 characters
- Indentation: 2 spaces
- Prefer zero spaces for private, public, and protected declarations (i.e. they should be in the same column as the class)
- Use char \* c instead of char\* c or char \*c
- Cuddled vs. Open Braces
	- Use open braces for function, class, enum, and struct definitions, but cuddle braces on if, else, while, for, etc…
	- Exception: when an if (or while, etc.) condition is long enough to require line-wrapping, then use an open brace (i.e., don’t cuddle).
	- When a function call cannot fit on one line, wrap at the open parenthesis (not in between arguments) and start them on the next line with a 2-space indent. Continue with the 2-space indent on subsequent lines for more arguments.
	- Examples:
		```cpp
		int main(int argc, char **argv)
		{
		  if (condition) {
		    return 0;
		  } else {
		    return 1;
		  }
		}
		
		if (this && that || both) {
		  ...
		}
		
		// Long condition; open brace
		if (
		  this && that || both && this && that || both && this && that || both && this && that)
		{
		  ...
		}
		
		// Short function call
		call_func(foo, bar);
		
		// Long function call; wrap at the open parenthesis
		call_func(
		  foo, bar, foo, bar, foo, bar, foo, bar, foo, bar, foo, bar, foo, bar, foo, bar, foo, bar,
		  foo, bar, foo, bar, foo, bar, foo, bar, foo, bar, foo, bar, foo, bar, foo, bar, foo, bar);
		
		// Very long function argument; separate it for readability
		call_func(
		  bang,
		  fooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo,
		  bar, bat);
		```

		```cpp
		ReturnType LongClassName::ReallyReallyReallyLongFunctionName(
		  Type par_name1,  // 2 space indent
		  Type par_name2,
		  Type par_name3)
		{
		  DoSomething();  // 2 space indent
		  ...
		}
		
		MyClass::MyClass(int var)
		: some_var_(var),
		  some_other_var_(var + 1)
		{
		  ...
		  DoSomething();
		  ...
		```

## Naming
- Variable naming
	- Use snake case (snake\_case\)
	- global variables: lowercase with underscores prefixed with g_
		- Ex. g_snake_case
	- class data members have trailing underscores
		- local\_variable, struct\_data\_member, class\_data\_member\_
		- struct data members do not have trailing underscores
	- constants: Variables declared constexpr or const, and whose value is fixed for the duration of the program, are named with a leading "k" followed by mixed case
		- const int kDaysInAWeek = 7;
- Function and method naming
	- CamelCase or snake_case is acceptable, be consistent in file
- Classes use CamelCase
- Namespace names are all lowercase, with words separated by underscores
- Enumerators (for both scoped and unscoped enums) should be named like constants
	```cpp
	enum class UrlTableError {
	  kOk = 0,
	  kOutOfMemory,
	  kMalformedInput,
	};
	```

