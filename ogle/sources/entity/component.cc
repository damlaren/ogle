/**
 * @file component.cc
 * @brief Implements component.h.
 */

#include "entity/component.h"
#include "entity/entity.h"

namespace ogle {

Component::Component(const ComponentType type)
  : type_(type), entity_(nullptr) {
}

Entity* Component::entity() const {
  return entity_;
}

void Component::set_entity(Entity* entity) {
  entity_ = entity;
}

const ComponentType Component::type() const {
  return type_;
}

}  // namespace ogle
