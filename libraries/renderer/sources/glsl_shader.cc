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

#include "GL/glew.h"
#include "GLFW/glfw3.h"

namespace ogle{

/// Implementation to hide OpenGL includes.
struct GLSLShader::GLSLShaderImpl {
  GLuint shader_id;
};

GLSLShader::GLSLShader(const std::string& shader_text, ShaderType type) :
    Shader(shader_text, type),
    pimpl_(std::make_unique<GLSLShader::GLSLShaderImpl>()) {
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

}  // namespace ogle
