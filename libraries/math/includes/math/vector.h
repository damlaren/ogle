/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file Defines Vector class.
 */

#ifndef LIBRARIES_MATH_INCLUDES_MATH_VECTOR_H_
#define LIBRARIES_MATH_INCLUDES_MATH_VECTOR_H_

#include <assert.h>

#include <algorithm>
#include <array>
#include <iterator>
#include <type_traits>

namespace ogle {

/// Type for indexing into Vector.
using VectorIndex = std::uint64_t;

/**
* @brief Geometric vectors and points.
*/
template <typename T, int K>
class Vector {
 public:
  static_assert(K > 0, "Vectors must be of length > 0.");
  static_assert(std::is_integral<T>::value || std::is_floating_point<T>::value,
                "Vectors must use numeric types.");

  /**
   * @brief Default constructor.
   * Does not init values.
   */
  Vector() noexcept {
  }

  /**
   * @brief Constructor.
   * @param ts Initializer list, or variable-length list of
   *   parameters, to set data. The exact number of arguments
   *   to set the Vector is required.
   */
  template <typename... U>
  Vector(U... ts)
      : data_{ts...} {
    static_assert(sizeof...(U) == K, "Wrong number of arguments.");
  }

  ///@{
  /**
   * @brief Constructor that initializes Vector from array.
   * @param data Array of values copied into vector.
   */
  Vector(const T data[K]) {
    std::copy(data, data + K, std::begin(data_));
  }
  Vector(T data[K]) {
    std::copy(data, data + K, std::begin(data_));
  }
  ///@}

  /**
  * @brief Array subscript operator that allows modification.
  * @param index Index into vector. It is an error to use an
  *     index past its end.
  * @returns Reference to element in Vector.
  */
  T& operator[](VectorIndex index) {
    assert(index < K);
    return data_[index];
  }

  /**
  * @brief Array subscript operator that bars modification.
  * @param index Index into vector. It is an error to use an
  *     index past its end.
  * @returns Copy of element.
  */
  const T operator[](VectorIndex index) const {
    assert(index < K);
    return data_[index];
  }

  /**
  * @brief Zero out the vector.
  */
  void Clear() noexcept {
    data_.fill(0);
  }

  ///@{
  /**
  * @brief Convenience function to access an element.
  * @return Reference to corresponding element of vector.
  */
  template <bool K2 = K >= 1 && K <= 4>
  std::enable_if_t<K2, T&> x() {
    // For some reason, this only compiles when a dependency
    // on a template variable is introduced:
    // http://cboard.cprogramming.com/cplusplus-programming/164150-sfinae-trouble.html
    return data_[0];
  }
  template <bool K2 = K >= 2 && K <= 4>
  std::enable_if_t<K2, T&> y() {
    return data_[1];
  }
  template <bool K2 = K >= 3 && K <= 4>
  std::enable_if_t<K2, T&> z() {
    return data_[2];
  }
  template <bool K2 = K == 4>
  std::enable_if_t<K2, T&> w() {
    return data_[3];
  }
  ///@}

 private:
  std::array<T, K> data_;
};

///@{
/// Shorthand types.
using Vector3f = Vector<float, 3>;
///@}

}  // namespace ogle

#endif  // LIBRARIES_MATH_INCLUDES_MATH_VECTOR_H_
