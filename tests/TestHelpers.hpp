#pragma once
#include <opencv2/opencv.hpp>
#include <vector>

// Build a CV_8UC1 binary image from 0/255 rows
inline cv::Mat makeBinary(const std::vector<std::vector<int>>& rows) {
    int R = (int)rows.size();
    int C = (int)rows[0].size();
    cv::Mat m(R, C, CV_8UC1);
    for (int y = 0; y < R; ++y) {
        for (int x = 0; x < C; ++x) {
            m.at<uchar>(y, x) = static_cast<uchar>(rows[y][x]);
        }
    }
    return m;
}