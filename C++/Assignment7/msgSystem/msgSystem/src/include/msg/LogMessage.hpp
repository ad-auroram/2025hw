#pragma once
#include "Message.hpp"

class LogMessage : public Message 
{
public:
    explicit LogMessage(const MsgHeader& hdr) { header = hdr; }
    
    bool loadBody(std::string& body) override;
    std::string process() override;
    std::string toJson() override;
private:
    std::string path;
};
