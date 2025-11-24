#pragma once
#include "MsgIO.hpp"
#include <string>

class StdinIO : public MsgIO 
{
public:
    void open() override;
    void close() override;
    std::string readOne() override;
    void writeOne(const std::string& frame) override;
};
