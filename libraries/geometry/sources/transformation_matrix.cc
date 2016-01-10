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
#include "easylogging++.h"  // NOLINT

namespace ogle {

const Matrix44f TransformationMatrix::TranslationMatrix3D(
    const Vector3f& translation) {
  return {1.f, 0.f, 0.f, translation.x(),
          0.f, 1.f, 0.f, translation.y(),
          0.f, 0.f, 1.f, translation.z(),
          0.f, 0.f, 0.f, 1.f};
}

const Matrix44f TransformationMatrix::ScalingMatrix3D(const Vector3f& scales) {
  return {scales.x(), 0.f, 0.f, 0.f,
          0.f, scales.y(), 0.f, 0.f,
          0.f, 0.f, scales.z(), 0.f,
          0.f, 0.f, 0.f, 1.f};
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

const Matrix44f TransformationMatrix::ViewMatrix3D(
    const Vector3f& camera_position, const Vector3f& target_position,
    const Vector3f& up_vector) {
  // Create Vector pointing from target to Camera. This is backwards from
  // what might seem intuitive, but is done to construct a right-handed matrix.
  const Vector3f neg_forward_vector =
      (camera_position - target_position).NormalizedCopy();

  if (neg_forward_vector == Vector3f::Zero()) {
    LOG(WARNING) << "Constructing view matrix with camera located at target.";
  }
  if (!up_vector.HasUnitNorm()) {
    LOG(WARNING) << "up vector for view matrix does not have unit length.";
  }
  const Vector3f right_vector = up_vector.Cross(neg_forward_vector);
  const Vector3f neg_camera_position = -camera_position;

  // The view matrix transforms the coordinate system, which can be thought of
  // as the opposite of moving a point. Hence it is built with inverted rotation
  // and translation matrices.
  const Vector3f& r = right_vector;
  const Vector3f& u = up_vector;
  const Vector3f& f = neg_forward_vector;
  const Vector3f& p = neg_camera_position;
  return {r.x(), r.y(), r.z(), p.x(),
          u.x(), u.y(), u.z(), p.y(),
          f.x(), f.y(), f.z(), p.z(),
          0.f, 0.f, 0.f, 1.f};
}

}  // namespace ogle
