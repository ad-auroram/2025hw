#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip> 
#include "MsgSystem.hpp"
#include "Message.hpp"


MsgSystem::MsgSystem(IOType ioType, const std::string& param)
    : msgIO(MsgIO::makeIO(ioType, param)) {}

void MsgSystem::start() 
{
    
}

void MsgSystem::end() 
{
    std::cout << "[MsgSystem] Shutdown complete.\n";
}

void MsgSystem::countMsgType(const std::string& type)
{
    if (type.empty()) {
        return;
    }

    auto it = counts.find (type);
    if (it == counts.end ()) {
        counts.emplace(type, 1);
    }
    else {
        it->second++;
    }

    return;
}

void MsgSystem::printMsgStats()
{
    std::string stat = buildStatsText();
    std::cout<<stat<<"\n";
}

std::string MsgSystem::buildStatsText() const 
{
    std::vector<std::pair<std::string, std::size_t>> rows(counts.begin(), counts.end());
    std::sort(rows.begin(), rows.end(),
              [](auto& a, auto& b){ return a.first < b.first; });

    std::size_t name_w = 4;
    for (const auto& kv : rows) name_w = std::max(name_w, kv.first.size());

    std::size_t total = 0;
    for (const auto& kv : rows) total += kv.second;

    std::ostringstream out;
    out << "Message Summary\n";
    out << "Total: " << total << "\n";
    out << std::left << std::setw(static_cast<int>(name_w)) << "Type" << "  Count\n";
    out << std::string(name_w, '-') << "  " << "-----\n";

    for (const auto& kv : rows) {
        out << std::left << std::setw(static_cast<int>(name_w)) << kv.first
            << "  " << kv.second << "\n";
    }
    return out.str();
}