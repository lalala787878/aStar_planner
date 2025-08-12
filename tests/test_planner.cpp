#include <gtest/gtest.h>
#include "AStarPlanner.hpp"
#include "TestHelpers.hpp"

// Straight corridor
TEST(Planner, SimpleStraightPath) {
    auto m = makeBinary({
        {255,255,255,255,255}
    });
    AStarPlanner planner(m);
    auto path = planner.plan({0,0},{4,0});
    ASSERT_FALSE(path.empty());
    EXPECT_EQ(path.front(), std::make_pair(1,0));
    EXPECT_EQ(path.back(),  std::make_pair(4,0));
    EXPECT_EQ(path.size(), 4u); // 4 nodes
}

// No path
TEST(Planner, NoPathDueToWall) {
    auto m = makeBinary({
        {255,  0,255},
        {255,  0,255},
        {255,  0,255},
    });
    AStarPlanner planner(m);
    auto path = planner.plan({0,1},{2,1});
    EXPECT_TRUE(path.empty());
}