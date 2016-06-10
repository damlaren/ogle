/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file Defines Entity.
 */

#ifndef OGLE_INCLUDES_ENTITY_COMPONENT_H_
#define OGLE_INCLUDES_ENTITY_COMPONENT_H_

#include "std/ogle_std.inc"

namespace ogle {

class Entity;

enum class ComponentType {
  CAMERA,
  RENDERER,
  UNKNOWN
};

/**
 * @brief An object that can be attached to an entity to add behavior.
 *
 * It is owned by its attached entity.
 *
 * Each type inheriting from Component must define a kComponentType constant
 * taking on one of the values from ComponentType.
 */
class Component {
 public:
  /**
   * @brief Constructor.
   * @param type Run-time type.
   */
  explicit Component(const ComponentType type);

  /**
   * @brief Destructor. Allows inheritance.
   */
  virtual ~Component() = default;

  /**
   * @brief Accessor.
   * @returns owning entity.
   */
  Entity* entity() const;

  /**
   * @brief Sets attached entity.
   * @param[in] entity Owner.
   */
  void set_entity(Entity* entity);

  /**
   * @brief Accessor.
   * @return Component run-time type.
   */
  const ComponentType type() const;

 private:
  /// Run-time type information.
  ComponentType type_;

  /// Entity this Component is attached to.
  Entity* entity_;
};

}  // namespace ogle

#endif  // OGLE_INCLUDES_ENTITY_COMPONENT_H_
