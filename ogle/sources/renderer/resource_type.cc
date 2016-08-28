/**
 * @file resource_type.cc
 * @brief Implementation of resource_type.h.
 */

#include "resource/resource_type.h"

namespace ogle {

std::ostream& operator<<(std::ostream& os,  // NOLINT
                         const ResourceType type) {
  switch (type) {
    case ResourceType::MATERIAL:
      os << "material";
      break;
    case ResourceType::MESH:
      os << "mesh";
      break;
    case ResourceType::SHADER:
      os << "shader";
      break;
    case ResourceType::SHADER_PROGRAM:
      os << "shader_program";
      break;
    default:
      os << "unknown";
      break;
  }
  return os;
}

}  // namespace ogle
