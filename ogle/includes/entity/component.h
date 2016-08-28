/**
 * @file component.h
 * @brief Defines Component.
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
