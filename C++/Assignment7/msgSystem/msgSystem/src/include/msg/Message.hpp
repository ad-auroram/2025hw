#pragma once
#include <string>
#include <iostream>

// Messgage header fields
struct MsgHeader 
{
    std::string type;
    unsigned    ver{1};
    unsigned    id{0};
    unsigned    ts{0};

    MsgHeader() = default;
    MsgHeader(const std::string& t, unsigned v, unsigned i, unsigned time)
        : type(t), ver(v), id(i), ts(time) {}
};

// Abstract message base. 
class Message 
{
public:
    virtual ~Message() = default;

    // Create a specific Message from a raw JSON string.
    static Message* fromJson(std::string& raw);

    // Parse type-specific body.
    virtual bool loadBody(std::string& body) = 0;

    // Perform type-specific logic.
    virtual std::string process() = 0;

    // Serialize back to JSON (to be implemented by derived classes in A8).
    virtual std::string toJson() = 0;

    // Helper to create JSON header.
    std::string toJsonHeader();

public:
    std::string getType() const { return header.type; }
    unsigned    getVer()  const { return header.ver;  }
    unsigned    getId()   const { return header.id;   }
    unsigned    getTs()   const { return header.ts;   }

protected:
    MsgHeader header;
};
