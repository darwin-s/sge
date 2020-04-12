include(FetchContent)
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG        3.3.2
)

message(STATUS "Downloading glfw. Please wait")
FetchContent_MakeAvailable(glfw)

set(SGE_SRC hash.cpp log.cpp)

add_library(sge SHARED ${SGE_SRC})
target_link_libraries(sge PRIVATE glfw)
target_compile_features(sge PUBLIC cxx_std_17)
set_target_properties(sge PROPERTIES CXX_EXTENSIONS OFF
                                     CXX_VISIBILITY_PRESET hidden 
                                     VISIBILITY_INLINES_HIDDEN TRUE
                                     RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/binaries
                                     LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/binaries
                                     ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/binaries)
target_include_directories(sge PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE src)
generate_export_header(sge EXPORT_FILE_NAME ${CMAKE_BINARY_DIR}/include/sge/export.hpp
    INCLUDE_GUARD_NAME __SGE_EXPORT_HPP__ EXPORT_MACRO_NAME SGE_API
    NO_EXPORT_MACRO_NAME SGE_PRIVATE)

if(APPLE)
    message(FATAL_ERROR "Apple is not supported, because of lack of OpenGL 4.5 support")
endif()

if(UNIX)
    target_compile_definitions(sge PRIVATE SGE_UNIX)
elseif(WIN32)
    target_compile_definitions(sge PRIVATE SGE_WIN32)
else()
    message(FATAL_ERROR "OS target target not supported by GLFW")
endif()

target_compile_definitions(sge PRIVATE "$<$<CONFIG:DEBUG>:SGE_DEBUG>")