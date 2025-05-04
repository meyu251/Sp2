/*
author: Meir Yust
mail: meyu251@gmail.com
*/

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include "SquareMat.hpp"

using namespace ex2;
using namespace std;

// Helper function to capture cout output
class CoutRedirect{
public:
    CoutRedirect(std::stringstream& buffer) : old_buf(std::cout.rdbuf(buffer.rdbuf())){}
    ~CoutRedirect() {std::cout.rdbuf(old_buf);}
private:
    std::streambuf* old_buf;
};

// Helper function to check if two doubles are approximately equal
bool approx_equal(double a, double b, double epsilon = 1e-10){
    return std::fabs(a - b) < epsilon;
}

TEST_CASE("Constructor and basic operations"){
    SUBCASE("Basic constructor"){
        SquareMat mat(3);
        // Check that all elements are initialized to 0
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                CHECK(mat[i][j] == 0);
            }
        }
    }

    SUBCASE("Invalid size"){
        CHECK_THROWS_AS(SquareMat(0), std::invalid_argument);
        CHECK_THROWS_AS(SquareMat(-3), std::invalid_argument);
    }

    SUBCASE("Copy constructor"){
        SquareMat mat1(2);
        mat1[0][0] = 1;
        mat1[0][1] = 2;
        mat1[1][0] = 3;
        mat1[1][1] = 4;

        SquareMat mat2(mat1);
        // Check that all elements are copied correctly
        for(int i = 0; i < 2; i++){
            for(int j = 0; j < 2; j++){
                CHECK(mat2[i][j] == mat1[i][j]);
            }
        }
        
        // Check that changing one doesn't change the other
        mat1[0][0] = 10;
        CHECK(mat2[0][0] == 1);
    }

    SUBCASE("Edge case: 1x1 matrix"){
        SquareMat mat(1);
        mat[0][0] = 5;
        CHECK(mat[0][0] == 5);
    }
}

TEST_CASE("Assignment operator"){
    SUBCASE("Same size assignment"){
        SquareMat mat1(2);
        mat1[0][0] = 1;
        mat1[0][1] = 2;
        mat1[1][0] = 3;
        mat1[1][1] = 4;

        SquareMat mat2(2);
        mat2 = mat1;
        
        // Check assignment worked
        for(int i = 0; i < 2; i++){
            for(int j = 0; j < 2; j++){
                CHECK(mat2[i][j] == mat1[i][j]);
            }
        }
        
        // Check deep copy
        mat1[0][0] = 10;
        CHECK(mat2[0][0] == 1);
    }

    SUBCASE("Different size assignment"){
        SquareMat mat1(3);
        mat1[0][0] = 1;
        mat1[1][1] = 2;
        mat1[2][2] = 3;

        SquareMat mat2(2);
        mat2 = mat1;
        
        // Check assignment worked and sizes changed
        CHECK(mat1.get_size() == mat2.get_size());
    
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                CHECK(mat2[i][j] == mat1[i][j]);
            }
        }
    }

    SUBCASE("Self-assignment"){
        SquareMat mat(2);
        mat[0][0] = 1;
        mat[0][1] = 2;
        mat[1][0] = 3;
        mat[1][1] = 4;
        
        mat = mat; // Self-assignment
        
        // Should'nt change anything
        CHECK(mat[0][0] == 1);
        CHECK(mat[0][1] == 2);
        CHECK(mat[1][0] == 3);
        CHECK(mat[1][1] == 4);
    }
}

TEST_CASE("Bracket operator []"){
    int num = 1;
    SquareMat mat(3);
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            mat[i][j] = num++;
        }
    }

    SUBCASE("Read and write access"){
        CHECK(mat[0][0] == 1);
        CHECK(mat[1][1] == 5);
        CHECK(mat[2][2] == 9);
        
        mat[1][1] = 15;
        CHECK(mat[1][1] == 15);
    }

    SUBCASE("Out of bounds access"){
        CHECK_THROWS_AS(mat[-1][0], std::out_of_range);
        CHECK_THROWS_AS(mat[3][0], std::out_of_range);
    }

    SUBCASE("Const access"){
        const SquareMat const_mat(mat);
        CHECK(const_mat[0][0] == 1);
        CHECK(const_mat[1][1] == 5);
        CHECK_THROWS_AS(const_mat[-1][0], std::out_of_range);
    }
}

