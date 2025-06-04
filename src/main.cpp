#include "../include/gauss.hpp"
#include <iostream>

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input_csv> <output_csv>\n";
        return 1;
    }

    try {
        MatrixXd A;
        VectorXd b;
        
        readSystemFromCSV(argv[1], A, b);
        VectorXd x = solveGaussian(A, b);
        writeSolutionToCSV(argv[2], x);
        
        std::cout << "Solution written to " << argv[2] << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}