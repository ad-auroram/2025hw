
#include <iostream>
#include <string>
#include <cmath>

long nbonacci(unsigned int series, unsigned int n){
    if (n == 0) return 0;
    if (series == 0) return 0;
    if (n<series+1) return 1;

    long sum = 0;
    for (unsigned int i = 1; i <= series; ++i)
        sum += nbonacci(series, n - i);

    return sum;
}

void computeNbonacciRatio(std::string title, unsigned int series){
    const double maxDiff = 0.000001;
    double prevRatio = 0.0;
    double curRatio = 1.0;
    unsigned int n = series;
    unsigned int iterations = n-1;

    while (true) {
        long num = nbonacci(series, n);
        long prevNum = nbonacci(series, n - 1);
        curRatio = static_cast<double>(num) / static_cast<double>(prevNum);

        if (std::abs(curRatio - prevRatio) < maxDiff) {
            break;
        }
        prevRatio = curRatio;
        n+=1;
        iterations+=1;
    }
    std::cout << title << " ratio approaches " << curRatio << " after " << iterations << " iterations" << std::endl;
}


int main() {
    std::cout << "--- Fibonacci Sequence ---" << std::endl;
    for (unsigned int i = 1; i < 21; ++i) {
        std::cout << nbonacci(2, i) << " ";
    }
    std::cout << "\n--- Tribonacci Sequence ---" << std::endl;
    for (unsigned int i = 1; i < 21; ++i) {
        std::cout << nbonacci(3, i) << " ";
    }
    std::cout << "\n--- Fourbonacci Sequence ---" << std::endl;
    for (unsigned int i = 1; i < 21; ++i) {
        std::cout << nbonacci(4, i) << " ";
    }
    std::cout << "\n--- Fivebonacci Sequence ---" << std::endl;
    for (unsigned int i = 1; i < 21; ++i) {
        std::cout << nbonacci(5, i) << " ";
    }
    std::cout<< "\n" << std::endl;
    computeNbonacciRatio("Fibonacci", 2);
    computeNbonacciRatio("Tribonacci", 3);
    computeNbonacciRatio("Fourbonacci", 4);
    computeNbonacciRatio("Fivebonacci", 5);
    return 0;
}