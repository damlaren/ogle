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
 * @brief Base class for all Renderers.
 *
 * Handles all rendering operations in an API-independent manner.
 * Subclassed Renderers are based on specific APIs and render
 * specific types of objects. They are designed for reuse by
 * different Entities.
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
   * @param camera Entity with attached Camera to render from.
   */
  virtual void Render(const Transform& transform, Entity *camera) = 0;

 protected:
  /**
   * @brief Default constructor.
   */
  Renderer();
};

}  // namespace ogle

