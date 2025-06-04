## Author  
Mobina Ahmadimasoud, group 24.B83-mm  
## Contacts  
st067173@student.spbu.ru

# Gaussian Elimination Solver

A C++ implementation of Gaussian Elimination for solving linear systems, featuring:

- CSV file I/O for matrices
- Eigen library for optimized computations
- Unit tests with Google Test
- CI/CD via GitHub Actions

## Usage

# Build the project
./scripts/build.sh

# Run tests
./scripts/test.sh

# Solve a system
./build/solver input.csv output.csv

# Generate random systems
python system_generator.py 100 large_system.csv

# File Format
Input CSV should have each row as coefficients followed by the right-hand side value:
a11, a12,..., a1n, b1
a21, a22,..., a2n, b2
...
am1, am2,..., amn, bm
Output is a single-column CSV with the solution vector.