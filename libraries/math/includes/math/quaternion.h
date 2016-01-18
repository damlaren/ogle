/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file Defines Quaternion.
 */

#ifndef LIBRARIES_MATH_INCLUDES_MATH_QUATERNION_H_
#define LIBRARIES_MATH_INCLUDES_MATH_QUATERNION_H_

#include <assert.h>
#include "math/angle.h"
#include "math/vector.h"

namespace ogle {

/**
 * @brief A unit-length quaternion: Q = (qx*i + qy*j + qz*k) + qw.
 *
 * New Quaternions are forcibly normalized.
 */
template<typename T>
class Quaternion {
 public:
  /**
   * @brief Default constructor. Returns 0 rotation.
   */
  Quaternion()
    : vector_{static_cast<T>(0), static_cast<T>(0), static_cast<T>(0)},
      scalar_{static_cast<T>(1)} {
  }

  /**
   * @brief Copy constructor.
   * @param other Quaternion to copy.
   */
  explicit Quaternion(const Quaternion& other)
    : vector_(other.vector_), scalar_(other.scalar_) {
  }

  /**
   * @brief Retrieves qx.
   * @return Copy of qx.
   */
  const T qx() const {
    return vector_(0);
  }

  /**
   * @brief Retrieves qy.
   * @return Copy of qy.
   */
  const T qy() const {
    return vector_(1);
  }

  /**
   * @brief Retrieves qz.
   * @return Copy of qz.
   */
  const T qz() const {
    return vector_(2);
  }

  /**
   * @brief Retrieves scalar value, qw.
   * @return Copy of qw.
   */
  const T qw() const {
    return scalar_;
  }

  /**
   * @brief Copy assignment operator.
   * @param rhs Quaternion to copy.
   * @return Reference to this Quaternion.
   */
  Quaternion& operator=(const Quaternion& rhs) {
    vector_ = rhs.vector_;
    scalar_ = rhs.scalar_;
  }

  /**
   * @brief Equality operator.
   * @param lhs Left operand.
   * @param rhs Right operand.
   * @return true if both Quaternions have exactly the same values.
   */
  friend const bool operator==(const Quaternion& lhs,
                               const Quaternion& rhs) {
    return lhs.vector_ == rhs.vector_ && lhs.scalar_ == rhs.scalar_;
  }

  /**
   * @brief Output stream operator, writes in human-readable format.
   * @param[in,out] os Output stream.
   * @param rhs Quaternion to write.
   * @return Reference to @p os.
   */
  friend std::ostream& operator<<(std::ostream& os, const Quaternion& rhs) {
    os << "(" << rhs.qx() << "i + " << rhs.qy() << "j + "
       << rhs.qz() << "k + " << rhs.qw() << ")";
    return os;
  }

  /**
   * @brief Computes Grassman product of @p lhs and @p rhs.
   * @param lhs Left operand.
   * @param rhs Right operand.
   * @return The product.
   */
  friend const Quaternion operator*(const Quaternion& lhs,
                                    const Quaternion& rhs) {
    return {(lhs.scalar_ * rhs.vector_ + rhs.scalar_ * lhs.vector_ +
             lhs.vector_.Cross(rhs.vector_)),
            lhs.scalar_ * rhs.scalar_ - lhs.vector_ * rhs.vector_};
  }

  /**
   * @brief Computes rotation of @p vector by this Quaternion.
   * @param rhs Right operand.
   * @return New Quaternion.
   */
  template<typename U>
  const Quaternion operator*(const Vector<U, 3>& rhs) {
    Quaternion v(rhs, static_cast<T>(0), false);  // Unnormalized.
    return *this * v * Inverse();
  }

  /**
   * @brief Returns square of the 2-norm of this Quaternion (aka squared length).
   * @return As above.
   */
  const T NormSquared() const {
    return vector_.Dot(vector_) + scalar_ * scalar_;
  }

  /**
   * @brief Returns 2-norm of this Quaternion (aka length).
   * @return The norm, always as a double.
   */
  const double Norm() const {
    return sqrt(NormSquared());
  }

  /**
   * @brief Normalize this Quaternion.
   *
   * No action is taken if its norm is 0.
   *
   * @return Reference to this Quaternion.
   */
  Quaternion& NormalizeInPlace() {
    const double n = Norm();
    if (n != 0) {
      return *this /= n;
    }
    return *this;
  }

