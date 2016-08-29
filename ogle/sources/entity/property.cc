/**
 * @file property.cc
 * @brief Implements property.h.
 */

#include "entity/property.h"
#include "easylogging++.h"  // NOLINT

namespace ogle {

std::ostream& operator<<(std::ostream& os, const PropertyType type) {
  switch (type) {
    case PropertyType::BOOLEAN: {
      os << "boolean";
      break;
    }
    case PropertyType::INT32: {
      os << "int32";
      break;
    }
    case PropertyType::UINT32: {
      os << "uint32";
      break;
    }
    case PropertyType::FLOAT: {
      os << "float";
      break;
    }
    case PropertyType::DOUBLE: {
      os << "double";
      break;
    }
    case PropertyType::STRING: {
      os << "string";
      break;
    }
    default: {
      LOG(ERROR) << "Unknown PropertyType: " << static_cast<int>(type);
      break;
    }
  }
  return os;
}

Property::Property(const stl_string& name, const stl_vector<int>& dims,
                   const PropertyType variable_type, const void* data)
  : name_{name}, dims_{dims}, variable_type_{variable_type}, data_{data} {
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

const bool Property::IsNumeric() const {
  switch (variable_type_) {
    case PropertyType::INT32:
    case PropertyType::UINT32:
    case PropertyType::DOUBLE:
    case PropertyType::FLOAT:
      return true;
    default: break;
  }
  return false;
}

}  // namespace ogle
