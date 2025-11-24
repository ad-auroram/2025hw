#include "FileIO.hpp"

namespace fs = std::filesystem;

FileIO::FileIO(std::string path) : in_path(std::move(path)) {}

void FileIO::open() 
{
    in.open(in_path);
    if (!in.is_open()) {
        throw std::runtime_error("FileIO: could not open input file: " + in_path);
    }

    out_path = getOutputPath();

    out.open(out_path, std::ios::trunc);
    if (!out.is_open()) {
        throw std::runtime_error("FileIO: could not open output file: " + out_path);
    }
}

void FileIO::close() 
{
    if (in.is_open()) in.close();
    if (out.is_open()) out.close();
}

std::string FileIO::readOne() 
{
    return "";
}

void FileIO::writeOne(const std::string& frame) 
{ 
    (void)frame;
    return;
}


std::string FileIO::getOutputPath() 
{
    return "";
}