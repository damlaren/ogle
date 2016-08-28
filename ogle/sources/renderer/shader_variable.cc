/**
 * @file shader_variable.cc
 * @brief Implementation of shader_variable.h.
 */

#include "renderer/shader_variable.h"
#include "easylogging++.h"  // NOLINT

namespace ogle {

std::ostream& operator<<(std::ostream& os, const ShaderVariableType type) {
  switch (type) {
    case ShaderVariableType::MATRIX: {
      os << "matrix";
      break;
    }
    case ShaderVariableType::VECTOR: {
      os << "vector";
      break;
    }
    case ShaderVariableType::SCALAR: {
      os << "scalar";
      break;
    }
    default: {
      LOG(ERROR) << "Unknown ShaderVariableType: " << static_cast<int>(type);
      break;
    }
  }
  return os;
}

}  // namespace ogle
