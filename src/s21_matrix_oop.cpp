#include "./s21_matrix_oop.h"

void S21Matrix::AllocateMemory() {
  matrix_ = new double *[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_]();
  }
}

void S21Matrix::FreeMemory() {
  if (matrix_) {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
    matrix_ = nullptr;
  }
}

S21Matrix::S21Matrix() : rows_(0), cols_(0), matrix_(nullptr) {}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows_ < 1 || cols_ < 1) {
    throw std::out_of_range("Matrix size must be > 0");
  }
  AllocateMemory();
}

S21Matrix::S21Matrix(const S21Matrix &other)
    : rows_(other.rows_), cols_(other.cols_) {
  AllocateMemory();
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

S21Matrix::S21Matrix(S21Matrix &&other)
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

S21Matrix::~S21Matrix() { FreeMemory(); }

bool S21Matrix::EqMatrix(const S21Matrix &other) const {
  if (rows_ != other.rows_ || cols_ != other.cols_) return false;
  bool flag = true;
  for (int i = 0; i < rows_ && flag == true; i++) {
    for (int j = 0; j < cols_ && flag == true; j++) {
      if (std::fabs(matrix_[i][j] - other.matrix_[i][j]) > 1e-7) {
        flag = false;
      }
    }
  }
  return flag;
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::out_of_range(
        "Incorrect input, matrices should have the same size");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      this->matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::out_of_range(
        "Incorrect input, matrices should have the same size");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      this->matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (cols_ != other.rows_) {
    throw std::out_of_range(
        "The number of columns of the first matrix is not equal to the number "
        "of rows of the second matrix");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      double res = 0;
      for (int k = 0; k < cols_; k++) {
        res += matrix_[i][k] * other.matrix_[k][j];
      }
      matrix_[i][j] = res;
    }
  }
}

S21Matrix S21Matrix::Transpose() {
  S21Matrix res(cols_, rows_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      res.matrix_[j][i] = matrix_[i][j];
    }
  }
  return res;
}

S21Matrix S21Matrix::Minor(int row, int col) {
  S21Matrix res(rows_ - 1, cols_ - 1);
  int index_i = 0, index_j = 0;
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (i != row && j != col) {
        index_i = i, index_j = j;
        if (i > row) index_i--;
        if (j > col) index_j--;
        res.matrix_[index_i][index_j] = matrix_[i][j];
      }
    }
  }
  return res;
}

double S21Matrix::Determinant() {
  if (cols_ != rows_) {
    throw std::out_of_range("The matrix is not square");
  }
  double res = 0;
  if (rows_ == 1) {
    res = matrix_[0][0];
  } else if (rows_ == 2) {
    res = matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
  } else {
    for (int i = 0; i < rows_; i++) {
      S21Matrix minor = Minor(0, i);
      double det = minor.Determinant();
      double sign = (i % 2 == 0) ? 1 : -1;
      res += matrix_[0][i] * det * sign;
    }
  }
  return res;
}

S21Matrix S21Matrix::CalcComplements() {
  if (cols_ != rows_) {
    throw std::out_of_range("The matrix is not square");
  }
  S21Matrix res(rows_, cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      S21Matrix minor = Minor(i, j);
      res.matrix_[i][j] = minor.Determinant();
      if ((i + j) % 2 == 1) {
        res.matrix_[i][j] *= -1;
      }
    }
  }
  return res;
}

S21Matrix S21Matrix::InverseMatrix() {
  double det = Determinant();
  if (fabs(det) < 1e-7) {
    throw std::logic_error("The determinant of the matrix is 0");
  }
  S21Matrix tmp(CalcComplements().Transpose());
  tmp.MulNumber(1 / det);
  return tmp;
}

bool S21Matrix::operator==(const S21Matrix &other) const {
  return EqMatrix(other);
}

S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  this->FreeMemory();
  rows_ = other.rows_;
  cols_ = other.cols_;
  AllocateMemory();
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
  return *this;
}

S21Matrix S21Matrix::operator+(const S21Matrix &other) {
  S21Matrix res(*this);
  res.SumMatrix(other);
  return res;
}

S21Matrix &S21Matrix::operator+=(const S21Matrix &other) {
  this->SumMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) {
  S21Matrix res(*this);
  res.SubMatrix(other);
  return res;
}

S21Matrix &S21Matrix::operator-=(const S21Matrix &other) {
  this->SubMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) {
  S21Matrix res(*this);
  res.MulMatrix(other);
  return res;
}

S21Matrix &S21Matrix::operator*=(const S21Matrix &other) {
  this->MulMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator*(const double num) {
  S21Matrix res(*this);
  res.MulNumber(num);
  return res;
}

S21Matrix &S21Matrix::operator*=(const double num) {
  this->MulNumber(num);
  return *this;
}

double &S21Matrix::operator()(int i, int j) {
  if (i >= rows_ || j >= cols_ || i < 0 || j < 0) {
    throw std::out_of_range("The index is out of range");
  } else {
    return matrix_[i][j];
  }
}