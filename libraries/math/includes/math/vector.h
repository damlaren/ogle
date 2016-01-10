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
#include <iostream>
#include <iterator>
#include <numeric>
#include <type_traits>

namespace ogle {

/// Type for indexing into Vector.
using VectorIndex = std::uint64_t;

/**
* @brief Geometric vectors and points with K elements.
*
* This class represents column vectors which multiply a matrix to their left.
*/
template <typename T, VectorIndex K>
class Vector {
 public:
  // Declare friend classes so Shrunk & Expanded can access data!
  friend class Vector<T, K - 1>;
  friend class Vector<T, K + 1>;

  static_assert(K > 0, "Vector have at least 1 element.");
  static_assert(std::is_integral<T>::value || std::is_floating_point<T>::value,
                "Vector must use numeric type.");

  /**
   * @brief Default constructor. Does not init values.
   */
  Vector() noexcept {
  }

  /**
   * @brief Constructor that takes list of values.
   * @param[in] ts Initializer list, or variable-length list of
   *     parameters, to set data. The exact number of arguments
   *     to set the Vector is required.
   */
  template <typename... U>
  Vector(U... ts)  // NOLINT
      : data_{ts...} {
    static_assert(sizeof...(U) == K, "Wrong number of arguments.");
  }

  /**
   * @brief Constructor that initializes Vector from array.
   * @param[in] data Array of values copied into vector.
   */
  explicit Vector(const T data[K]) {
    std::copy(data, data + K, data_.begin());
  }

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
   * @brief Copy assignment operator.
   * @param[in] rhs Vector to copy data from.
   * @return Reference to this Vector.
   */
  Vector& operator=(const Vector& rhs) noexcept {
    std::copy(rhs.data_.begin(), rhs.data_.end(), data_.begin());
  }

