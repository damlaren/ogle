/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file Defines Entity.
 */

#ifndef OGLE_INCLUDES_ENTITY_ENTITY_H_
#define OGLE_INCLUDES_ENTITY_ENTITY_H_

#include "std/ogle_std.inc"
#include <memory>
#include "entity/component.h"
#include "geometry/transform.h"

namespace ogle {

/**
 * @brief An object that exists in the world of an application.
 *
 * An Entity is an object that exists in a scene at a specific location.
 * It is closely linked to #Transform.
 *
 * Objects should not be implemented as subclasses of Entity, but TODO(damlaren)
 * by adding components to it.
 */
class Entity {
 public:
  /**
   * @brief Constructor.
   * @param parent Transform of parent Entity.
   */
  explicit Entity(Transform *parent);

  /**
   * @brief Renders this Entity.
   *
   * Rendering is skipped if no Renderer is set on this object.
   *
   * @param camera Camera to render from. Note that not all Entites have a
   *        Camera, and the #camera_ field is just a placeholder until
   *        Components are added anyway.
   */
  void Render(const Entity &camera);

  /**
   * @brief Adds component to this entity.
   *
   * Only one component of a given type can be added at once.
   *
   * @param component Component to add. Will be owned by entity afterwards.
   * @return success/failure.
   */
  bool AddComponent(std::unique_ptr<Component> component);

  /**
   * @brief Search for a component of a specific type.
   * @returns Pointer to component with matching type, or null if not found.
   */
  template<typename T>
  T* GetComponent() {
    for (auto& component : components_) {
      if (component->type() == T::kComponentType) {
        return static_cast<T*>(component.get());
      }
    }
    return nullptr;
  }

  /// Entity location and orientation.
  Transform transform_;

 private:
  /// Components attached to (and owned by) this entity.
  stl_vector<std::unique_ptr<Component>> components_;
};

}  // namespace ogle

#endif  // OGLE_INCLUDES_ENTITY_ENTITY_H_
