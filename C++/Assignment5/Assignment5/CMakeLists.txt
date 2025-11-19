cmake_minimum_required(VERSION 3.20)
project(TypeAhead LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_executable(TypeAhead
    main.cpp
    WordTree.cpp
)

target_include_directories(TypeAhead PRIVATE ${/Assignment5})

set_target_properties(TypeAhead PROPERTIES LINK_FLAGS "/STACK:10000000")

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
    WordTree.cpp
    TestWordTree.cpp
)

target_link_libraries(UnitTestRunner
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(UnitTestRunner)

set_target_properties(UnitTestRunner PROPERTIES LINK_FLAGS "/STACK:10000000")

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_CURRENT_SOURCE_DIR}/dictionary.txt dictionary.txt
)