
#include <gtest/gtest.h>
#include <filesystem>
#include <fstream>
#include <string>
#include "io/FileIO.hpp"

namespace fs = std::filesystem;

static std::string slurp(const fs::path& p) {
    std::ifstream ifs(p, std::ios::binary);
    return std::string((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
}

static void dump(const fs::path& p, const std::string& s) {
    std::ofstream ofs(p, std::ios::binary);
    ofs << s;
}

TEST(FileIO, ReadWrite) {
    auto dir = fs::temp_directory_path() / "assignment7_fileio_test";
    fs::create_directories(dir);
    auto in = dir / "messages.txt";
    auto out = dir / "output.txt";

    dump(in, std::string(R"({"header":{"type":"Ping"},"body":{}})") + "\n" +
              R"({"header":{"type":"Quit"},"body":{}})" + "\n");

    FileIO io(in.string());
    io.open();
    auto l1 = io.readOne();
    auto l2 = io.readOne();
    EXPECT_NE(l1.find("\"Ping\""), std::string::npos);
    EXPECT_NE(l2.find("\"Quit\""), std::string::npos);

    io.writeOne("ACK-1");
    io.writeOne("ACK-2");
    io.close();

    ASSERT_TRUE(fs::exists(out));
    auto outText = slurp(out);
    EXPECT_NE(outText.find("ACK-1"), std::string::npos);
    EXPECT_NE(outText.find("ACK-2"), std::string::npos);
}
