/**
 * @file Implementation of entity.h.
 */

#include "entity/entity.h"
#include <algorithm>

namespace ogle {

Entity::Entity(Transform *parent)
  : transform_(parent, this) {
}

bool Entity::AddComponent(std::unique_ptr<Component> component) {
  if (std::find_if(components_.begin(), components_.end(),
                   [&](const std::unique_ptr<Component>& element)->bool {  // NOLINT
                     return element->type() == component->type();
                   }) == components_.end()) {
    component->set_entity(this);
    components_.emplace_back(std::move(component));
    return true;
  }
  return false;
}

}  // namespace ogle
