#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include "Func.h"

using namespace std;

class Matrix : Func
{
public:
    size_t N, M, COUNTx, COUNTy;
    double x1, x2, x3, x4, y1, y2, y3, l, g, ax, bx, ay, by, k;
    string path = "test1/", out = "f";
    vector<double> f, hx, hy, ux;
    vector<vector<double>> mat;

    Matrix()
    {
        ifstream f;
        f.open(path + "area.txt");
        f >> ax >> bx >> ay >> by;
        f >> l >> g;
        f >> COUNTx >> COUNTy >> k;
        f.close();
        scale();
        resize();
        step();
        matrix();
    }

    void matrix()
    {
        for (size_t i = 0; i < COUNTy; i++)
            for (size_t j = 0; j < COUNTx; j++)
                if ((x2 < hx[j] && x3 > hx[j]) && (hy[i] < y2)) // проверка на дырку в штанах
                {
                    mat[2][COUNTx*i + j] = 1;
                    f[COUNTx*i + j] = ux[COUNTx * i + j] = 0;
                }
                else if ((hx[j] == x1 || hx[j] == x4 || hy[i] == y1 || hy[i] == y3) || ((hx[j] == x2 || hx[j] == x3) && (hy[i] < y2)) || ((hy[i] == y2) && (x2 <= hx[j] && x3 >= hx[j]))) // кравевые первые
                {
                    mat[2][COUNTx * i + j] = 1;
                    f[COUNTx * i + j] = ux[COUNTx * i + j] = u(hx[j], hy[i]);
                }
                else
                {
                    mat[3][COUNTx * i + j] = -2 * l / ((hx[j + 1] - hx[j]) * ((hx[j + 1] - hx[j]) + (hx[j] - hx[j - 1])));
                    mat[1][COUNTx * i + j] = -2 * l / ((hx[j] - hx[j - 1]) * ((hx[j + 1] - hx[j]) + (hx[j] - hx[j - 1])));
                    mat[4][COUNTx * i + j] = -2 * l / ((hy[i + 1] - hy[i]) * ((hy[i + 1] - hy[i]) + (hy[i] - hy[i - 1])));
                    mat[0][COUNTx * i + j] = -2 * l / ((hy[i] - hy[i - 1]) * ((hy[i + 1] - hy[i]) + (hy[i] - hy[i - 1])));
                    mat[2][COUNTx * i + j] = 2 * l / ((hx[j] - hx[j - 1]) * (hx[j + 1] - hx[j])) + 2 * l / ((hy[i] - hy[i - 1]) * (hy[i + 1] - hy[i])) + g;
                    f[COUNTx * i + j] = func(hx[j], hy[i], l, g);
                    ux[COUNTx * i + j] = u(hx[j], hy[i]);
                }
    }

    void scale()
    {
        M = COUNTx;                                            //размерность матрицы
        N = (COUNTx) * (COUNTy);      //кол-во элементов на диагонал€х
    }

    void resize()
    {
        f.resize(N);
        ux.resize(N);
        mat.resize(5, vector<double>(N));
    }

    void step()
    {
        hx.resize(COUNTx);
        hy.resize(COUNTy);
        k = sqrt(k);
        k = sqrt(k);
        double xn = (bx - ax) * k / pow(k, COUNTx - 1);
        double yn = (by - ay) * k / pow(k, COUNTy - 1);
        x1 = ax; y1 = ay;
        hx[0] = x1; hy[0] = y1;
        hx[1] = xn; hy[1] = yn;
        for (size_t i = 2; i < COUNTx; i++)
            hx[i] = hx[i - 1] * k;
        for (size_t i = 2; i < COUNTy; i++)
            hy[i] = hy[i - 1] * k;
        y2 = hy[(COUNTy - 1) / 2]; y3 = hy[COUNTy - 1];
        x2 = hx[(COUNTx - 1) / 3]; x3 = hx[((COUNTx - 1) / 3) * 2]; x4 = hx[COUNTx - 1];
    }

};