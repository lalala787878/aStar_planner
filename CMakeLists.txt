cmake_minimum_required(VERSION 3.10)
project(AstarPathPlanner)
set(CMAKE_CXX_STANDARD 17)

# OpenCV
find_package(OpenCV REQUIRED)

# ---- Library with core code (used by app + tests)
add_library(astar_core
    src/Heuristics.cpp
    src/MapUtils.cpp
    src/AStarPlanner.cpp
)
target_include_directories(astar_core PUBLIC include)
target_link_libraries(astar_core PUBLIC ${OpenCV_LIBS})

# ---- App 
add_executable(astar src/main.cpp)
target_link_libraries(astar PRIVATE astar_core)

# ---- Testing setup 
include(CTest)
enable_testing()
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# ---- Tests target
file(GLOB TEST_SOURCES tests/*.cpp)
add_executable(astar_tests ${TEST_SOURCES})
target_link_libraries(astar_tests PRIVATE astar_core gtest_main)
add_test(NAME astar_tests COMMAND astar_tests)