TEST_CASE("Addition operator +"){
    SquareMat mat1(2);
    mat1[0][0] = 1;
    mat1[0][1] = 2;
    mat1[1][0] = 3;
    mat1[1][1] = 4;

    SquareMat mat2(2);
    mat2[0][0] = 5;
    mat2[0][1] = 6;
    mat2[1][0] = 7;
    mat2[1][1] = 8;

    SUBCASE("Regular addition"){
        SquareMat result = mat1 + mat2;
        CHECK(result[0][0] == 6);
        CHECK(result[0][1] == 8);
        CHECK(result[1][0] == 10);
        CHECK(result[1][1] == 12);
    }

    SUBCASE("Different size addition"){
        SquareMat mat3(3);
        CHECK_THROWS_AS(mat1 + mat3, std::invalid_argument);
    }

    SUBCASE("Addition with zero matrix"){
        SquareMat zero(2); // All zeros by default
        
        SquareMat result = mat1 + zero;
        CHECK(result[0][0] == 1);
        CHECK(result[0][1] == 2);
        CHECK(result[1][0] == 3);
        CHECK(result[1][1] == 4);
    }
}

TEST_CASE("Subtraction operator -"){
    SquareMat mat1(2);
    mat1[0][0] = 5;
    mat1[0][1] = 6;
    mat1[1][0] = 7;
    mat1[1][1] = 8;

    SquareMat mat2(2);
    mat2[0][0] = 1;
    mat2[0][1] = 2;
    mat2[1][0] = 3;
    mat2[1][1] = 4;

    SUBCASE("Regular subtraction"){
        SquareMat result = mat1 - mat2;
        CHECK(result[0][0] == 4);
        CHECK(result[0][1] == 4);
        CHECK(result[1][0] == 4);
        CHECK(result[1][1] == 4);
    }

    SUBCASE("Different size subtraction"){
        SquareMat mat3(3);
        CHECK_THROWS_AS(mat1 - mat3, std::invalid_argument);
    }

    SUBCASE("Subtraction with zero matrix"){
        SquareMat zero(2); // All zeros by default
        
        SquareMat result = mat1 - zero;
        CHECK(result[0][0] == 5);
        CHECK(result[0][1] == 6);
        CHECK(result[1][0] == 7);
        CHECK(result[1][1] == 8);
    }
}

TEST_CASE("Unary minus operator -"){
    SquareMat mat(2);
    mat[0][0] = 1;
    mat[0][1] = -2;
    mat[1][0] = 3;
    mat[1][1] = -4;

    SquareMat result = -mat;
    CHECK(result[0][0] == -1);
    CHECK(result[0][1] == 2);
    CHECK(result[1][0] == -3);
    CHECK(result[1][1] == 4);
}

TEST_CASE("Matrix multiplication *"){
    SUBCASE("Regular matrix multiplication"){
        SquareMat mat1(2);
        mat1[0][0] = 1;
        mat1[0][1] = 2;
        mat1[1][0] = 3;
        mat1[1][1] = 4;

        SquareMat mat2(2);
        mat2[0][0] = 5;
        mat2[0][1] = 6;
        mat2[1][0] = 7;
        mat2[1][1] = 8;

        SquareMat result = mat1 * mat2;
        CHECK(result[0][0] == 19); // 1*5 + 2*7
        CHECK(result[0][1] == 22); // 1*6 + 2*8
        CHECK(result[1][0] == 43); // 3*5 + 4*7
        CHECK(result[1][1] == 50); // 3*6 + 4*8
    }

    SUBCASE("Multiplication with identity"){
        SquareMat mat(3);
        int num = 1;
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                mat[i][j] = num++;
            }
        }

        SquareMat identity(3);
        identity[0][0] = 1;
        identity[1][1] = 1;
        identity[2][2] = 1;

        SquareMat result = mat * identity;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                CHECK(result[i][j] == mat[i][j]);
            }
        }
    }

    SUBCASE("Different size multiplication"){
        SquareMat mat1(2);
        SquareMat mat2(3);
        CHECK_THROWS_AS(mat1 * mat2, std::invalid_argument);
    }

    SUBCASE("1x1 matrix multiplication"){
        SquareMat mat1(1);
        mat1[0][0] = 5;
        
        SquareMat mat2(1);
        mat2[0][0] = 3;
        
        SquareMat result = mat1 * mat2;
        CHECK(result[0][0] == 15);
    }
}

