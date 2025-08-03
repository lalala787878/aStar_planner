// Define node structure for A* algorithm
#pragma once

struct AStarNode {
    int x; // X coordinate of node (pixel)
    int y; // Y coordinate of node (pixel)
    double cost;
    double priority;
};