/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file Implements transform.h.
 */

#include "geometry/transform.h"

namespace ogle {

Transform::Transform()
  : world_position_{0.f, 0.f, 0.f}, world_orientation_{} {
}

Transform::~Transform() {
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

const Quaternionf& Transform::world_orientation() const {
  return world_orientation_;
}

const Vector3f Transform::kFrontAxis = {1.f, 0.f, 0.f};
const Vector3f Transform::kRightAxis = {0.f, 0.f, 1.f};
const Vector3f Transform::kUpAxis = {0.f, 1.f, 0.f};

}  // namespace ogle
