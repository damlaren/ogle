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

namespace ogle {

/**
 * @brief Utility functions to build transformation matrices.
 *
 * A Matrix output from these functions can be right-multiplied by a Vector
 * to perform the transformation. All rotation matrices perform
 * counter-clockwise rotation using the right-hand rule.
 */
class TransformationMatrix {
 public:
  /**
   * @brief Builds a Matrix to translate by @p(x,y,z).
   * @param[in] x
   * @param[in] y
   * @param[in] z
   * @return Resulting Matrix.
   */
  static const Matrix44f TranslationMatrix3D(const float x,
                                             const float y,
                                             const float z);

  /**
   * @brief Builds a translation matrix.
   * @param translation Vector to translate by.
   * @return Resulting Matrix.
   */
  static const Matrix44f TranslationMatrix3D(const Vector3f& translation);

  /**
   * @brief Builds a Matrix to scale by @p(sx,sy,sz).
   * @param[in] sx
   * @param[in] sy
   * @param[in] sz
   * @return Resulting Matrix.
   */
  static const Matrix44f ScalingMatrix3D(const float sx,
                                         const float sy,
                                         const float sz);

  /**
   * @brief Builds a scaling matrix.
   * @param scales Vector containing factors to scale by.
   * @return Resulting Matrix.
   */
  static const Matrix44f ScalingMatrix3D(const Vector3f& scales);

  /**
   * @brief Builds a Matrix to rotate about X axis.
   * @param[in] theta_x
   * @return Resulting Matrix.
   */
  static const Matrix44f RotationMatrixX3D(const Angle theta_x);

  /**
   * @brief Builds a Matrix to rotate about Y axis.
   * @param[in] theta_y
   * @return Resulting Matrix.
   */
  static const Matrix44f RotationMatrixY3D(const Angle theta_x);

  /**
   * @brief Builds a Matrix to rotate about Z axis.
   * @param[in] theta_z
   * @return Resulting Matrix.
   */
  static const Matrix44f RotationMatrixZ3D(const Angle theta_x);
};

}  // namespace ogle

#endif  // LIBRARIES_GEOMETRY_INCLUDES_GEOMETRY_TRANSFORMATION_MATRIX_H_
