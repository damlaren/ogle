/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file Defines Matrix.
 */

#ifndef LIBRARIES_MATH_INCLUDES_MATH_MATRIX_H_
#define LIBRARIES_MATH_INCLUDES_MATH_MATRIX_H_

#include <assert.h>
#include <algorithm>
#include <array>
#include <functional>
#include <iostream>
#include <iterator>
#include <type_traits>
#include "math/vector.h"

namespace ogle {

/// Type for indexing into a Matrix.
using MatrixIndex = std::uint64_t;

/**
 * @namespace Namespace to contain helper functions for Matrix.
 *
 * These are not intended for use outside that class.
 */
namespace matrix_helpers {

///{@
/**
 * @brief Helper for computing Matrix determinant.
 *
 * @param data Raw data from a Matrix.
 * @return Determinant value.
 */
template<typename T>
const T Determinant(const T data[1][1]) {
  return data[0][0];
}

template<typename T>
const T Determinant(const T data[2][2]) {
  return data[0][0] * data[1][1] - data[0][1] * data[1][0];
}

template<typename T>
const T Determinant(const T data[3][3]) {
  return data[0][0] * data[1][1] * data[2][2] +
         data[0][1] * data[1][2] * data[2][0] +
         data[0][2] * data[1][0] * data[2][1] -
         data[0][0] * data[1][2] * data[2][1] -
         data[0][1] * data[1][0] * data[2][2] -
         data[0][2] * data[1][1] * data[2][0];
}

template<typename T>
const T Determinant(const T data[4][4]) {
  // Thanks to:
  // http://www.euclideanspace.com/maths/algebra/matrix/functions/determinant/fourD/index.htm  // NOLINT
  return data[0][3] * data[1][2] * data[2][1] * data[3][0] -
         data[0][2] * data[1][3] * data[2][1] * data[3][0] -
         data[0][3] * data[1][1] * data[2][2] * data[3][0] +
         data[0][1] * data[1][3] * data[2][2] * data[3][0] +
         data[0][2] * data[1][1] * data[2][3] * data[3][0] -
         data[0][1] * data[1][2] * data[2][3] * data[3][0] -
         data[0][3] * data[1][2] * data[2][0] * data[3][1] +
         data[0][2] * data[1][3] * data[2][0] * data[3][1] +
         data[0][3] * data[1][0] * data[2][2] * data[3][1] -
         data[0][0] * data[1][3] * data[2][2] * data[3][1] -
         data[0][2] * data[1][0] * data[2][3] * data[3][1] +
         data[0][0] * data[1][2] * data[2][3] * data[3][1] +
         data[0][3] * data[1][1] * data[2][0] * data[3][2] -
         data[0][1] * data[1][3] * data[2][0] * data[3][2] -
         data[0][3] * data[1][0] * data[2][1] * data[3][2] +
         data[0][0] * data[1][3] * data[2][1] * data[3][2] +
         data[0][1] * data[1][0] * data[2][3] * data[3][2] -
         data[0][0] * data[1][1] * data[2][3] * data[3][2] -
         data[0][2] * data[1][1] * data[2][0] * data[3][3] +
         data[0][1] * data[1][2] * data[2][0] * data[3][3] +
         data[0][2] * data[1][0] * data[2][1] * data[3][3] -
         data[0][0] * data[1][2] * data[2][1] * data[3][3] -
         data[0][1] * data[1][0] * data[2][2] * data[3][3] +
         data[0][0] * data[1][1] * data[2][2] * data[3][3];
}
///@}

///{@
/**
 * @brief Helper function for computing Inverse.
 * @param data Raw data from Matrix for which to compute inverse.
 * @param[out] result Raw data from Matrix which will contain result.
 */
template<typename T>
void InverseHelper(const T data[1][1], T result[1][1]) {
  result[0][0] = static_cast<T>(1);
}

template<typename T>
void InverseHelper(const T data[2][2], T result[2][2]) {
  result[0][0] = data[1][1];
  result[0][1] = -data[0][1];
  result[1][0] = -data[1][0];
  result[1][1] = data[0][0];
}

template<typename T>
void InverseHelper(const T data[3][3], T result[3][3]) {
  result[0][0] = data[1][1] * data[2][2] - data[1][2] * data[2][1];
  result[0][1] = data[0][2] * data[2][1] - data[0][1] * data[2][2];
  result[0][2] = data[0][1] * data[1][2] - data[0][2] * data[1][1];
  result[1][0] = data[1][2] * data[2][0] - data[1][0] * data[2][2];
  result[1][1] = data[0][0] * data[2][2] - data[0][2] * data[2][0];
  result[1][2] = data[0][2] * data[1][0] - data[0][0] * data[1][2];
  result[2][0] = data[1][0] * data[2][1] - data[1][1] * data[2][0];
  result[2][1] = data[0][1] * data[2][0] - data[0][0] * data[2][1];
  result[2][2] = data[0][0] * data[1][1] - data[0][1] * data[1][0];
}

template<typename T>
void InverseHelper(const T data[4][4], T result[4][4]) {
  result[0][0] = data[1][2] * data[2][3] * data[3][1] -
                 data[1][3] * data[2][2] * data[3][1] +
                 data[1][3] * data[2][1] * data[3][2] -
                 data[1][1] * data[2][3] * data[3][2] -
                 data[1][2] * data[2][1] * data[3][3] +
                 data[1][1] * data[2][2] * data[3][3];
  result[0][1] = data[0][3] * data[2][2] * data[3][1] -
                 data[0][2] * data[2][3] * data[3][1] -
                 data[0][3] * data[2][1] * data[3][2] +
                 data[0][1] * data[2][3] * data[3][2] +
                 data[0][2] * data[2][1] * data[3][3] -
                 data[0][1] * data[2][2] * data[3][3];
  result[0][2] = data[0][2] * data[1][3] * data[3][1] -
                 data[0][3] * data[1][2] * data[3][1] +
                 data[0][3] * data[1][1] * data[3][2] -
                 data[0][1] * data[1][3] * data[3][2] -
                 data[0][2] * data[1][1] * data[3][3] +
                 data[0][1] * data[1][2] * data[3][3];
  result[0][3] = data[0][3] * data[1][2] * data[2][1] -
                 data[0][2] * data[1][3] * data[2][1] -
                 data[0][3] * data[1][1] * data[2][2] +
                 data[0][1] * data[1][3] * data[2][2] +
                 data[0][2] * data[1][1] * data[2][3] -
                 data[0][1] * data[1][2] * data[2][3];
  result[1][0] = data[1][3] * data[2][2] * data[3][0] -
                 data[1][2] * data[2][3] * data[3][0] -
                 data[1][3] * data[2][0] * data[3][2] +
                 data[1][0] * data[2][3] * data[3][2] +
                 data[1][2] * data[2][0] * data[3][3] -
                 data[1][0] * data[2][2] * data[3][3];
  result[1][1] = data[0][2] * data[2][3] * data[3][0] -
                 data[0][3] * data[2][2] * data[3][0] +
                 data[0][3] * data[2][0] * data[3][2] -
                 data[0][0] * data[2][3] * data[3][2] -
                 data[0][2] * data[2][0] * data[3][3] +
                 data[0][0] * data[2][2] * data[3][3];
  result[1][2] = data[0][3] * data[1][2] * data[3][0] -
                 data[0][2] * data[1][3] * data[3][0] -
                 data[0][3] * data[1][0] * data[3][2] +
                 data[0][0] * data[1][3] * data[3][2] +
                 data[0][2] * data[1][0] * data[3][3] -
                 data[0][0] * data[1][2] * data[3][3];
  result[1][3] = data[0][2] * data[1][3] * data[2][0] -
                 data[0][3] * data[1][2] * data[2][0] +
                 data[0][3] * data[1][0] * data[2][2] -
                 data[0][0] * data[1][3] * data[2][2] -
                 data[0][2] * data[1][0] * data[2][3] +
                 data[0][0] * data[1][2] * data[2][3];
  result[2][0] = data[1][1] * data[2][3] * data[3][0] -
                 data[1][3] * data[2][1] * data[3][0] +
                 data[1][3] * data[2][0] * data[3][1] -
                 data[1][0] * data[2][3] * data[3][1] -
                 data[1][1] * data[2][0] * data[3][3] +
                 data[1][0] * data[2][1] * data[3][3];
  result[2][1] = data[0][3] * data[2][1] * data[3][0] -
                 data[0][1] * data[2][3] * data[3][0] -
                 data[0][3] * data[2][0] * data[3][1] +
                 data[0][0] * data[2][3] * data[3][1] +
                 data[0][1] * data[2][0] * data[3][3] -
                 data[0][0] * data[2][1] * data[3][3];
  result[2][2] = data[0][1] * data[1][3] * data[3][0] -
                 data[0][3] * data[1][1] * data[3][0] +
                 data[0][3] * data[1][0] * data[3][1] -
                 data[0][0] * data[1][3] * data[3][1] -
                 data[0][1] * data[1][0] * data[3][3] +
                 data[0][0] * data[1][1] * data[3][3];
  result[2][3] = data[0][3] * data[1][1] * data[2][0] -
                 data[0][1] * data[1][3] * data[2][0] -
                 data[0][3] * data[1][0] * data[2][1] +
                 data[0][0] * data[1][3] * data[2][1] +
                 data[0][1] * data[1][0] * data[2][3] -
                 data[0][0] * data[1][1] * data[2][3];
  result[3][0] = data[1][2] * data[2][1] * data[3][0] -
                 data[1][1] * data[2][2] * data[3][0] -
                 data[1][2] * data[2][0] * data[3][1] +
                 data[1][0] * data[2][2] * data[3][1] +
                 data[1][1] * data[2][0] * data[3][2] -
                 data[1][0] * data[2][1] * data[3][2];
  result[3][1] = data[0][1] * data[2][2] * data[3][0] -
                 data[0][2] * data[2][1] * data[3][0] +
                 data[0][2] * data[2][0] * data[3][1] -
                 data[0][0] * data[2][2] * data[3][1] -
                 data[0][1] * data[2][0] * data[3][2] +
                 data[0][0] * data[2][1] * data[3][2];
  result[3][2] = data[0][2] * data[1][1] * data[3][0] -
                 data[0][1] * data[1][2] * data[3][0] -
                 data[0][2] * data[1][0] * data[3][1] +
                 data[0][0] * data[1][2] * data[3][1] +
                 data[0][1] * data[1][0] * data[3][2] -
                 data[0][0] * data[1][1] * data[3][2];
  result[3][3] = data[0][1] * data[1][2] * data[2][0] -
                 data[0][2] * data[1][1] * data[2][0] +
                 data[0][2] * data[1][0] * data[2][1] -
                 data[0][0] * data[1][2] * data[2][1] -
                 data[0][1] * data[1][0] * data[2][2] +
                 data[0][0] * data[1][1] * data[2][2];
}

///@}

}  // namespace matrix_helpers

/**
 * @brief An MxN matrix.
 *
 * This class is intended to be used with small matrices (up to 4x4).
 * Data is stored in row-major format (row by row in an array).
 */
template<typename T, MatrixIndex M, MatrixIndex N>
class Matrix {
 public:
  static_assert(M > 0 && N > 0, "Matrix dimensions must be > 0.");
  static_assert(std::is_integral<T>::value || std::is_floating_point<T>::value,
                "Matrix must use numeric type.");

