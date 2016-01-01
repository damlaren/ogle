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
#include <iterator>
#include <type_traits>

namespace ogle {

/**
 * @brief An MxN matrix in column-major format.
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
   * @brief Sets all data in Matrix to #value.
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
