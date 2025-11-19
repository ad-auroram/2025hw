#include <iostream>
#include <array>
#include <algorithm>
#include <random>
#include "sortutils.hpp"

int main(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(-10000000, 10000000);

    SourceArray random;
    std::generate(random.begin(), random.end(), [&]() { return dist(gen); });

    SourceArray sorted = random;
    std::sort(sorted.begin(), sorted.end());

    SourceArray reversed = sorted;
    std::reverse(reversed.begin(), reversed.end());

    SourceArray organPipe = sorted;
    organPipeStdArray(organPipe);

    SourceArray rotated = sorted;
    std::rotate(rotated.begin(), rotated.begin() + 1, rotated.end());

    std::cout << "\n --- Raw Array Performance ---\n\n";
    evaluateRawArray(random, sorted, reversed, organPipe, rotated);

    std::cout << "\n\n --- std::array Performance ---\n\n";
    evaluateStdArray(random, sorted, reversed, organPipe, rotated);

    std::cout << "\n\n --- std::vector Performance ---\n\n";
    evaluateStdVector(random, sorted, reversed, organPipe, rotated);
    return 0;
}