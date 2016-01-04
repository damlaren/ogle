/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file Defines Renderer.
 */

#ifndef LIBRARIES_RENDERER_INCLUDES_RENDERER_RENDERER_H_
#define LIBRARIES_RENDERER_INCLUDES_RENDERER_RENDERER_H_

#include "math/vector.h"

namespace ogle {

class Mesh;

/**
 * @brief Base class for all Renderers.
 *
 * Handles all rendering operations in an API-independent manner.
 * Subclassed Renderers are based on specific APIs and render
 * specific types of objects. They are designed for reuse by
 * different Entities.
 */
class Renderer {
 public:
  /**
   * @brief Render object.
   * @param[in] position Where to draw object.
   */
  virtual void Render(const Vector3f& position) = 0;

 protected:
  /**
   * @brief Default constructor.
   */
  Renderer() = default;

  /**
   * @brief Default destructor.
   */
  virtual ~Renderer() = default;
};

}  // namespace ogle

#endif  // LIBRARIES_RENDERER_INCLUDES_RENDERER_RENDERER_H_
