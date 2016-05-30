/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file Defines Renderer.
 */

#ifndef OGLE_INCLUDES_RENDERER_RENDERER_H_
#define OGLE_INCLUDES_RENDERER_RENDERER_H_

#include "std/ogle_std.inc"
#include "math/vector.h"

namespace ogle {

class Entity;
class Mesh;
class Transform;

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
  /// Configuration module describing renderers.
  static const stl_string kConfigModule;

  /// Configuration attribute defining implementation to use.
  static const stl_string kConfigAttributeImplementation;

  /**
   * @brief Default destructor.
   */
  virtual ~Renderer() = default;

  /**
   * @brief Render object.
   * @param transform Position and orientation at which to render.
   * @param camera Entity with attached Camera to render from.
   */
  virtual void Render(const Transform& transform, Entity *camera) = 0;

 protected:
  /**
   * @brief Default constructor.
   */
  Renderer() = default;
};

}  // namespace ogle

#endif  // OGLE_INCLUDES_RENDERER_RENDERER_H_
