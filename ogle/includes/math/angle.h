/**
 * @file Defines Angle.
 */

#ifndef OGLE_INCLUDES_MATH_ANGLE_H_
#define OGLE_INCLUDES_MATH_ANGLE_H_

#include "std/ogle_std.inc"
#include <math.h>
#include <iostream>

namespace ogle {

/// Pi, in radians.
static constexpr float kPi = M_PI;

/**
 * @brief Type used to represent angles in all calculations.
 *
 * All angles are clipped to the range +/- PI (180 degrees).
 */
class Angle {
 public:
  /**
   * @brief Default constructor (zero angle).
   */
  Angle();

  /**
   * @brief Constructor.
   * @param radians Angle, in radians.
   */
  explicit Angle(const float radians);

  /**
   * @brief Prints angle, in degrees.
   * @param[in,out] os Output stream.
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
  friend const Angle operator+(const Angle lhs, const Angle rhs);

  /**
   * @brief Add Angle to this one.
   * @param rhs Right operand.
   * @return Reference to this Angle.
   */
  Angle& operator+=(const Angle rhs);

  /**
   * @brief Computes @p -rhs.
   * @param rhs Right operand.
   * @return Negated Angle.
   */
  friend const Angle operator-(const Angle rhs);

  /**
   * @brief Computes @p lhs - @p rhs.
   * @param lhs Left operand.
   * @param rhs Right operand.
   * @return New Angle with result.
   */
  friend const Angle operator-(const Angle lhs, const Angle rhs);

  /**
   * @brief Subtracts @p rhs from this Angle.
   * @param rhs Right operand.
   * @return Reference to this Angle.
   */
  Angle& operator-=(const Angle rhs);

  /**
   * @brief Computes Angle multiplied by a scale factor.
   * @param scale Scale factor.
   * @param rhs Right Angle operand.
   * @return New Angle with result.
   */
  friend const Angle operator*(const float scale, const Angle rhs);

  /**
   * @brief Computes Angle multiplied by a scale factor.
   * @param lhs Left Angle operand.
   * @param scale Scale factor.
   * @return New Angle with result.
   */
  friend const Angle operator*(const Angle lhs, const float scale);

  /**
   * @brief Scales this Angle.
   * @param scale Scale factor.
   * @return Reference to this Angle.
   */
  Angle& operator*=(const float scale);

  /**
   * @brief Computes Angle divided by a scale factor.
   * @param lhs Left Angle operand.
   * @param scale Scale factor. Not checked for divide by 0.
   * @return New Angle with result.
   */
  friend const Angle operator/(const Angle lhs, const float scale);

  /**
   * @brief Divides this Angle by a scale factor.
   * @param scale Scale factor. Not checked for divide by 0.
   * @return Reference to this Angle.
   */
  Angle& operator/=(const float scale);

  //@{
  /**
   * @brief Angle comparison operators. Always compare raw radian values.
   * @param lhs Left operand.
   * @param rhs Right operand.
   * @return true/false depending on comparison outcome.
   */
  friend const bool operator<(const Angle lhs, const Angle rhs);
  friend const bool operator<=(const Angle lhs, const Angle rhs);
  friend const bool operator>(const Angle lhs, const Angle rhs);
  friend const bool operator>=(const Angle lhs, const Angle rhs);
  friend const bool operator==(const Angle lhs, const Angle rhs);
  //@}

  /**
   * @brief Constructs an Angle from a value in degrees.
   * @param degrees Angle value.
   * @return New Angle.
   */
  static const Angle FromDegrees(const float degrees);

  /**
   * @brief Getter.
   * @return Angle, in radians.
   */
  const float radians() const;

  /**
   * @brief Getter.
   * @return Angle, in degrees.
   */
  const float degrees() const;

 private:
  /**
   * @brief Clip value between +/- PI.
   * @param radians Value to clip, in radians.
   * @return Clipped value.
   */
  static const float Clip(const float radians);

  /// Angle, in radians
  float theta_;
};

}  // namespace ogle

#endif  // OGLE_INCLUDES_MATH_ANGLE_H_
