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
 * @file Implementation of glsl_shader_program.h.
 */

#include "renderer/glsl_shader_program.h"
#include <memory>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "renderer/glsl_shader.h"
#include "resource/resource_metadata.h"

namespace ogle {

const stl_string GLSLShaderProgram::kImplementationName = "glsl";

GLSLShaderProgram::GLSLShaderProgram(const ResourceMetadata& metadata,
                                     GLSLShader* vertex_shader,
                                     GLSLShader* fragment_shader)
    : ShaderProgram(metadata),
      program_id_(0),
      vertex_shader_(vertex_shader),
      fragment_shader_(fragment_shader) {}

bool GLSLShaderProgram::Create() {
  if (vertex_shader_->shader_type() != ShaderType::Vertex) {
    LOG(ERROR) << "Shader is not a vertex shader.";
    return false;
  }
  if (fragment_shader_->shader_type() != ShaderType::Fragment) {
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

void GLSLShaderProgram::UseProgram() { glUseProgram(program_id_); }

void GLSLShaderProgram::SetUniformMatrix22f(const stl_string& variable,
                                            const Matrix22f& mat) {
  SetUniformMatrix(variable, mat, glUniformMatrix2fv);
}

void GLSLShaderProgram::SetUniformMatrix33f(const stl_string& variable,
                                            const Matrix33f& mat) {
  SetUniformMatrix(variable, mat, glUniformMatrix3fv);
}

void GLSLShaderProgram::SetUniformMatrix44f(const stl_string& variable,
                                            const Matrix44f& mat) {
  SetUniformMatrix(variable, mat, glUniformMatrix4fv);
}

void GLSLShaderProgram::SetUniformVector2f(const stl_string& variable,
                                           const Vector2f& vec) {
  SetUniformVector(variable, vec, glUniform2fv);
}

void GLSLShaderProgram::SetUniformVector3f(const stl_string& variable,
                                           const Vector3f& vec) {
  SetUniformVector(variable, vec, glUniform3fv);
}

void GLSLShaderProgram::SetUniformVector4f(const stl_string& variable,
                                           const Vector4f& vec) {
  SetUniformVector(variable, vec, glUniform4fv);
}

ogle::GLint GLSLShaderProgram::GetUniformLocation(const stl_string& variable) {
  // Getting uniform location is slow. Cache it.
  auto it = variable_ids_.find(variable);
  if (it != variable_ids_.end()) {
    return it->second;
  }
  auto location = glGetUniformLocation(program_id_, variable.c_str());
  variable_ids_[variable] = location;
  return location;
}

}  // namespace ogle
