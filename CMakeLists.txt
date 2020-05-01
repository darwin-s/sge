cmake_minimum_required(VERSION 3.15)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

project(sge
        VERSION 0.1.0.0
        LANGUAGES CXX C)

add_subdirectory(3rdparty)
add_subdirectory(src)

include(CTest)
add_subdirectory(test)