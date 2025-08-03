#include "Heuristics.hpp"
#include <cmath>
#include <algorithm>

// Heuristic functions for A* algorithm for planning without diagonal movement
double manhattan_distance(std::pair<int, int> a, std::pair<int, int> b) {
    return abs(a.first - b.first) + abs(a.second - b.second);
}

//Using octile distance for A* algorithm with diagonal movement
//Basically, asumes orthogonal movements for all possible moves since cost is lower, and diagonal movements for the movement needed with two orthogonal movements
double octile_distance(std::pair<int, int> a, std::pair<int, int> b) {
    int dx = abs(a.first - b.first);
    int dy = abs(a.second - b.second);
    return dx + dy + (sqrt(2) - 2) * std::min(dx, dy);
}