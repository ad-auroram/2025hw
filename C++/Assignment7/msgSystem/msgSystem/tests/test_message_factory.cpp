
#include <gtest/gtest.h>
#include <memory>
#include <string>
#include "msg/Message.hpp"

static std::unique_ptr<Message> mk(const std::string& s) {
    std::string tmp = s;
    return std::unique_ptr<Message>(Message::fromJson(tmp));
}

TEST(MessageFactory, ConstructsKnownTypes) {
    auto log = mk(R"({"header":{"type":"Log","ver":"1","id":"1","ts":"1730400000"},"body":{"path":"./app.log"}})");
    EXPECT_TRUE(log != nullptr);

    auto ping = mk(R"({"header":{"type":"Ping","ver":"1","id":"2","ts":"1730400000"},"body":{"target":"alice"}})");
    EXPECT_TRUE(ping != nullptr);

    auto quit = mk(R"({"header":{"type":"Quit","ver":"1","id":"3","ts":"1730400000"},"body":{}})");
    EXPECT_TRUE(quit != nullptr);
}

TEST(MessageFactory, FailsOnMissingType) {
    auto bad = mk(R"({"header":{"ver":"1","id":"4","ts":"1730400000"},"body":{}})");
    EXPECT_EQ(bad, nullptr);
}
