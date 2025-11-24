// Message.cpp
#include "Util.hpp"
#include "PingMessage.hpp"

using json = nlohmann::json;

/*
Example inputs:

{"header":{"type":"Ping","ver":"1","id":"0003","ts":"1730402000"},
 "body":{"target":"alice"}}
*/

bool PingMessage::loadBody(std::string& body) 
{
    (void)body;
    return true;
}

std::string PingMessage::process() 
{
    return "";
}

std::string PingMessage::toJson() 
{
    return "";
}

