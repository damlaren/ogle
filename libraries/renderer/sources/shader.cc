/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file Implementation of shader.h.
 */

#include "renderer/shader.h"
#include "config/configuration.h"
#include "file_system/text_file.h"
#include "renderer/glsl_shader.h"

namespace ogle {

const stl_string Shader::kConfigModule = "render";

const stl_string Shader::kConfigImplementationAttribute =
    "shader_implementation";

Shader* Shader::Load(const Configuration& configuration,
                     const ShaderType shader_type,
                     const stl_string& shader_text) {
  const stl_string shader_implementation = configuration.Get<stl_string>(
      kConfigModule, kConfigImplementationAttribute);
  Shader* new_shader = nullptr;
  if (shader_implementation == GLSLShader::kConfigImplementation) {
    new_shader = new GLSLShader(shader_text, shader_type);
    if (new_shader->Create()) {
      return new_shader;
    } else {
      LOG(ERROR) << "Shader Create() failed.";
    }
  }
  LOG(ERROR) << "Unable to create shader for implementation: "
             << shader_implementation;
  return new_shader;
}

const stl_string& Shader::shader_text() const {
  return shader_text_;
}

const ShaderType Shader::shader_type() const {
  return shader_type_;
}

Shader::Shader(const stl_string &shader_text, ShaderType type)
  : shader_text_{shader_text}, shader_type_{type} {
}

const stl_string ShaderProgram::kModelMatrixArg = "model_matrix";
const stl_string ShaderProgram::kViewMatrixArg = "view_matrix";
const stl_string ShaderProgram::kProjectionMatrixArg = "projection_matrix";

ShaderProgram* ShaderProgram::Link(const Configuration &configuration,
                                   Shader *vertex_shader,
                                   Shader *fragment_shader) {
  const stl_string shader_implementation = configuration.Get<stl_string>(
      Shader::kConfigModule, Shader::kConfigImplementationAttribute);
  ShaderProgram* new_program = nullptr;
  if (shader_implementation == GLSLShader::kConfigImplementation) {
    new_program = new GLSLShaderProgram(
        static_cast<GLSLShader*>(vertex_shader),
        static_cast<GLSLShader*>(fragment_shader));
    if (new_program->Create()) {
      return new_program;
    } else {
      LOG(ERROR) << "ShaderProgram Create() failed.";
    }
  }
  LOG(ERROR) << "Unable to create shader program for implementation: "
             << shader_implementation;
  return new_program;
}

}  // namespace ogle
