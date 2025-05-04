#include <iostream>
#include "SquareMat.hpp"

using namespace ex2;
using namespace std;

int main(){

    SquareMat mat(3);
    int num = 1;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            mat[i][j] = num++;
        }
    }

    cout << "Matrix:" << endl;
    cout << mat << endl;
    cout << "Transpose:" << endl;
    cout << ~mat << endl;
    cout << "Matrix after increment:" << endl;
    cout << ++mat << endl;


    return 0;
}