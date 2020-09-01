cmake_minimum_required(VERSION 3.15)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

project(sge
        VERSION 0.1.0.0
        LANGUAGES CXX C)

add_subdirectory(3rd-party)
add_subdirectory(src)