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
        util::requireObject(j, "header", "Message::fromJson");
        json hdr = j["header"];

        // 2) Parse header fields
        util::requireField(hdr, "type", "Message::fromJson");
        util::requireField(hdr, "ver",  "Message::fromJson");
        util::requireField(hdr, "id",   "Message::fromJson");
        util::requireField(hdr, "ts",   "Message::fromJson");

        auto getStr = [&](const std::string& key) -> std::string
        {
            const json& v = hdr[key];

            if (v.is_string())
                return v.get<std::string>();

            if (v.is_number_integer() || v.is_number_unsigned())
                return std::to_string(v.get<long long>());

            throw std::runtime_error("Header field '" + key + "' must be string or number");
        };

        std::string typeStr = getStr("type");
        std::string verStr  = getStr("ver");
        std::string idStr   = getStr("id");
        std::string tsStr   = getStr("ts");

        unsigned ver = std::stoul(verStr);
        unsigned id  = std::stoul(idStr);
        unsigned ts  = std::stoul(tsStr);

        // 3) Grab body (pass it to the concrete parser)
        util::requireObject(j, "body", "Message::fromJson");
        json bodyJson = j["body"];
        std::string bodyStr = bodyJson.dump();

        // 4) Construct the right concrete message
        Message* msg = nullptr;

        if (typeStr == "Log")
            msg = new LogMessage();
        else if (typeStr == "Ping")
            msg = new PingMessage();
        else if (typeStr == "Ls")
            msg = new LsMessage();
        else if (typeStr == "Quit")
            msg = new QuitMessage();
        else
            throw std::runtime_error("Unknown message type: " + typeStr);

        msg->header = MsgHeader(typeStr, ver, id, ts);

        if (!msg->loadBody(bodyStr)) {
            delete msg;
            throw std::runtime_error("Failed to load body for type: " + typeStr);
        }

        return msg;
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
