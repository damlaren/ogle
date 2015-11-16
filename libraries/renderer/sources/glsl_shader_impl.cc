/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file Implementation of glsl_shader.h and glsl_shader_program.h.
 */

#include "renderer/glsl_shader.h"
#include "renderer/glsl_shader_program.h"

#include <memory>

#include "easylogging++.h"  // NOLINT
#include "GL/glew.h"
#include "GLFW/glfw3.h"

namespace ogle {

/// Shader data.
struct GLSLShader::Impl {
  GLuint shader_id;  ///< OpenGL-generated shader ID.
};

GLSLShader::GLSLShader(const std::string& shader_text, ShaderType type) :
    Shader(shader_text, type),
    pimpl_(std::make_unique<GLSLShader::Impl>()) {
  if (shader_type_ == ShaderType::Vertex) {
    pimpl_->shader_id = glCreateShader(GL_VERTEX_SHADER);
  } else if (shader_type_ == ShaderType::Fragment) {
    pimpl_->shader_id = glCreateShader(GL_FRAGMENT_SHADER);
  }

  const char* shader_text_c_str = shader_text.c_str();
  glShaderSource(pimpl_->shader_id, 1, &shader_text_c_str, nullptr);
  glCompileShader(pimpl_->shader_id);

  // TODO(damlaren): error checking
}

GLSLShader::~GLSLShader() {
}

/// Program data.
struct GLSLShaderProgram::Impl {
  GLuint program_id;  ///< OpenGL-generated program ID.
};

GLSLShaderProgram::GLSLShaderProgram(
    std::shared_ptr<GLSLShader> vertex_shader,
    std::shared_ptr<GLSLShader> fragment_shader) :
    ShaderProgram(), vertex_shader_(vertex_shader),
    fragment_shader_(fragment_shader),
    pimpl_(std::make_unique<GLSLShaderProgram::Impl>()) {
  if (vertex_shader_->shader_type_ != ShaderType::Vertex) {
    LOG(ERROR) << "Shader is not a vertex shader.";
    throw ShaderProgramLinkError();
  }
  if (vertex_shader_->shader_type_ != ShaderType::Fragment) {
      LOG(ERROR) << "Shader is not a fragment shader.";
      throw ShaderProgramLinkError();
  }

  pimpl_->program_id = glCreateProgram();
  glAttachShader(pimpl_->program_id, fragment_shader_->pimpl_->shader_id);
  glAttachShader(pimpl_->program_id, vertex_shader_->pimpl_->shader_id);
  glLinkProgram(pimpl_->program_id);
}

void GLSLShaderProgram::UseProgram() {
  glUseProgram(pimpl_->program_id);
}

}  // namespace ogle
