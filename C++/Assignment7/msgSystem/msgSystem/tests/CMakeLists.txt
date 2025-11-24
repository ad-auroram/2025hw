
cmake_minimum_required(VERSION 3.16)

include(FetchContent)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
# For Windows: prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Common include dirs
include_directories(${CMAKE_SOURCE_DIR}/src/include)

# Helper to add a test target and link the libs + gtest
function(add_gtest name)
  add_executable(${name} ${ARGN})
  target_link_libraries(${name} PRIVATE gtest_main io msg)
  add_test(NAME ${name} COMMAND ${name})
endfunction()

# Individual test executables
add_gtest(test_message_factory
  ${CMAKE_SOURCE_DIR}/tests/test_message_factory.cpp
)


add_gtest(test_fileio
  ${CMAKE_SOURCE_DIR}/tests/test_fileio.cpp
)


add_gtest(test_msgio_poly
  ${CMAKE_SOURCE_DIR}/tests/test_msgio_poly.cpp
)
