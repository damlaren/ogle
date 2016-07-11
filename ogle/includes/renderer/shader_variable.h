/*
Copyright (c) 2016 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

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
} ScalarVariable;

}  // namespace ogle

#endif  // OGLE_INCLUDES_RENDERER_SHADER_VARIABLE_H_
