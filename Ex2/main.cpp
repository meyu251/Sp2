/*
author: Meir Yust
mail: meyu251@gmail.com
*/

#include <iostream>
#include "SquareMat.hpp"

using namespace ex2;
using namespace std;

int main(){

    // Create a 3x3 matrix and fill it with values
    SquareMat mat1(3);
    int num = 1;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            mat1[i][j] = num++;
        }
    }

    cout << "mat1 = \n" << mat1 << endl;
    
    // Create another 3x3 matrix
    SquareMat mat2(3);
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            mat2[i][j] = --num;
        }
    }
    
    cout << "mat2 = \n" << mat2 << endl;
    
    // Addition
    cout << "Addition: mat1 + mat2 = \n";
    SquareMat matSum = mat1 + mat2;
    cout << matSum << endl;
    
    // Subtraction
    cout << "Subtraction: mat1 - mat2 = \n";
    SquareMat matDiff = mat1 - mat2;
    cout << matDiff << endl;
    
    // Matrix multiplication
    cout << "Matrix multiplication: mat1 * mat2 = \n";
    SquareMat matProd = mat1 * mat2;
    cout << matProd << endl;
    
    // Scalar multiplication
    cout << "Scalar multiplication: mat1 * 2 = \n";
    SquareMat matScaled = mat1 * 2;
    cout << matScaled << endl;
    
    // Element-wise multiplication
    cout << "Special multiplication: mat1 % mat2 = \n";
    SquareMat matElem = mat1 % mat2;
    cout << matElem << endl;
    
    // Transpose
    cout << "Transpose of mat1: ~mat1 = \n";
    SquareMat matTrans = ~mat1;
    cout << matTrans << endl;
    
    // Determinant
    cout << "Determinant of mat1: !mat1 = " << !mat1 << endl;
    
    // Create a 2x2 matrix for power example
    cout << "\nCreating a 2x2 matrix (mat3):\n";
    SquareMat mat3(2);
    mat3[0][0] = 1;  mat3[0][1] = 2;
    mat3[1][0] = 3;  mat3[1][1] = 4;
    
    cout << "mat3 = \n" << mat3 << endl;
    
    // Matrix power
    cout << "Matrix power: mat3^2 = \n";
    SquareMat matPow = mat3 ^ 2;
    cout << matPow << endl;
    
    return 0;
}