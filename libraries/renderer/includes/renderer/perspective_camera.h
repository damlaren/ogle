/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file Defines PerspectiveCamera.
 */

#ifndef LIBRARIES_RENDERER_INCLUDES_RENDERER_PERSPECTIVE_CAMERA_H_
#define LIBRARIES_RENDERER_INCLUDES_RENDERER_PERSPECTIVE_CAMERA_H_

#include "renderer/camera.h"

namespace ogle {

/**
 * @brief A traditional perspective projection camera.
 */
class PerspectiveCamera {
 public:
  /**
   * @brief Constructor. Zeros out initial position and orientation.
   */
  PerspectiveCamera(const float near_clip, const float far_clip,
                    const Angle vertical_fov, const float aspect_ratio);

  /**
   * @brief Destructor.
   */
  ~PerspectiveCamera() override;

  Matrix44f GetViewMatrix() override;

  Matrix44f GetProjectionMatrix() override;

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

#endif  // LIBRARIES_RENDERER_INCLUDES_RENDERER_PERSPECTIVE_CAMERA_H_
