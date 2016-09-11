/**
 * @file component.cc
 * @brief Implements component.h.
 */

#include "entity/component.h"
#include "entity/entity.h"

namespace ogle {

Component::Component(const ComponentType type)
    : type_(type), entity_(nullptr) {}

Entity* Component::entity() const { return entity_; }

void Component::set_entity(Entity* entity) { entity_ = entity; }

const ComponentType Component::type() const { return type_; }

void Component::SetProperty(const Property& variable) {
  if (GetProperty(variable.name())) {
    LOG(ERROR) << "Property already assigned on component: " << variable.name();
  } else {
    variables_.emplace_back(variable.Clone());
  }
}

Property* Component::GetProperty(const stl_string& name) const {
  auto it = std::find_if(variables_.begin(), variables_.end(),
                         [&](const std::unique_ptr<Property>& property) {
                           return property->name() == name;
                         });
  return (it != variables_.end()) ? (*it).get() : nullptr;
}

}  // namespace ogle