TEST_CASE("Scalar multiplication *"){
    SquareMat mat(2);
    mat[0][0] = 1;
    mat[0][1] = 2;
    mat[1][0] = 3;
    mat[1][1] = 4;

    SUBCASE("Matrix * scalar"){
        SquareMat result = mat * 2;
        CHECK(result[0][0] == 2);
        CHECK(result[0][1] == 4);
        CHECK(result[1][0] == 6);
        CHECK(result[1][1] == 8);
    }

    SUBCASE("Scalar * matrix"){
        SquareMat result = 2 * mat;
        CHECK(result[0][0] == 2);
        CHECK(result[0][1] == 4);
        CHECK(result[1][0] == 6);
        CHECK(result[1][1] == 8);
    }

    SUBCASE("Multiplication by 0"){
        SquareMat result = mat * 0;
        for(int i = 0; i < 2; i++){
            for(int j = 0; j < 2; j++){
                CHECK(result[i][j] == 0);
            }
        }
    }

    SUBCASE("Multiplication by 1"){
        SquareMat result = 1 * mat;
        for(int i = 0; i < 2; i++){
            for(int j = 0; j < 2; j++){
                CHECK(result[i][j] == mat[i][j]);
            }
        }
    }

    SUBCASE("Multiplication by -1"){
        SquareMat result = mat * (-1);
        CHECK(result == -mat);
    }
}

TEST_CASE("Special multiplication %"){
    SquareMat mat1(2);
    mat1[0][0] = 1;
    mat1[0][1] = 2;
    mat1[1][0] = 3;
    mat1[1][1] = 4;

    SquareMat mat2(2);
    mat2[0][0] = 5;
    mat2[0][1] = 6;
    mat2[1][0] = 7;
    mat2[1][1] = 8;

    SUBCASE("Regular special multiplication"){
        SquareMat result = mat1 % mat2;
        CHECK(result[0][0] == 5);  // 1*5
        CHECK(result[0][1] == 12); // 2*6
        CHECK(result[1][0] == 21); // 3*7
        CHECK(result[1][1] == 32); // 4*8
    }

    SUBCASE("Different size special multiplication"){
        SquareMat mat3(3);
        CHECK_THROWS_AS(mat1 % mat3, std::invalid_argument);
    }

    SUBCASE("Special multiplication with identity"){
        SquareMat identity(2);
        identity[0][0] = 1;
        identity[1][1] = 1;
        
        SquareMat result = mat1 % identity;
        CHECK(result[0][0] == 1);
        CHECK(result[0][1] == 0);
        CHECK(result[1][0] == 0);
        CHECK(result[1][1] == 4);
    }
}

TEST_CASE("Modulo operation %"){
    SquareMat mat(2);
    mat[0][0] = 10.5;
    mat[0][1] = 7.2;
    mat[1][0] = -3.5;
    mat[1][1] = 14.0;

    SUBCASE("Modulo with positive integer"){
        SquareMat result = mat % 2;
        CHECK(approx_equal(result[0][0], 0.5));
        CHECK(approx_equal(result[0][1], 1.2));
        CHECK(approx_equal(result[1][0], -1.5));
        CHECK(approx_equal(result[1][1], 0.0));
    }

    SUBCASE("Modulo with negative integer") {
        // Note: fmod behavior with negative numbers
        SquareMat result = mat % (-3);
        CHECK(approx_equal(result[0][0], 1.5));
        CHECK(approx_equal(result[0][1], 1.2));
        CHECK(approx_equal(result[1][0], -0.5));
        CHECK(approx_equal(result[1][1], 2.0));
    }
}

TEST_CASE("Division operator /"){
    SquareMat mat(2);
    mat[0][0] = 10;
    mat[0][1] = 20;
    mat[1][0] = 30;
    mat[1][1] = 40;

    SUBCASE("Regular division"){
        SquareMat result = mat / 2;
        CHECK(result[0][0] == 5);
        CHECK(result[0][1] == 10);
        CHECK(result[1][0] == 15);
        CHECK(result[1][1] == 20);
    }

    SUBCASE("Division by zero"){
        CHECK_THROWS_AS(mat / 0, std::invalid_argument);
    }

    SUBCASE("Division by negative number"){
        SquareMat result = mat / (-5);
        CHECK(result[0][0] == -2);
        CHECK(result[0][1] == -4);
        CHECK(result[1][0] == -6);
        CHECK(result[1][1] == -8);
    }
}