  // TODO(damlaren): may want to introduce a more flexible Matrix class later,
  //     one that allows variation in # of rows and columns.

  /**
   * @brief Default constructor. Does not init values.
   */
  Matrix() noexcept {
  }

  /**
   * @brief Constructor that inits Matrix from 2D array.
   * @param data MxN 2D array of values to copy in.
   */
  Matrix(const T data[M][N]) {  // NOLINT
    std::copy(data[0], data[0] + M * N, data_[0]);
  }

  /**
   * @brief Constructor that inits Matrix from 1D array.
   *
   * @param data 1D array of values copied into matrix.
   */
  Matrix(const T data[M * N]) {  // NOLINT
    std::copy(data, data + M * N, data_[0]);
  }

  /**
   * @brief Constructor that takes list of data values.
   * @param ts Initializer list, or variable-length list of parameters,
   *     to set data. The exact number of arguments to set the Matrix is
   *     required. Values in the initializer list set Matrix values row by row.
   */
  template <typename... U>
  Matrix(U... ts) // NOLINT
      : data_{ts...} {
    // TODO(damlaren): It seems like a small miracle that initializing a 2D
    // array in this way from an initializer list works?
    static_assert(sizeof...(U) == M * N, "Wrong number of arguments.");
  }

  /**
   * @brief Subscript operator that allows modification.
   * @param i Row index, must be < M.
   * @param j Column index, must be < N.
   * @return Reference to element at (i,j).
   */
  T& operator()(MatrixIndex i, MatrixIndex j) {
    assert(i < M && j < N);
    return data_[i][j];
  }

