/*
author: Meir Yust
mail: meyu251@gmail.com
*/

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <iostream>
#include <sstream>
#include <string>
#include "Graph.hpp"
#include "Algorithms.hpp"
#include "Data_Structures.hpp"

using namespace graph;
using namespace std;

// Helper function to capture cout output
class CoutRedirect{
public:
    CoutRedirect(std::stringstream& buffer) : old_buf(std::cout.rdbuf(buffer.rdbuf())) {}
    ~CoutRedirect() { std::cout.rdbuf(old_buf); }
private:
    std::streambuf* old_buf;
};

// Test suite for Data_Structures
TEST_CASE("DynamicArray tests"){
    SUBCASE("Empty array"){
        DynamicArray<int> arr;
        CHECK(arr.getSize() == 0);
        CHECK(arr.isEmpty() == true);
    }

    SUBCASE("Push back and access"){
        DynamicArray<int> arr;
        arr.push_back(5);
        arr.push_back(10);
        CHECK(arr.getSize() == 2);
        CHECK(arr[0] == 5);
        CHECK(arr[1] == 10);
        CHECK(arr.isEmpty() == false);
    }

    SUBCASE("Remove at"){
        DynamicArray<int> arr;
        arr.push_back(5);
        arr.push_back(10);
        arr.push_back(15);
        arr.removeAt(1);
        CHECK(arr.getSize() == 2);
        CHECK(arr[0] == 5);
        CHECK(arr[1] == 15);
    }

    SUBCASE("Copy constructor"){
        DynamicArray<int> arr1;
        arr1.push_back(5);
        arr1.push_back(10);

        DynamicArray<int> arr2(arr1);
        CHECK(arr2.getSize() == 2);
        CHECK(arr2[0] == 5);
        CHECK(arr2[1] == 10);

        // Change arr1, arr2 should remain the same
        arr1.push_back(15);
        CHECK(arr1.getSize() == 3);
        CHECK(arr2.getSize() == 2);
    }

    SUBCASE("Assignment operator"){
        DynamicArray<int> arr1;
        arr1.push_back(5);
        arr1.push_back(10);

        DynamicArray<int> arr2;
        arr2 = arr1;
        CHECK(arr2.getSize() == 2);
        CHECK(arr2[0] == 5);
        CHECK(arr2[1] == 10);

        // Modify arr1, arr2 should remain the same
        arr1.push_back(15);
        CHECK(arr1.getSize() == 3);
        CHECK(arr2.getSize() == 2);
    }

    SUBCASE("Out of range exception"){
        DynamicArray<int> arr;
        arr.push_back(5);
        CHECK_THROWS_AS(arr[1], std::out_of_range);
        CHECK_THROWS_AS(arr.removeAt(1), std::out_of_range);
    }
}
