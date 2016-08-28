/**
 * @file resource_type.h
 * @brief Defines ResourceType.
 */

#ifndef OGLE_INCLUDES_RESOURCE_RESOURCE_TYPE_H_
#define OGLE_INCLUDES_RESOURCE_RESOURCE_TYPE_H_

#include "std/ogle_std.inc"
#include <iostream>

namespace ogle {

/// Supported resource types.
enum class ResourceType {
  MATERIAL,
  MESH,
  SHADER,
  SHADER_PROGRAM,
  UNKNOWN,
  BEGIN = MATERIAL,
  END = UNKNOWN
};

/**
 * @brief Output stream operator for ResourceType.
 * @param[in,out] os Output stream.
 * @param type Type to print.
 */
std::ostream& operator<<(std::ostream& os, const ResourceType type);  // NOLINT

}  // namespace ogle

#endif  // OGLE_INCLUDES_RESOURCE_RESOURCE_TYPE_H_
