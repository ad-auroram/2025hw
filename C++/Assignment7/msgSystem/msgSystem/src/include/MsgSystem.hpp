#pragma once
#include "MsgIO.hpp"
#include <memory>
#include <string>
#include <unordered_map>

class MsgSystem 
{
public:
    explicit MsgSystem(IOType ioType, const std::string& param);
    void start();
    void end();
    
private:
    std::unique_ptr<MsgIO> msgIO;
    std::unordered_map<std::string, unsigned> counts;

private:
    void printMsgStats();
    std::string buildStatsText() const;  
    void countMsgType(const std::string& frame);
};
