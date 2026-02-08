#include "hyperloglog_bias.h"
#include <cmath>
#include <algorithm>

static double alphaMultiplier(uint32_t m) {
    if (m == 16) return 0.673 * m * m;
    if (m == 32) return 0.697 * m * m;
    if (m == 64) return 0.709 * m * m;
    return (0.7213 / (1 + 1.079 / m)) * m * m;
}

const std::vector<double> HyperLogLogBiasCorrected::biasTable = {
    0.0, 1.0, 2.0, 3.0, 4.0,  // примерные смещения, для более точных нужна таблица из статьи
};

HyperLogLogBiasCorrected::HyperLogLogBiasCorrected(uint8_t B)
    : B(B), m(1u << B), M(m, 0) {}

void HyperLogLogBiasCorrected::add(uint32_t hash) {
    uint32_t idx = hash >> (32 - B);
    uint32_t w = hash << B;
    uint8_t r = 1;
    while ((w & 0x80000000) == 0) {
        r++;
        w <<= 1;
    }
    M[idx] = std::max(M[idx], r);
}

double HyperLogLogBiasCorrected::rawEstimate() const {
    double sum = 0;
    for (auto v : M) sum += std::pow(2.0, -v);
    return alphaMultiplier(m) / sum;
}

double HyperLogLogBiasCorrected::biasCorrected(double raw) const {
    int idx = std::min((int)biasTable.size()-1, (int)std::round(raw));
    return raw - biasTable[idx]; 
}

double HyperLogLogBiasCorrected::estimate() const {
    double raw = rawEstimate();
    return biasCorrected(raw);
}
