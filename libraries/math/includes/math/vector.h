/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file Defines Vector.
 */

#ifndef LIBRARIES_MATH_INCLUDES_MATH_VECTOR_H_
#define LIBRARIES_MATH_INCLUDES_MATH_VECTOR_H_

#include <assert.h>
#include <algorithm>
#include <array>
#include <functional>
#include <iterator>
#include <numeric>
#include <type_traits>

namespace ogle {

/**
* @brief Geometric vectors and points of length K.
*/
template <typename T, int K>
class Vector {
 public:
  static_assert(K > 0, "Vector must be of length > 0.");
  static_assert(std::is_integral<T>::value || std::is_floating_point<T>::value,
                "Vector must use numeric type.");

  /// Type for indexing into Vector.
  using VectorIndex = std::uint64_t;

  /**
   * @brief Default constructor. Does not init values.
   */
  Vector() noexcept {
  }

  /**
   * @brief Constructor that takes list of data values.
   * @param[in] ts Initializer list, or variable-length list of
   *     parameters, to set data. The exact number of arguments
   *     to set the Vector is required.
   */
  template <typename... U>
  Vector(U... ts)  // NOLINT
      : data_{ts...} {
    static_assert(sizeof...(U) == K, "Wrong number of arguments.");
  }

  ///@{
  /**
   * @brief Constructor that initializes Vector from array.
   * @param[in] data Array of values copied into vector.
   */
  explicit Vector(const T data[K]) {
    std::copy(data, data + K, std::begin(data_));
  }
  explicit Vector(T data[K]) {
    std::copy(data, data + K, std::begin(data_));
  }
  ///@}

  /**
  * @brief Subscript operator that allows modification.
  * @param[in] index Index into vector. It is an error to use an
  *     index past its end.
  * @returns Reference to element in Vector.
  */
  T& operator()(VectorIndex index) {
    assert(index < K);
    return data_[index];
  }

  /**
  * @brief Subscript operator that bars modification.
  * @param[in] index Index into vector. It is an error to use an
  *     index past its end.
  * @returns Copy of element.
  */
  const T operator()(VectorIndex index) const {
    assert(index < K);
    return data_[index];
  }

  /**
   * @brief Output stream operator, writes in human-readable format.
   * @param[in,out] os Output stream.
   * @param[in] rhs Vector to write.
   * @return Reference to #os.
   */
  friend std::ostream& operator<<(std::ostream& os, const Vector& rhs) {
    os << "(" << rhs.data_[0];
    std::for_each(rhs.data_.begin() + 1, rhs.data_.end(),
                  [&os](T value){ os << ", " << value; });
    os << ")";
    return os;
  }

  /**
   * @brief Computes #lhs + #rhs.
   * @param[in] lhs Left operand.
   * @param[in] rhs Right operand.
   * @return New Vector containing result.
   */
  friend const Vector operator+(const Vector& lhs, const Vector& rhs) {
    return Vector(lhs) += rhs;
  }

  /**
   * @brief Adds #rhs to this Vector.
   * @param[in] rhs Right operand.
   * @return Reference to this Vector.
   */
  Vector& operator+=(const Vector& rhs) {
    return BinaryOpInPlace(rhs, std::plus<T>());
  }

  /**
   * @brief Computes negation of #v.
   * @param[in] v Right operand.
   * @return New Vector containing result.
   */
  friend const Vector operator-(const Vector& v) {
    return Vector(v).UnaryOpInPlace(std::negate<T>());
  }

  /**
   * @brief Computes #lhs - #rhs.
   * @param[in] lhs Left operand.
   * @param[in] rhs Right Operand.
   * @return New Vector containing result.
   */
  friend const Vector operator-(const Vector& lhs, const Vector& rhs) {
    return Vector(lhs) -= rhs;
  }

  /**
   * @brief Subtracts #rhs from this Vector.
   * @param[in] rhs Right operand.
   * @return Reference to this Vector.
   */
  Vector& operator-=(const Vector& rhs) {
    return BinaryOpInPlace(rhs, std::minus<T>());
  }

  /**
   * @brief Computes dot product of #lhs and #rhs.
   * @param[in] lhs Left operand.
   * @param[in] rhs Right operand.
   * @return The product.
   */
  friend const T operator*(const Vector& lhs, const Vector& rhs) {
    Vector temp(lhs);
    temp.BinaryOpInPlace(rhs, std::multiplies<T>());
    return std::accumulate(temp.data_.begin(), temp.data_.end(), 0);
  }

  /**
   * @brief Computes #lhs scaled by #factor.
   * @param[in] lhs Vector to scale.
   * @param[in] factor Scale factor.
   * @return New Vector containing result.
   */
  friend const Vector operator*(const Vector& lhs, const T factor) {
    return Vector(lhs) *= factor;
  }

  /**
   * @brief Computes #rhs scaled by #factor.
   * @param[in] factor Scale factor.
   * @param[in] rhs Vector to scale.
   * @return New Vector containing result.
   */
  friend const Vector operator*(const T factor, const Vector& rhs) {
    return Vector(rhs) *= factor;
  }

  /**
   * @brief Scales this Vector in place.
   * @param[in] factor Scale factor.
   * @return Reference to this Vector.
   */
  Vector& operator*=(const T factor) {
    return UnaryOpInPlace([factor](T value) { return value * factor; });
  }

  /**
   * @brief Computes #lhs divided by #factor.
   * @param[in] lhs Vector to divide.
   * @param[in] factor Factor to divide by.
   * @return New Vector containing result.
   */
  friend const Vector operator/(const Vector& lhs, const T factor) {
    return Vector(lhs) /= factor;
  }

  /**
   * @brief Divides this Vector in place.
   * @param[in] factor Factor to divide by.
   * @return Reference to this Vector.
   */
  Vector& operator/=(const T factor) {
    return UnaryOpInPlace([factor](T value) { return value / factor; });
  }

  /**
   * @brief Computes dot product of this Vector with #rhs.
   * @param[in] rhs Right operand.
   * @return The product.
   */
  const T Dot(const Vector& rhs) const {
    return (*this) * rhs;
  }

  /**
   * @brief Sets all data in Vector to #value.
   * @param[in] value
   */
  void Set(T value) noexcept {
    data_.fill(value);
  }

  /**
  * @brief Zeros out the vector.
  */
  void Clear() noexcept {
    Set(static_cast<T>(0));
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
  /**
   * @brief Performs unary operation on this Vector.
   * @param[in] op Operation to perform.
   * @return Reference to this Vector.
   */
  template <typename UnaryOperator>
  Vector& UnaryOpInPlace(UnaryOperator op) {
    std::transform(data_.begin(), data_.end(), data_.begin(), op);
    return *this;
  }

  /**
   * @brief Performs binary operation on this Vector.
   * @param[in] rhs Other Vector to use in operation.
   * @param[in] op Operation to perform.
   * @return Reference to this Vector.
   */
  template <typename BinaryOperator>
  Vector& BinaryOpInPlace(const Vector& rhs, BinaryOperator op) {
    std::transform(data_.begin(), data_.end(), rhs.data_.begin(),
                   data_.begin(), op);
    return *this;
  }

  /// Values stored in vector.
  std::array<T, K> data_;
};

///@{
/// Shorthand types.
using Vector3f = Vector<float, 3>;
///@}

}  // namespace ogle

#endif  // LIBRARIES_MATH_INCLUDES_MATH_VECTOR_H_
