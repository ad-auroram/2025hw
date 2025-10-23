#include "sortutils.hpp"
#include <iostream>
#include <cmath>
#include <chrono>
#include <algorithm>
#include <vector>
#include <format>


void initializeRawArrayFromStdArray(const SourceArray& source, int dest[]){  
    std::copy(source.begin(), source.end(), dest);
}


void organPipeStdArray(SourceArray& data){  
    SourceArray temp;
    std::size_t n = data.size();

    for (std::size_t i = 0; i < n / 2; ++i)
        temp[i] = data[i];

    for (std::size_t i = n / 2; i < n; ++i)
        temp[i] = data[n - 1 - i];

    data = temp;
}

static void printResult(const std::string& label, double avgMs) {
    std::cout << std::format("        {:<16}: {:>6.1f} ms\n", label + " Time", avgMs);
}

void evaluateRawArray(const SourceArray& random, const SourceArray& sorted, const SourceArray& reversed, const SourceArray& organPipe, const SourceArray& rotated){
    const std::pair<std::string, const SourceArray*> sources[] = {
        {"Random",     &random},
        {"Sorted",     &sorted},
        {"Reversed",   &reversed},
        {"Organ Pipe", &organPipe},
        {"Rotated",    &rotated}
    };
    for (const auto& [name, src] : sources) {
        std::chrono::microseconds total{0}; 

        for (std::uint8_t r = 0; r < HOW_MANY_TIMES; ++r) {

                int work[HOW_MANY_ELEMENTS];
                initializeRawArrayFromStdArray(*src, work);

                auto start = std::chrono::steady_clock::now();
                std::sort(std::begin(work), std::end(work));
                auto stop  = std::chrono::steady_clock::now();

                total += std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        }
        double avgMs = (total.count() / 1000.0) / HOW_MANY_TIMES;
        printResult(name, avgMs);
    }
}

void evaluateStdArray(const SourceArray& random, const SourceArray& sorted, const SourceArray& reversed, const SourceArray& organPipe, const SourceArray& rotated){
    const std::pair<std::string, const SourceArray*> sources[] = {
        {"Random",     &random},
        {"Sorted",     &sorted},
        {"Reversed",   &reversed},
        {"Organ Pipe", &organPipe},
        {"Rotated",    &rotated}
    };
    for (const auto& [name, src] : sources) {
        std::chrono::microseconds total{0};
        for (std::uint8_t r = 0; r < HOW_MANY_TIMES; ++r) {
                SourceArray work = *src;
                auto start = std::chrono::steady_clock::now();
                std::sort(work.begin(), work.end());
                auto stop  = std::chrono::steady_clock::now();

                total += std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        }
        double avgMs = (total.count() / 1000.0) / HOW_MANY_TIMES;
        printResult(name, avgMs);
    }
}

void evaluateStdVector(const SourceArray& random, const SourceArray& sorted, const SourceArray& reversed, const SourceArray& organPipe, const SourceArray& rotated){
    const std::pair<std::string, const SourceArray*> sources[] = {
        {"Random",     &random},
        {"Sorted",     &sorted},
        {"Reversed",   &reversed},
        {"Organ Pipe", &organPipe},
        {"Rotated",    &rotated}
    };
    for (const auto& [name, src] : sources) {
        std::chrono::microseconds total{0};
        for (std::uint8_t r = 0; r < HOW_MANY_TIMES; ++r) {
                std::vector<int> work(src->begin(), src->end());

                auto start = std::chrono::steady_clock::now();
                std::sort(work.begin(), work.end());
                auto stop  = std::chrono::steady_clock::now();

                total += std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        }
        double avgMs = (total.count() / 1000.0) / HOW_MANY_TIMES;
        printResult(name, avgMs);
    }
}

