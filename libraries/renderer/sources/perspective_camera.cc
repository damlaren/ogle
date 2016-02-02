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

PerspectiveCamera::PerspectiveCamera(const float near_clip,
                                     const float far_clip,
                                     const Angle vertical_fov,
                                     const int window_width,
                                     const int window_height)
  : Camera(), near_clip_(near_clip), far_clip_(far_clip),
    vertical_fov_(vertical_fov) {
  CHECK(near_clip_ < far_clip_) << "Near clip plane must be closer than far.";
  CHECK(near_clip_ >= 0) << "Near clip plane must be at positive distance.";
  CHECK(vertical_fov.radians() > 0) << "Vertical FOV must be > 0.";
  CHECK(window_width > 0) << "Window width must be > 0.";
  CHECK(window_height > 0) << "Window height must be > 0.";
  set_aspect_ratio(window_width, window_height);
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

void PerspectiveCamera::set_aspect_ratio(const int window_width,
                                         const int window_height) {
  if (window_width > 0 && window_height > 0) {
    aspect_ratio_ = static_cast<float>(window_width) / window_height;
  } else {
    LOG(ERROR) << "Failed to set aspect ratio; window WxH = "
               << window_width << " x " << window_height;
  }
}

}  // namespace ogle
