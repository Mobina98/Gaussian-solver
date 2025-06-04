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
if(BUILD_TESTS)
    find_package(GTest REQUIRED)
    include(GoogleTest)  # For gtest_discover_tests
    
    add_executable(test_executable 
        test/unit_tests.cpp 
        src/gauss.cpp
    )
    target_link_libraries(test_executable 
        GTest::GTest 
        GTest::Main
        Eigen3::Eigen
    )
    
    gtest_discover_tests(test_executable
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    )
endif()

# Installation
install(TARGETS solver DESTINATION bin)