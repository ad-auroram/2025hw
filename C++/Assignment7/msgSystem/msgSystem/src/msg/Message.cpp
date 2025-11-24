// Message.cpp
#include "Util.hpp"
#include "LogMessage.hpp"
#include "LsMessage.hpp"
#include "PingMessage.hpp"
#include "QuitMessage.hpp"

using json = nlohmann::json;

/*
Example inputs:

{"header":{"type":"Log","ver":1,"id":"0001","ts":1730400000},
 "body":{"path":"./app.log"}}

{"header":{"type":"Ping","ver":1,"id":"0003","ts":1730402000},
 "body":{"target":"alice"}}

 {"header":{"type":"Ls","ver":"1","id":"0002","ts":"1730401000"},
 "body":{"dir": "/home"}}

 {"header":{"type":"Quit","ver":1,"id":"0002","ts":1730401000},
 "body":{}}

*/


Message* Message::fromJson(std::string& raw)
{
    try {
        json j = json::parse(raw);

        // 1) Validate top-level structure, e.g.,  util::requireObject(j, "header", WHERE);
       

        // 2) Parse header fields
       

        // 3) Grab body (pass it to the concrete parser)


        // 4) Construct the right concrete message
        
        return nullptr;
    }
    catch (const std::exception& e) {
        std::cerr << "[MessageFactory] Parse/construct error: " << e.what() << "\n";
        return nullptr;
    }
}

std::string Message::toJsonHeader()
{
    json hdr = {
        {"type", header.type},
        {"ver", std::to_string(header.ver)},
        {"id", std::to_string(header.id)},
        {"ts", std::to_string(time(nullptr))}
    };

    return hdr.dump();
}
