#pragma once
#include <vector>
#include <string>
#include <random>

class RandomStreamGen {
public:
    RandomStreamGen(size_t streamSize, uint32_t seed = 42);

    const std::vector<std::string>& getStream() const;

    std::vector<std::string> getPrefix(double percent) const;

private:
    std::vector<std::string> stream;
    std::mt19937 rng;

    std::string randomString();
};
