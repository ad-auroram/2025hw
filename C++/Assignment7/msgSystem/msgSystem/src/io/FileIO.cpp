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
    if (!in.is_open()) {
        return "";
    }

    std::string line;

    while (std::getline(in, line)) {
        auto notspace = [](unsigned char c){ return !std::isspace(c); };

        line.erase(line.begin(),
        std::find_if(line.begin(), line.end(), notspace));

        line.erase(std::find_if(line.rbegin(), line.rend(), notspace).base(), line.end());

        if (!line.empty())
            return line;
    }

    return "";
}

void FileIO::writeOne(const std::string& frame) 
{ 
    if (!out.is_open()) {
        throw std::runtime_error("FileIO: output file is not open");
    }

    out << frame << "\n";
    out.flush();
}


std::string FileIO::getOutputPath() 
{
    fs::path p(in_path);
    fs::path dir = p.parent_path();

    return (dir / "output.txt").string();
}