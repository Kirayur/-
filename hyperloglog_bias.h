#pragma once
#include <vector>
#include <cstdint>

class HyperLogLogBiasCorrected {
public:
    HyperLogLogBiasCorrected(uint8_t B);

    void add(uint32_t hash);
    double estimate() const;

private:
    uint8_t B;
    uint32_t m;
    std::vector<uint8_t> M;

    double rawEstimate() const;
    double biasCorrected(double raw) const;

    static const std::vector<double> biasTable;
};
