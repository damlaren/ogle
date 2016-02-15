/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file Defines GLSLShader and GLSLShaderProgram.
 */

#ifndef LIBRARIES_RENDERER_INCLUDES_RENDERER_GLSL_SHADER_H_
#define LIBRARIES_RENDERER_INCLUDES_RENDERER_GLSL_SHADER_H_

#include <memory>
#include <string>
#include "easylogging++.h"  // NOLINT
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "renderer/shader.h"

namespace ogle {

/**
 * @brief A shader written in GLSL.
 */
class GLSLShader : public Shader {
 public:
  friend class GLSLShaderProgram;

  GLSLShader(const std::string& shader_text, ShaderType type);

  ~GLSLShader() override = default;

 protected:
  /// OpenGL-generated shader ID.
  GLuint shader_id_;
};

/**
 * @brief Linked GLSL shader program.
 */
class GLSLShaderProgram : public ShaderProgram {
 public:
  /**
   * @brief Constructor. Links shaders into a program.
   * @param vertex_shader Precompiled vertex Shader.
   * @param fragment_shader Precompiled fragment Shader.
   */
  GLSLShaderProgram(std::shared_ptr<GLSLShader> vertex_shader,
                    std::shared_ptr<GLSLShader> fragment_shader);
  ~GLSLShaderProgram() override = default;

  void UseProgram() override;

  void SetUniformMatrix22f(const std::string& variable,
                           const Matrix22f& mat) override;
  void SetUniformMatrix33f(const std::string& variable,
                           const Matrix33f& mat) override;
  void SetUniformMatrix44f(const std::string& variable,
                           const Matrix44f& mat) override;

 protected:
  /**
   * @brief Helper function for setting uniform variables.
   *
   * Most parameters are same as passed to @p SetUniformMatrix*f.
   * OpenGL's API only supports setting float matrices.
   *
   * @param variable
   * @param mat
   * @param gl_func OpenGL function to use to set values.
   */
  template<MatrixIndex M, MatrixIndex N, typename GLFunc>
  SetUniformMatrix(const std::string& variable, const Matrix<float, M, N>& mat,
                   GLFunc gl_func) {
    // TODO(damlaren): Getting location is best done outside of a loop.
    //     I've read that querying it is slow.
    GLint uniform_location = glGetUniformLocation(program_id_, variable.c_str());
    if (uniform_location == -1) {
      LOG(ERROR) << "Could not find uniform on program " << program_id_
                 << ": " << variable;
    } else {
      // Transpose matrix to column-major format used in OpenGL.
      gl_func(uniform_location, 1, GL_FALSE, mat.Transpose().data());
    }
  }

  /// OpenGL-generated program ID.
  GLuint program_id_;

  /// Precompiled vertex shader.
  std::shared_ptr<GLSLShader> vertex_shader_;

  /// Precompiled fragment shader.
  std::shared_ptr<GLSLShader> fragment_shader_;
};

}  // namespace ogle

#endif  // LIBRARIES_RENDERER_INCLUDES_RENDERER_GLSL_SHADER_H_
