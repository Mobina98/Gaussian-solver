#include <gtest/gtest.h>
#include "../src/gauss.hpp"
#include <chrono>

class GaussianTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Small system
        A_small.resize(3, 3);
        A_small << 2, -1, 0,
                  -1, 2, -1,
                  0, -1, 2;
        b_small.resize(3);
        b_small << 1, 0, 1;
        
        // Medium system (100x100)
        generateLargeSystem(100, A_medium, b_medium);
    }
    
    MatrixXd A_small, A_medium;
    VectorXd b_small, b_medium;
};

TEST_F(GaussianTest, SolvesSmallSystem) {
    VectorXd x = solveGaussian(A_small, b_small);
    EXPECT_TRUE(testSolution(A_small, b_small, x));
}

TEST_F(GaussianTest, SolvesMediumSystem) {
    auto start = std::chrono::high_resolution_clock::now();
    
    VectorXd x = solveGaussian(A_medium, b_medium);
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    EXPECT_TRUE(testSolution(A_medium, b_medium, x));
    std::cout << "100x100 system solved in " << duration.count() << " ms\n";
}

TEST_F(GaussianTest, BenchmarksLargeSystem) {
    MatrixXd A_large;
    VectorXd b_large;
    generateLargeSystem(1000, A_large, b_large);
    
    auto start = std::chrono::high_resolution_clock::now();
    VectorXd x = solveGaussian(A_large, b_large);
    auto end = std::chrono::high_resolution_clock::now();
    
    EXPECT_TRUE(testSolution(A_large, b_large, x, 1e-4)); // Relaxed tolerance
    
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "1000x1000 system solved in " << duration.count() << " ms\n";
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}