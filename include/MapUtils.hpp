// Map utility functions

#pragma once
#include <utility>
#include <opencv2/opencv.hpp>
#include <vector>
#include <string>
#include <utility>


bool is_valid(int x, int y, const cv::Mat& map);
std::vector<std::pair<int, int>> get_neighbors(std::pair<int,int> node, const cv::Mat& map);
cv::Mat inflate_obstacles(const cv::Mat& map, int radius);