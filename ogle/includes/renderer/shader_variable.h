/**
 * @file Defines ShaderVariable.
 */

#ifndef OGLE_INCLUDES_RENDERER_SHADER_VARIABLE_H_
#define OGLE_INCLUDES_RENDERER_SHADER_VARIABLE_H_

#include "std/ogle_std.inc"

namespace ogle {

/**
 * @brief Possible types for variables passed to shader programs.
 */
enum class ShaderVariableType {
  SCALAR,  // Scalar variable.
  VECTOR,  // 1D vector, length specified by dims[0].
  MATRIX   // 2D matrix, shape specified as dims[0] rows X dims[1] columns.
};

/**
 * @brief Output stream operator.
 * @param os Output stream.
 * @param type Variable type to write name of.
 * @return Reference to output stream.
 */
std::ostream& operator<<(std::ostream& os,  // NOLINT
                         const ShaderVariableType type);

/**
 * @brief Possible scalar types for variables passed to shader programs.
 *
 * These types aren't just applied to scalars, but also vectors, matrices, and
 * arrays.
 */
enum class ShaderScalarType {
  BOOLEAN,    // Boolean true/false value.
  INT32,      // 32-bit signed integer.
  UINT32,     // 32-bit unsigned integer.
  HALF,       // Half-precision float.
  FLOAT,      // Single-precision float.
  DOUBLE      // Double-precision float.
};

/**
 * @brief Describes a variable to pass to a shader program.
 */
typedef struct ShaderVariable {
  /// Special value for dims field denoting unspecified (unlimited) size.
  static constexpr int kUnspecifiedDim = -1;

  stl_string name;                   ///< Name of variable.
  stl_vector<int> dims;              ///< Dimensions expected for variable.
  ShaderVariableType variable_type;  ///< Variable type.
  ShaderScalarType scalar_type;      ///< Type of scalars within variable.
  const void* data;                  ///< Pointer to variable value.
} ShaderVariable;

}  // namespace ogle

#endif  // OGLE_INCLUDES_RENDERER_SHADER_VARIABLE_H_
