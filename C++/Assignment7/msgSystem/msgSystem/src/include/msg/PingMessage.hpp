#pragma once
#include "Message.hpp"

class PingMessage : public Message 
{
public:
    explicit PingMessage(const MsgHeader& hdr):target("") { header = hdr; }

    bool loadBody(std::string& body) override;
    std::string process() override;
    std::string toJson() override;
    
private:
    std::string target;
};

