/**
 * @file glsl_shader_program.h
 * @brief Defines GLSLShaderProgram.
 */

#pragma once

#include "std/ogle_std.inc"
#include "easylogging++.h"  // NOLINT
#include "entity/property.h"
#include "renderer/opengl_primitive_types.h"
#include "resource/resource_metadata.h"
#include "renderer/shader_program.h"

namespace ogle {

class GLSLShader;

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

  void SetVariable(const Property& variable) override;

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
                        const PropertyType scalar_type, const int rows,
                        const int cols, const void* data);

  /**
   * @brief Helper function for setting uniform vector variables.
   * @param uniform_location ID for uniform variable.
   * @param scalar_type Type for data in vector.
   * @param rows Number of elements in vector.
   * @param data Data constituting vector elements.
   */
  void SetUniformVector(const GLint uniform_location,
                        const PropertyType scalar_type, const int rows,
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

