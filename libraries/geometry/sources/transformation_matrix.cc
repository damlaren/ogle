/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file Implementation of transformation_matrix.h.
 */

#include "geometry/transformation_matrix.h"

namespace ogle {

const Matrix44f TransformationMatrix::TranslationMatrix3D(const float x,
                                                          const float y,
                                                          const float z) {
  return {1.f, 0.f, 0.f, x,
          0.f, 1.f, 0.f, y,
          0.f, 0.f, 1.f, z,
          0.f, 0.f, 0.f, 1.f};
}

const Matrix44f TransformationMatrix::TranslationMatrix3D(
    const Vector3f& translation) {
  return TranslationMatrix3D(translation.x(), translation.y(),
                             translation.z());
}

const Matrix44f TransformationMatrix::ScalingMatrix3D(const float sx,
                                                      const float sy,
                                                      const float sz) {
  return {sx, 0.f, 0.f, 0.f,
          0.f, sy, 0.f, 0.f,
          0.f, 0.f, sz, 0.f,
          0.f, 0.f, 0.f, 1.f};
}

const Matrix44f TransformationMatrix::ScalingMatrix3D(const Vector3f& scales) {
  return ScalingMatrix3D(scales.x(), scales.y(), scales.z());
}

const Matrix44f TransformationMatrix::RotationMatrixX3D(const Angle theta_x) {
  const float t = theta_x.radians();
  const float c = cos(t);
  const float s = sin(t);
  return {1.f, 0.f, 0.f, 0.f,
          0.f, c, s, 0.f,
          0.f, -s, c, 0.f,
          0.f, 0.f, 0.f, 1.f};
}

const Matrix44f TransformationMatrix::RotationMatrixY3D(const Angle theta_x) {
  const float t = theta_x.radians();
  const float c = cos(t);
  const float s = sin(t);
  return {c, 0.f, -s, 0.f,
          0.f, 1.f, 0.f, 0.f,
          s, 0.f, c, 0.f,
          0.f, 0.f, 0.f, 1.f};
}

const Matrix44f TransformationMatrix::RotationMatrixZ3D(const Angle theta_x) {
  const float t = theta_x.radians();
  const float c = cos(t);
  const float s = sin(t);
  return {c, s, 0.f, 0.f,
          -s, c, 0.f, 0.f,
          0.f, 0.f, 1.f, 0.f,
          0.f, 0.f, 0.f, 1.f};
}

}  // namespace ogle
