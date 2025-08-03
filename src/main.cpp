#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include "AStarPlanner.hpp"
#include "MapUtils.hpp"      
#include <cstdlib>


struct App {
    cv::Mat raw_gray;     // original binary map
    cv::Mat inflated;     // inflated binary map 
    cv::Mat display;      // color display for drawing
    int inflation_radius_px; 
    bool start_set = false;
    bool goal_set = false;
    std::pair<int,int> start; // (x,y)
    std::pair<int,int> goal;  // (x,y)
};

// Draw helper
static void redraw(App& app, const std::vector<std::pair<int,int>>* path = nullptr) {
    // Show the (non-inflated) original 
    cv::cvtColor(app.raw_gray, app.display, cv::COLOR_GRAY2BGR);
    /* Draw the edges of infated obstacles
    {
    cv::Mat edges;
    cv::Canny(app.inflated == 0, edges, 50, 150);
    app.display.setTo(cv::Scalar(50, 50, 50), edges); // darken obstacle edges
    }
    */
    if (app.start_set)
        cv::circle(app.display, {app.start.first, app.start.second}, 3, {0,255,0}, -1);
    if (app.goal_set)
        cv::circle(app.display, {app.goal.first, app.goal.second}, 3, {255,0,0}, -1); 

    if (path) {
        for (const auto& p : *path) {
            // path is (x,y) — OpenCV uses opposite coordinate system
            app.display.at<cv::Vec3b>(p.second, p.first) = {0, 0, 255}; 
        }
    }

    // UI hints
    int border = 30;
    cv::copyMakeBorder(app.display, app.display, 0, border, 0, 0, cv::BORDER_CONSTANT, cv::Scalar(20,20,20));
    cv::putText(app.display, "Left-click to set start & goal | 'r' reset | 'q' quit",
            {3, app.display.rows - 10}, cv::FONT_HERSHEY_SIMPLEX, 0.45, {255, 255, 255}, 1, cv::LINE_AA);

    cv::imshow("A* Planner", app.display);
}

static void mouse_cb(int event, int x, int y, int /*flags*/, void* userdata) {
    auto* app = static_cast<App*>(userdata);
    if (event != cv::EVENT_LBUTTONDOWN) return;

    // Validate against inflated map, warn if obstacle
    if (!is_valid(x, y, app->inflated)) {
        std::cerr << "Clicked on obstacle or out-of-bounds at (" << x << "," << y << ")\n";
        return;
    }

    if (!app->start_set) {
        app->start = {x, y};
        app->start_set = true;
        redraw(*app, nullptr);
        return;
    }

    if (!app->goal_set) {
        app->goal = {x, y};
        app->goal_set = true;

        // Run A* planning
        AStarPlanner planner(app->inflated); // plan on inflated map
        auto path = planner.plan(app->start, app->goal);

        if (path.empty()) {
            std::cout << "No path found.\n";
            redraw(*app, nullptr);
        } else {
            std::cout << "Path length (pixels): " << path.size() << "\n";
            redraw(*app, &path);
        }
        return;
    }

    app->goal = {x, y};
    // Re-run planning immediately if goal is set again
    AStarPlanner planner(app->inflated);
    auto path = planner.plan(app->start, app->goal);
    if (path.empty()) {
        std::cout << "No path found.\n";
        redraw(*app, nullptr);
    } else {
        std::cout << "Path length (pixels): " << path.size() << "\n";
        redraw(*app, &path);
    }
}

int main(int argc, char** argv) {
    App app;

    // Load map
    app.raw_gray = cv::imread("../map/binary_map.png", cv::IMREAD_GRAYSCALE);
    if (app.raw_gray.empty()) {
        std::cerr << "Failed to load map image.\n";
        return -1;
    }

    app.inflation_radius_px = (argc >= 2) ? std::atoi(argv[1]) : 1; // default radius=1
    if (app.inflation_radius_px <= 0) {
        std::cerr << "Invalid inflation radius: " << app.inflation_radius_px << "\n";
        return -1;
    }
    cv::threshold(app.raw_gray, app.raw_gray, 127, 255, cv::THRESH_BINARY);

    // Inflate obstacles by radius (in pixels)
    app.inflated = inflate_obstacles(app.raw_gray, app.inflation_radius_px);

    cv::namedWindow("A* Planner", cv::WINDOW_AUTOSIZE);
    cv::setMouseCallback("A* Planner", mouse_cb, &app);
    redraw(app, nullptr);
    std::cout << "Click to set start/goal points.\n";
    std::cout << "Press 'r' to reset, 'q' to quit.\n";
    std::cout << "Ran with robot radius set to: " << app.inflation_radius_px << " px\n";
    // Simple loop for UI keys
    for (;;) {
        int key = cv::waitKey(30);
        if (key == 'q' || key == 27) break; // q or ESC

        if (key == 'r') {
            app.start_set = app.goal_set = false;
            redraw(app, nullptr);
        }
    }

    return 0;
}