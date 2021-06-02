#pragma once
#include <iomanip>
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include "Seidel.h"
#include "Matrix.h"
#include "Func.h"

using namespace std;

class Output
{
public:
    Seidel matr1;
    Matrix matr;
    Func func;
    ofstream res;
    Output()
    {
        matr = Matrix();
        matr1 = Seidel();
        func = Func();
        result();
    }

    void result()
    {
        res.open(matr.path + matr.out + ".txt");
        res << setw(10) << "Count[" << "№" << "] " << setw(35) << "u[выч]" << setw(35) << "u[ист]" << setw(35) << "u[выч]-u[ист]" << endl;
        for (size_t i = 0; i < matr.N; i++)
        {
             res << setw(10) << "Count[" << i << "] " << setprecision(16) << setw(35) << matr1.xk[i] << setw(35) << matr.ux[i] << setw(35) << abs(matr1.xk[i] - matr.ux[i]) << endl;
        }
    }
};


