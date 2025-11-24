// Message.cpp
#include "Util.hpp"
#include "LogMessage.hpp"

using json = nlohmann::json;

/*
Example inputs:

{"header":{"type":"Log","ver":"1","id":"0001","ts":"1730400000"},
 "body":{"path":"./app.log"}}

*/

// LogMessage
bool LogMessage::loadBody(std::string& body) 
{
    (void)body;
    return true;
}

std::string LogMessage::process() 
{
    return "";
}

std::string LogMessage::toJson() 
{
    return "";
}

