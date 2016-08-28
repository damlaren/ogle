/**
 * @file transformation_matrix.h
 * @brief Defines TransformationMatrix.
 */

#ifndef OGLE_INCLUDES_GEOMETRY_TRANSFORMATION_MATRIX_H_
#define OGLE_INCLUDES_GEOMETRY_TRANSFORMATION_MATRIX_H_

#include "std/ogle_std.inc"
#include "math/angle.h"
#include "math/matrix.h"

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
   * @brief Builds a 3Dtranslation matrix.
   *
   * This Matrix is always 4x4.
   *
   * @param translation Vector to translate by.
   * @return Resulting Matrix.
   */
  static const Matrix44f TranslationMatrix3D(const Vector3f& translation);

  /**
   * @brief Builds a 3x3 scaling Matrix.
   * @param scales Vector containing factors to scale by.
   * @return Resulting Matrix.
   */
  static const Matrix33f ScalingMatrix3D(const Vector3f& scales);

  /**
   * @brief Builds a 3x3 Matrix to rotate about X axis.
   * @param theta_x .
   * @return Resulting Matrix.
   */
  static const Matrix33f RotationMatrixX3D(const Angle theta_x);

  /**
   * @brief Builds a 3x3 Matrix to rotate about Y axis.
   * @param theta_y .
   * @return Resulting Matrix.
   */
  static const Matrix33f RotationMatrixY3D(const Angle theta_y);

  /**
   * @brief Builds a 3x3 Matrix to rotate about Z axis.
   * @param theta_z .
   * @return Resulting Matrix.
   */
  static const Matrix33f RotationMatrixZ3D(const Angle theta_z);

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
   * @param target_position Where to point the camera. Should be distinct from
   *        camera position.
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

#endif  // OGLE_INCLUDES_GEOMETRY_TRANSFORMATION_MATRIX_H_
