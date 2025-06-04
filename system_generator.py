import numpy as np
import sys

def generate_system(size, filename):
    A = np.random.uniform(-10, 10, (size, size))
    b = np.random.uniform(-10, 10, size)
    
    with open(filename, 'w') as f:
        for i in range(size):
            row = ','.join(map(str, A[i])) + f',{b[i]}'
            f.write(row + '\n')

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: python system_generator.py <size> <output.csv>")
        sys.exit(1)
    
    size = int(sys.argv[1])
    output_file = sys.argv[2]
    generate_system(size, output_file)