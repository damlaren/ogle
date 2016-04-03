/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file Defines Camera.
 */

#ifndef LIBRARIES_RENDERER_INCLUDES_RENDERER_CAMERA_H_
#define LIBRARIES_RENDERER_INCLUDES_RENDERER_CAMERA_H_

#include "std/ogle_std.inc"
#include "math/matrix.h"

namespace ogle {

class Transform;

/**
 * @brief A camera positioned in the world.
 *
 * TODO(damlaren): Implement as component.
 */
class Camera {
 public:
  /**
   * @brief Virtual destructor.
   */
  virtual ~Camera() = default;

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

#endif  // LIBRARIES_RENDERER_INCLUDES_RENDERER_CAMERA_H_
