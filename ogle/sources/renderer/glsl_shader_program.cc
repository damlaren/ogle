/**
 * @file Implementation of glsl_shader_program.h.
 */

#include "renderer/glsl_shader_program.h"
#include <memory>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "renderer/glsl_shader.h"
#include "renderer/shader_variable.h"
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

void GLSLShaderProgram::SetVariable(const ShaderVariable& variable) {
  // TODO(damlaren): Only sets uniforms, how about per-vertex attributes?
  auto uniform_location = GetUniformLocation(variable.name);
  if (uniform_location == -1) {
    LOG(ERROR) << "Could not find uniform on program " << program_id_ << ": "
               << variable.name;
    return;
  }

  switch (variable.variable_type) {
    case ShaderVariableType::VECTOR: {
      if (variable.dims.size() != 1) {
        LOG(ERROR) << "Expected 1-dimensional vector data.";
        return;
      }
      SetUniformVector(uniform_location, variable.scalar_type, variable.dims[0],
                       variable.data);
      break;
    }
    case ShaderVariableType::MATRIX: {
      if (variable.dims.size() != 2) {
        LOG(ERROR) << "Expected 2-dimensional matrix data.";
        return;
      }
      SetUniformMatrix(uniform_location, variable.scalar_type, variable.dims[0],
                       variable.dims[1], variable.data);
      break;
    }
    default: {
      LOG(ERROR) << "Unsupported uniform variable type: "
                 << variable.variable_type;
      break;
    }
  }
}

GLint GLSLShaderProgram::GetUniformLocation(const stl_string& variable) {
  // Getting uniform location is slow. Cache it.
  auto it = variable_ids_.find(variable);
  if (it != variable_ids_.end()) {
    return it->second;
  }
  auto location = glGetUniformLocation(program_id_, variable.c_str());
  variable_ids_[variable] = location;
  return location;
}

void GLSLShaderProgram::SetUniformMatrix(const GLint uniform_location,
                                         const ShaderScalarType scalar_type,
                                         const int rows, const int cols,
                                         const void* data) {
  if (scalar_type != ShaderScalarType::FLOAT) {
    LOG(ERROR) << "Only floats are currently supported in SetUniformMatrix.";
    return;
  }

  if (rows != cols) {
    LOG(ERROR) << "Only square matrices can be set by SetUniformMatrix.";
    return;
  }

  // Transpose matrix to column-major format used in OpenGL.
  switch (rows) {
    case 2: {
      glUniformMatrix2fv(
          uniform_location, 1, 0,
          Matrix22f(static_cast<const float*>(data)).Transpose().data());
      break;
    }
    case 3: {
      glUniformMatrix3fv(
          uniform_location, 1, 0,
          Matrix33f(static_cast<const float*>(data)).Transpose().data());
      break;
    }
    case 4: {
      glUniformMatrix4fv(
          uniform_location, 1, 0,
          Matrix44f(static_cast<const float*>(data)).Transpose().data());
      break;
    }
    default: {
      LOG(ERROR) << "SetUniformMatrix only supports 2x2 -> 4x4 matrices.";
      return;
    }
  }
}

void GLSLShaderProgram::SetUniformVector(const GLint uniform_location,
                                         const ShaderScalarType scalar_type,
                                         const int rows, const void* data) {
  if (scalar_type != ShaderScalarType::FLOAT) {
    LOG(ERROR) << "Only floats are currently supported in SetUniformVector.";
    return;
  }

  switch (rows) {
    case 2: {
      glUniform2fv(uniform_location, 1, static_cast<const float*>(data));
      break;
    }
    case 3: {
      glUniform3fv(uniform_location, 1, static_cast<const float*>(data));
      break;
    }
    case 4: {
      glUniform4fv(uniform_location, 1, static_cast<const float*>(data));
      break;
    }
    default: {
      LOG(ERROR) << "SetUniformVector only supports vectors of length 2->4.";
      return;
    }
  }
}

}  // namespace ogle
