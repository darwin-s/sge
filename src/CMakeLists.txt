include(FetchContent)
include(GenerateExportHeader)

find_package(Threads REQUIRED)

#Force some GLFW parameters
set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "")
set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "")
set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "")
set(GLFW_INSTALL OFF CACHE INTERNAL "")

FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.3.2
)

message(STATUS "Downloading glfw. Please wait")
FetchContent_MakeAvailable(glfw)

set(SRC_PREF ${CMAKE_CURRENT_SOURCE_DIR})
set(INC_PREF ${CMAKE_CURRENT_SOURCE_DIR}/../include/SGE)
set(SGE_GENERATED_INCLUDES
        ${CMAKE_CURRENT_BINARY_DIR}/../include/SGE/Export.hpp)
set(SGE_PUBLIC_INCLUDES
        ${INC_PREF}/Types.hpp
        ${INC_PREF}/Hash.hpp
        ${INC_PREF}/Log.hpp
        ${INC_PREF}/Application.hpp
        ${INC_PREF}/Vector2.hpp
        ${INC_PREF}/Vector2.inl
        ${INC_PREF}/Monitor.hpp
        ${INC_PREF}/Keyboard.hpp
        ${INC_PREF}/Mouse.hpp
        ${INC_PREF}/EventHandler.hpp
        ${INC_PREF}/ContextSettings.hpp
        ${INC_PREF}/Context.hpp
        ${INC_PREF}/Window.hpp
        ${INC_PREF}/Filesystem.hpp
        ${INC_PREF}/InputFile.hpp
        ${INC_PREF}/Resource.hpp
        ${INC_PREF}/ResourceManager.hpp
        ${INC_PREF}/ResourceManager.inl
        ${INC_PREF}/VBO.hpp
        ${INC_PREF}/SGE.hpp)
set(SGE_PUBLIC ${SGE_GENERATED_INCLUDES} ${SGE_PUBLIC_INCLUDES})
set(SGE_PRIVATE_INCLUDES)
set(SGE_SRC
        ${SRC_PREF}/Hash.cpp
        ${SRC_PREF}/Log.cpp
        ${SRC_PREF}/Application.cpp
        ${SRC_PREF}/Monitor.cpp
        ${SRC_PREF}/Keyboard.cpp
        ${SRC_PREF}/Mouse.cpp
        ${SRC_PREF}/EventHandler.cpp
        ${SRC_PREF}/ContextSettings.cpp
        ${SRC_PREF}/Context.cpp
        ${SRC_PREF}/Window.cpp
        ${SRC_PREF}/Filesystem.cpp
        ${SRC_PREF}/InputFile.cpp
        ${SRC_PREF}/Resource.cpp
        ${SRC_PREF}/ResourceManager.cpp
        ${SRC_PREF}/VBO.cpp)

add_library(sge SHARED ${SGE_SRC} ${SGE_GENERATED_INCLUDES} ${SGE_PUBLIC_INCLUDES} ${SGE_PRIVATE_INCLUDES})
add_library(SGE::sge ALIAS sge)
target_link_libraries(sge PUBLIC ${CMAKE_THREAD_LIBS_INIT} ${CMAKE_DL_LIBS} PRIVATE glfw glad physfs-static)
target_compile_features(sge PUBLIC cxx_std_17)
set_target_properties(sge PROPERTIES
        PUBLIC_HEADER "${SGE_PUBLIC}"
        FOLDER "Libraries"
        CXX_EXTENSIONS OFF
        CXX_VISIBILITY_PRESET hidden
        VISIBILITY_INLINES_HIDDEN TRUE
        INTERPROCEDURAL_OPTIMIZATION_RELEASE TRUE
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/../binaries
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/../binaries
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/../binaries)

target_include_directories(sge PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/../include>
        $<INSTALL_INTERFACE:include>
        PRIVATE src)

generate_export_header(sge EXPORT_FILE_NAME ${CMAKE_CURRENT_BINARY_DIR}/../include/SGE/Export.hpp
        INCLUDE_GUARD_NAME SGE_EXPORT_HPP EXPORT_MACRO_NAME SGE_API
        NO_EXPORT_MACRO_NAME SGE_PRIVATE)

if (APPLE)
    message(FATAL_ERROR "Apple is not supported, because of lack of OpenGL 4.5 support")
endif ()

if (UNIX)
    target_compile_definitions(sge PRIVATE SGE_UNIX)
elseif (WIN32)
    target_compile_definitions(sge PRIVATE SGE_WIN32)
else ()
    message(FATAL_ERROR "OS target target not supported by GLFW")
endif ()

target_compile_definitions(sge PRIVATE "$<$<CONFIG:DEBUG>:SGE_DEBUG>")

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/../include/SGE" PREFIX "Header Files" FILES ${SGE_PUBLIC_HEADERS})

install(TARGETS sge
        EXPORT sgeTargets
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION lib
        PUBLIC_HEADER DESTINATION include/SGE)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
        ${CMAKE_CURRENT_BINARY_DIR}/../sgeConfigVersion.cmake
        VERSION ${PACKAGE_VERSION}
        COMPATIBILITY AnyNewerVersion)

install(EXPORT sgeTargets
        FILE sgeTargets.cmake
        NAMESPACE SGE::
        DESTINATION lib/cmake/sge)

install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/../cmake/sgeConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/../sgeConfigVersion.cmake"
        DESTINATION lib/cmake/sge)

export(TARGETS sge NAMESPACE SGE:: FILE sgeTargets.cmake)
set(CMAKE_EXPORT_PACKAGE_REGISTRY ON)
export(PACKAGE sge)

