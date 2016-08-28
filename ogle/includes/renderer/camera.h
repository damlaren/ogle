/**
 * @file camera.h
 * @brief Defines Camera.
 */

#pragma once

#include "std/ogle_std.inc"
#include "entity/component.h"
#include "math/matrix.h"

namespace ogle {

class Transform;

/**
 * @brief A camera positioned in the world.
 */
class Camera : public Component {
 public:
  /// Run-time type for all cameras.
  static constexpr ComponentType kComponentType = ComponentType::CAMERA;

  /**
   * @brief Default constructor.
   */
  Camera();

  /**
   * @brief Setter.
   * @param aspect_ratio Camera aspect ratio (width / height).
   */
  virtual void set_aspect_ratio(const float aspect_ratio) = 0;

  /**
   * @brief Computes view matrix.
   * @param transform Transform from which to view scene.
   * @return Matrix.
   */
  virtual Matrix44f GetViewMatrix(const Transform &transform) const = 0;

  /**
   * @brief Computes projection matrix from current camera state.
   * @return Matrix.
   */
  virtual Matrix44f GetProjectionMatrix() const = 0;
};

}  // namespace ogle

