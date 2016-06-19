/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file Defines GLSLShader and GLSLShaderProgram.
 */

#ifndef OGLE_INCLUDES_RENDERER_GLSL_SHADER_H_
#define OGLE_INCLUDES_RENDERER_GLSL_SHADER_H_

#include "std/ogle_std.inc"
#include "easylogging++.h"  // NOLINT
#include "renderer/opengl_primitive_types.h"
#include "renderer/shader.h"
#include "resource/resource_metadata.h"

namespace ogle {

/**
 * @brief A shader written in GLSL.
 */
class GLSLShader : public Shader {
 public:
  friend class GLSLShaderProgram;

  /// String indicating that this implementation should be used.
  static const stl_string kImplementationName;

  GLSLShader(const ResourceMetadata& metadata, const stl_string& shader_text,
             const ShaderType type);

  ~GLSLShader() override;

  /**
   * @brief Builds Shader from loaded text.
   * @return Success/failure.
   */
  bool Create();

 protected:
  /// OpenGL-generated shader ID.
  ogle::GLuint shader_id_;
};

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
  GLSLShaderProgram(const ResourceMetadata& metadata,
                    GLSLShader* vertex_shader, GLSLShader* fragment_shader);

  /**
   * @brief Links program from Shaders.
   * @return Success/failure.
   */
  bool Create();

  void UseProgram() override;

  void SetUniformMatrix22f(const stl_string& variable,
                           const Matrix22f& mat) override;
  void SetUniformMatrix33f(const stl_string& variable,
                           const Matrix33f& mat) override;
  void SetUniformMatrix44f(const stl_string& variable,
                           const Matrix44f& mat) override;

 protected:
  /**
   * @brief Get location of uniform variable.
   * @param variable Uniform variable name.
   * @return OpenGL ID.
   */
  ogle::GLint GetUniformLocation(const stl_string& variable);

  /**
   * @brief Helper function for setting uniform variables.
   *
   * Most parameters are same as passed to @p SetUniformMatrix*f.
   *
   * @param variable Name of uniform variable.
   * @param mat Matrix to set data from.
   * @param gl_func OpenGL function to use to set values.
   */
  template<MatrixIndex M, MatrixIndex N, typename GLFunc>
  void SetUniformMatrix(const stl_string& variable,
                        const Matrix<float, M, N>& mat, GLFunc gl_func) {
    auto uniform_location = GetUniformLocation(variable);
    if (uniform_location == -1) {
      LOG(ERROR) << "Could not find uniform on program " << program_id_
                 << ": " << variable;
    } else {
      // Transpose matrix to column-major format used in OpenGL.
      gl_func(uniform_location, 1, 0, mat.Transpose().data());
    }
  }

  /// OpenGL-generated program ID.
  ogle::GLuint program_id_;

  /// Caches IDs of shader variables.
  stl_map<stl_string, ogle::GLint> variable_ids_;

  /// Precompiled vertex shader.
  GLSLShader* vertex_shader_;

  /// Precompiled fragment shader.
  GLSLShader* fragment_shader_;
};

}  // namespace ogle

#endif  // OGLE_INCLUDES_RENDERER_GLSL_SHADER_H_