  /**
   * @brief Equality operator.
   * @param[in] lhs Left operand.
   * @param[in] rhs Right operand.
   * @return true if both Vectors have exactly the same values.
   */
  friend const bool operator==(const Vector& lhs,
                               const Vector& rhs) noexcept {
    return lhs.data_ == rhs.data_;
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
   * @return Reference to @p os.
   */
  friend std::ostream& operator<<(std::ostream& os, const Vector& rhs) {
    os << "(" << rhs.data_[0];
    std::for_each(rhs.data_.begin() + 1, rhs.data_.end(),
                  [&os](T value){ os << ", " << value; });
    os << ")";
    return os;
  }

  /**
   * @brief Computes @p lhs + @p rhs.
   * @param[in] lhs Left operand.
   * @param[in] rhs Right operand.
   * @return New Vector containing result.
   */
  friend const Vector operator+(const Vector& lhs, const Vector& rhs) noexcept {
    return Vector(lhs) += rhs;
  }

  /**
   * @brief Adds @p rhs to this Vector.
   * @param[in] rhs Right operand.
   * @return Reference to this Vector.
   */
  Vector& operator+=(const Vector& rhs) noexcept {
    return BinaryOpInPlace(rhs, std::plus<T>());
  }

  /**
   * @brief Computes negation of @p v.
   * @param[in] v Right operand.
   * @return New Vector containing result.
   */
  friend const Vector operator-(const Vector& v) noexcept {
    return Vector(v).UnaryOpInPlace(std::negate<T>());
  }

  /**
   * @brief Computes @p lhs - @p rhs.
   * @param[in] lhs Left operand.
   * @param[in] rhs Right Operand.
   * @return New Vector containing result.
   */
  friend const Vector operator-(const Vector& lhs, const Vector& rhs) noexcept {
    return Vector(lhs) -= rhs;
  }

  /**
   * @brief Subtracts @p rhs from this Vector.
   * @param[in] rhs Right operand.
   * @return Reference to this Vector.
   */
  Vector& operator-=(const Vector& rhs) noexcept {
    return BinaryOpInPlace(rhs, std::minus<T>());
  }

  /**
   * @brief Computes dot product of @p lhs and @p rhs.
   * @param[in] lhs Left operand.
   * @param[in] rhs Right operand.
   * @return The product.
   */
  friend const T operator*(const Vector& lhs, const Vector& rhs) noexcept {
    Vector temp(lhs);
    temp.BinaryOpInPlace(rhs, std::multiplies<T>());
    return std::accumulate(temp.data_.begin(), temp.data_.end(), 0);
  }

  /**
   * @brief Computes @p lhs scaled by @p factor.
   * @param[in] lhs Vector to scale.
   * @param[in] factor Scale factor.
   * @return New Vector containing result.
   */
  friend const Vector operator*(const Vector& lhs, const T factor) noexcept {
    return Vector(lhs) *= factor;
  }

  /**
   * @brief Computes @p rhs scaled by @p factor.
   * @param[in] factor Scale factor.
   * @param[in] rhs Vector to scale.
   * @return New Vector containing result.
   */
  friend const Vector operator*(const T factor, const Vector& rhs) noexcept {
    return Vector(rhs) *= factor;
  }

  /**
   * @brief Scales this Vector in place.
   * @param[in] factor Scale factor.
   * @return Reference to this Vector.
   */
  Vector& operator*=(const T factor) noexcept {
    return UnaryOpInPlace([factor](T value) { return value * factor; });
  }

  /**
   * @brief Computes @p lhs divided by @p factor.
   *
   * Division is done even if @p factor is 0. No special action is taken.
   *
   * @param[in] lhs Vector to divide.
   * @param[in] factor Factor to divide by.
   * @return New Vector containing result.
   */
  friend const Vector operator/(const Vector& lhs, const T factor) {
    return Vector(lhs) /= factor;
  }

  /**
   * @brief Divides this Vector in place.
   *
   * Division is done even if @p factor is 0. No special action is taken.
   *
   * @param[in] factor Factor to divide by.
   * @return Reference to this Vector.
   */
  Vector& operator/=(const T factor) {
    return UnaryOpInPlace([factor](T value) { return value / factor; });
  }

  /**
   * @brief Computes dot product of this Vector with @p rhs.
   * @param[in] rhs Right operand.
   * @return The product.
   */
  const T Dot(const Vector& rhs) const noexcept {
    return (*this) * rhs;
  }

  /**
   * @brief Computes cross product of this Vector with @p rhs.
   *
   * Only enabled for 3D Vectors.
   *
   * @param[in] rhs Right operand.
   * @return New Vector containing result.
   */
  template<VectorIndex N>
  const Vector Cross(const Vector<T, N>& rhs) const noexcept {
    static_assert(K == 3 && N == 3,
                  "Cross product only works for 3D Vectors.");
    return Vector(y() * rhs.z() - z() * rhs.y(),
                  z() * rhs.x() - x() * rhs.z(),
                  x() * rhs.y() - y() * rhs.x());
  }

  /**
   * @brief Sets all data in Vector to @p value.
   * @param[in] value
   */
  void Set(const T value) noexcept {
    data_.fill(value);
  }

  /**
  * @brief Zeros out the vector.
  */
  void Clear() noexcept {
    Set(static_cast<T>(0));
  }

  /**
   * @brief A copy of this Vector, excluding the last element.
   * @return New Vector containing result.
   */
  const Vector<T, K - 1> Shrunk() const noexcept {
    static_assert(K > 1, "Cannot shrink Vector with 1 element.");
    Vector<T, K - 1> result;
    std::copy(data_.begin(), data_.end() - 1, result.data_.begin());
    return result;
  }

  /**
   * @brief A copy of this Vector, with one extra element.
   * @param[in] value Value to insert in extra element.
   * @return New Vector containing result.
   */
  const Vector<T, K + 1> Expanded(const T value) const noexcept {
    Vector<T, K + 1> result;
    std::copy(data_.begin(), data_.end(), result.data_.begin());
    result(K) = value;
    return result;
  }

  /**
   * @brief Returns square of the 2-norm of this Vector (aka squared length).
   * @return As above.
   */
  const T NormSquared() const noexcept {
    return Dot(*this);
  }

  /**
   * @brief Returns 2-norm of this Vector (aka length).
   * @return The norm, always as a double.
   */
  const double Norm() const {
    return sqrt(NormSquared());
  }

  /**
   * @brief Normalize this Vector.
   *
   * No action is taken if its norm is 0.
   *
   * @return Reference to this Vector.
   */
  Vector& NormalizeInPlace() {
    const double n = Norm();
    if (n != 0) {
      return *this /= n;
    }
    return *this;
  }

  /**
   * @brief Returns a normalized copy of this Vector.
   *
   * An unaltered copy is returned if its norm is 0.
   *
   * @return New Vector with result.
   */
  const Vector NormalizedCopy() const {
    return Vector(*this).NormalizeInPlace();
  }

  /**
   * @brief Test if this Vector has unit-length norm.
   * @return As above.
   */
  const bool HasUnitNorm() const noexcept {
    return NormSquared() == static_cast<T>(1);
  }

  /**
   * @brief Constructs 0-vector with K elements.
   * @return New Vector.
   */
  static const Vector Zero() noexcept {
    Vector v;
    v.Clear();
    return v;
  }

  //@{
  /**
   * @brief Convenience function to access an element.
   * @return Reference to corresponding element of Vector.
   */
  T& x() {
    static_assert(K >= 1 && K <= 4, "x() accessor is disabled.");
    return data_[0];
  }
  T& y() {
    static_assert(K >= 2 && K <= 4, "y() accessor is disabled.");
    return data_[1];
  }
  T& z() {
    static_assert(K >= 3 && K <= 4, "z() accessor is disabled.");
    return data_[2];
  }
  T& w() {
    static_assert(K == 4, "w() accessor is disabled.");
    return data_[3];
  }
  //@}

  //@{
  /**
   * @brief Convenience function to access an element.
   * @return Value of corresponding element in Vector.
   */
  const T x() const {
    static_assert(K >= 1 && K <= 4, "x() accessor is disabled.");
    return data_[0];
  }
  const T y() const {
    static_assert(K >= 2 && K <= 4, "y() accessor is disabled.");
    return data_[1];
  }
  const T z() const {
    static_assert(K >= 3 && K <= 4, "z() accessor is disabled.");
    return data_[2];
  }
  const T w() const {
    static_assert(K == 4, "w() accessor is disabled.");
    return data_[3];
  }
  //@}

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

//@{
/// Shorthand types.
using Vector3f = Vector<float, 3>;
//@}

}  // namespace ogle

#endif  // LIBRARIES_MATH_INCLUDES_MATH_VECTOR_H_
