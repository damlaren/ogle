/**
 * @file renderer.h
 * @brief Defines Renderer.
 */

#pragma once

#include "std/ogle_std.inc"
#include "entity/component.h"
#include "math/vector.h"

namespace ogle {

class Entity;
class Transform;

/**
 * @brief Base class for all renderers.
 *
 * Handles all rendering operations in an API-independent manner.
 * Subclassed renderers are based on specific APIs and render
 * specific types of objects. They are designed for reuse by
 * different entities.
 */
class Renderer : public Component {
 public:
  /// Configuration module describing renderers.
  static const stl_string kConfigModule;

  /// Configuration attribute defining implementation to use.
  static const stl_string kConfigAttributeImplementation;

  /// Run-time type for all renderers.
  static constexpr ComponentType kComponentType = ComponentType::RENDERER;

  /**
   * @brief Render object.
   * @param transform Position and orientation at which to render.
   * @param camera Entity with attached camera to render from.
   * @param lights Entities with attached lights.
   */
  virtual void Render(const Transform& transform, const Entity& camera,
                      const stl_vector<const Entity*>& lights) = 0;

 protected:
  /**
   * @brief Default constructor.
   */
  Renderer();
};

}  // namespace ogle
