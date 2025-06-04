cmake_minimum_required(VERSION 3.12)
project(GaussianSolver)

set(CMAKE_CXX_STANDARD 17)

# Find dependencies
find_package(Eigen3 REQUIRED)
find_package(GTest REQUIRED)

# Main executable
add_executable(solver src/main.cpp src/gauss.cpp)
target_link_libraries(solver Eigen3::Eigen)

# Tests
add_executable(tests test/unit_tests.cpp src/gauss.cpp)
target_link_libraries(tests GTest::GTest Eigen3::Eigen)
add_test(NAME UnitTests COMMAND tests)

# Installation
install(TARGETS solver DESTINATION bin)