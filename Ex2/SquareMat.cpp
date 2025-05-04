/*
author: Meir Yust
mail: meyu251@gmail.com
*/

#include <iostream>
#include <stdexcept>
#include <cmath>
#include "SquareMat.hpp"

using namespace ex2;
using std::cout;
using std::endl;

// Constructor
// Initializes a square matrix of given size to 0
SquareMat::SquareMat(int size) : size(size){
    if(size <= 0){
        throw std::invalid_argument("Size must be greater than 0");
    }
    
    // Allocate memory for a 2D array
    data = new double*[size];
    for(int i = 0; i < size; i++){
        data[i] = new double[size];
        for(int j = 0; j < size; ++j){
            data[i][j] = 0;
        }
    }
}

// Copy constructor
SquareMat::SquareMat(const SquareMat& other) : size(other.size){
    data = new double*[size];
    for(int i = 0; i < size; i++){
        data[i] = new double[size];
        for(int j = 0; j < size; ++j){
            data[i][j] = other.data[i][j];
        }
    }
}

// Destructor
SquareMat::~SquareMat(){
    // Free the 2D array
    for(int i = 0; i < size; i++){
        delete[] data[i];
    }
    delete[] data;
}

SquareMat& SquareMat::operator=(const SquareMat& other){
    if(this != &other){
        if(size != other.size){     // If the sizes are equal, we can use the existing memory
            // Free the existing memory
            for(int i = 0; i < size; i++){
                delete[] data[i];
            }
            delete[] data;

            // Allocate new memory
            size = other.size;
            data = new double*[size];
            for(int i = 0; i < size; i++){
                data[i] = new double[size];
            }
        }
        
        // Copy the data
        for(int i = 0; i < size; i++){
            for(int j = 0; j < size; ++j){
                data[i][j] = other.data[i][j];
            }
        }
    }
    return *this;
}

SquareMat SquareMat::operator+(const SquareMat& other) const{
    if(size != other.size){
        throw std::invalid_argument("Matrices are not with the same size");
    }

    SquareMat result(size);
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            result.data[i][j] = data[i][j] + other.data[i][j];
        }
    }
    return result;
}

SquareMat SquareMat::operator-(const SquareMat& other) const{
    if(size != other.size){
        throw std::invalid_argument("Matrices are not with the same size");
    }

    SquareMat result(size);
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            result.data[i][j] = data[i][j] - other.data[i][j];
        }
    }
    return result;
}

/*
Turns the matrix into its negative.
*/
SquareMat SquareMat::operator-(){
    return *this * -1;
}

double* SquareMat::operator[](int index){
    if(index < 0 || index >= size){
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

const double* SquareMat::operator[](int index) const{
    if(index < 0 || index >= size){
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

/*
We can use the operator* only on SquareMat objects of the same size,
becouse all the matrices are square matrices.
The multiplication is done by the standard matrix multiplication algorithm.
*/
SquareMat SquareMat::operator*(const SquareMat& other) const{
    if(size != other.size){
        throw std::invalid_argument("Matrices are not with the same size");
    }

    SquareMat result(size);
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            result.data[i][j] = 0;
            for(int k = 0; k < size; k++){
                result.data[i][j] += data[i][k] * other.data[k][j];
            }
        }
    }
    return result;
}

SquareMat SquareMat::operator*(double scalar) const{
    SquareMat result(size);
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            result.data[i][j] = data[i][j] * scalar;
        }
    }
    return result;
}

/*
This is a Friend Function
It allows us to multiply a scalar by a matrix by 'scalar * Mat'
*/
SquareMat ex2::operator*(double scalar, const SquareMat& mat){
    return mat * scalar; // Reuse the existing operator*
}

/*
This operator is used to multiply every element of the matrix by the corresponding element of another matrix.
*/
SquareMat SquareMat::operator%(const SquareMat& other) const{
    if(size != other.size){
        throw std::invalid_argument("Matrices are not with the same size");
    }

    SquareMat result(size);
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            result.data[i][j] = data[i][j] * other.data[i][j];
        }
    }
    return result;
}

/*
This operator is used to calculate the modulo of each element of the matrix by a given integer.
*/
SquareMat SquareMat::operator%(int mod) const{
    SquareMat result(size);
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            result.data[i][j] = fmod(data[i][j], mod);
        }
    }
    return result;
}

SquareMat SquareMat::operator/(double divisor) const{
    if(divisor == 0){
        throw std::invalid_argument("Division by zero is not allowed");
    }

    SquareMat result(size);
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            result.data[i][j] = data[i][j] / divisor;
        }
    }
    return result;
}

SquareMat SquareMat::operator^(int exponent) const{
    if(exponent < 0){
        throw std::invalid_argument("Exponent must be greater than or equal to 0");
    }

    if(exponent == 0){
        // Return identity matrix
        SquareMat result(size);
        for(int i = 0; i < size; i++){
            for(int j = 0; j < size; j++){
                result.data[i][j] = (i == j) ? 1 : 0;
            }
        }
        return result;
    }

    if(exponent == 1){
        SquareMat result(*this);
        return result;
    }

    // Use binary exponentiation for exponent > 1 | O(log n)
    SquareMat result(size);
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            result.data[i][j] = (i == j) ? 1 : 0; // Identity matrix
        }
    }

    SquareMat base(*this);
    while(exponent > 0){
        if(exponent % 2 == 1){
            result = result * base;
        }
        base = base * base;
        exponent /= 2;
    }
    return result;
}

