#pragma once
#include "MsgIO.hpp"
#include <fstream>
#include <string>
#include <filesystem>
#include <iostream>

class FileIO : public MsgIO 
{
public:
    explicit FileIO(std::string path);
    void open() override;
    void close() override;
    std::string readOne() override;
    void writeOne(const std::string& frame) override;

private:
    std::string in_path;
    std::ifstream in;

    std::string out_path;
    std::ofstream  out; // under the same direction as input file, e.g., "<dir>/output.txt"

private:
    std::string getOutputPath();
};
