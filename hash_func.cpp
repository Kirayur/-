#include "hash_func.h"

uint32_t HashFuncGen::hash(const std::string& s) const {
    uint32_t hash = 2166136261u;
    for (char c : s) {
        hash ^= static_cast<uint8_t>(c);
        hash *= 16777619u;
    }
    return hash;
}
