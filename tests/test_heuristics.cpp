#include <gtest/gtest.h>
#include "Heuristics.hpp"
#include <cmath>

TEST(Heuristics, OctileMatchesGridCosts) {
    auto h = octile_distance({0,0}, {5,3});
    double expected = std::sqrt(2.0)*3 + (5-3)*1.0;
    EXPECT_NEAR(h, expected, 1e-9);
}
