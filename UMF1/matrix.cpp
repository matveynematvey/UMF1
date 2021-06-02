//#pragma once
//#include <iostream>
//#include <fstream>
//#include <vector>
//
//using namespace std;
//
//class Matrix
//{
//public:
//    size_t size;
//    double x1, x2, x3, x4, y1, y2, y3, hx, hy;
//    vector<vector<int>> elems;
//    vector<vector<double>> points;
//
//    Matrix()
//    {
//        string path = "test1/";
//        ifstream f;
//        f.open(path + "area.txt");
//        f >> x1 >> x2 >> x3 >> x4;
//        f >> y1 >> y2 >> y3;
//        f >> hx >> hy;
//        f.close();
//    }
//
//
//    void splitP(double x1, double x2, double y1, double y2)
//    {
//        while(y2 - y1 >= 0)
//            while(x2 - x1 >= 0)
//
//    }
//
//    void size()
//    {
//        size = ((x4 - x1) / hx + 1) * ((y3 - y1) / hy + 1) - ((x3 - x2) / hx - 1) * (y2 - y1) / hy;
//        elems.resize(size);
//    }
//};
