#pragma once
#include <iomanip>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Func
{
public:
    Func() {}

    double u(double x, double y)
    {
        return sin(x) + cos(y);
    }

    double func(double x, double y, double l, double g)
    {
        return l*(sin(x) + cos(y)) + (g * u(x, y));
    }
};


