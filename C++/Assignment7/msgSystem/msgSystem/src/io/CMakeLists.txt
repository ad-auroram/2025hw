# Static library for IO layer
add_library(io STATIC
  FileIO.cpp
  MsgIO.cpp
  StdinIO.cpp
)

target_include_directories(io PUBLIC
  ${CMAKE_SOURCE_DIR}/src/include/io
)

target_link_libraries(io PRIVATE nlohmann_json::nlohmann_json)
