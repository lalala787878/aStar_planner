# A* Path Planning in C++

![Ubuntu Build](https://github.com/lalala787878/aStar_planner/actions/workflows/ubuntu_build.yml/badge.svg)

A C++ implementation of the **A\*** pathfinding algorithm using OpenCV for image-based map processing.  
The planner supports configurable robot radius (map inflation), and interactive start/goal selection with the mouse.


---

## 📜 Overview

This project implements an A* path planner that operates on a binary map image:
- **White pixels (255)** = free space  
- **Black pixels (0)** = obstacles  

The program reads a binary map, optionally inflates obstacles based on the robot radius, and computes the optimal path between a start and goal position set by user via mouse on the pop up UI.

---
## Requirements

- **Ubuntu 22.04 / 24.04** 
- **CMake ≥ 3.10**
- **g++ ≥ 9** (or any compiler supporting C++17)
- **OpenCV ≥ 4.5** (core + imgproc modules)

## Building and Running

```bash
git clone https://github.com/lalala787878/aStar_planner.git

cd aStar_planner

# Create build directory
mkdir build && cd build

# Configure with CMake
cmake ..

# Build
make

# Run (with defult robot radius which is 1 pixel.)
./astar

# Run (with robot radius set to 2 pixels.)
./astar 2
```

MIT License – feel free to use and modify.
