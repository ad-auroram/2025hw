#pragma once
#include "Message.hpp"

class LsMessage : public Message 
{
public:
    explicit LsMessage(const MsgHeader& hdr) { header = hdr; }
    
    bool loadBody(std::string& body) override;
    std::string process() override;
    std::string toJson() override;
};


