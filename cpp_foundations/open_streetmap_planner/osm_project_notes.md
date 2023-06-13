# Building and Running

To get started with your project, you can download the code from the GitHub repo [here](https://github.com/udacity/CppND-Route-Planning-Project), or you can use the workspace provided below. If you decide to work on this project on your local machine, you will need to install the dependencies outlined in the GitHub [README](README.md) for the project, which can be difficult.

In this classroom concept, you will see the instructions for building, running, and testing your project. In the next classroom concept, you will see a detailed overview of the project code, so you'll be well prepared to start work on the project.

This project will use CMake as the build system. Building the project code can be done from the terminal workspace or from the virtual desktop workspace. It is also possible to build this project locally. To do this, you will need to install the project dependencies in your local environment, including the IO2D library, which can be difficult. The complete list of dependencies can be found in the [GitHub README](https://github.com/udacity/CppND-Route-Planning-Project/blob/master/README.md) for the project.

**When building IO2D Library, use instructions here instead of the link from the README:**
- Install dependencies:
	- Refresh apt: sudo apt update
	- Install GCC: sudo apt install build-essential
	- Install Cairo: sudo apt install libcairo2-dev
	- Install graphicsmagick: sudo apt install libgraphicsmagick1-dev
	- Install libpng: sudo apt install libpng-dev
- Setup IO2D lib:
	- git clone --recurse-submodules https://github.com/cpp-io2d/P0267_RefImpl
	- cd into dir and mkdir build
	- comment out the last two build options for tests and samples in the CMakeLists.txt
	- from the build directory run cmake: cmake --config Release
	- compile with: make
	- install the library with: sudo make install

## After dependencies are installed:
- Make a build directory and cmake .., then make
- To run, from withing the build directory
	- ./OSM_A_star_search (to run the program)
	- ./test (to run unit tests)

