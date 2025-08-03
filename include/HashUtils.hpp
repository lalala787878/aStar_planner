// Util function for hasing pair<int, int>

#pragma once
#include <utility>
#include <functional>
#include <cstddef>

struct pair_hash {
    size_t operator()(const std::pair<int, int>& p) const {
        return std::hash<int>()(p.first) ^ (std::hash<int>()(p.second) << 1);
    }
};