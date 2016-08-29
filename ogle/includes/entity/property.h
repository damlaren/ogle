/**
 * @file property.h
 * @brief Defines Property.
 */

#pragma once

#include "std/ogle_std.inc"

namespace ogle {

/**
 * @brief Possible types for property variables.
 *
 * Note that the boolean type isn't named BOOL, to avoid using the WINBOOL type.
 */
enum class PropertyType {
  BOOLEAN,  // Boolean true/false value.
  INT32,    // 32-bit signed integer.
  UINT32,   // 32-bit unsigned integer.
  FLOAT,    // Single-precision float.
  DOUBLE,   // Double-precision float.
  STRING    // Text string.
};

/**
 * @brief Output stream operator.
 * @param os Output stream.
 * @param type Property type to write name of.
 * @return Reference to output stream.
 */
std::ostream& operator<<(std::ostream& os,  // NOLINT
                         const PropertyType type);

/**
 * @brief Describes a variable that can be set for an object.
 */
class Property {
 public:
  /// Special value for dims field denoting unspecified (unlimited) size.
  static constexpr int kUnspecifiedDim = -1;

  /**
   * @brief Constructor.
   *
   * Parameters correspond to same-named fields. The data member is copied
   * shallowly.
   */
  Property(const stl_string& name, const stl_vector<int>& dims,
           const PropertyType variable_type, const void* data);

  /// @brief Returns true if this is a single value (0-dimensional).
  const bool IsSingle() const;

  /// @brief Returns true if this is a vector value (1-dim, length N).
  const bool IsVector() const;

  /// @brief Returns true if this is a matrix value (2-dim, size M x N).
  const bool IsMatrix() const;

  /**
   * @brief Returns true if this is a numeric value.
   *
   * Bools are not considered numeric.
   */
  const bool IsNumeric() const;

  stl_string name_;             ///< Name of variable.
  stl_vector<int> dims_;        ///< Dimensions expected for variable.
  PropertyType variable_type_;  ///< Variable type.
  const void* data_;            ///< Pointer to variable value.
};

}  // namespace ogle
