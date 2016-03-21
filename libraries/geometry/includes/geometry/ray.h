/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file Defines Ray.
 */

#ifndef LIBRARIES_GEOMETRY_INCLUDES_GEOMETRY_RAY_H_
#define LIBRARIES_GEOMETRY_INCLUDES_GEOMETRY_RAY_H_

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

#endif  // LIBRARIES_GEOMETRY_INCLUDES_GEOMETRY_RAY_H_

