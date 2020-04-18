# SGE - Sauce Game Engine ![CMake Build](https://github.com/darwin-s/sge/workflows/CMake%20Build/badge.svg?branch=master)

SGE or Sauce Game Engine is a small hobbyist 2D game engine written in C++.
It's main goal is to bring personal experience and maybe a small reference to those starting out.

## Authors

  - Dan Sirbu - main developer
  
## Installation

Use CMake to build and install the library. 
If you downloaded the source in a folder named "sge" then and 
you want to build a release build, then the installation will
look like this:

````Shell
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ../sge
cmake --build .
sudo cmake --install .
````

## Usage

The library installs CMake configuration files, so after installing you can write
a CMake based project and use ``find_package(sge)`` to find the library on the system
adn then link your target with ``target_link_libraries(target SGE::sge)``. Here is
an example of a project:

````CMake
cmake_minimum_required(VERSION 3.15)

project(myproject)

find_package(sge REQUIRED)

add_executable(myexecutable main.cpp)
target_link_libraries(myexecutable SGE::sge)
````
## Special Thanks

  - Yashmerino (a good friend) - Project name idea

## License

The project is licensed under the [Apache License 2.0](https://choosealicense.com/licenses/apache-2.0/).
