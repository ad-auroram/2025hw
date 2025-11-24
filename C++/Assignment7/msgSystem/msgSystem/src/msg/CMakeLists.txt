# Static library for message layer
add_library(msg STATIC
  Message.cpp
  LogMessage.cpp
  PingMessage.cpp
  LsMessage.cpp
  QuitMessage.cpp
)

target_include_directories(msg PUBLIC
  ${CMAKE_SOURCE_DIR}/src/include/msg
)

target_link_libraries(msg PRIVATE nlohmann_json::nlohmann_json)
