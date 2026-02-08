#pragma once
#include <string>
#include <cstdint>

class HashFuncGen {
public:
    uint32_t hash(const std::string& s) const;
};
