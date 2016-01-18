/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file Defines TransformationMatrix.
 */

#ifndef LIBRARIES_GEOMETRY_INCLUDES_GEOMETRY_TRANSFORMATION_MATRIX_H_
#define LIBRARIES_GEOMETRY_INCLUDES_GEOMETRY_TRANSFORMATION_MATRIX_H_

#include "math/angle.h"
#include "math/matrix.h"
#include "math/quaternion.h"

namespace ogle {

/**
 * @brief Utility functions to build transformation matrices.
 *
 * All matrices are constructed in a right-handed coordinate system and are
 * right-multiplied by vectors to perform transformations. All rotation matrices
 * perform counter-clockwise rotation using the right-hand rule.
 */
class TransformationMatrix {
 public:
  /**
   * @brief Builds a translation matrix.
   * @param translation Vector to translate by.
   * @return Resulting Matrix.
   */
  static const Matrix44f TranslationMatrix3D(const Vector3f& translation);

  /**
   * @brief Builds a scaling matrix.
   * @param scales Vector containing factors to scale by.
   * @return Resulting Matrix.
   */
  static const Matrix44f ScalingMatrix3D(const Vector3f& scales);

  /**
   * @brief Builds a Matrix to rotate about X axis.
   * @param theta_x
   * @return Resulting Matrix.
   */
  static const Matrix44f RotationMatrixX3D(const Angle theta_x);

  /**
   * @brief Builds a Matrix to rotate about Y axis.
   * @param theta_y
   * @return Resulting Matrix.
   */
  static const Matrix44f RotationMatrixY3D(const Angle theta_x);

  /**
   * @brief Builds a Matrix to rotate about Z axis.
   * @param theta_z
   * @return Resulting Matrix.
   */
  static const Matrix44f RotationMatrixZ3D(const Angle theta_x);

  /**
   * @brief Builds a rotation Matrix from a Quaternion.
   * @param q Quaternion.
   * @return Resulting Matrix.
   */
  static const Matrix44f RotationMatrix3D(const Quaternionf q);

  /**
   * @brief Builds a camera view matrix.
   * @param camera_position Camera world position.
   * @param forward_vector Camera direction. Should be a unit vector.
   * @param up_vector Up direction. Should be a unit vector.
   * @return Resulting Matrix.
   */
  static const Matrix44f ViewMatrix3D(const Vector3f& camera_position,
                                      const Vector3f& forward_vector,
                                      const Vector3f& up_vector);
  /**
   * @brief Builds a camera view matrix looking at a position.
   * @param camera_position Camera world position.
   * @param target_position Where to point the camera. Should be distinct from camera position.
   * @param up_vector Up direction. Should be a unit vector.
   * @return Resulting Matrix.
   */
  static const Matrix44f ViewMatrix3DLookAt(const Vector3f& camera_position,
                                            const Vector3f& target_position,
                                            const Vector3f& up_vector);

  /**
   * @brief Builds a perspective projection matrix.
   * @param near_clip Distance to near clip plane.
   * @param far_clip Distance to far clip plane.
   * @param vertical_fov Vertical FOV angle.
   * @param aspect_ratio Width of viewport / height.
   * @return Resulting matrix.
   */
  static const Matrix44f PerspectiveMatrix3D(const float near_clip,
                                             const float far_clip,
                                             const Angle vertical_fov,
                                             const float aspect_ratio);
};

}  // namespace ogle

#endif  // LIBRARIES_GEOMETRY_INCLUDES_GEOMETRY_TRANSFORMATION_MATRIX_H_
