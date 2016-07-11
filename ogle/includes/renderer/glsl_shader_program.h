/*
Copyright (c) 2015 damlaren

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
 * @file Defines GLSLShaderProgram.
 */

#ifndef OGLE_INCLUDES_RENDERER_GLSL_SHADER_PROGRAM_H_
#define OGLE_INCLUDES_RENDERER_GLSL_SHADER_PROGRAM_H_

#include "std/ogle_std.inc"
#include "easylogging++.h"  // NOLINT
#include "renderer/opengl_primitive_types.h"
#include "resource/resource_metadata.h"
#include "renderer/shader_program.h"

namespace ogle {

class GLSLShader;
enum class ShaderScalarType;

/**
 * @brief Linked GLSL shader program.
 */
class GLSLShaderProgram : public ShaderProgram {
 public:
  /// String indicating that this implementation should be used.
  static const stl_string kImplementationName;

  /**
   * @brief Constructor.
   * @param metadata Metadata for resource.
   * @param[in] vertex_shader Precompiled GLSL vertex Shader.
   * @param[in] fragment_shader Precompiled GLSL fragment Shader.
   */
  GLSLShaderProgram(const ResourceMetadata& metadata, GLSLShader* vertex_shader,
                    GLSLShader* fragment_shader);

  /**
   * @brief Links program from Shaders.
   * @return Success/failure.
   */
  bool Create();

  void UseProgram() override;

  void SetVariable(const ShaderVariable& variable) override;

 protected:
  /**
   * @brief Get location of uniform variable.
   * @param variable Uniform variable name.
   * @return OpenGL ID.
   */
  ogle::GLint GetUniformLocation(const stl_string& variable);

  /**
   * @brief Helper function for setting uniform matrix variables.
   * @param uniform_location ID for uniform variable.
   * @param scalar_type Type for data in matrix.
   * @param rows Number of rows in matrix.
   * @param cols Number of columns in matrix.
   * @param data Data constituting matrix elements.
   */
  void SetUniformMatrix(const GLint uniform_location,
                        const ShaderScalarType scalar_type, const int rows,
                        const int cols, const void* data);

  /**
   * @brief Helper function for setting uniform vector variables.
   * @param uniform_location ID for uniform variable.
   * @param scalar_type Type for data in vector.
   * @param rows Number of elements in vector.
   * @param data Data constituting vector elements.
   */
  void SetUniformVector(const GLint uniform_location,
                        const ShaderScalarType scalar_type, const int rows,
                        const void* data);

  /// OpenGL-generated program ID.
  GLuint program_id_;

  /// Caches IDs of shader variables.
  stl_map<stl_string, ogle::GLint> variable_ids_;

  /// Precompiled vertex shader.
  GLSLShader* vertex_shader_;

  /// Precompiled fragment shader.
  GLSLShader* fragment_shader_;
};

}  // namespace ogle

#endif  // OGLE_INCLUDES_RENDERER_GLSL_SHADER_PROGRAM_H_
