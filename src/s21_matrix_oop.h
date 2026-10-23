#ifndef S21MATRIXOOP_H
#define S21MATRIXOOP_H

#include <cmath>
#include <cstring>
#include <iostream>

class S21Matrix {
 private:
  int rows_, cols_;
  double **matrix_;

  void AllocateMemory();
  void FreeMemory();

 public:
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix &other);
  S21Matrix(S21Matrix &&other);
  ~S21Matrix();

  bool EqMatrix(const S21Matrix &other) const;
  void SumMatrix(const S21Matrix &other);
  void SubMatrix(const S21Matrix &other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix &other);
  S21Matrix Transpose();
  S21Matrix Minor(int row, int col);
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();

  bool operator==(const S21Matrix &other) const;
  S21Matrix operator+(const S21Matrix &other);
  S21Matrix operator-(const S21Matrix &other);
  S21Matrix operator*(const double num);
  S21Matrix operator*(const S21Matrix &other);
  S21Matrix &operator=(const S21Matrix &other);
  S21Matrix &operator+=(const S21Matrix &other);
  S21Matrix &operator-=(const S21Matrix &other);
  S21Matrix &operator*=(const S21Matrix &other);
  S21Matrix &operator*=(const double num);
  double &operator()(int row, int col);

  int GetRows() const { return rows_; }
  int GetCols() const { return cols_; }
};

#endif