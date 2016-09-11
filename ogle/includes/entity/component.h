/**
 * @file component.h
 * @brief Defines Component.
 */

#pragma once

#include "std/ogle_std.inc"
#include "entity/property.h"

namespace ogle {

class Entity;

enum class ComponentType {
  CAMERA,
  LIGHT,
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

  /**
   * @brief Copies property into component.
   *
   * TODO(damlaren): More copying than I would like in this interface.
   *
   * @param variable Value to set.
   */
  void SetProperty(const Property& variable);

  /**
   * @brief Gets property with name.
   * @param name Name of property to search.
   * @return Pointer to property.
   */
  Property* GetProperty(const stl_string& name) const;

 private:
  /// Run-time type information.
  ComponentType type_;

  /// Entity this component is attached to.
  Entity* entity_;

  /// Properties set on component.
  stl_vector<std::unique_ptr<Property>> variables_;
};

}  // namespace ogle
