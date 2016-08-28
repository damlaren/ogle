/**
 * @file ray.h
 * @brief Defines Ray.
 */

#pragma once

#include "std/ogle_std.inc"
#include "math/vector.h"

namespace ogle {

/**
 * @brief A ray starting at some point and cast in a direction.
 */
template<typename T, VectorIndex K>
class Ray {
 public:
  /**
   * @brief Constructor.
   * @param origin Sets Ray origin.
   * @param direction Sets Ray direction, which will be normalized.
   */
  Ray(const Vector<T, K>& origin, const Vector<T, K>& direction)
    : origin_{origin}, direction_{direction.NormalizedCopy()} {
  }

  /**
   * @brief Calculates point at distance.
   * @param distance .
   * @return The point.
   */
  const Vector<T, K> PointAt(const T distance) const {
    return origin_ + direction_ * distance;
  }

  /// Origin point of ray.
  Vector<T, K> origin_;

  /// Direction in which ray is cast.
  Vector<T, K> direction_;
};

}  // namespace ogle

