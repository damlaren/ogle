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

namespace ogle {

/// Type for indexing into a Matrix.
using MatrixIndex = std::uint64_t;

/**
 * @brief An MxN matrix in column-major format.
 *
 * This class is intended to be used with small matrices (up to 4x4).
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
   * @brief Constructor that inits matrix from 2D array.
   * @param[in] data 2D array of values copied into matrix.
   */
  explicit Matrix(const T data[M][N]) {
    std::copy(data[0], data[0] + M * N, std::begin(data_[0]));
  }

  /**
   * @brief Subscript operator that allows modification.
   * @param[in] i Row index, must be < M.
   * @param[in] j Column index, must be < N.
   * @return Reference to element at (i,j).
   */
  T& operator()(MatrixIndex i, MatrixIndex j) {
    assert(i < M && j < N);
    return data_[i][j];
  }

  /**
   * @brief Subscript operator that bars modification.
   * @param[in] i Row index, must be < M.
   * @param[in] j Column index, must be < N.
   * @return Copy of element at (i,j).
   */
  const T operator()(MatrixIndex i, MatrixIndex j) const {
    assert(i < M && j < N);
    return data_[i][j];
  }

  /**
   * @brief Output stream operator, writes matrix in human-readable format.
   * @param[in] os Output stream.
   * @param[in] rhs Matrix to write.
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
   * @param[in] lhs Left operand.
   * @param[in] rhs Right operand.
   * @return New Matrix containing result.
   */
  friend const Matrix operator+(const Matrix& lhs, const Matrix& rhs) {
    return Matrix(lhs) += rhs;
  }

  /**
   * @brief Adds @p rhs to this Matrix.
   * @param[in] rhs Right operand.
   * @return Reference to this Matrix.
   */
  Matrix& operator+=(const Matrix& rhs) {
    BinaryOpInPlace(rhs, std::plus<T>());
    return *this;
  }

  /**
   * @brief Computes negation of @p rhs.
   * @param[in] rhs Right operand.
   * @return New Matrix containing result.
   */
  friend const Matrix operator-(const Matrix& rhs) {
    return Matrix(rhs).UnaryOpInPlace(std::negate<T>());
  }

  /**
   * @brief Computes @p lhs - @p rhs.
   * @param[in] lhs Left operand.
   * @param[in] rhs Right operand.
   * @return New Matrix containing result.
   */
  friend const Matrix operator-(const Matrix& lhs, const Matrix& rhs) {
    return Matrix(lhs) -= rhs;
  }

  /**
   * @brief Subtracts @p rhs from this Matrix.
   * @param[in] rhs Right operand.
   * @return Reference to this Matrix.
   */
  Matrix& operator-=(const Matrix& rhs) {
    BinaryOpInPlace(rhs, std::minus<T>());
    return *this;
  }

  /**
   * @brief Computes multiplication of @p lhs by a scalar.
   * @param[in] lhs Matrix on left.
   * @param[in] factor Scalar to multiply by on right.
   * @return New Matrix containing result.
   */
  friend const Matrix operator*(const Matrix& lhs, const T factor) {
    return Matrix(lhs) *= factor;
  }

  /**
   * @brief Computes multiplication of @p rhs by a scalar.
   * @param[in] factor Scalar to multiply by on left.
   * @param[in] rhs Matrix on right.
   * @return New Matrix containing result.
   */
  friend const Matrix operator*(const T factor, const Matrix& rhs) {
    return Matrix(rhs) *= factor;
  }

  /**
   * @brief Multiplies this Matrix by @p factor.
   * @param[in] factor Scalar to multiply by on right.
   * @return Reference to this Matrix.
   */
  Matrix& operator*=(const T factor) {
    UnaryOpInPlace([factor](T value) { return value * factor; });
    return *this;
  }

  /**
   * @brief Computes Matrix multiplication.
   * @param[in] lhs Left operand, MxN Matrix.
   * @param[in] rhs Right operand, NxO Matrix.
   * @return New Matrix containing result.
   */
  template<MatrixIndex O>
  friend const Matrix<T, M, O> operator*(const Matrix<T, M, N>& lhs,
                                         const Matrix<T, N, O>& rhs) {
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
   * @param[in] lhs Matrix on left.
   * @param[in] factor Factor to divide by.
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
   * @param[in] factor Factor to divide by.
   * @return
   */
  Matrix& operator/=(const T factor) {
    UnaryOpInPlace([factor](T value){ return value / factor; });
    return *this;
  }

  /**
   * @brief Sets all data in Matrix to @p value.
   * @param[in] value
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

  // TODO(damlaren): inverse 2x2, 3x3, maybe 4x4

 private:
  /**
   * @brief Performs unary operation on this Matrix.
   * @param[in] op Operation to perform.
   * @return Reference to this Matrix.
   */
  template <typename UnaryOperator>
  Matrix& UnaryOpInPlace(UnaryOperator op) {
    std::transform(data_[0], data_[0] + M * N, data_[0], op);
    return *this;
  }

  /**
   * @brief Performs binary operation on this Matrix.
   * @param[in] rhs Other Matrix to use in operation.
   * @param[in] op Operation to perform.
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

}  // namespace ogle

#endif  // LIBRARIES_MATH_INCLUDES_MATH_MATRIX_H_