  /**
   * @brief Returns a normalized copy of this Quaternion.
   *
   * An unaltered copy is returned if its norm is 0.
   *
   * @return New Quaternion with result.
   */
  const Quaternion NormalizedCopy() const {
    return Quaternion(*this).NormalizeInPlace();
  }

  /**
   * @brief Test if this Quaternion has unit-length norm.
   * @return As above.
   */
  const bool HasUnitNorm() const {
    // TODO(damlaren): EPSILON.
    return NormSquared() == static_cast<T>(1);
  }

  /**
   * @brief Computes conjugate of this Quaternion.
   * @return New Quaternion.
   */
  const Quaternion Conjugate() const {
    return {-vector_, scalar_};
  }

  /**
   * @brief Computes inverse of this Quaternion.
   *
   * This is just the conjugate, as the Quaternion is assumed to be unit-length.
   *
   * @return New Quaternion.
   */
  const Quaternion Inverse() const {
    return Conjugate();
  }

  /**
   * @brief Gets axis of rotation.
   * @return Axis as a 3-Vector.
   */
  const Vector3f Axis() const {
    return vector_ / sin(RotationAngle() / 2.f);
  }

  /**
   * @brief Angle of rotation.
   * @return The Angle.
   */
  const Angle RotationAngle() const {
    assert(scalar_ >= static_cast<T>(-1) && scalar_ <= static_cast<T>(1));
    return {2.f * acos(scalar_)};
  }

 private:
  /**
   * @brief Constructor.
   * @param vector {qx, qy, qz}.
   * @param scalar qw.
   * @param normalize If true (default), normalize the new Quaternion.
   */
  Quaternion(const Vector<T, 3>& vector, const T scalar,
             const bool normalize = true)
    : vector_(vector), scalar_(scalar) {
    if (normalize) {
      NormalizeInPlace();
    }
  }

  /**
   * @brief Retrieves qx.
   * @return Reference to qx.
   */
  T& qx() {
    return vector_(0);
  }

  /**
   * @brief Retrieves qy.
   * @return Reference to qy.
   */
  T& qy() {
    return vector_(1);
  }

  /**
   * @brief Retrieves qz.
   * @return Reference to qz.
   */
  T& qz() {
    return vector_(2);
  }

  /**
   * @brief Retrieves scalar value, qw.
   * @return Reference to qw.
   */
  T& qw() {
    return scalar_;
  }

  /**
   * @brief Computes @p lhs scaled by @p factor.
   * @param lhs Quaternion to scale.
   * @param factor Scale factor.
   * @return New Quaternion containing result.
   */
  friend const Quaternion operator*(const Quaternion& lhs,
                                    const T factor) {
    return Quaternion(lhs) *= factor;
  }

  /**
   * @brief Computes @p rhs scaled by @p factor.
   * @param factor Scale factor.
   * @param rhs Quaternion to scale.
   * @return New Quaternion containing result.
   */
  friend const Quaternion operator*(const T factor, const Quaternion& rhs) {
    return Quaternion(rhs) *= factor;
  }

  /**
   * @brief Scales this Quaternion in place.
   * @param factor Scale factor.
   * @return Reference to this Quaternion.
   */
  Quaternion& operator*=(const T factor) {
    vector_ *= factor;
    scalar_ *= factor;
    return *this;
  }

  /**
   * @brief Computes @p lhs divided by @p factor.
   *
   * Division is done even if @p factor is 0. No special action is taken.
   *
   * @param lhs Quaternion to divide.
   * @param factor Factor to divide by.
   * @return New Quaternion containing result.
   */
  friend const Quaternion operator/(const Quaternion& lhs, const T factor) {
    return Quaternion(lhs) /= factor;
  }

  /**
   * @brief Divides this Quaternion in place.
   *
   * Division is done even if @p factor is 0. No special action is taken.
   *
   * @param factor Factor to divide by.
   * @return Reference to this Quaternion.
   */
  Quaternion& operator/=(const T factor) {
    vector_ /= factor;
    scalar_ /= factor;
    return *this;
  }

  /// Quaternion vector components: {qx qy qz}.
  Vector<T, 3> vector_;

  /// Quaternion scalar component: qw.
  T scalar_;
};

using Quaternionf = Quaternion<float>;

}  // namespace ogle

#endif  // LIBRARIES_MATH_INCLUDES_MATH_QUATERNION_H_