  /**
   * @brief Subscript operator that bars modification.
   * @param i Row index, must be < M.
   * @param j Column index, must be < N.
   * @return Copy of element at (i,j).
   */
  const T operator()(MatrixIndex i, MatrixIndex j) const {
    assert(i < M && j < N);
    return data_[i][j];
  }

  /**
   * @brief Output stream operator, writes matrix in human-readable format.
   * @param os Output stream.
   * @param rhs Matrix to write.
   * @return Reference to @p os.
   */
  friend std::ostream& operator<<(std::ostream& os, const Matrix& rhs) {
    for (MatrixIndex i = 0; i < M; i++) {
      if (i == 0) {
        os << "[";
      } else {
        os << " ";
      }
      os << "[";
      os << rhs.data_[i][0];
      for (MatrixIndex j = 1; j < N; j++) {
        os << ", " << rhs.data_[i][j];
      }
      os << "]";
      if (i != M - 1) {
        os << std::endl;
      }
    }
    os << "]";
    return os;
  }

  /**
   * @brief Computes @p lhs + @p rhs.
   * @param lhs Left operand.
   * @param rhs Right operand.
   * @return New Matrix containing result.
   */
  friend const Matrix operator+(const Matrix& lhs,
                                const Matrix& rhs) noexcept {
    return Matrix(lhs) += rhs;
  }