TEST_CASE("Matrix power ^"){
    SUBCASE("Power of 0"){  // Result should be identity matrix
        SquareMat mat(2);
        mat[0][0] = 1;
        mat[0][1] = 2;
        mat[1][0] = 3;
        mat[1][1] = 4;

        SquareMat result = mat ^ 0;
        CHECK(result[0][0] == 1);
        CHECK(result[0][1] == 0);
        CHECK(result[1][0] == 0);
        CHECK(result[1][1] == 1);
    }

    SUBCASE("Power of 1"){
        SquareMat mat(2);
        mat[0][0] = 1;
        mat[0][1] = 2;
        mat[1][0] = 3;
        mat[1][1] = 4;

        SquareMat result = mat ^ 1;
        CHECK(result[0][0] == 1);
        CHECK(result[0][1] == 2);
        CHECK(result[1][0] == 3);
        CHECK(result[1][1] == 4);
    }

    SUBCASE("Power of 2"){
        SquareMat mat(2);
        mat[0][0] = 1;
        mat[0][1] = 2;
        mat[1][0] = 3;
        mat[1][1] = 4;

        SquareMat result = mat ^ 2;
        CHECK(result[0][0] == 7);  // 1*1 + 2*3
        CHECK(result[0][1] == 10); // 1*2 + 2*4
        CHECK(result[1][0] == 15); // 3*1 + 4*3
        CHECK(result[1][1] == 22); // 3*2 + 4*4
    }

    SUBCASE("Power of 3"){
        SquareMat mat(2);
        mat[0][0] = 1;
        mat[0][1] = 2;
        mat[1][0] = 3;
        mat[1][1] = 4;

        SquareMat result = mat ^ 3;
        // mat * mat * mat
        SquareMat expected = mat * mat * mat;
        
        CHECK(result[0][0] == expected[0][0]);
        CHECK(result[0][1] == expected[0][1]);
        CHECK(result[1][0] == expected[1][0]);
        CHECK(result[1][1] == expected[1][1]);
    }

    SUBCASE("Negative power"){
        SquareMat mat(2);
        mat[0][0] = 1;
        mat[0][1] = 2;
        mat[1][0] = 3;
        mat[1][1] = 4;

        CHECK_THROWS_AS(mat ^ (-1), std::invalid_argument);
    }
}

TEST_CASE("Increment/decrement operators"){
    SquareMat mat(2);
    mat[0][0] = 1;
    mat[0][1] = 2;
    mat[1][0] = 3;
    mat[1][1] = 4;

    SUBCASE("Pre-increment ++mat"){
        SquareMat& result = ++mat;
        CHECK(mat[0][0] == 2);
        CHECK(mat[0][1] == 3);
        CHECK(mat[1][0] == 4);
        CHECK(mat[1][1] == 5);
        CHECK(&result == &mat); // Should return reference to itself
    }

    SUBCASE("Post-increment mat++"){
        SquareMat original_mat(2);
        original_mat[0][0] = 1;
        original_mat[0][1] = 2;
        original_mat[1][0] = 3;
        original_mat[1][1] = 4;
        
        SquareMat result = original_mat++;
        CHECK(original_mat[0][0] == 2);  // Original incremented
        CHECK(original_mat[0][1] == 3);
        CHECK(original_mat[1][0] == 4);
        CHECK(original_mat[1][1] == 5);
        
        CHECK(result[0][0] == 1);  // Result has old values
        CHECK(result[0][1] == 2);
        CHECK(result[1][0] == 3);
        CHECK(result[1][1] == 4);
    }

    SUBCASE("Pre-decrement --mat"){
        SquareMat& result = --mat;
        CHECK(mat[0][0] == 0);
        CHECK(mat[0][1] == 1);
        CHECK(mat[1][0] == 2);
        CHECK(mat[1][1] == 3);
        CHECK(&result == &mat); // Should return reference to itself
    }

    SUBCASE("Post-decrement mat--"){
        SquareMat original_mat(2);
        original_mat[0][0] = 1;
        original_mat[0][1] = 2;
        original_mat[1][0] = 3;
        original_mat[1][1] = 4;
        
        SquareMat result = original_mat--;
        CHECK(original_mat[0][0] == 0);  // Original decremented
        CHECK(original_mat[0][1] == 1);
        CHECK(original_mat[1][0] == 2);
        CHECK(original_mat[1][1] == 3);
        
        CHECK(result[0][0] == 1);  // Result has old values
        CHECK(result[0][1] == 2);
        CHECK(result[1][0] == 3);
        CHECK(result[1][1] == 4);
    }
}

