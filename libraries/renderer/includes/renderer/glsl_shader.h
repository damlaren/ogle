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

#include "renderer/shader.h"

namespace ogle {

/**
 * @brief A shader written in GLSL.
 */
class GLSLShader : public Shader {
 public:
  friend class GLSLShaderProgram;

  GLSLShader(const std::string& shader_text, ShaderType type);
  ~GLSLShader() override;

 private:
  struct Impl;

  /// Implementation of shaders for GLSL.
  std::unique_ptr<Impl> pimpl_;
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

 private:
  struct Impl;

  /// Precompiled vertex shader.
  std::shared_ptr<GLSLShader> vertex_shader_;

  /// Precompiled fragment shader.
  std::shared_ptr<GLSLShader> fragment_shader_;

  /// Hidden implementation.
  std::unique_ptr<Impl> pimpl_;
};

}  // namespace ogle

#endif  // LIBRARIES_RENDERER_INCLUDES_RENDERER_GLSL_SHADER_H_
