// Message.cpp
#include "Util.hpp"
#include "LsMessage.hpp"

using json = nlohmann::json;

/*
Example inputs:

{"header":{"type":"Ls","ver":"1","id":"0002","ts":"1730401000"},
 "body":{"dir": "/home"}}

*/

// LsMessage
bool LsMessage::loadBody(std::string& body) 
{
    (void)(body);
    return true;
}

std::string LsMessage::process() 
{
    return "";
}

std::string LsMessage::toJson() 
{
    return "";
}

