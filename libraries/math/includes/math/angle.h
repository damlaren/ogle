/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file Some extra definitions for trigonometry.
 */

#ifndef LIBRARIES_MATH_INCLUDES_MATH_ANGLE_H_
#define LIBRARIES_MATH_INCLUDES_MATH_ANGLE_H_

#include <math.h>
#include <iostream>

namespace ogle {

/**
 * @brief Type used to represent angles in all calculations.
 *
 * Also includes some utility functions.
 */
class Angle {
 public:
  /// Pi.
  static constexpr float kPi = M_PI;

  /**
   * @brief Constructor. Implicit by design.
   * @param[in] radians Angle, in radians.
   */
  Angle(const float radians);  // NOLINT

  /**
   * @brief Getter.
   * @return Angle, in radians.
   */
  const float radians() const noexcept;

  /**
   * @brief Getter.
   * @return Angle, in degrees.
   */
  const float degrees() const noexcept;

  /**
   * @brief Prints angle, in degrees.
   * @param os Output stream.
   * @param rhs Angle to print.
   * @return Reference to @p os.
   */
  friend std::ostream& operator<<(std::ostream& os, const Angle rhs);

  /**
   * @brief Computes @p lhs + @p rhs.
   * @param lhs Left operand.
   * @param rhs Right operand.
   * @return New Angle with result.
   */
  friend const Angle operator+(const Angle lhs, const Angle rhs) noexcept;

  /**
   * @brief Add Angle to this one.
   * @param rhs Right operand.
   * @return Reference to this Angle.
   */
  Angle& operator+=(const Angle rhs) noexcept;

  /**
   * @brief Computes @p lhs - @p rhs.
   * @param lhs Left operand.
   * @param rhs Right operand.
   * @return New Angle with result.
   */
  friend const Angle operator-(const Angle lhs, const Angle rhs) noexcept;

  /**
   * @brief Subtracts @p rhs from this Angle.
   * @param rhs Right operand.
   * @return Reference to this Angle.
   */
  Angle& operator-=(const Angle rhs) noexcept;

  /**
   * @brief Computes @p lhs * @p rhs.
   * @param lhs Left operand.
   * @param rhs Right operand.
   * @return New Angle with result.
   */
  friend const Angle operator*(const Angle lhs, const Angle rhs) noexcept;

  /**
   * @brief Scales this Angle by @p rhs.
   * @param rhs Right operand.
   * @return Reference to this Angle.
   */
  Angle& operator*=(const Angle rhs) noexcept;

  /**
   * @brief Computes @p lhs / @p rhs.
   * @param lhs Left operand.
   * @param rhs Right operand.
   * @return New Angle with result.
   */
  friend const Angle operator/(const Angle lhs, const Angle rhs);

  /**
   * @brief Divides this Angle by @p rhs.
   * @param rhs Right operand.
   * @return Reference to this Angle.
   */
  Angle& operator/=(const Angle rhs);

 private:
  /// Angle, in radians
  float theta_;
};

}  // namespace ogle

#endif  // LIBRARIES_MATH_INCLUDES_MATH_ANGLE_H_
