# SquareMat - Square Matrix Operations Library

## Author
- **Name:** Meir Yust
- **Email:** meyu251@gmail.com

## Overview
This library provides a comprehensive C++ implementation of a square matrix class (`SquareMat`) with an extensive set of operator overloads for mathematical operations. It enables intuitive manipulation of square matrices using standard mathematical operators.

## Features
- Square matrix representation with dynamic memory allocation
- Comprehensive set of mathematical operators:
  - Basic arithmetic: `+`, `-`, `*`, `/`
  - Matrix-specific operations: matrix multiplication, transpose, determinant
  - Element-wise operations: element-wise multiplication (`%`)
  - Modulo operations (`%`)
  - Matrix powers (`^`)
  - Increment/decrement: `++`, `--`
  - Comparison operators: `==`, `!=`, `<`, `>`, `<=`, `>=`
  - Compound assignment: `+=`, `-=`, `*=`, `%=`, `/=`
- Memory-safe implementation with proper copy construction and assignment
- Extensive test suite using doctest framework

## Files
- **SquareMat.hpp** - Class declaration with operator overloads
- **SquareMat.cpp** - Implementation of the SquareMat class
- **main.cpp** - Example usage demonstrating various operations
- **test.cpp** - Comprehensive test suite using doctest framework
- **Makefile** - Build configuration

## Build Instructions
The project includes a Makefile for easy building:

```bash
# Build both main executable and tests
make

# Build and run main program
make Main

# Build and run tests
make test

# Run with Valgrind memory checker
make valgrind

# Clean build files
make clean
```

## Usage Example
```cpp
#include "SquareMat.hpp"
#include <iostream>

using namespace ex2;
using namespace std;

int main() {
    // Create a 3x3 matrix
    SquareMat mat1(3);
    
    // Fill with values (1-9)
    int num = 1;
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            mat1[i][j] = num++;
        }
    }
    
    // Display the matrix
    cout << "Matrix:\n" << mat1 << endl;
    
    // Transpose the matrix
    SquareMat transposed = ~mat1;
    cout << "Transposed:\n" << transposed << endl;
    
    // Calculate determinant
    cout << "Determinant: " << !mat1 << endl;
    
    // Matrix multiplication
    SquareMat squared = mat1 * mat1;
    cout << "Squared:\n" << squared << endl;
    
    return 0;
}
```

## Operator Guide
- `+`, `-`: Matrix addition and subtraction
- Unary `-`: Negation of all elements
- `*`: Matrix multiplication or scalar multiplication
- `%` (with matrix): Element-wise multiplication
- `%` (with integer): Modulo operation on each element
- `/`: Division by scalar
- `^`: Matrix power (A^n)
- `++`, `--`: Increment/decrement all elements
- `~`: Matrix transpose
- `!`: Calculate determinant
- `==`, `!=`, `<`, `>`, `<=`, `>=`: Compare matrices (based on sum of elements)
- `+=`, `-=`, `*=`, `%=`, `/=`: Compound assignment operators

## Error Handling
The implementation includes robust error handling for:
- Invalid matrix sizes
- Out-of-bounds access
- Division by zero
- Incompatible matrices for operations
- Negative exponents in power operation

## Testing
The project includes an extensive test suite using the doctest framework, covering all operators and edge cases.
