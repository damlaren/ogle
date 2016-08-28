/**
 * @file perspective_camera.cc
 * @brief Implementation of perspective_camera.h.
 */

#include "renderer/perspective_camera.h"
#include <cmath>
#include "easylogging++.h"  // NOLINT
#include "geometry/transformation_matrix.h"

namespace ogle {

PerspectiveCamera::PerspectiveCamera(const float near_clip,
                                     const float far_clip,
                                     const Angle vertical_fov,
                                     const float aspect_ratio)
  : Camera(), near_clip_(near_clip), far_clip_(far_clip),
    vertical_fov_(vertical_fov) {
  if (near_clip_ >= far_clip_) {
    LOG(ERROR) << "Near clip plane must be closer than far.";
  }
  if (near_clip_ < 0) {
    LOG(ERROR) << "Near clip plane must be at positive distance.";
  }
  set_aspect_ratio(aspect_ratio);
}

Matrix44f PerspectiveCamera::GetViewMatrix(const Transform &transform) const {
  return TransformationMatrix::ViewMatrix3D(
      transform.world_position(), transform.world_front(),
      transform.world_up());
}

Matrix44f PerspectiveCamera::GetProjectionMatrix() const {
  return TransformationMatrix::PerspectiveMatrix3D(
      near_clip_, far_clip_, vertical_fov_, aspect_ratio_);
}

void PerspectiveCamera::set_aspect_ratio(const float aspect_ratio) {
  if (aspect_ratio <= 0 || std::isnan(aspect_ratio)) {
    LOG(ERROR) << "Invalid aspect ratio set: " << aspect_ratio;
  } else {
    aspect_ratio_ = aspect_ratio;
  }
}

}  // namespace ogle
