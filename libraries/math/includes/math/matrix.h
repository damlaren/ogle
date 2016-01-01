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
#include <iostream>
#include <iterator>
#include <type_traits>

namespace ogle {

/**
 * @brief An MxN matrix in column-major format.
 *
 * This class is intended to be used with small matrices (up to 4x4).
 */
template<typename T, int M, int N>
class Matrix {
 public:
  static_assert(M > 0 && N > 0, "Matrix dimensions must be > 0.");
  static_assert(std::is_integral<T>::value || std::is_floating_point<T>::value,
                "Matrix must use numeric type.");

  /// Type for indexing into a Matrix.
  using MatrixIndex = std::uint64_t;

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
    for (int i = 0; i < M; i++) {
      os << "[";
      os << rhs.data_[i][0];
      for (int j = 1; j < N; j++) {
        os << ", " << rhs.data_[i][j];
      }
      os << "]";
      if (i != M - 1) {
        os << std::endl;
      }
    }
  }

  /**
   * @brief Computes @p lhs + @p rhs.
   * @param[in] lhs Left operand.
   * @param[in] rhs Right operand.
   * @return A new Matrix containing the result.
   */
  friend const Matrix operator+(const Matrix& lhs, const Matrix& rhs) {
    return Matrix(lhs) += rhs;
  }

  /**
   * @brief Adds @p rhs to this Matrix.
   * @param rhs Right operand.
   * @return Reference to this Matrix.
   */
  Matrix& operator+=(const Matrix& rhs) {
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

 private:
  /// Data stored in matrix.
  T data_[M][N];
};

}  // namespace ogle

#endif  // LIBRARIES_MATH_INCLUDES_MATH_MATRIX_H_
