#include <gtest/gtest.h>

#include "./s21_matrix_oop.h"

// Конструкторы
TEST(ConstructorTest, DefaultConstructor) {
  S21Matrix A;
  EXPECT_EQ(A.GetRows(), 0);
  EXPECT_EQ(A.GetCols(), 0);
}

TEST(ConstructorTest, ParamConstructorValid) {
  S21Matrix A(3, 4);
  EXPECT_EQ(A.GetRows(), 3);
  EXPECT_EQ(A.GetCols(), 4);
}

TEST(ConstructorTest, ParamConstructorInvalid) {
  EXPECT_THROW(S21Matrix A(0, 4), std::out_of_range);
  EXPECT_THROW(S21Matrix A(-2, 3), std::out_of_range);
}

TEST(ConstructorTest, CopyConstructor) {
  S21Matrix A(2, 2);
  A(0, 0) = 5;
  S21Matrix B(A);
  EXPECT_TRUE(A == B);
}

TEST(ConstructorTest, MoveConstructor) {
  S21Matrix A(2, 2);
  A(0, 0) = 5;
  S21Matrix B(std::move(A));
  EXPECT_EQ(B(0, 0), 5);
  EXPECT_EQ(A.GetRows(), 0);
  EXPECT_EQ(A.GetCols(), 0);
}

// EqMatrix
TEST(EqMatrixTest, EqualMatrices) {
  S21Matrix A(2, 2);
  S21Matrix B(2, 2);
  EXPECT_TRUE(A.EqMatrix(B));
}

TEST(EqMatrixTest, NotEqualMatrices) {
  S21Matrix A(2, 2);
  S21Matrix B(2, 2);
  B(1, 1) = 1.5;
  EXPECT_FALSE(A.EqMatrix(B));
}

// SumMatrix

TEST(SumMatrixTest, CorrectSum) {
  S21Matrix A(2, 2);
  S21Matrix B(2, 2);
  A(0, 0) = 1;
  B(0, 0) = 2;
  A.SumMatrix(B);
  EXPECT_EQ(A(0, 0), 3);
}

TEST(SumMatrixTest, SumException) {
  S21Matrix A(2, 3);
  S21Matrix B(3, 2);
  EXPECT_THROW(A.SumMatrix(B), std::out_of_range);
}

// SubMatrix

TEST(SubMatrixTest, CorrectSub) {
  S21Matrix A(2, 2);
  S21Matrix B(2, 2);
  A(0, 0) = 5;
  B(0, 0) = 2;
  A.SubMatrix(B);
  EXPECT_EQ(A(0, 0), 3);
}

TEST(SubMatrixTest, SubException) {
  S21Matrix A(2, 3);
  S21Matrix B(3, 2);
  EXPECT_THROW(A.SubMatrix(B), std::out_of_range);
}

// MulNumber

TEST(MulNumberTest, MultiplyByNumber) {
  S21Matrix A(2, 2);
  A(0, 0) = 2;
  A.MulNumber(3);
  EXPECT_EQ(A(0, 0), 6);
}

// MulMatrix

