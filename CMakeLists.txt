cmake_minimum_required(VERSION 3.10)
project(AstarPathPlanner)

set(CMAKE_CXX_STANDARD 17)

# OpenCV
find_package(OpenCV REQUIRED)

# Include directories
include_directories(include)

#source files
add_executable(astar
    src/Heuristics.cpp
    src/MapUtils.cpp
    src/main.cpp
    src/AStarPlanner.cpp
)

target_link_libraries(astar
    ${OpenCV_LIBS}
)