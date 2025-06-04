#include <gtest/gtest.h>
#include "../include/gauss.hpp"
#include "../src/gauss.hpp"

TEST(GaussianSolverTest, SolvesSimpleSystem) {
    MatrixXd A(2, 2);
    A << 1, 1, 
         0, 1;
    VectorXd b(2);
    b << 3, 2;
    
    VectorXd x = solveGaussian(A, b);
    EXPECT_TRUE(testSolution(A, b, x));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(GaussianSolverTest, HandlesSingularMatrix) {
    MatrixXd A = MatrixXd::Zero(3, 3);
    VectorXd b = VectorXd::Random(3);
    EXPECT_THROW(solveGaussian(A, b), std::runtime_error);
}

TEST(GaussianSolverTest, CSVReadWrite) {
    MatrixXd A(2, 2);
    A << 1, 2, 3, 4;
    VectorXd b(2);
    b << 5, 6;
    
    writeSolutionToCSV("test_output.csv", b);
    
    MatrixXd A_read;
    VectorXd b_read;
    readSystemFromCSV("test_data/system1.csv", A_read, b_read);
    
    EXPECT_EQ(A_read.rows(), 2);
    EXPECT_EQ(b_read.size(), 2);
}