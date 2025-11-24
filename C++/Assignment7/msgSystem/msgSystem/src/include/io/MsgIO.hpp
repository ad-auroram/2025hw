#pragma once
#include <memory>
#include <string>

enum class IOType { File, Stdin, Socket };

class MsgIO 
{
public:
    virtual ~MsgIO() = default;
    virtual void open() = 0;
    virtual void close() = 0;

    // Read exactly one frame (e.g., one line). Return empty string on EOF/closed.
    virtual std::string readOne() = 0;

    // Write exactly one frame (the implementation decides where it goes: stdout, file, etc.)
    virtual void writeOne(const std::string& frame) = 0;

    // Factory
    static std::unique_ptr<MsgIO> makeIO(IOType ioType, const std::string& param);
};
