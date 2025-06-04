#include "../include/gauss.hpp"
#include <fstream>
#include <sstream>
#include <random>

void readSystemFromCSV(const std::string& filename, MatrixXd& A, VectorXd& b) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }

    std::vector<std::vector<double>> data;
    std::string line;
    
    while (std::getline(file, line)) {
        std::vector<double> row;
        std::stringstream ss(line);
        std::string cell;
        
        while (std::getline(ss, cell, ',')) {
            row.push_back(std::stod(cell));
        }
        data.push_back(row);
    }

    int rows = data.size();
    if (rows == 0) throw std::runtime_error("Empty CSV file");
    
    int cols = data[0].size();
    if (cols < 2) throw std::runtime_error("Invalid CSV format");

    A = MatrixXd(rows, cols - 1);
    b = VectorXd(rows);

    for (int i = 0; i < rows; ++i) {
        if (data[i].size() != cols) {
            throw std::runtime_error("Inconsistent row lengths in CSV");
        }
        for (int j = 0; j < cols - 1; ++j) {
            A(i, j) = data[i][j];
        }
        b(i) = data[i][cols - 1];
    }
}

VectorXd solveGaussian(const MatrixXd& A, const VectorXd& b) {
    if (A.determinant() == 0) {
        throw std::runtime_error("Matrix is singular - no unique solution");
    }
    return A.partialPivLu().solve(b);
}

void writeSolutionToCSV(const std::string& filename, const VectorXd& x) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not create file: " + filename);
    }
    file << x.transpose() << "\n";
}

void generateRandomSystem(int size, MatrixXd& A, VectorXd& b, int seed) {
    std::mt19937 gen(seed);
    std::uniform_real_distribution<double> dist(-10.0, 10.0);
    
    A = MatrixXd::Zero(size, size);
    b = VectorXd::Zero(size);
    
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            A(i,j) = dist(gen);
        }
        b(i) = dist(gen);
    }
}

void generateLargeSystem(int size, MatrixXd& A, VectorXd& b, double sparsity = 0.9) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> val_dist(-10.0, 10.0);
    std::bernoulli_distribution sparse_dist(sparsity);

    A = MatrixXd::Zero(size, size);
    b = VectorXd::Zero(size);

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (!sparse_dist(gen)) {
                A(i,j) = val_dist(gen);
            }
        }
        b(i) = val_dist(gen);
    }
    
    // Ensure diagonal dominance for solvability
    for (int i = 0; i < size; ++i) {
        A(i,i) = A.row(i).cwiseAbs().sum() + 1.0;
    }
}

bool testSolution(const MatrixXd& A, const VectorXd& b, const VectorXd& x, double tolerance) {
    return (A * x - b).norm() < tolerance;
}