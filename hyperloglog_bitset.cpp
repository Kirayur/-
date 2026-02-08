#include "hyperloglog_bitset.h"
#include <algorithm>

HyperLogLogBitset::HyperLogLogBitset(uint8_t B) : B(B), m(1u << B), M(m, 0) {}

void HyperLogLogBitset::add(uint32_t hash) {
    uint32_t idx = hash >> (32 - B);
    uint32_t w = (hash << B);
    uint8_t r = 1;
    while ((w & 0x80000000) == 0 && r < 32) {
        r++;
        w <<= 1;
    }
    if (r > M[idx]) M[idx] = r;
}

double HyperLogLogBitset::estimate() const {
    double sum = 0.0;
    for (auto v : M) sum += std::pow(2.0, -v);

    double raw = alphaMM(m) / sum;

    size_t V = std::count(M.begin(), M.end(), 0);
    if (raw <= 2.5 * m && V > 0)
        return m * std::log((double)m / V);
    else
        return raw;
}
