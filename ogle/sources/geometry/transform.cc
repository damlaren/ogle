/**
 * @file Implements transform.h.
 */

#include "geometry/transform.h"
#include <algorithm>
#include "easylogging++.h"  // NOLINT
#include "geometry/transformation_matrix.h"

namespace ogle {

const Vector3f Transform::kFrontAxis = {1.f, 0.f, 0.f};
const Vector3f Transform::kRightAxis = {0.f, 0.f, 1.f};
const Vector3f Transform::kUpAxis = {0.f, 1.f, 0.f};

Transform::Transform(Transform *parent, Entity *entity)
  : world_position_{0.f, 0.f, 0.f}, world_orientation_{}, parent_(parent),
    entity_(entity) {
  if (parent_ != nullptr) {
    parent_->children_.push_back(this);
  }
}

Transform::~Transform() {
  if (parent_ != nullptr) {
    auto it = std::find(parent_->children_.begin(), parent_->children_.end(),
                        this);
    if (it == parent_->children_.end()) {
      LOG(ERROR) << "Transform parent doesn't recognize child.";
    } else {
      parent_->children_.erase(it);
    }
  }
  for (Transform* child_transform : children_) {
    child_transform->parent_ = parent_;
  }
}

void Transform::set_world_position(const Vector3f& new_position) {
  world_position_ = new_position;
}

const Vector3f& Transform::world_position() const {
  return world_position_;
}

void Transform::set_world_orientation(const Quaternionf& new_orientation) {
  world_orientation_ = new_orientation;
}

void Transform::set_world_orientation(const Angle yaw, const Angle pitch,
                                      const Angle roll) {
  world_orientation_ = {};
  RotateYaw(yaw);
  RotatePitch(pitch);
  RotateRoll(roll);
}

const Quaternionf& Transform::world_orientation() const {
  return world_orientation_;
}

const Vector3f Transform::world_up() const {
  return world_orientation_ * kUpAxis;
}

const Vector3f Transform::world_front() const {
  return world_orientation_ * kFrontAxis;
}

const Vector3f Transform::world_right() const {
  return world_orientation_ * kRightAxis;
}

Transform* Transform::parent() {
  return parent_;
}

const stl_vector<Transform*>& Transform::children() {
  return children_;
}

Entity* Transform::entity() {
  return entity_;
}

void Transform::TranslateForward(const float delta) {
  world_position_ += world_front() * delta;
}

void Transform::TranslateRight(const float delta) {
  world_position_ += world_right() * delta;
}

void Transform::TranslateUp(const float delta) {
  world_position_ += world_up() * delta;
}

void Transform::RotateYaw(const Angle yaw) {
  world_orientation_ = Quaternionf(world_up(), yaw) * world_orientation_;
  world_orientation_.NormalizeInPlace();
}

void Transform::RotatePitch(const Angle pitch) {
  world_orientation_ = Quaternionf(world_right(), pitch) * world_orientation_;
  world_orientation_.NormalizeInPlace();
}

void Transform::RotateRoll(const Angle roll) {
  world_orientation_ = Quaternionf(world_front(), roll) * world_orientation_;
  world_orientation_.NormalizeInPlace();
}

const Matrix33f Transform::RotationMatrix3D() const {
  return world_orientation_.RotationMatrix3D();
}

const Matrix44f Transform::TransformationMatrix3D() const {
  return RotationMatrix3D().ExpandedHomogeneous() *
      TransformationMatrix::TranslationMatrix3D(world_position_);
}

}  // namespace ogle
