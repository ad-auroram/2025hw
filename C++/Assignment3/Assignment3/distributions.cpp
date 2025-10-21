#include "distributions.hpp"
#include <iostream>
#include <random>
#include <format>
#include <cmath>

DistributionPair::DistributionPair(std::uint32_t minValue, std::uint32_t maxValue)
    : minValue(minValue), maxValue(maxValue), count(0) 
{
}

std::vector<DistributionPair> generateUniformDistribution(std::uint32_t howMany, std::uint32_t min, std::uint32_t max, std::uint8_t numberBins)
{
    std::vector<DistributionPair> result;

    if (min > max || numberBins == 0) {
        return result;
    }

    std::uint32_t range = max - min + 1;
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

    if (numberBins == 0 || stdev <= 0.0f){
        return result;
    } 

    float rawMin = mean - 4.0f * stdev;
    float rawMax = mean + 4.0f * stdev;

    int rangeMin = static_cast<int>(std::floor(rawMin));
    int rangeMax = static_cast<int>(std::ceil(rawMax));

    int totalRange = rangeMax - rangeMin + 1;
    if (totalRange < numberBins) totalRange = numberBins;

    int binSize = totalRange / numberBins;
    if (binSize == 0) binSize = 1;

    rangeMax = rangeMin + binSize * numberBins - 1;

    for (int i = 0; i < numberBins; ++i) {
        int binMin = rangeMin + i * binSize;
        int binMax = (i == numberBins - 1) ? rangeMax : binMin + binSize - 1;
        result.emplace_back(static_cast<std::uint32_t>(binMin), static_cast<std::uint32_t>(binMax));
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<float> dist(mean, stdev);

    for (std::uint32_t i = 0; i < howMany; ++i) {
        int value = static_cast<int>(std::floor(dist(gen)));
        int binIndex = (value - rangeMin) / binSize;
        if (binIndex < 0) binIndex = 0;
        else if (binIndex >= numberBins) binIndex = numberBins - 1;
        ++result[binIndex].count;
    }

    return result;
}

std::vector<DistributionPair> generatePoissonDistribution(std::uint32_t howMany, std::uint8_t howOften, std::uint8_t numberBins)
{
    std::vector<DistributionPair> result;

    if (numberBins == 0 || howOften == 0){
        return result;
    }

    std::uint32_t maxValue = static_cast<std::uint32_t>(howOften) * 3;
    std::uint32_t totalRange = maxValue;
    std::uint32_t binSize = totalRange / numberBins;
    if (binSize == 0) binSize = 1;

    for (std::uint8_t i = 0; i < numberBins; ++i) {
        std::uint32_t binMin = i * binSize;
        std::uint32_t binMax = (i == numberBins - 1) ? maxValue - 1 : binMin + binSize - 1;
        result.emplace_back(binMin, binMax);
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::poisson_distribution<int> dist(howOften);

    for (std::uint32_t i = 0; i < howMany; ++i) {
        int value = dist(gen);
        if (value >= static_cast<int>(maxValue)) value = static_cast<int>(maxValue) - 1;

        int binIndex = value / binSize;
        if (binIndex >= numberBins) binIndex = numberBins - 1;
        ++result[binIndex].count;
    }

    return result;
}

void plotDistribution(std::string title, const std::vector<DistributionPair>& distribution, std::uint8_t maxPlotLineSize)
{
    if (distribution.empty() || maxPlotLineSize == 0) return;

    std::uint32_t maxCount = 0;
    for (const auto& bin : distribution) {
        if (bin.count > maxCount) maxCount = bin.count;
    }

    if (maxCount == 0) maxCount = 1;

    std::cout << std::format("--- {} ---\n", title);

    for (const auto& bin : distribution) {
        std::uint8_t numStars = static_cast<std::uint8_t>(
            std::round(static_cast<float>(bin.count) / maxCount * maxPlotLineSize)
        );

        std::string stars(numStars, '*');
        std::cout << std::format("[{:3}, {:3}] : {}\n", bin.minValue, bin.maxValue, stars);
    }
}