/*
Pre-increment operator (++Mat)
*/
SquareMat& SquareMat::operator++(){
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            data[i][j]++;
        }
    }
    return *this;
}

/*
Post-increment operator (Mat++)
*/
SquareMat SquareMat::operator++(int){
    SquareMat temp(*this);
    ++(*this);
    return temp;
}

/*
Pre-decrement operator (--Mat)
*/
SquareMat& SquareMat::operator--(){
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            data[i][j]--;
        }
    }
    return *this;
}

/*
Post-decrement operator (Mat--)
*/
SquareMat SquareMat::operator--(int){
    SquareMat temp(*this);
    --(*this);
    return temp;
}

/*
Transpose operator (~Mat)
*/
SquareMat SquareMat::operator~() const{
    SquareMat result(size);
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            result.data[j][i] = data[i][j];
        }
    }
    return result;
}

bool SquareMat::operator==(const SquareMat& other) const{    
    return this->sum_elements() == other.sum_elements();
}

bool SquareMat::operator!=(const SquareMat& other) const{
    return !(*this == other);
}

bool SquareMat::operator<(const SquareMat& other) const{
    return this->sum_elements() < other.sum_elements();
}

bool SquareMat::operator>(const SquareMat& other) const{
    return !(*this == other) && !(*this < other);
}

bool SquareMat::operator<=(const SquareMat& other) const{
    return (*this < other) || (*this == other);
}

bool SquareMat::operator>=(const SquareMat& other) const{
    return (*this > other) || (*this == other);
}

/*
This operator is used to calculate the determinant of the matrix.
The determinant is calculated using the Gaussian elimination method.
*/
double SquareMat::operator!() const{
    if(size == 1){
        return data[0][0];
    }
    
    if(size == 2){
        return data[0][0] * data[1][1] - data[0][1] * data[1][0];
    }
    
    // For larger matrices, use Gaussian elimination
    // Create a copy of the matrix to perform elimination on
    SquareMat temp(*this);
    double det = 1.0;
    
    // Gaussian elimination
    for(int i = 0; i < size; i++){
        // Find pivot (maximum element) in the current column
        int maxRow = i;
        double maxVal = std::fabs(temp[i][i]);
        
        for(int j = i + 1; j < size; j++){
            if(std::fabs(temp[j][i]) > maxVal){
                maxRow = j;
                maxVal = std::fabs(temp[j][i]);
            }
        }
        
        // If max value in column is 0, determinant is 0
        if(maxVal < 1e-10){return 0;}
        
        // Swap rows if needed
        if(maxRow != i){
            for(int j = i; j < size; j++){
                std::swap(temp[i][j], temp[maxRow][j]);
            }
            det = -det; // Swap changes sign of determinant
        }
        
        // Store the pivot
        double pivot = temp[i][i];
        det *= pivot;
        
        // Eliminate below the pivot
        for(int j = i + 1; j < size; j++){
            double factor = temp[j][i] / pivot;
            for(int k = i; k < size; k++){
                temp[j][k] -= factor * temp[i][k];
            }
        }
    }
    
    return det;
}

SquareMat& SquareMat::operator+=(const SquareMat& other){
    if(size != other.size){
        throw std::invalid_argument("Matrices are not with the same size");
    }

    *this = *this + other;

    return *this;
}

SquareMat& SquareMat::operator-=(const SquareMat& other){
    if(size != other.size){
        throw std::invalid_argument("Matrices are not with the same size");
    }

    *this = *this - other;

    return *this;
}

SquareMat& SquareMat::operator*=(const SquareMat& other){
    if(size != other.size){
        throw std::invalid_argument("Matrices are not with the same size");
    }

    *this = *this * other;

    return *this;
}

SquareMat& SquareMat::operator*=(double scalar){
    *this = *this * scalar;

    return *this;
}

/*
This operator is used to multiply every element of the matrix by the corresponding element of another matrix.
*/
SquareMat& SquareMat::operator%=(const SquareMat& other){
    if(size != other.size){
        throw std::invalid_argument("Matrices are not with the same size");
    }

    *this = *this % other;

    return *this;
}

SquareMat& SquareMat::operator%=(int mod){
    *this = *this % mod;

    return *this;
}

SquareMat& SquareMat::operator/=(double divisor){
    if(divisor == 0){
        throw std::invalid_argument("Division by zero is not allowed");
    }

    *this = *this / divisor;

    return *this;
}

std::ostream& ex2::operator<<(std::ostream& os, const SquareMat& mat){
    mat.print();    
    return os;
}


void SquareMat::print() const{
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            cout << data[i][j] << " ";
        }
        cout << endl;
    }
}

double SquareMat::sum_elements() const{
    double sum = 0;
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            sum += data[i][j];
        }
    }
    return sum;
}