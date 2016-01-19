/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file Defines Transform.
 */

#ifndef LIBRARIES_GEOMETRY_INCLUDES_GEOMETRY_TRANSFORM_H_
#define LIBRARIES_GEOMETRY_INCLUDES_GEOMETRY_TRANSFORM_H_

#include "math/angle.h"
#include "math/matrix.h"
#include "math/quaternion.h"
#include "math/vector.h"

namespace ogle {

/**
 * @brief Represents position and orientation of an object.
 *
 * Representation with respect to both the world and space local to a parent
 * Transform. The root Transform is the ancestor of all Transforms, and defines
 * the origin and orientation of world space.
 *
 * TODO: parenting will be added later...
 */
class Transform {
 public:
  /**
   * @brief Default constructor. Zeros out world position and orientation.
   */
  Transform();

  /**
   * @brief Destructor. TODO(damlaren): Handle children & parent.
   */
  ~Transform();

  /**
   * @brief Sets world position and [TODO(damlaren)] adjusts children as well.
   * @param new_position New world position.
   */
  void set_world_position(const Vector3f& new_position);

  /**
   * @brief Returns world position.
   * @return .
   */
  const Vector3f& world_position() const;

  /**
   * @brief set_world_orientation Sets world-space orientation.
   * @param new_orientation New orientation in world.
   */
  void set_world_orientation(const Quaternionf& new_orientation);

  /**
   * @brief Returns orientation in world space.
   * @return .
   */
  const Quaternionf& world_orientation() const;

  //@{
  /// Axes that represent front, right, and up directions.
  static const Vector3f kFrontAxis;
  static const Vector3f kRightAxis;
  static const Vector3f kUpAxis;
  //@}

 private:
  /// Position in world space.
  Vector3f world_position_;

  /// Orientation in world space.
  Quaternionf world_orientation_;
};

}  // namespace ogle

#endif  // LIBRARIES_GEOMETRY_INCLUDES_GEOMETRY_TRANSFORM_H_