TEST(MulMatrixTest, CorrectMul) {
  S21Matrix A(2, 3);
  S21Matrix B(3, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(0, 2) = 3;
  A(1, 0) = 3;
  A(1, 1) = 2;
  A(1, 2) = 1;
  B(0, 0) = 1;
  B(1, 0) = 2;
  B(2, 0) = 3;
  B(0, 1) = 3;
  B(1, 1) = 2;
  B(2, 1) = 1;
  A.MulMatrix(B);
  EXPECT_EQ(A(0, 0), 14);
  EXPECT_EQ(A(1, 0), 10);
}

TEST(MulMatrixTest, MulException) {
  S21Matrix A(2, 3);
  S21Matrix B(4, 5);
  EXPECT_THROW(A.MulMatrix(B), std::out_of_range);
}

// Transpose

TEST(TransposeTest, TransposeMatrix) {
  S21Matrix A(2, 3);
  A(0, 1) = 5;
  S21Matrix T = A.Transpose();
  EXPECT_EQ(T(1, 0), 5);
}

// Determinant

TEST(DeterminantTest, Determinant1x1) {
  S21Matrix A(1, 1);
  A(0, 0) = 5;
  EXPECT_EQ(A.Determinant(), 5);
}

TEST(DeterminantTest, Determinant2x2) {
  S21Matrix A(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;
  EXPECT_EQ(A.Determinant(), -2);
}

TEST(DeterminantTest, DeterminantNotSquare) {
  S21Matrix A(2, 3);
  EXPECT_THROW(A.Determinant(), std::out_of_range);
}

// CalcComplements

TEST(CalcComplementsTest, CorrectComplements) {
  S21Matrix A(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;
  S21Matrix C = A.CalcComplements();
  EXPECT_EQ(C(0, 0), 4);
}

TEST(CalcComplementsTest, ComplementsException) {
  S21Matrix A(2, 3);
  EXPECT_THROW(A.CalcComplements(), std::out_of_range);
}

// InverseMatrix

TEST(InverseMatrixTest, CorrectInverse) {
  S21Matrix A(2, 2);
  A(0, 0) = 4;
  A(0, 1) = 7;
  A(1, 0) = 2;
  A(1, 1) = 6;
  S21Matrix Inv = A.InverseMatrix();
  EXPECT_NEAR(Inv(0, 0), 0.6, 1e-7);
}

TEST(InverseMatrixTest, InverseException) {
  S21Matrix A(2, 2);
  EXPECT_THROW(A.InverseMatrix(), std::logic_error);
}

// Операторы

TEST(OperatorTest, OperatorBoolEqual) {
  S21Matrix A(2, 2);
  S21Matrix B(2, 2);
  A(0, 0) = 1;
  B(0, 0) = 1;
  bool c = A == B;
  EXPECT_EQ(c, true);
}

TEST(OperatorTest, OperatorEqual) {
  S21Matrix A(2, 2);
  A(0, 0) = 1;
  S21Matrix C = A;
  EXPECT_EQ(C(0, 0), 1);
}

TEST(OperatorTest, OperatorPlus) {
  S21Matrix A(2, 2);
  S21Matrix B(2, 2);
  A(0, 0) = 1;
  B(0, 0) = 2;
  S21Matrix C = A + B;
  EXPECT_EQ(C(0, 0), 3);
}

TEST(OperatorTest, OperatorPlusEqual) {
  S21Matrix A(2, 2);
  S21Matrix B(2, 2);
  A(0, 0) = 1;
  B(0, 0) = 2;
  A += B;
  EXPECT_EQ(A(0, 0), 3);
}

TEST(OperatorTest, OperatorMinus) {
  S21Matrix A(2, 2);
  S21Matrix B(2, 2);
  A(0, 0) = 2;
  B(0, 0) = 1;
  S21Matrix C = A - B;
  EXPECT_EQ(C(0, 0), 1);
}

TEST(OperatorTest, OperatorMinusEqual) {
  S21Matrix A(2, 2);
  S21Matrix B(2, 2);
  A(0, 0) = 2;
  B(0, 0) = 1;
  A -= B;
  EXPECT_EQ(A(0, 0), 1);
}

TEST(OperatorTest, OperatorMultiplyByNumber) {
  S21Matrix A(2, 2);
  A(0, 0) = 2;
  S21Matrix B = A * 3;
  EXPECT_EQ(B(0, 0), 6);
}

TEST(OperatorTest, OperatorMultiplyEqualByNumber) {
  S21Matrix A(2, 2);
  A(0, 0) = 2;
  A *= 3;
  EXPECT_EQ(A(0, 0), 6);
}

TEST(OperatorTest, OperatorMulMatrix) {
  S21Matrix A(2, 3);
  S21Matrix B(3, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(0, 2) = 3;
  A(1, 0) = 3;
  A(1, 1) = 2;
  A(1, 2) = 1;
  B(0, 0) = 1;
  B(1, 0) = 2;
  B(2, 0) = 3;
  B(0, 1) = 3;
  B(1, 1) = 2;
  B(2, 1) = 1;
  S21Matrix C = A * B;
  EXPECT_EQ(C(0, 0), 14);
  EXPECT_EQ(C(1, 0), 10);
}

TEST(OperatorTest, OperatorMulEqualMatrix) {
  S21Matrix A(2, 3);
  S21Matrix B(3, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(0, 2) = 3;
  A(1, 0) = 3;
  A(1, 1) = 2;
  A(1, 2) = 1;
  B(0, 0) = 1;
  B(1, 0) = 2;
  B(2, 0) = 3;
  B(0, 1) = 3;
  B(1, 1) = 2;
  B(2, 1) = 1;
  A *= B;
  EXPECT_EQ(A(0, 0), 14);
  EXPECT_EQ(A(1, 0), 10);
}

TEST(OperatorTest, OperatorIndexOutOfRange) {
  S21Matrix A(2, 2);
  EXPECT_THROW(A(5, 5), std::out_of_range);
}

TEST(OperatorTest, OperatorIndex) {
  S21Matrix A(2, 2);
  A(0, 0) = 1;
  EXPECT_EQ(A(0, 0), 1);
}

int main() {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}
