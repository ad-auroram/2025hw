#include "MsgIO.hpp"
#include "FileIO.hpp"
#include "StdinIO.hpp"
#include <stdexcept>

std::unique_ptr<MsgIO> MsgIO::makeIO(IOType ioType, const std::string& param) 
{
    (void)ioType;
    (void)param;
    throw std::runtime_error("Unknown IOType");
}
