#include "AStarPlanner.hpp"
#include "Heuristics.hpp"
AStarPlanner::AStarPlanner(const cv::Mat& map) : map_(map) {}

std::vector<std::pair<int, int>> AStarPlanner::plan(const std::pair<int, int>& start, const std::pair<int, int>& goal) {
    //custom comparator for priority queue to be min queue
    auto cmp = [](const AStarNode& a, const AStarNode& b) {
        return a.priority > b.priority; // lower priority first
    };
    std::priority_queue<AStarNode, std::vector<AStarNode>, decltype(cmp)> node_min_queue(cmp);

    came_from_.clear();
    cost_so_far_.clear();

    node_min_queue.push({start.first, start.second, 0.0, 0.0});
    cost_so_far_[start] = 0.0;

    while (!node_min_queue.empty()) {
        // Get the node with the lowest priority (cost_so_far + heuristic), and remove it from the queue
        AStarNode current = node_min_queue.top(); node_min_queue.pop();
        std::pair<int, int> pos = {current.x, current.y};

        // Stop and reconstruct path backwards if goal is reached
        if (pos == goal) {
            std::vector<std::pair<int, int>> path;
            reconstruct_path(path, goal);
            return path;
        }

        for (const auto& neighbor : get_neighbors(pos, map_)) {
            // Move cost is 1 or sqrt (2) depending on the movement direction
            double move_cost = (neighbor.first != pos.first && neighbor.second != pos.second)
                   ? std::sqrt(2.0) : 1.0;
            double cost = cost_so_far_[pos] + move_cost;
            // If the next node has not been visited or the new cost is lower
            if (!cost_so_far_.count(neighbor) || cost < cost_so_far_[neighbor]) {
                // Update cost and priority
                cost_so_far_[neighbor] = cost;
                double priority = cost + octile_distance(neighbor, goal);
                // Push the neighbor into the priority queue
                node_min_queue.push({neighbor.first, neighbor.second, cost, priority});
                came_from_[neighbor] = pos; // Update the parent of the neighbor node

            }
        }
    }

    std::cout << "No path found from start to goal." << std::endl;
    return {}; // Return empty path if no path found
    
}

void AStarPlanner::reconstruct_path(std::vector<std::pair<int, int>>& path, const std::pair<int,int>& goal) {
    std::pair<int,int> current = goal;
    while (came_from_.count(current)) {
        path.push_back(current);
        current = came_from_[current];
    }
    std::reverse(path.begin(), path.end()); // Reverse the path to get it from start to goal
}

