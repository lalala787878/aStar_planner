#pragma once

#include <utility>
#include <vector>
#include <unordered_map>
#include <queue>
#include <opencv2/opencv.hpp>
#include "AStarNode.hpp"
#include "HashUtils.hpp"
#include "MapUtils.hpp"
#include "Heuristics.hpp"

class AStarPlanner {
    public:
        // Constructor
        AStarPlanner(const cv::Mat& map);

        std::vector<std::pair<int, int>> plan(const std::pair<int, int>& start, const std::pair<int, int>& goal);

    private:
        const cv::Mat& map_;
        std::unordered_map<std::pair<int,int>, double, pair_hash> cost_so_far_;
        std::unordered_map<std::pair<int,int>, std::pair<int,int>, pair_hash> came_from_;

        void reconstruct_path(std::vector<std::pair<int, int>>& path, const std::pair<int,int>& goal);
};