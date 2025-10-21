#include <iostream>
#include <random>
#include <format>
#include <cstdint>
#include <cmath>
#include <vector>

class DistributionPair
{
    public:
    DistributionPair(std::uint32_t minValue, std::uint32_t maxValue) :
        minValue(minValue),
        maxValue(maxValue),
        count(0)
    {
    }

    std::uint32_t minValue;
    std::uint32_t maxValue;
    std::uint32_t count;
};

std::vector<DistributionPair> generateUniformDistribution(std::uint32_t howMany, std::uint32_t min, std::uint32_t max, std::uint8_t numberBins)
{
    std::vector<DistributionPair> result;

    if (min > max || numberBins == 0) {
        return result;
    }

    std::uint32_t range = max - min+1;
    std::uint32_t binSize = range / numberBins;

    for (std::uint8_t i = 0; i < numberBins; ++i) {
        std::uint32_t binMin = min + i * binSize;
        std::uint32_t binMax = (i == numberBins - 1) ? max : binMin + binSize - 1;
        result.emplace_back(binMin, binMax);
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<std::uint32_t> dist(min, max - 1);

    for (std::uint32_t i = 0; i < howMany; ++i) {
        std::uint32_t value = dist(gen);
        std::uint8_t binIndex = (value - min) / binSize;
        if (binIndex >= numberBins) binIndex = numberBins - 1;
        ++result[binIndex].count;
    }

    return result;
}

std::vector<DistributionPair> generateNormalDistribution(std::uint32_t howMany, float mean, float stdev, std::uint8_t numberBins)
{
    std::vector<DistributionPair> result;

    if (numberBins == 0 || howMany == 0 || stdev <= 0.0f) {
        return result;
    }

    int rangeMin = static_cast<int>(std::floor(mean - 4 * stdev));
    int rangeMax = static_cast<int>(std::ceil(mean + 4 * stdev));

    while ((rangeMax - rangeMin) % numberBins != 0) {
        --rangeMax;
    }

    int totalRange = rangeMax - rangeMin;
    int binSize = totalRange / numberBins;

    for (int i = 0; i < numberBins; ++i) {
        std::uint32_t binStart = rangeMin + i * binSize;
        std::uint32_t binEnd = std::min(binStart + binSize - 1, static_cast<std::uint32_t>(rangeMax));
        result.emplace_back(binStart, binEnd);
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<float> dist(mean, stdev);


    for (std::uint32_t i = 0; i < howMany; ++i) {
        float value = dist(gen);
        int intVal = static_cast<int>(std::floor(value));

        int binIndex;
        if (intVal < rangeMin) {
            binIndex = 0;
        }
        else if (intVal >= rangeMax) {
            binIndex = numberBins - 1;
        }
        else {
            binIndex = (intVal - rangeMin) / binSize;
        }

        if (binIndex >= 0 && binIndex < static_cast<int>(result.size())) {
            ++result[binIndex].count;
        }
    }

    return result;
}

std::vector<DistributionPair> generatePoissonDistribution(std::uint32_t howMany, std::uint8_t howOften, std::uint8_t numberBins)
{
    std::vector<DistributionPair> result;

    if (numberBins == 0 || howMany == 0 || howOften == 0) {
        return result;
    }

    for (std::uint8_t i = 0; i < numberBins; ++i) {
        result.emplace_back(i, i);
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::poisson_distribution<std::uint32_t> dist(howOften);

    for (std::uint32_t i = 0; i < howMany; ++i) {
        std::uint32_t value = dist(gen);
        std::uint8_t binIndex;

        if (value < 0) {
            binIndex = 0;
        }
        else if (value >= numberBins) {
            binIndex = numberBins - 1;
        }
        else {
            binIndex = static_cast<std::uint8_t>(value);
        }
        ++result[binIndex].count;
    }

    return result;
}

void plotDistribution(std::string title, const std::vector<DistributionPair>& distribution, const std::uint8_t maxPlotLineSize)
{
    if (distribution.empty() || maxPlotLineSize == 0) {
        return;
    }

    std::uint32_t maxCount = 0;
    for (const auto& bin : distribution) {
        if (bin.count > maxCount) {
            maxCount = bin.count;
        }
    }

    if (maxCount == 0) {
        maxCount = 1;
    }

    std::cout << std::format("--- {} ---\n", title);

    for (const auto& bin : distribution) {
        std::uint8_t numStars = static_cast<std::uint8_t>(
            std::round(static_cast<float>(bin.count) / maxCount * maxPlotLineSize)
        );

        std::string stars(numStars, '*');

        std::cout << std::format("[{:3}, {:3}] : {}\n", bin.minValue, bin.maxValue, stars);
    }
}

void test();
int main()
{
    auto uniform = generateUniformDistribution(100000, 0, 79, 40);
    plotDistribution("--- Uniform ---", uniform, 80);

    auto normal = generateNormalDistribution(100000, 50, 5, 40);
    plotDistribution("--- Normal ---", normal, 80);

    auto poisson = generatePoissonDistribution(100000, 6, 40);
    plotDistribution("--- Poisson ---", poisson, 80);

    test();
}



// ------------------------------------------------------------------
//
// Testing Code
//
// ------------------------------------------------------------------
#include <functional>
#include <iostream>
#include <numeric>
#include <string>

namespace testing::detail
{
    using namespace std::string_literals;

    using Bins = std::vector<std::pair<std::uint32_t, std::uint32_t>>;
    using DistFunc = std::function<std::vector<DistributionPair>()>;

#define CS3460_ASSERT_EQ(expected, actual, message)                    \
    if (expected != actual)                                            \
    {                                                                  \
        fail(message, "[ Expected", expected, "but got", actual, "]"); \
        return;                                                        \
    }

#define CS3460_CASE(x) \
    [] {               \
        return x;      \
    };                 \
    std::cout << " Case " << #x << "\n";

    template <typename Message>
    void failInternal(const Message& message)
    {
        std::cout << message << " ";
    }

    template <typename Message, typename... Messages>
    void failInternal(const Message& message, const Messages&... messages)
    {
        failInternal(message);
        failInternal(messages...);
    }

    template <typename... Messages>
    void fail(const Messages&... messages)
    {
        std::cout << "  Assertion failed: ";
        failInternal(messages...);
        std::cout << "\n";
    }

    Bins generateBins(const std::uint32_t min, const std::uint32_t max, const std::uint8_t numberBins)
    {
        const auto binRange = (max - min) / numberBins;
        auto minBin = min;
        auto maxBin = min + binRange;

        Bins results(numberBins);
        for (std::uint8_t bin = 0u; bin < numberBins; bin++)
        {
            results[bin] = { minBin, maxBin };
            minBin = maxBin + 1;
            maxBin = minBin + binRange;
        }

        return results;
    }

    void returnsTheExpectedBins(const DistFunc& func, const Bins& bins)
    {
        const auto result = func();
        CS3460_ASSERT_EQ(bins.size(), result.size(), "Wrong number of bins");
        for (auto i = 0u; i < bins.size(); i++)
        {
            CS3460_ASSERT_EQ(bins[i].first, result[i].minValue, "Wrong minimum value for bin "s + std::to_string(i));
            CS3460_ASSERT_EQ(bins[i].second, result[i].maxValue, "Wrong maximum value for bin "s + std::to_string(i));
        }
    }

    void hasTheCorrectTotalAcrossAllBins(const DistFunc& func, const std::uint32_t howMany)
    {
        const auto result = func();
        const auto add_counts = [](std::uint32_t total, const DistributionPair& bin)
        {
            return total + bin.count;
        };
        CS3460_ASSERT_EQ(howMany, std::accumulate(result.cbegin(), result.cend(), 0u, add_counts),
                        "Wrong number of elements across all bins");
    }

    void testUniformDistribution()
    {
        std::cout << "Testing generateUniformDistribution\n";
        auto func = CS3460_CASE(generateUniformDistribution(100000, 0, 79, 40));
        returnsTheExpectedBins(func, generateBins(0, 79, 40));
        hasTheCorrectTotalAcrossAllBins(func, 100000);

        auto func2 = CS3460_CASE(generateUniformDistribution(0, 50, 59, 10));
        returnsTheExpectedBins(func2, generateBins(50, 59, 10));

        auto func3 = CS3460_CASE(generateUniformDistribution(0, 0, 79, 40));
        hasTheCorrectTotalAcrossAllBins(func3, 0);

        auto func4 = CS3460_CASE(generateUniformDistribution(100000, 0, 79, 1));
        hasTheCorrectTotalAcrossAllBins(func4, 100000);
    }

    void testNormalDistribution()
    {
        std::cout << "Testing generateNormalDistribution\n";
        auto func = CS3460_CASE(generateNormalDistribution(100000, 50, 5, 40));
        returnsTheExpectedBins(func, generateBins(30, 69, 40));
        hasTheCorrectTotalAcrossAllBins(func, 100000);

        auto func2 = CS3460_CASE(generateNormalDistribution(0, 50, 5, 40));
        hasTheCorrectTotalAcrossAllBins(func2, 0);

        auto func3 = CS3460_CASE(generateNormalDistribution(100000, 20.5, 1.125, 9));
        returnsTheExpectedBins(func3, generateBins(16, 24, 9));
        hasTheCorrectTotalAcrossAllBins(func3, 100000);
    }

    void testPoissonDistribution()
    {
        std::cout << "Testing generatePoissonDistribution\n";
        auto func = CS3460_CASE(generatePoissonDistribution(100000, 6, 40));
        returnsTheExpectedBins(func, generateBins(0, 39, 40));
        hasTheCorrectTotalAcrossAllBins(func, 100000);

        auto func2 = CS3460_CASE(generatePoissonDistribution(0, 6, 40));
        hasTheCorrectTotalAcrossAllBins(func2, 0);

        auto func3 = CS3460_CASE(generatePoissonDistribution(100000, 255, 40));
        hasTheCorrectTotalAcrossAllBins(func3, 100000);
    }
} // namespace testing::detail

void test()
{
    using namespace testing::detail;

    testUniformDistribution();
    testNormalDistribution();
    testPoissonDistribution();

    std::cout << "\n\n";
}