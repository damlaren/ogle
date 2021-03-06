/**
 * @file transformation_matrix.cc
 * @brief Implementation of transformation_matrix.h.
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

const Matrix33f TransformationMatrix::ScalingMatrix3D(const Vector3f& scales) {
  return {scales.x(), 0.f, 0.f,
          0.f, scales.y(), 0.f,
          0.f, 0.f, scales.z()};
}

const Matrix33f TransformationMatrix::RotationMatrixX3D(const Angle theta_x) {
  const float t = theta_x.radians();
  const float c = cos(t);
  const float s = sin(t);
  return {1.f, 0.f, 0.f,
          0.f, c,   -s,
          0.f, s,  c};
}

const Matrix33f TransformationMatrix::RotationMatrixY3D(const Angle theta_y) {
  const float t = theta_y.radians();
  const float c = cos(t);
  const float s = sin(t);
  return {c, 0.f, s,
          0.f, 1.f, 0.f,
          -s, 0.f, c};
}

const Matrix33f TransformationMatrix::RotationMatrixZ3D(const Angle theta_z) {
  const float t = theta_z.radians();
  const float c = cos(t);
  const float s = sin(t);
  return {c,   -s,   0.f,
          s,  c,   0.f,
          0.f, 0.f, 1.f};
}

const Matrix44f TransformationMatrix::ViewMatrix3D(
    const Vector3f& camera_position, const Vector3f& forward_vector,
    const Vector3f& up_vector) {
  if (!forward_vector.HasUnitNorm()) {
    LOG(WARNING) << "Forward vector for view matrix doesn't have unit length.";
  }
  if (!up_vector.HasUnitNorm()) {
    LOG(WARNING) << "Up vector for view matrix doesn't have unit length.";
  }
  const Vector3f neg_forward_vector = -forward_vector;
  const Vector3f neg_camera_position = -camera_position;
  const Vector3f right_vector =
      up_vector.Cross(neg_forward_vector).NormalizedCopy();

  // The view matrix transforms the coordinate system, which can be thought of
  // as the opposite of moving a point. Hence it is built with inverted rotation
  // and translation matrices. The forward vector is negated to preserve a
  // right-handed coordinate system.
  const Vector3f& r = right_vector;
  const Vector3f& u = up_vector;
  const Vector3f& f = neg_forward_vector;
  const Vector3f& p = neg_camera_position;
  const Matrix44f R = {r.x(), r.y(), r.z(), 0.f,
                       u.x(), u.y(), u.z(), 0.f,
                       f.x(), f.y(), f.z(), 0.f,
                       0.f,   0.f,   0.f,   1.f};
  const Matrix44f T = TranslationMatrix3D(p);
  return R * T;
}

const Matrix44f TransformationMatrix::ViewMatrix3DLookAt(
    const Vector3f& camera_position, const Vector3f& target_position,
    const Vector3f& up_vector) {
  const Vector3f forward_vector =
      (target_position - camera_position).NormalizedCopy();
  return ViewMatrix3D(camera_position, forward_vector, up_vector);
}

const Matrix44f TransformationMatrix::PerspectiveMatrix3D(
    const float near_clip, const float far_clip, const Angle vertical_fov,
    const float aspect_ratio) {
  if (near_clip >= far_clip) {
    LOG(ERROR) << "Far clip plane should be behind near clip plane.";
  }
  if (vertical_fov <= Angle(0.f)) {
    LOG(ERROR) << "Vertical FOV should be > 0.";
  }
  if (aspect_ratio <= 0.f) {
    LOG(ERROR) << "Aspect ratio should be > 0.";
  }

  const float f = 1.0f / tan(vertical_fov.radians() * 0.5f);
  const float sx = f / aspect_ratio;
  const float sy = f;
  const float sz = (far_clip + near_clip) / (near_clip - far_clip);
  const float pz = (2.f * far_clip * near_clip) / (near_clip - far_clip);
  return {sx,  0.f, 0.f, 0.f,
          0.f, sy,  0.f, 0.f,
          0.f, 0.f, sz,  pz,
          0.f, 0.f, -1.f, 0.f};
}

}  // namespace ogle
