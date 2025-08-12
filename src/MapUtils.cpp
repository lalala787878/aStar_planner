#include "MapUtils.hpp"

bool is_valid(int x, int y, const cv::Mat& map) {
    return x >= 0 && y >= 0 && x < map.cols && y < map.rows && map.at<uchar>(y, x) == 255;
}

std::vector<std::pair<int, int>> get_neighbors(std::pair<int,int> node, const cv::Mat& map) {
    std::vector<std::pair<int, int>> deltas = {
        {-1,0},{1,0},{0,-1},{0,1},
       {-1,-1},{-1,1},{1,-1},{1,1}
    };

    std::vector<std::pair<int,int>> neighbors;
    for (auto [dx, dy] : deltas) {
        int nx = node.first + dx;
        int ny = node.second + dy;

        // Prevent diagonal wall clipping
        // If moving diagonally
        if (dx != 0 && dy != 0) {
            // Check if either side of the diagonal move is blocked by an obstacle
            // If so, skip this neighbor
            if (!is_valid(node.first + dx, node.second, map) ||
                !is_valid(node.first, node.second + dy, map)) {
                continue;
            }
        }

        if (is_valid(nx, ny, map)) {
            neighbors.push_back({nx, ny});
        }
        // else {std::cout << "Invalid neighbor: (" << nx << ", " << ny << ")\n";} // Debugging output
    }
    return neighbors;
}

cv::Mat inflate_obstacles(const cv::Mat& map, int radius) {
    CV_Assert(map.type() == CV_8UC1);

    cv::Mat inv, dilated, inflated;
    // We are using 0 = obstacle, 255 = free. Invert first to dilate
    cv::bitwise_not(map, inv);

    // Kernel for dilation
    int k = std::max(1, 2 * radius + 1);
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_ELLIPSE, {k, k});

    // Add image border obstacles because robot is not a point
   cv::rectangle(inv, {0, 0}, {inv.cols-1, inv.rows-1}, cv::Scalar(255), 1);
    
    cv::dilate(inv, dilated, kernel);

    // Invert back: 0 = obstacle (inflated), 255 = free
    cv::bitwise_not(dilated, inflated);
    // Double ensure strict binary
    cv::threshold(inflated, inflated, 127, 255, cv::THRESH_BINARY);
    return inflated;
}
