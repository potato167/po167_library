#pragma once
#include "../modint/mint61.hpp"
#include <random>
#include <string>
#include <vector>

namespace po167{
struct RollingHash {
    using u64 = uint64_t;
    static inline const mint61 base = std::mt19937_64{std::random_device{}()}();
    int n;
    std::vector<mint61> hash, pow;
    RollingHash(const std::string& s): n(s.size()), hash(n + 1), pow(n + 1, 1) {
        for (int i = 0; i < n; i++) {
            pow[i + 1] = pow[i] * base;
            hash[i + 1] = hash[i] * base + s[i];
        }
    }
    template<class T>
    RollingHash(const std::vector<T> &v): n(v.size()), hash(n + 1), pow(n + 1, 1) {
        for (int i = 0; i < n; i++){
            pow[i + 1] = pow[i] * base;
            hash[i + 1] = hash[i] * base + v[i];
        }
    }
    mint61 get(int l, int r) const {
        return hash[r] - hash[l] * pow[r - l];
    }
};
}