TEST_CASE("Transpose operator ~"){
    int num = 1;
    SUBCASE("Regular transpose"){
        SquareMat mat(3);
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                mat[i][j] = num++;
            }
        }

        SquareMat result = ~mat;
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                CHECK(result[i][j] == mat[j][i]);
            }
        }
    }

    SUBCASE("Symmetric matrix transpose"){
        SquareMat mat(2);
        mat[0][0] = 1;
        mat[0][1] = 2;
        mat[1][0] = 2;
        mat[1][1] = 3;

        SquareMat result = ~mat;
        CHECK(result[0][0] == 1);
        CHECK(result[0][1] == 2);
        CHECK(result[1][0] == 2);
        CHECK(result[1][1] == 3);
    }

    SUBCASE("1x1 matrix transpose"){
        SquareMat mat(1);
        mat[0][0] = 5;

        SquareMat result = ~mat;
        CHECK(result[0][0] == 5);
    }

    SUBCASE("Double transpose"){
        SquareMat mat(2);
        mat[0][0] = 1;
        mat[0][1] = 2;
        mat[1][0] = 3;
        mat[1][1] = 4;

        SquareMat result = ~(~mat);
        CHECK(result[0][0] == 1);
        CHECK(result[0][1] == 2);
        CHECK(result[1][0] == 3);
        CHECK(result[1][1] == 4);
    }
}

TEST_CASE("Comparison operators"){
    SUBCASE("Equal matrices by sum"){
        SquareMat mat1(2);
        mat1[0][0] = 1;
        mat1[0][1] = 2;
        mat1[1][0] = 3;
        mat1[1][1] = 4;

        SquareMat mat2(2);
        mat2[0][0] = 4;
        mat2[0][1] = 3;
        mat2[1][0] = 2;
        mat2[1][1] = 1;

        CHECK(mat1 == mat2);
        CHECK_FALSE(mat1 != mat2);
    }

    SUBCASE("Different sized matrices with same sum"){
        SquareMat mat1(2);
        mat1[0][0] = 2;
        mat1[0][1] = 2;
        mat1[1][0] = 2;
        mat1[1][1] = 3;

        SquareMat mat2(3);
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                mat2[i][j] = 1;
            }
        }

        CHECK(mat1 == mat2);
        CHECK_FALSE(mat1 != mat2);
    }

    SUBCASE("Less/Greater than operator"){
        SquareMat mat1(2);
        mat1[0][0] = 1;
        mat1[0][1] = 2;
        mat1[1][0] = 3;
        mat1[1][1] = 3;

        SquareMat mat2(2);
        mat2[0][0] = 2;
        mat2[0][1] = 3;
        mat2[1][0] = 2;
        mat2[1][1] = 4;

        CHECK(mat1 < mat2);
        CHECK(mat2 > mat1);
    }
    
    SUBCASE("Less than or equal operator"){
        SquareMat mat1(2);
        mat1[0][0] = 1;
        mat1[0][1] = 2;
        mat1[1][0] = 3;
        mat1[1][1] = 4;

        SquareMat mat2(2);
        mat2[0][0] = 2;
        mat2[0][1] = 3;
        mat2[1][0] = 2;
        mat2[1][1] = 3;

        CHECK(mat1 <= mat2);    // It's actually equal
        CHECK(mat2 <= mat1);    // It's actually equal
        
        SquareMat mat3(2);
        mat3[0][0] = 1;
        mat3[0][1] = 2;
        mat3[1][0] = 2;
        mat3[1][1] = 3;
        
        CHECK(mat3 <= mat1);    // It's actually less than
        CHECK_FALSE(mat1 <= mat3);  // It's actually greater than
    }

    SUBCASE("Greater than or equal operator"){
        SquareMat mat1(2);
        mat1[0][0] = 5;
        mat1[0][1] = 5;
        mat1[1][0] = 5;
        mat1[1][1] = 5;

        SquareMat mat2(2);
        mat2[0][0] = 5;
        mat2[0][1] = 5;
        mat2[1][0] = 5;
        mat2[1][1] = 5;

        CHECK(mat1 >= mat2);    // It's actually equal
        CHECK(mat2 >= mat1);    // It's actually equal
        
        SquareMat mat3(2);
        mat3[0][0] = 3;
        mat3[0][1] = 3;
        mat3[1][0] = 3;
        mat3[1][1] = 3;
        
        CHECK(mat1 >= mat3);    // It's actually greater than
        CHECK_FALSE(mat3 >= mat1);  // It's actually less than
    }
}

