# Getting Started
## Compiling Code
- Use standard library whenever possible
	- Standard library functions and classes are in the std:: namespace. You need to include the necessary header file, and namespace classes with std::
- There are many different compilers that take code from human readable to machine readable. We mainly use the GNU Compiler Collection (g++ program in particular, which is command line executable that compiles the code and automatically links the standard library
- The compiler needs to have access to compiled versions of the standard library stored in object files.
- Build tools - automate the process of compiling multiple files into object files, linking those object files together, and generating an executable
	- CMake and Make are examples of these. In this program, we won’t need to build our own Makefiles (for make) or CMakeLists.txt files (for CMake)
## Installations for this course
You are welcome to write all of your code in Udacity's web-based Workspaces. If, however, you prefer to work locally on your machine, you will need to install certain software.

---
### g++, gdb, make
#### macOS
includes g++ as part of Command Line Tools.
- Launch Terminal, which can be found in the Utilities folder in Applications.
- Type xcode-select --install into the Terminal window and press "Enter"
- If you don't already have Xcode or Command Line Tools installed, a window will pop up. Press the Install button.
- Verify: Type g++ into Terminal and press enter. If the output is clang: error: no input files, then the installation was successful.

#### Linux
These programs are typically available through the default package manager for each Linux distribution. For example, we can use [APT](https://help.ubuntu.com/lts/serverguide/apt.html) on Ubuntu systems.
- sudo apt update
- sudo apt install build-essential
- sudo apt install gdb

### Windows
[MinGW](http://www.mingw.org/) provides the necessary software.
- Proceed from [Section 3.2 of these linked instructions](https://www.cs.odu.edu/~zeil/cs250PreTest/latest/Public/installingACompiler/#installing-the-mingw-compiler).
---
### Microsoft Visual Studio (VSCode):
The instructions for this are the same for all machines:
- Go to the [Visual Studio Code download webpage](https://code.visualstudio.com/Download)
- Select your operating system.
- Click on the downloaded file
- Complete the installation instructions.

---
### VSCode C/C++ Extension
- Open VSCode
- Navigate to VSCode extensions by clicking into the following menus:
- Code > Preferences > Extensions
	- In search bar type "C/C++"
	- Select the C/C++ extension aqnd press the **Install** button to install this extension
- [Debugging in VSCode](https://code.visualstudio.com/docs/cpp/cmake-linux)
