/**
 * @file fp_comparison.h
 * @brief Epsilon constant, and other numerical comparison utilities.
 */

#pragma once

#include "std/ogle_std.inc"
#include <math.h>
#include <type_traits>

namespace ogle {

/// Epsilon constant for comparing floating point numbers.
static constexpr double kEpsilon = 1e-6;

/**
 * @brief Compares floating point values.
 * @param left Left operand.
 * @param right Right operand.
 * @param epsilon Threshold at which to consider operands equal.
 * @return -1 if left > right; 0 if left == right; 1 if left < right
 */
template<typename T>
const int CompareFP(const T left, const T right, const double epsilon) {
  static_assert(std::is_floating_point<T>::value,
                "CompareFP must be used for floating-point numbers only.");
  if (fabs(left - right) <= epsilon) {
    return 0;
  } else if (left > right) {
    return -1;
  } else {
    return 1;
  }
}

/**
 * @brief Equality comparison for floating point values.
 * @param left Left operand.
 * @param right Right operand.
 * @param epsilon Threshold at which to consider operands equal.
 * @return true if @p left == @p right, within @p epsilon.
 */
template<typename T>
const bool FPEquals(const T left, const T right,
                    const double epsilon = kEpsilon) {
  return CompareFP(left, right, epsilon) == 0;
}

/**
 * @brief Less-than comparison for floating point values.
 * @param left Left operand.
 * @param right Right operand.
 * @param epsilon Threshold at which to consider operands equal.
 * @return true if @p left + @p epsilon < @p right.
 */
template<typename T>
const bool FPLess(const T left, const T right,
                  const double epsilon = kEpsilon) {
  return CompareFP(left, right, epsilon) == 1;
}

/**
 * @brief Greater-than comparison for floating point values.
 * @param left Left operand.
 * @param right Right operand.
 * @param epsilon Threshold at which to consider operands equal.
 * @return true if @p left > @p right + @p epsilon.
 */
template<typename T>
const bool FPGreater(const T left, const T right,
                    const double epsilon = kEpsilon) {
  return CompareFP(left, right, epsilon) == -1;
}

}  // namespace ogle

