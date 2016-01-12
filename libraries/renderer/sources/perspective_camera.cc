/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file Implementation of perspective_camera.h.
 */

#include "renderer/perspective_camera.h"
#include "easylogging++.h"  // NOLINT
#include "geometry/transformation_matrix.h"

namespace ogle {

/**
 * @brief Constructor. Enforces constraints on fields.
 *
 * @param[in] near_clip Distance to near clip plane. Must be >= 0, < far_clip.
 * @param[in] far_clip Distance to far clip plane.
 * @param[in] vertical_fov Vertical field of view. Must be > 0.
 * @param[in] aspect_ratio View aspect ratio. Must be > 0.
 */
PerspectiveCamera::PerspectiveCamera(const float near_clip,
                                     const float far_clip,
                                     const Angle vertical_fov,
                                     const float aspect_ratio)
  : Camera(), near_clip_(near_clip), far_clip_(far_clip),
    vertical_fov_(vertical_fov), aspect_ratio_(aspect_ratio) {
  CHECK(near_clip_ < far_clip_) << "Near clip plane must be closer than far.";
  CHECK(near_clip_ >= 0) << "Near clip plane must be at positive distance.";
  CHECK(vertical_fov.radians() > 0) << "Vertical FOV must be > 0.";
  CHECK(aspect_ratio > 0) << "Aspect ratio must be > 0.";
}

PerspectiveCamera::~PerspectiveCamera() {
}

Matrix44f PerspectiveCamera::GetViewMatrix() const {
  // TODO(damlaren): orientation is hardcoded.
  return TransformationMatrix::ViewMatrix3D(world_position_,
                                            Vector3f(0.f, 0.f, -1.f),
                                            Vector3f(0.f, 1.f, 0.f));
}

Matrix44f PerspectiveCamera::GetProjectionMatrix() const {
  return TransformationMatrix::PerspectiveMatrix3D(near_clip_, far_clip_,
                                                   vertical_fov_,
                                                   aspect_ratio_);
}

}  // namespace ogle