  /**
   * @brief Adds @p rhs to this Matrix.
   * @param rhs Right operand.
   * @return Reference to this Matrix.
   */
  Matrix& operator+=(const Matrix& rhs) noexcept {
    BinaryOpInPlace(rhs, std::plus<T>());
    return *this;
  }

  /**
   * @brief Computes negation of @p rhs.
   * @param rhs Right operand.
   * @return New Matrix containing result.
   */
  friend const Matrix operator-(const Matrix& rhs) noexcept {
    return Matrix(rhs).UnaryOpInPlace(std::negate<T>());
  }

  /**
   * @brief Computes @p lhs - @p rhs.
   * @param lhs Left operand.
   * @param rhs Right operand.
   * @return New Matrix containing result.
   */
  friend const Matrix operator-(const Matrix& lhs,
                                const Matrix& rhs) noexcept {
    return Matrix(lhs) -= rhs;
  }

  /**
   * @brief Subtracts @p rhs from this Matrix.
   * @param rhs Right operand.
   * @return Reference to this Matrix.
   */
  Matrix& operator-=(const Matrix& rhs) noexcept {
    BinaryOpInPlace(rhs, std::minus<T>());
    return *this;
  }

  /**
   * @brief Computes multiplication of @p lhs by a scalar.
   * @param lhs Matrix on left.
   * @param factor Scalar to multiply by on right.
   * @return New Matrix containing result.
   */
  friend const Matrix operator*(const Matrix& lhs,
                                const T factor) noexcept {
    return Matrix(lhs) *= factor;
  }

  /**
   * @brief Computes multiplication of @p rhs by a scalar.
   * @param factor Scalar to multiply by on left.
   * @param rhs Matrix on right.
   * @return New Matrix containing result.
   */
  friend const Matrix operator*(const T factor, const Matrix& rhs) noexcept {
    return Matrix(rhs) *= factor;
  }

  /**
   * @brief Multiplies this Matrix by @p factor.
   * @param factor Scalar to multiply by on right.
   * @return Reference to this Matrix.
   */
  Matrix& operator*=(const T factor) noexcept {
    UnaryOpInPlace([factor](T value) { return value * factor; });
    return *this;
  }

  /**
   * @brief Computes Matrix multiplication.
   * @param lhs Left operand, MxN Matrix.
   * @param rhs Right operand, NxO Matrix.
   * @return New Matrix containing result.
   */
  template <MatrixIndex O>
  friend const Matrix<T, M, O> operator*(const Matrix<T, M, N>& lhs,
                                         const Matrix<T, N, O>& rhs) noexcept {
    Matrix<T, M, O> result;
    for (MatrixIndex i = 0; i < M; i++) {
      for (MatrixIndex j = 0; j < O; j++) {
        T sum = 0;
        for (MatrixIndex k = 0; k < N; k++) {
          sum += lhs.data_[i][k] * rhs(k, j);
        }
        result(i, j) = sum;
      }
    }
    return result;
  }

  /**
   * @brief Computes division of @p lhs by @p factor.
   *
   * Division by 0 is performed without any precautions.
   *
   * @param lhs Matrix on left.
   * @param factor Factor to divide by.
   * @return New Matrix containing result.
   */
  friend const Matrix operator/(const Matrix& lhs, const T factor) {
    return Matrix(lhs) /= factor;
  }

  /**
   * @brief Divides this Matrix by @p factor.
   *
   * Division by 0 is performed without any precautions
   *
   * @param factor Factor to divide by.
   * @return
   */
  Matrix& operator/=(const T factor) {
    UnaryOpInPlace([factor](T value){ return value / factor; });
    return *this;
  }

  /**
   * Returns value at index.
   * @return Value at @p (i,j).
   */
  const T At(MatrixIndex i, MatrixIndex j) const {
    return operator()(i, j);
  }

