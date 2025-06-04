#pragma once
#include <Eigen/Dense>
#include <string>
#include <stdexcept>

using namespace Eigen;

void readSystemFromCSV(const std::string& filename, MatrixXd& A, VectorXd& b);
VectorXd solveGaussian(const MatrixXd& A, const VectorXd& b);
void writeSolutionToCSV(const std::string& filename, const VectorXd& x);
void generateRandomSystem(int size, MatrixXd& A, VectorXd& b, int seed=42);
bool testSolution(const MatrixXd& A, const VectorXd& b, const VectorXd& x, double tolerance=1e-6);