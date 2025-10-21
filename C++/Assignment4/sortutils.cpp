#include <iostream>
#include <cmath>
#include <chrono>
#include <algorithm>
#include "sortutils.hpp"

void initializeRawArrayFromStdArray(const SourceArray& source, int dest[]){
    //This function accepts an std::array and copies its elements into a raw array.  
    //The muthor of assumptions is that the dest array is the same size and the source array; 
    //assume valid arrays and matching sizes are passed in (for this class, not ever for production code).
}


void organPipeStdArray(SourceArray& data){
    //This function re-organizes the values in the data array to have an organ pipe structure.  
    //It is assumed that data is already sorted.  Refer to the notes below on what an organ pipe organization looks like.
}


//Each of the evaluateX functions time and report how long it takes to sort each of the array types HOW_MANY_TIMES; look at the sample output to better understand this.  
//Each function separately times how long it takes for each array type. You'll use the constant arrays passed in as originals, making a copy of them each time you want to sort it (HOW_MANY_TIMES).
void evaluateRawArray(const SourceArray& random, const SourceArray& sorted, const SourceArray& reversed, const SourceArray& organPipe, const SourceArray& rotated){

    for (std::uint8_t r = 0; r < HOW_MANY_TIMES; ++r) {

            int work[HOW_MANY_ELEMENTS];
            initializeRawArrayFromStdArray(src, work);        // each loop, re-initialize an raw array work from src

            auto start = std::chrono::steady_clock::now();
            std::sort(std::begin(work), std::end(work));      // timed, only for sorting
            auto stop  = std::chrono::steady_clock::now();

            total += std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    }


}

void evaluateStdArray(const SourceArray& random, const SourceArray& sorted, const SourceArray& reversed, const SourceArray& organPipe, const SourceArray& rotated);

void evaluateStdVector(const SourceArray& random, const SourceArray& sorted, const SourceArray& reversed, const SourceArray& organPipe, const SourceArray& rotated);

