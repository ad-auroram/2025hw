#include "StdinIO.hpp"
#include <iostream>

void StdinIO::open() 
{
    std::cout << "[StdinIO] Ready. Type a line and press Enter (empty line to quit).\n";
}

void StdinIO::close() 
{
    std::cout << "[StdinIO] Closing.\n";
}

std::string StdinIO::readOne() 
{
    std::string line;
    if (!std::getline(std::cin, line)) {
        return {};
    }

    return line;
}

void StdinIO::writeOne(const std::string& frame) 
{
    std::cout << "[StdinIO echo] " << frame << "\n";
}