TEST_CASE("Determinant operator !"){
    int num = 1;

    SUBCASE("1x1 matrix determinant"){
        SquareMat mat(1);
        mat[0][0] = 5;
        
        double det = !mat;
        CHECK(det == 5);
    }

    SUBCASE("2x2 matrix determinant"){
        SquareMat mat(2);
        mat[0][0] = 4;
        mat[0][1] = 3;
        mat[1][0] = 2;
        mat[1][1] = 1;
        
        double det = !mat;
        CHECK(det == -2); // 4*1 - 3*2
    }

    SUBCASE("3x3 matrix determinant"){
        SquareMat mat(3);
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                mat[i][j] = num++;
            }
        }
        // Determinant = 1*(5*9 - 6*8) - 2*(4*9 - 6*7) + 3*(4*8 - 5*7)
        // = 1*(-3) - 2*(-6) + 3*(-3)
        // = -3 - (-12) + (-9) = 0
        
        double det = !mat;
        CHECK(approx_equal(det, 0.0)); // This matrix is singular
    }

    SUBCASE("3x3 matrix determinant (non-singular)"){
        SquareMat mat(3);
        mat[0][0] = 2;
        mat[0][1] = 1;
        mat[0][2] = 3;
        mat[1][0] = 0;
        mat[1][1] = 4;
        mat[1][2] = -1;
        mat[2][0] = 5;
        mat[2][1] = 2;
        mat[2][2] = 2;
        // Determinant = 2*(4*2 - (-1)*2) - 1*(0*2 - (-1)*5) + 3*(0*2 - 4*5)
        // = 2*(8 + 2) - 1*(0 + 5) + 3*(0 - 20)
        // = 20 - 5 - 60
        // = -45
        
        double det = !mat;
        CHECK(approx_equal(det, -45));
    }
}