  /**
   * @brief Sets all data in Matrix to @p value.
   * @param value
   */
  void Set(T value) noexcept {
    std::fill(data_[0], data_[0] + M * N, value);
  }

  /**
   * @brief Zeroes out the matrix.
   */
  void Clear() noexcept {
    Set(static_cast<T>(0));
  }

  /**
   * @brief Computes transpose of this Matrix.
   * @return New Matrix containing result.
   */
  const Matrix<T, N, M> Transpose() const noexcept {
    Matrix<T, N, M> result;
    for (MatrixIndex i = 0; i < M; i++) {
      for (MatrixIndex j = 0; j < N; j++) {
        result(j, i) = data_[i][j];
      }
    }
    return result;
  }

  /**
   * @brief Computes identity Matrix. Only allowed for square Matrix.
   * @return New Matrix containing result.
   */
  static const Matrix Identity() noexcept {
    static_assert(M == N,
                  "Identity can only be constructed for square Matrix.");
    Matrix result;
    result.Clear();
    for (MatrixIndex i = 0; i < M; i++) {
      result.data_[i][i] = 1.0f;
    }
    return result;
  }

  /**
   * @brief Compute determinant of this Matrix, if it is square and up to 4x4.
   * @return Determinant value.
   */
  const T Determinant() const noexcept {
    static_assert(M == N,
                  "Determinant only exists for square Matrix. AFAIK.");
    static_assert(M <= 4, "Determinant only computed up to 4x4 Matrix.");
    return matrix_helpers::Determinant(data_);
  }

  /**
   * @brief Compute inverse of this Matrix.
   * @param result Matrix to contain resulting inverse.
   *
   * Only possible if it is square, invertible, and up to 4x4 in size.
   *
   * @return Whether the inverse could be computed.
   */
  const bool Inverse(Matrix* result) const {
    static_assert(M == N, "Inverse can only be computed for square Matrix.");
    static_assert(M <= 4, "Inverse can only be computed for Matrix up to 4x4.");

    // TODO(damlaren): Define an EPSILON somewhere.
    const T determinant = Determinant();
    if (fabs(static_cast<float>(determinant)) < 1e-5) {
      return false;
    }

    matrix_helpers::InverseHelper(data_, result->data_);
    *result /= determinant;

    return true;
  }

  /**
   * @brief Build an Mx1 Matrix from M-Vector @p v.
   * @param v
   * @return New Matrix with result.
   */
  static const Matrix<T, M, 1> AsMatrix(const Vector<T, M>& v) noexcept {
    Matrix<T, M, 1> result;
    for (MatrixIndex i = 0; i < M; i++) {
      result.data_[i][0] = v(i);
    }
    return result;
  }

  /**
   * @brief Build an M-Vector from an Mx1 Matrix.
   * @return New Vector with result.
   */
  const Vector<T, M> AsVector() const noexcept {
    static_assert(N == 1,
                  "Can only construct Vector from Matrix with 1 column.");
    Vector<T, M> result;
    for (MatrixIndex i = 0; i < M; i++) {
      result(i) = data_[i][0];
    }
    return result;
  }

  /**
   * @brief Provides a pointer to raw data (for use in graphics APIs).
   * @return Pointer to matrix data.
   */
  const T* data() const noexcept {
    return static_cast<const T*>(data_[0]);
  }

 private:
  /**
   * @brief Performs unary operation on this Matrix.
   * @param op Operation to perform.
   * @return Reference to this Matrix.
   */
  template <typename UnaryOperator>
  Matrix& UnaryOpInPlace(UnaryOperator op) {
    std::transform(data_[0], data_[0] + M * N, data_[0], op);
    return *this;
  }

  /**
   * @brief Performs binary operation on this Matrix.
   * @param rhs Other Matrix to use in operation.
   * @param op Operation to perform.
   * @return Reference to this Matrix.
   */
  template <typename BinaryOperator>
  Matrix& BinaryOpInPlace(const Matrix& rhs, BinaryOperator op) {
    std::transform(data_[0], data_[0] + M * N, rhs.data_[0], data_[0], op);
    return *this;
  }

  /// Data stored in matrix.
  T data_[M][N];
};

using Matrix22f = Matrix<float, 2, 2>;
using Matrix33f = Matrix<float, 3, 3>;
using Matrix44f = Matrix<float, 4, 4>;
using Matrix21f = Matrix<float, 2, 1>;
using Matrix31f = Matrix<float, 3, 1>;
using Matrix41f = Matrix<float, 4, 1>;

}  // namespace ogle

#endif  // LIBRARIES_MATH_INCLUDES_MATH_MATRIX_H_
