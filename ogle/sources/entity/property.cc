/**
 * @file property.cc
 * @brief Implements property.h.
 */

#include "entity/property.h"
#include "easylogging++.h"  // NOLINT

namespace ogle {

std::ostream& operator<<(std::ostream& os, const PropertyType type) {
  switch (type) {
    case PropertyType::BOOLEAN: os << "bool"; break;
    case PropertyType::FLOAT: os << "float"; break;
    case PropertyType::DOUBLE: os << "double"; break;
    case PropertyType::STRING: os << "string"; break;
    default: os << "Unknown";
  }

  return os;
}

Property::Property(const stl_string& name,
                   const stl_vector<PropertyDimIndex>& dims)
  : name_{name}, dims_{dims} {
}

const bool Property::IsSingle() const {
  return dims_.empty();
}

const bool Property::IsVector() const {
  return dims_.size() == 1;
}

const bool Property::IsMatrix() const {
  return dims_.size() == 2;
}

const PropertyDimIndex Property::NumValues() const {
  if (dims_.empty()) {
    return 1;
  }
  PropertyDimIndex num = 1;
  for (const auto dim : dims_) {
    num *= dim;
  }
  return num;
}

const stl_string& Property::name() const {
  return name_;
}

const stl_vector<PropertyDimIndex> Property::dims() const {
  return dims_;
}

}  // namespace ogle
