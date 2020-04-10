include(FetchContent)
FetchContent_Declare(
    sdl
    GIT_REPOSITORY https://github.com/spurious/SDL-mirror.git
    GIT_TAG        release-2.0.12
)

message(STATUS "Downloading SDL2. Please wait")
FetchContent_MakeAvailable(sdl)

set(SGE_SRC hash.cpp)

add_library(sge SHARED ${SGE_SRC})
target_link_libraries(sge PUBLIC SDL2)
target_compile_features(sge PUBLIC cxx_std_17)
set_target_properties(sge PROPERTIES CXX_EXTENSIONS OFF
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

add_custom_command(TARGET sge POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:SDL2> ${CMAKE_BINARY_DIR}/binaries/$<TARGET_FILE_NAME:SDL2>
    COMMENT "Copying SDL2 to binary directory"
)