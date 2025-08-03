#include "Heuristics.hpp"
#include <cmath>

// Heuristic functions for A* algorithm for planning without diagonal movement
double manhattan_distance(std::pair<int, int> a, std::pair<int, int> b) {
    return abs(a.first - b.first) + abs(a.second - b.second);
}

// Heuristic functions for A* algorithm for planning with diagonal movement if implmented
/*
double euclidean_distance(std::pair<int, int> a, std::pair<int, int> b) {
    return hypot(a.first - b.first, a.second - b.second);
}
*/