/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file Implementation of glsl_shader.h.
 */

#include "renderer/glsl_shader.h"
#include <memory>

namespace ogle {

GLSLShader::GLSLShader(const std::string& shader_text, ShaderType type) :
    Shader(shader_text, type), shader_id_(0) {
}

GLSLShader::~GLSLShader() {
  if (shader_id_ != 0) {
    glDeleteShader(shader_id_);
  }
}

bool GLSLShader::Create() {
  if (shader_type_ == ShaderType::Vertex) {
    shader_id_ = glCreateShader(GL_VERTEX_SHADER);
  } else if (shader_type_ == ShaderType::Fragment) {
    shader_id_ = glCreateShader(GL_FRAGMENT_SHADER);
  }

  if (shader_id_ == 0) {
    LOG(ERROR) << "glCreateShader() failed.";
    return false;
  }

  const char* shader_text_c_str = shader_text_.c_str();
  glShaderSource(shader_id_, 1, &shader_text_c_str, nullptr);
  glCompileShader(shader_id_);

  // Check for error.
  int params = -1;
  glGetShaderiv(shader_id_, GL_COMPILE_STATUS, &params);
  if (params != GL_TRUE) {
    LOG(ERROR) << "Shader " << shader_id_ << " failed to compile.";
    static constexpr int kMaxLogLength = 2048;
    int log_length = 0;
    char log[kMaxLogLength];
    glGetShaderInfoLog(shader_id_, kMaxLogLength, &log_length, log);
    LOG(ERROR) << log;
    return false;
  }
  return true;
}

GLSLShaderProgram::GLSLShaderProgram(
    GLSLShader* vertex_shader, GLSLShader* fragment_shader)
  : ShaderProgram(), program_id_(0), vertex_shader_(vertex_shader),
    fragment_shader_(fragment_shader) {
}

bool GLSLShaderProgram::Create() {
  if (vertex_shader_->shader_type_ != ShaderType::Vertex) {
    LOG(ERROR) << "Shader is not a vertex shader.";
    return false;
  }
  if (fragment_shader_->shader_type_ != ShaderType::Fragment) {
    LOG(ERROR) << "Shader is not a fragment shader.";
    return false;
  }

  program_id_ = glCreateProgram();
  if (program_id_ == 0) {
    LOG(ERROR) << "glCreateProgram() failed.";
    return false;
  }
  glAttachShader(program_id_, fragment_shader_->shader_id_);
  glAttachShader(program_id_, vertex_shader_->shader_id_);
  glLinkProgram(program_id_);

  // Check for error.
  int params = -1;
  glGetProgramiv(program_id_, GL_LINK_STATUS, &params);
  if (params != GL_TRUE) {
    LOG(ERROR) << "Shader program " << program_id_ << " failed to link.";
    static constexpr int kMaxLogLength = 2048;
    int log_length = 0;
    char log[kMaxLogLength];
    glGetProgramInfoLog(program_id_, kMaxLogLength, &log_length, log);
    LOG(ERROR) << log;
    return false;
  }
  return true;
}

void GLSLShaderProgram::UseProgram() {
  glUseProgram(program_id_);
}

void GLSLShaderProgram::SetUniformMatrix22f(const std::string& variable,
                                            const Matrix22f& mat) {
  SetUniformMatrix(variable, mat, glUniformMatrix2fv);
}

void GLSLShaderProgram::SetUniformMatrix33f(const std::string& variable,
                                            const Matrix33f& mat) {
  SetUniformMatrix(variable, mat, glUniformMatrix3fv);
}

void GLSLShaderProgram::SetUniformMatrix44f(const std::string& variable,
                                            const Matrix44f& mat) {
  SetUniformMatrix(variable, mat, glUniformMatrix4fv);
}

}  // namespace ogle
