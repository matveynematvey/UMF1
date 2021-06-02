#pragma once
#include <vector>
#include "Matrix.h"

using namespace std;

class Seidel : Matrix
{
public:
    int D = 5;
    vector<int> index;     // Индексы столбцов
    vector<double> xk, xk1, mult;  // Вспомогательные векторы

    Seidel()
    {
        index.resize(5);
        index[0] = -1 * M;
        index[1] = -1;
        index[2] = 0;
        index[3] = 1;
        index[4] = M;
        xk.resize(N);
        xk1.resize(N);
        GaussSeidel(1000, 1e-5, 0.3);
    }

   // Умножение матрицы системы на вектор vec,
   // результат в res
   void Multiplication(vector<double>& vec, vector<double>& res)
   {
      int n = vec.size(), k = 0;
      for(int i = 0; i < D; i++)
      {
         k = index[i];
         if(k < 0)
            for(int j = abs(k); j < n; j++)
               res[j] += mat[i][j] * vec[k + j];
         else
            for(int j = 0; j < n - k; j++)
               res[j] += mat[i][j] * vec[k + j];
      }

      for(int j = 0; j < n; j++)
      {
         for(int d = 0; d < D; d++)
         {
            k = index[d];
            if(k < 0 && j + k > 0 ||
               k > 0 && j + k < n)
               res[j] += mat[d][j] * vec[k + j];
         }
      }
   }

   // Норма вектора
   double Norm(const vector<double>& vec)
   {
      double res = 0;
      for (int i = 0; i < N; i++)
         res += vec[i] * vec[i];

      return sqrt(res);
   }

   // Получение относительной невязки системы
   double RelativeResidual(vector<double>& vec)
   {
      mult.resize(N);
      Multiplication(vec, mult);
      for (size_t i = 0; i < N; i++)
         mult[i] = f[i] - mult[i];

      return Norm(mult) / Norm(f);
   }

   // Итерационный процесс метода Гаусса-Зейделя
   void IterativeProcess(const int& j, double& sum)
   {
      int k = 0, n = xk.size();

      for(int d = 0; d < D; d++)
      {
         k = index[d];
         if(k + j >= 0 && k + j < n)
         {
            if(d < 3) // нижний треугольник
               sum += mat[d][j] * xk1[k + j];
            else // верхний треугольник
               sum += mat[d][j] * xk[k + j];
         }
      }
   }

   // Решение системы методом Гаусса-Зейделя
   void GaussSeidel(const int& MAX_ITER, const double& EPS,
      const double& RELAX)
   {
      double residual = 0.0, sum = 0.0;
      residual = RelativeResidual(xk);
      for(int k = 0; k < MAX_ITER && residual > EPS; k++)
      {
         for(int j = 0; j < N; j++)
         {
            IterativeProcess(j, sum);
            xk1[j] = xk[j] + (RELAX / mat[2][j]) * (f[j] - sum);
            sum = 0.;
         }
         xk.swap(xk1);
         residual = RelativeResidual(xk);
      }
   }
};