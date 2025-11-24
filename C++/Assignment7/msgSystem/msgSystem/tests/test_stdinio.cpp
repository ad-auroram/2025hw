
#include <gtest/gtest.h>
#include <iostream>
#include <sstream>
#include <string>
#include "io/StdinIO.hpp"

TEST(StdinIO, ReadWrite) {
    std::istringstream fakeIn(
        std::string("hello\nworld\n")
    );
    std::streambuf* oldIn = std::cin.rdbuf(fakeIn.rdbuf());

    std::ostringstream fakeOut;
    std::streambuf* oldOut = std::cout.rdbuf(fakeOut.rdbuf());

    StdinIO io;
    io.open();
    auto a = io.readOne();
    auto b = io.readOne();
    io.writeOne("ok1");
    io.writeOne("ok2");
    io.close();

    std::cin.rdbuf(oldIn);
    std::cout.rdbuf(oldOut);

    EXPECT_EQ(a, "hello");
    EXPECT_EQ(b, "world");
    auto out = fakeOut.str();
    EXPECT_NE(out.find("ok1"), std::string::npos);
    EXPECT_NE(out.find("ok2"), std::string::npos);
}
