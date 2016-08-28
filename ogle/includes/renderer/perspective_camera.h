/**
 * @file perspective_camera.h
 * @brief Defines PerspectiveCamera.
 */

#pragma once

#include "std/ogle_std.inc"
#include "renderer/camera.h"
#include "geometry/transform.h"

namespace ogle {

/**
 * @brief A traditional perspective projection camera.
 */
class PerspectiveCamera : public Camera {
 public:
    /**
     * @brief Constructor. Enforces constraints on fields.
     *
     * Zeroes out initial position and orientation.
     *
     * @param near_clip Distance to near clip plane. Must be >= 0, < far_clip.
     * @param far_clip Distance to far clip plane.
     * @param vertical_fov Vertical field of view. Must be > 0.
     * @param aspect_ratio Window aspect ratio.
     */
  PerspectiveCamera(const float near_clip, const float far_clip,
                    const Angle vertical_fov, const float aspect_ratio);

  void set_aspect_ratio(const float aspect_ratio) override;

  Matrix44f GetViewMatrix(const Transform &transform) const override;

  Matrix44f GetProjectionMatrix() const override;

 private:
  /// Distance to near clip plane, in front of camera.
  float near_clip_;

  /// Distance to far clip plane.
  float far_clip_;

  /// Vertical field of view.
  Angle vertical_fov_;

  /// Width / height ratio.
  float aspect_ratio_;
};

}  // namespace ogle

