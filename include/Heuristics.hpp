//A* Heuristic functions
#pragma once
#include <utility>

double manhattan_distance(std::pair<int, int> a, std::pair<int, int> b);
double octile_distance(std::pair<int, int> a, std::pair<int, int> b);
