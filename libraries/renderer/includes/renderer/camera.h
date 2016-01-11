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

#include "math/matrix.h"
#include "math/vector.h"

namespace ogle {

/**
 * @brief A camera positioned in the world.
 */
class Camera {
 public:
  /**
   * @brief Constructor. Zeros out initial position and orientation.
   */
  Camera();

  /**
   * @brief Virtual destructor.
   */
  virtual ~Camera();

  /**
   * @brief Computes view matrix from current camera state.
   * @return Matrix.
   */
  virtual Matrix44f GetViewMatrix() = 0;

  /**
   * @brief Computes projection matrix from current camera state.
   * @return Matrix.
   */
  virtual Matrix44f GetProjectionMatrix() = 0;

  /// Position of camera in world space.
  Vector3f world_position_;

  // TODO(damlaren): Add camera orientation.
};

}  // namespace ogle

#endif  // LIBRARIES_RENDERER_INCLUDES_RENDERER_CAMERA_H_
