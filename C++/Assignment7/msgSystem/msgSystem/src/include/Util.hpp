#include <nlohmann/json.hpp>

namespace util 
{

static inline std::string where(const char* file, int line) 
{
    return std::string(file) + ":" + std::to_string(line) + " ";
}

static inline void requireField(const nlohmann::json& j, 
                                const std::string& field, 
                                std::string WHERE = "") 
{
    if (!j.contains(field)) {
        throw std::runtime_error("Missing required field: " + field + " @" + WHERE);
    }
}

static inline void requireString(const nlohmann::json& j, 
                                 const std::string& field, 
                                 std::string WHERE = "") 
{
    requireField(j, field, WHERE);
    if (!j[field].is_string()) {
        throw std::runtime_error("Field '" + field + "' is not a string");
    }   
}

static inline void requireObject(const nlohmann::json& j, 
                                 const std::string& field, 
                                 std::string WHERE = "") 
{
    requireField(j, field, WHERE);
    if (!j[field].is_object()) {
        throw std::runtime_error("Field '" + field + "' is not an object");
    }  
}

static inline void requireInt(const nlohmann::json& j, 
                              const std::string& field, 
                              std::string WHERE = "") 
{
    requireField(j, field, WHERE);
    if (!j[field].is_number_integer()) {
        throw std::runtime_error("Field '" + field + "' is not an integer");
    }
}

} // namespace util

#define WHERE ::util::where(__FILE__, __LINE__)
