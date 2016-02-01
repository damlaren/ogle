/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file Epsilon constant, and other numerical comparison utilities.
 */

#ifndef LIBRARIES_MATH_INCLUDES_MATH_FP_COMPARISON_H_
#define LIBRARIES_MATH_INCLUDES_MATH_FP_COMPARISON_H_

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

#endif  // LIBRARIES_MATH_INCLUDES_MATH_FP_COMPARISON_H_

