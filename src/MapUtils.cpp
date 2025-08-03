#include "MapUtils.hpp"

bool is_valid(int x, int y, const cv::Mat& map) {
    return x >= 0 && y >= 0 && x < map.cols && y < map.rows && map.at<uchar>(y, x) == 255;
}

std::vector<std::pair<int, int>> get_neighbors(std::pair<int,int> node, const cv::Mat& map) {
    std::vector<std::pair<int, int>> deltas = {
        {-1,0},{1,0},{0,-1},{0,1}
       // {-1,-1},{-1,1},{1,-1},{1,1}
    };

    std::vector<std::pair<int,int>> neighbors;
    for (auto [dx, dy] : deltas) {
        int nx = node.first + dx;
        int ny = node.second + dy;

        if (is_valid(nx, ny, map)) {
            neighbors.push_back({nx, ny});
        }
        else {std::cout << "Invalid neighbor: (" << nx << ", " << ny << ")\n";} // Debugging output
    }
    return neighbors;
}