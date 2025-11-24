
#include <gtest/gtest.h>
#include <filesystem>
#include <fstream>
#include <memory>
#include <string>
#include "io/MsgIO.hpp"
#include "io/FileIO.hpp"
#include "io/StdinIO.hpp"

namespace fs = std::filesystem;

static void dump(const fs::path& p, const std::string& s) {
    std::ofstream ofs(p, std::ios::binary);
    ofs << s;
}

TEST(MsgIO, PolymorphicUsage) {
    // FileIO via base
    auto dir = fs::temp_directory_path() / "assignment7_msgio_poly";
    fs::create_directories(dir);
    auto in = dir / "messages.txt";
    auto out = dir / "output.txt";
    dump(in, "line1\nline2\n");

    std::unique_ptr<MsgIO> io(new FileIO(in.string()));
    io->open();
    auto a = io->readOne();
    auto b = io->readOne();
    io->writeOne("w1");
    io->close();
    EXPECT_EQ(a, "line1");
    EXPECT_EQ(b, "line2");
    EXPECT_TRUE(fs::exists(out));

    // StdinIO via base
    std::istringstream fakeIn("x\ny\n");
    std::streambuf* oldIn = std::cin.rdbuf(fakeIn.rdbuf());
    std::ostringstream fakeOut;
    std::streambuf* oldOut = std::cout.rdbuf(fakeOut.rdbuf());

    std::unique_ptr<MsgIO> io2(new StdinIO());
    io2->open();
    auto x = io2->readOne();
    auto y = io2->readOne();
    io2->writeOne("ok");
    io2->close();

    std::cin.rdbuf(oldIn);
    std::cout.rdbuf(oldOut);

    EXPECT_EQ(x, "x");
    EXPECT_EQ(y, "y");
    EXPECT_NE(fakeOut.str().find("ok"), std::string::npos);
}
