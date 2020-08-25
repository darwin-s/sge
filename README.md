# SGE - Sauce Game Engine ![CMake Build](https://github.com/darwin-s/sge/workflows/CMake%20Build/badge.svg?branch=master)

SGE or Sauce Game Engine is a small hobbyist 2D game engine written in C++.
It's main goal is for me to improve my skills, be a part of my portfolio and maybe become a small reference for those starting out.
SGE officially supports only 64-bit machines, with OpenGL 4.6 support. It is based on C++17 standart, and requires a compiler that supports it.

## Authors

  - Dan Sirbu (@darwin-s) - main developer
  
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
and then link your target with ``target_link_libraries(target SGE::sge)``. Here is
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

SGE also uses other projects internally:
  - [GLFW](https://www.glfw.org/) - Licensed under [zlib/libpng license](https://www.glfw.org/license.html).
  - [PhysicsFS](https://icculus.org/physfs/) - Licensed under [zlib license](https://hg.icculus.org/icculus/physfs/raw-file/tip/LICENSE.txt).
  - [stb_image](https://github.com/nothings/stb/blob/master/stb_image.h) - Public Domain
  - [glad](https://github.com/Dav1dde/glad) - Public Domain for generated files, source code uses [this license](https://github.com/Dav1dde/glad/blob/master/LICENSE).
  - [SFML](https://github.com/SFML/SFML) - Licensed under [zlib/png license](https://www.sfml-dev.org/license.php). SFML is used as a reference for some code implementations.
