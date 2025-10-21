#include <iostream>
#include <array>
#include <algorithm>
#include <random>
#include "sortutils.hpp"

void main(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(-10000000, 10000000);

    SourceArray random;
    std::generate(random.begin(), random.end(), [&]() { return dist(gen); });

    SourceArray sorted = random;
    std::sort(sorted.begin(), sorted.end());

    SourceArray reversed = random;
    std::reverse(reversed.begin(), reversed.end());

    SourceArray organPipe = random;
    organPipeStdArray(organPipe);

    SourceArray rotated = random;
    std::rotate(rotated.begin(), rotated.end());

    std::cout << "\n --- Raw Array Performance ---\n\n";
    evaluateRawArray(random, sorted, reversed, organPipe, rotated);

    std::cout << "\n\n --- std::array Performance ---\n\n";
    evaluateStdArray(random, sorted, reversed, organPipe, rotated);

    std::cout << "\n\n --- std::vector Performance ---\n\n";
    evaluateStdVector(random, sorted, reversed, organPipe, rotated);

}