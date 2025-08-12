#include <gtest/gtest.h>
#include "MapUtils.hpp"
#include "TestHelpers.hpp"
#include <set>

TEST(MapUtils, IsValid) {
    auto m = makeBinary({
        {255,255,  0},
        {255,  0,255}
    });
    EXPECT_TRUE(is_valid(0,0,m));
    EXPECT_TRUE(is_valid(1,0,m));
    EXPECT_FALSE(is_valid(2,0,m)); // obstacle
    EXPECT_FALSE(is_valid(1,1,m)); // obstacle
    EXPECT_FALSE(is_valid(-1,0,m)); // OOB
    EXPECT_FALSE(is_valid(0,2,m));  // OOB
}

TEST(MapUtils, Neighbors8Connected) {
    auto m = makeBinary({
        {255,255,255},
        {255,255,255},
        {255,255,255}
    });
    auto nbrs = get_neighbors({1,1}, m);
    std::set<std::pair<int,int>> s(nbrs.begin(), nbrs.end());
    EXPECT_EQ(s.size(), 8u);
    EXPECT_TRUE(s.count({0,0}));
    EXPECT_TRUE(s.count({0,1}));
    EXPECT_TRUE(s.count({0,2}));
    EXPECT_TRUE(s.count({1,0}));
    EXPECT_TRUE(s.count({1,2}));
    EXPECT_TRUE(s.count({2,0}));
    EXPECT_TRUE(s.count({2,1}));
    EXPECT_TRUE(s.count({2,2}));
}

TEST(MapUtils, DiagonalCornerCutBlocked) {
    auto m = makeBinary({
        {255,  0},
        {  0,255}
    });
    auto nbrs = get_neighbors({0,0}, m);
    std::set<std::pair<int,int>> s(nbrs.begin(), nbrs.end());
    // (1,1) should be blocked because both side-adjacent cells are obstacles
    EXPECT_FALSE(s.count({1,1}));
}

TEST(MapUtils, DiagonalCornerCutBlocked2) {
    auto m = makeBinary({
        {255,  0},
        {255,255}
    });
    auto nbrs = get_neighbors({0,0}, m);
    std::set<std::pair<int,int>> s(nbrs.begin(), nbrs.end());
    // (1,1) should be blocked because one side-adjacent cell is an obstacle
    EXPECT_FALSE(s.count({1,1}));
}

TEST(MapUtils, InflateObstacles) {
    auto m = makeBinary({
        {255,255,255,255,255,255,255,255,255,255},
        {255,255,255,255,255,255,255,255,255,255},
        {255,255,255,255,255,255,255,255,255,255},
        {255,255,255,  0,  0,  0,255,255,255,255},
        {255,255,255,255,255,255,255,255,255,255},
        {255,255,255,255,255,255,255,255,255,255},
        {255,255,255,255,255,255,255,255,255,255},
    });
    auto inflated = inflate_obstacles(m, /*radius_px=*/1);
    // Middle 0s will be inflated, and border will be created
    EXPECT_EQ(inflated.at<uchar>(3,2), 0);
    EXPECT_EQ(inflated.at<uchar>(2,2), 255);
    EXPECT_EQ(inflated.at<uchar>(1,1), 0);
}