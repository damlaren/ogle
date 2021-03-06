/**
 * @file transform.h
 * @brief Defines Transform.
 */

#pragma once

#include "std/ogle_std.inc"
#include "math/angle.h"
#include "math/matrix.h"
#include "math/quaternion.h"
#include "math/vector.h"

namespace ogle {

class Entity;

/**
 * @brief Represents position and orientation of an object.
 *
 * Representation with respect to both the world and space local to a parent.
 * Local space is defined by a hierarchy of transforms.
 */
class Transform {
 public:
  //@{
  /// Axes that represent front, right, and up directions in world space.
  static const Vector3f kFrontAxis;
  static const Vector3f kRightAxis;
  static const Vector3f kUpAxis;
  //@}

  /**
   * @brief Constructor.
   *
   * Zeros out world position and orientation. Attaches Transform to Entity.
   *
   * @param parent Parent Transform. Can be null.
   * @param entity Entity to attach to. Can be null.
   */
  Transform(Transform* parent, Entity* entity);

  /**
   * @brief Destructor.
   */
  ~Transform();

  /**
   * @brief Sets world position and adjusts children's local coordinates.
   * @param new_position New world position.
   */
  void set_world_position(const Vector3f& new_position);

  /**
   * @brief Accessor.
   * @return World position.
   */
  const Vector3f& world_position() const;

  /**
   * @brief set_world_orientation Sets world-space orientation.
   * @param new_orientation New orientation.
   */
  void set_world_orientation(const Quaternionf& new_orientation);

  /**
   * @brief Setter. Sets world-space orientation from angles.
   * @param yaw .
   * @param pitch .
   * @param roll .
   */
  void set_world_orientation(const Angle yaw, const Angle pitch,
                             const Angle roll);

  /**
   * @brief Accessor.
   * @return Orientation in world space.
   */
  const Quaternionf& world_orientation() const;

  //@{
  /**
   * @brief Computes current up/front/right vector in world space.
   * @return Unit vector.
   */
  const Vector3f world_up() const;
  const Vector3f world_front() const;
  const Vector3f world_right() const;
  //@}

  /**
   * @brief Accessor.
   * @return Parent Transform.
   */
  Transform* parent();

  /**
   * @brief Accessor.
   *
   * Individual Transforms can be manipulated, but the returned vector should
   * not be.
   *
   * @return Child Transforms.
   */
  const stl_vector<Transform*>& children();

  /**
   * @brief Accessor.
   * @return Entity attached to this Transform.
   */
  Entity* entity();

  //@{
  /**
   * @brief Translate in direction.
   * @param delta Distance to move.
   */
  void TranslateForward(const float delta);
  void TranslateRight(const float delta);
  void TranslateUp(const float delta);
  //@}

  //@{
  /**
   * @brief Rotate transform by yaw, pitch, or roll angles.
   * @param yaw .
   * @param pitch .
   * @param roll .
   */
  void RotateYaw(const Angle yaw);
  void RotatePitch(const Angle pitch);
  void RotateRoll(const Angle roll);
  //@}

  /**
   * @brief Retrieves world-space rotation Matrix.
   * @return New Matrix.
   */
  const Matrix33f RotationMatrix3D() const;

  /**
   * @brief Retrieves full world-space transformation Matrix.
   * @return New Matrix.
   */
  const Matrix44f TransformationMatrix3D() const;

 private:
  /// Child Transforms. It's assumed that the # of child Transforms, and changes
  /// to them, remains small.
  stl_vector<Transform*> children_;

  /// Position in world space.
  Vector3f world_position_;

  /// Orientation in world space.
  Quaternionf world_orientation_;

  /// Parent Transform, null for root.
  Transform* parent_;

  /// Entity attached to this transform.
  Entity* entity_;
};

}  // namespace ogle