TEST_CASE("Compound assignment operators"){
    SUBCASE("Addition assignment +="){
        SquareMat mat1(2);
        mat1[0][0] = 1;
        mat1[0][1] = 2;
        mat1[1][0] = 3;
        mat1[1][1] = 4;

        SquareMat mat2(2);
        mat2[0][0] = 5;
        mat2[0][1] = 6;
        mat2[1][0] = 7;
        mat2[1][1] = 8;
        
        mat1 += mat2;
        CHECK(mat1[0][0] == 6);
        CHECK(mat1[0][1] == 8);
        CHECK(mat1[1][0] == 10);
        CHECK(mat1[1][1] == 12);
    }

    SUBCASE("Different size addition assignment"){
        SquareMat mat1(2);
        SquareMat mat2(3);
        CHECK_THROWS_AS(mat1 += mat2, std::invalid_argument);
    }

    SUBCASE("Subtraction assignment -="){
        SquareMat mat1(2);
        mat1[0][0] = 6;
        mat1[0][1] = 8;
        mat1[1][0] = 10;
        mat1[1][1] = 12;

        SquareMat mat2(2);
        mat2[0][0] = 1;
        mat2[0][1] = 2;
        mat2[1][0] = 3;
        mat2[1][1] = 4;
        
        mat1 -= mat2;
        CHECK(mat1[0][0] == 5);
        CHECK(mat1[0][1] == 6);
        CHECK(mat1[1][0] == 7);
        CHECK(mat1[1][1] == 8);
    }

    SUBCASE("Different size subtraction assignment"){
        SquareMat mat1(2);
        SquareMat mat2(3);
        CHECK_THROWS_AS(mat1 -= mat2, std::invalid_argument);
    }

    SUBCASE("Multiplication assignment *="){
        SquareMat mat1(2);
        mat1[0][0] = 1;
        mat1[0][1] = 2;
        mat1[1][0] = 3;
        mat1[1][1] = 4;

        SquareMat mat2(2);
        mat2[0][0] = 5;
        mat2[0][1] = 6;
        mat2[1][0] = 7;
        mat2[1][1] = 8;
        
        mat1 *= mat2;
        CHECK(mat1[0][0] == 19); // 1*5 + 2*7
        CHECK(mat1[0][1] == 22); // 1*6 + 2*8
        CHECK(mat1[1][0] == 43); // 3*5 + 4*7
        CHECK(mat1[1][1] == 50); // 3*6 + 4*8
    }

    SUBCASE("Different size multiplication assignment"){
        SquareMat mat1(2);
        SquareMat mat2(3);
        CHECK_THROWS_AS(mat1 *= mat2, std::invalid_argument);
    }

    SUBCASE("Scalar multiplication assignment *="){
        SquareMat mat(2);
        mat[0][0] = 1;
        mat[0][1] = 2;
        mat[1][0] = 3;
        mat[1][1] = 4;
        
        mat *= 3;
        CHECK(mat[0][0] == 3);
        CHECK(mat[0][1] == 6);
        CHECK(mat[1][0] == 9);
        CHECK(mat[1][1] == 12);
    }

    SUBCASE("Special multiplication assignment %="){
        SquareMat mat1(2);
        mat1[0][0] = 1;
        mat1[0][1] = 2;
        mat1[1][0] = 3;
        mat1[1][1] = 4;

        SquareMat mat2(2);
        mat2[0][0] = 5;
        mat2[0][1] = 6;
        mat2[1][0] = 7;
        mat2[1][1] = 8;

        mat1 %= mat2;
        CHECK(mat1[0][0] == 5);  // 1*5
        CHECK(mat1[0][1] == 12); // 2*6
        CHECK(mat1[1][0] == 21); // 3*7
        CHECK(mat1[1][1] == 32); // 4*8
    }

    SUBCASE("Different size special multiplication assignment"){
        SquareMat mat1(2);
        SquareMat mat2(3);
        CHECK_THROWS_AS(mat1 %= mat2, std::invalid_argument);
    }

    SUBCASE("Modulo assignment %="){
        SquareMat mat(2);
        mat[0][0] = 10.5;
        mat[0][1] = 7.2;
        mat[1][0] = -3.5;
        mat[1][1] = 14.0;

        mat %= 2;
        CHECK(approx_equal(mat[0][0], 0.5));
        CHECK(approx_equal(mat[0][1], 1.2));
        CHECK(approx_equal(mat[1][0], -1.5));
        CHECK(approx_equal(mat[1][1], 0.0));
    }

    SUBCASE("Division assignment /="){
        SquareMat mat(2);
        mat[0][0] = 10;
        mat[0][1] = 20;
        mat[1][0] = 30;
        mat[1][1] = 40;

        mat /= 2;
        CHECK(mat[0][0] == 5);
        CHECK(mat[0][1] == 10);
        CHECK(mat[1][0] == 15);
        CHECK(mat[1][1] == 20);
    }

    SUBCASE("Division by zero assignment"){
        SquareMat mat(2);
        CHECK_THROWS_AS(mat /= 0, std::invalid_argument);
    }
}

TEST_CASE("Print and sum_elements functions"){
    SUBCASE("Print function"){
        SquareMat mat(2);
        mat[0][0] = 1;
        mat[0][1] = 2;
        mat[1][0] = 3;
        mat[1][1] = 4;

        std::stringstream buffer;
        CoutRedirect redirect(buffer);

        mat.print();

        std::string output = buffer.str();
        CHECK(output == "1 2 \n3 4 \n");
    }

    SUBCASE("Print function for 1x1 matrix"){
        SquareMat mat(1);
        mat[0][0] = 5;

        std::stringstream buffer;
        CoutRedirect redirect(buffer);

        mat.print();

        std::string output = buffer.str();
        CHECK(output == "5 \n");
    }

    SUBCASE("Sum elements function"){
        int num = 1;

        SquareMat mat(3);
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                mat[i][j] = num++;
            }
        }

        double sum = mat.sum_elements();
        CHECK(sum == 45);
    }

    SUBCASE("Sum elements for matrix with negative values"){
        SquareMat mat(2);
        mat[0][0] = -1;
        mat[0][1] = 2;
        mat[1][0] = -3;
        mat[1][1] = 4;

        double sum = mat.sum_elements();
        CHECK(sum == 2);
    }

    SUBCASE("Sum elements for empty values matrix"){
        SquareMat mat(3); // Initialized to 0

        double sum = mat.sum_elements();
        CHECK(sum == 0);
    }
}

