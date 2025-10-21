#include <iostream>
#include <cmath>
#include <chrono>
#include "sortutils.hpp"

void initializeRawArrayFromStdArray(const SourceArray& source, int dest[]);

void organPipeStdArray(SourceArray& data);

void evaluateRawArray(const SourceArray& random, const SourceArray& sorted, const SourceArray& reversed, const SourceArray& organPipe, const SourceArray& rotated){

    for (std::uint8_t r = 0; r < HOW_MANY_TIMES; ++r) {

            int work[HOW_MANY_ELEMENTS];
            initializeRawArrayFromStdArray(src, work);        // each loop, re-initialize an raw array work from src

            auto start = Clock::now();
            std::sort(std::begin(work), std::end(work));      // timed, only for sorting
            auto stop  = Clock::now();

            total += std::chrono::duration_cast<Micro>(stop - start);
    }


}

void evaluateStdArray(const SourceArray& random, const SourceArray& sorted, const SourceArray& reversed, const SourceArray& organPipe, const SourceArray& rotated);

void evaluateStdVector(const SourceArray& random, const SourceArray& sorted, const SourceArray& reversed, const SourceArray& organPipe, const SourceArray& rotated);

