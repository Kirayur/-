#pragma once
#include <bitset>
#include <cstdint>
#include <cmath>
#include <vector>

class HyperLogLogBitset {
public:
    HyperLogLogBitset(uint8_t B);

    void add(uint32_t hash);
    double estimate() const;

private:
    uint8_t B;
    size_t m;
    std::vector<uint8_t> M;

    static double alphaMM(size_t m) {
        if (m == 16) return 0.673 * m * m;
        if (m == 32) return 0.697 * m * m;
        if (m == 64) return 0.709 * m * m;
        return (0.7213 / (1 + 1.079 / m)) * m * m;
    }
};
