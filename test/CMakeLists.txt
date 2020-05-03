include(FetchContent)

#Force GTest not to install
set(INSTALL_GTEST OFF CACHE INTERNAL "")

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        release-1.10.0
)

message(STATUS "Downloading Google Test. Please wait")

FetchContent_MakeAvailable(googletest)
include(GoogleTest)

add_executable(sgetst test.cpp)
target_link_libraries(sgetst SGE::sge gtest gmock gtest_main)
set_target_properties(sgetst PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/binaries)
gtest_discover_tests(sgetst)
