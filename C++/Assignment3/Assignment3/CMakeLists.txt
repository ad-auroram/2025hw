cmake_minimum_required(VERSION 3.20)
project(RandomDistributionsProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_executable(RandDistributions
    main.cpp
    distributions.cpp
)

target_include_directories(RandDistributions PRIVATE ${/Assignment3})

include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.15.0
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(UnitTestRunner
    distributions.cpp
    TestDistributions.cpp
)

target_link_libraries(UnitTestRunner
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(UnitTestRunner)