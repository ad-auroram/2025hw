// Message.cpp
#include "Util.hpp"
#include "QuitMessage.hpp"

using json = nlohmann::json;

/*
Example inputs:

{"header":{"type":"Quit","ver":"1","id":"0002","ts":"1730401000"},
 "body":{}}

*/

// QuitMessage
bool QuitMessage::loadBody(std::string& body) 
{
    (void)body;
    return true;
}

std::string QuitMessage::process() 
{
    return "";
}

std::string QuitMessage::toJson() 
{
    return "";
}