TEST_CASE("Complex operations and combinations"){
    SUBCASE("Multiple operations chain"){
        SquareMat mat1(2);
        mat1[0][0] = 1;
        mat1[0][1] = 2;
        mat1[1][0] = 3;
        mat1[1][1] = 4;

        SquareMat mat2(2);
        mat2[0][0] = 5;
        mat2[0][1] = 6;
        mat2[1][0] = 7;
        mat2[1][1] = 8;

        // (mat1 + mat2) * 2
        SquareMat result = (mat1 + mat2) * 2;
        CHECK(result[0][0] == 12);
        CHECK(result[0][1] == 16);
        CHECK(result[1][0] == 20);
        CHECK(result[1][1] == 24);
    }

    SUBCASE("Matrix power and addition"){
        SquareMat mat1(2);
        mat1[0][0] = 1;
        mat1[0][1] = 2;
        mat1[1][0] = 3;
        mat1[1][1] = 4;

        SquareMat identity(2);
        identity[0][0] = 1;
        identity[1][1] = 1;

        // (mat1^2) + identity
        SquareMat result = (mat1 ^ 2) + identity;
        CHECK(result[0][0] == 8);  // (1*1 + 2*3) + 1
        CHECK(result[0][1] == 10); // (1*2 + 2*4) + 0
        CHECK(result[1][0] == 15); // (3*1 + 4*3) + 0
        CHECK(result[1][1] == 23); // (3*2 + 4*4) + 1
    }

    SUBCASE("Transposition and multiplication"){
        SquareMat mat(2);
        mat[0][0] = 1;
        mat[0][1] = 2;
        mat[1][0] = 3;
        mat[1][1] = 4;

        // mat * (~mat)
        SquareMat result = mat * (~mat);
        CHECK(result[0][0] == 5);  // 1*1 + 2*2
        CHECK(result[0][1] == 11); // 1*3 + 2*4
        CHECK(result[1][0] == 11); // 3*1 + 4*2
        CHECK(result[1][1] == 25); // 3*3 + 4*4
    }

    SUBCASE("Determinant of matrix power"){
        SquareMat mat(2);
        mat[0][0] = 2;
        mat[0][1] = 1;
        mat[1][0] = 1;
        mat[1][1] = 3;
        
        double det1 = !mat;
        double det2 = !(mat ^ 2);
        
        CHECK(approx_equal(det1, 5));  // 2*3 - 1*1 = 5
        CHECK(approx_equal(det2, 25));       
        // mat ^ 2 = [5, 5]
        //           [5, 10]
        // det(mat^2) = 5*10 - 5*5 = 50 - 25 = 25
    }

    SUBCASE("Complex combination"){
        SquareMat mat1(2);
        mat1[0][0] = 1;
        mat1[0][1] = 2;
        mat1[1][0] = 3;
        mat1[1][1] = 4;

        SquareMat mat2(2);
        mat2[0][0] = 5;
        mat2[0][1] = 6;
        mat2[1][0] = 7;
        mat2[1][1] = 8;

        // ((mat1 + mat2) * (~mat1)) % 5
        SquareMat result = ((mat1 + mat2) * (~mat1)) % 5;
        
        // mat1 + mat2 = [6, 8]
        //              [10, 12]
        
        // ~mat1 = [1, 3]
        //         [2, 4]
        
        // (mat1 + mat2) * (~mat1) =
        // [6*1 + 8*2, 6*3 + 8*4]
        // [10*1 + 12*2, 10*3 + 12*4] = [22, 50]
        //                              [34, 78]
        
        // ((mat1 + mat2) * (~mat1)) % 5 = [2, 0]
        //                                 [4, 3]
        
        CHECK(result[0][0] == 2);
        CHECK(result[0][1] == 0);
        CHECK(result[1][0] == 4);
        CHECK(result[1][1] == 3);
    }
}