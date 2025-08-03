#include <iostream>
#include <opencv2/opencv.hpp>
#include "AStarPlanner.hpp"

int main() {
    // Load map image (0 = obstacle, 255 = free space)
    cv::Mat map = cv::imread("map/binary_map.png", cv::IMREAD_GRAYSCALE);
    if (map.empty()) {
        std::cerr << "Failed to load map image.\n";
        return -1;
    }


    // Start and goal positions
    std::pair<int, int> start(10, 10);  // row, col
    std::pair<int, int> goal(150, 200);

    // Run planner
    AStarPlanner planner(map);
    std::vector<std::pair<int, int>> path = planner.plan(start, goal);

    // Draw the planned path 
    if (!path.empty()) {
        cv::Mat color_map;
        cv::cvtColor(map, color_map, cv::COLOR_GRAY2BGR);

        for (const auto& p : path) {
            color_map.at<cv::Vec3b>(p.second, p.first) = {0, 0, 255};
        }

        cv::imshow("A* Path", color_map);
        cv::waitKey(0);
    } else {
        std::cout << "No path found.\n";
    }

    return 0;
}