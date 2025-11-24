cmake_minimum_required(VERSION 3.16)
project(msgSystem LANGUAGES CXX)

# C++ standard and warnings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (MSVC)
  add_compile_options(/W4)
else()
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Local json
set(LOCAL_JSON "${CMAKE_SOURCE_DIR}/src/third_party/nlohmann/json.hpp")
add_library(nlohmann_json INTERFACE)
target_include_directories(nlohmann_json INTERFACE
  BEFORE
  SYSTEM
  $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src/third_party>
)
add_library(nlohmann_json::nlohmann_json ALIAS nlohmann_json)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/src/include)

# Build submodules
add_subdirectory(src/io)
add_subdirectory(src/msg)

# target: msgSystem
add_executable(msgSystem
  src/main.cpp
  src/MsgSystem.cpp
)

# Link the two static libraries
target_link_libraries(msgSystem PRIVATE io msg nlohmann_json::nlohmann_json)

include(CTest)
enable_testing()
add_subdirectory(tests)
