/**
 * @file Implementation of glsl_shader.h.
 */

#include "renderer/glsl_shader.h"
#include <memory>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "resource/resource_metadata.h"

namespace ogle {

const stl_string GLSLShader::kImplementationName = "glsl";

GLSLShader::GLSLShader(const ResourceMetadata& metadata,
                       const stl_string& shader_text, const ShaderType type)
    : Shader(metadata, shader_text, type), shader_id_(0) {}

GLSLShader::~GLSLShader() { glDeleteShader(shader_id_); }

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

}  // namespace ogle
