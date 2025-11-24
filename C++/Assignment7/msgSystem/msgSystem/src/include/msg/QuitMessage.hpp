#pragma once
#include "Message.hpp"

class QuitMessage : public Message 
{
public:
    explicit QuitMessage(const MsgHeader& hdr) { header = hdr; }
    
    bool loadBody(std::string& body) override;
    std::string process() override;
    std::string toJson() override;
};


