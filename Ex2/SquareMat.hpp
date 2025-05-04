/*
author: Meir Yust
mail: meyu251@gmail.com
*/

#pragma once

#include <iostream>

namespace ex2 {

    class SquareMat {
    private:
        int size = 0;
        double** data;

    public:
        SquareMat(int size);
        SquareMat(const SquareMat& other);
        ~SquareMat();

        SquareMat& operator=(const SquareMat& other);

        SquareMat operator+(const SquareMat& other) const;  // Mat1 + Mat2

        SquareMat operator-(const SquareMat& other) const;  // Mat1 - Mat2

        SquareMat operator-();     // Unary minus operator (-Mat)

        double* operator[](int index);

        const double* operator[](int index) const;

        SquareMat operator*(const SquareMat& other) const;  // Mat1 * Mat2

        SquareMat operator*(double scalar) const;   // Mat * scalar
        
        friend SquareMat operator*(double scalar, const SquareMat& mat);    // Friend function that allows 'scalar * Mat'

        SquareMat operator%(const SquareMat& other) const;

        SquareMat operator%(int mod) const;

        SquareMat operator/(double divisor) const;

        SquareMat operator^(int exponent) const;

        SquareMat& operator++();    // Pre-increment operator (++Mat)

        SquareMat operator++(int);  // Post-increment operator (Mat++)

        SquareMat& operator--();    // Pre-decrement operator (--Mat)

        SquareMat operator--(int);  // Post-decrement operator (Mat--)

        SquareMat operator~() const; // Transpose operator (~Mat)

        bool operator==(const SquareMat& other) const;

        bool operator!=(const SquareMat& other) const;

        bool operator<(const SquareMat& other) const;

        bool operator>(const SquareMat& other) const;

        bool operator<=(const SquareMat& other) const;
        
        bool operator>=(const SquareMat& other) const;

        double operator!() const;   // Determinant operator (!Mat)

        SquareMat& operator+=(const SquareMat& other);   // Mat1 += Mat2

        SquareMat& operator-=(const SquareMat& other);   // Mat1 -= Mat2

        SquareMat& operator*=(const SquareMat& other);   // Mat1 *= Mat2

        SquareMat& operator*=(double scalar);            // Mat1 *= scalar

        SquareMat& operator%=(const SquareMat& other);   // Mat1 %= Mat2

        SquareMat& operator%=(int mod);                  // Mat1 %= mod

        SquareMat& operator/=(double divisor);           // Mat1 /= divisor

        int get_size() const{return size;}
        void print() const;
        double sum_elements() const;    // Sum of all elements in the matrix

    }; // class SquareMat

    std::ostream& operator<<(std::ostream& os, const SquareMat& mat);

} // namespace ex2