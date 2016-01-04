/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file Defines Entity.
 */

#ifndef LIBRARIES_ENTITY_INCLUDES_ENTITY_ENTITY_H_
#define LIBRARIES_ENTITY_INCLUDES_ENTITY_ENTITY_H_

#include <memory>
#include "math/vector.h"

namespace ogle {

class Renderer;

/**
 * @brief An object instantiated in an application.
 *
 * An entity is an object that exists in a scene
 * at a specific location.
 */
class Entity {
 public:
    /**
   * @brief Constructor.
   * @param[in] renderer Renderer to use to draw this Entity.  Rendering is
   *     skipped if one is not provided.
   */
  explicit Entity(std::shared_ptr<Renderer> renderer);

  /**
   * @brief Renders this Entity.
   *
   * Rendering is skipped if no Renderer is set on this object.
   */
  void Render();

  /// World position.  TODO(damlaren): full transform.
  Vector3f position_;

 private:
  /// Renderer used to display Entity.
  std::shared_ptr<Renderer> renderer_;
};

}  // namespace ogle

#endif  // LIBRARIES_ENTITY_INCLUDES_ENTITY_ENTITY_H_
