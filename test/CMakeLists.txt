include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        release-1.10.0
)

FetchContent_MakeAvailable(googletest)
include(GoogleTest)

add_executable(tst test.cpp)
target_link_libraries(tst sge gtest gmock gtest_main)
set_target_properties(tst PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/binaries)
gtest_discover_tests(tst)
