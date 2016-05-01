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
#include "util/string_utils.h"

namespace ogle {

const stl_string Shader::kResourceType = "shader";
const stl_string Shader::kVertexShaderSubType = "vertex";
const stl_string Shader::kFragmentShaderSubType = "fragment";

std::unique_ptr<Shader> Shader::Load(const ResourceMetadata& metadata) {
  const auto& implementation =
      metadata.Get<stl_string>(Resource::kImplementationField);
  const auto& type = metadata.Get<stl_string>(Resource::kTypeField);
  const auto& split_type = StringUtils::Split(type, Resource::kTypeSeparator);
  CHECK(split_type[0] == Shader::kResourceType);  // Shouldn't fail.
  if (split_type.size() < 2) {
    LOG(ERROR) << "Cannot find shader subtype: " << split_type;
    return nullptr;
  }

  const auto& shader_type_string = split_type[1];
  ShaderType shader_type;
  if (shader_type_string == kVertexShaderSubType) {
    shader_type = ShaderType::Vertex;
  } else if (shader_type_string == kFragmentShaderSubType) {
    shader_type = ShaderType::Fragment;
  } else {
    LOG(ERROR) << "Unrecognized shader type: " << shader_type_string;
    return nullptr;
  }

  if (implementation == GLSLShader::kImplementationName) {
    auto new_object = std::make_unique<GLSLShader>(shader_text, shader_type);
    if (new_object->Create()) {
      return std::move(new_object);
    } else {
      LOG(ERROR) << "Shader Create() failed.";
      return nullptr;
    }
  }
  LOG(ERROR) << "Unable to create Shader for implementation: "
             << implementation;
  return nullptr;
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
  const stl_string implementation = configuration.Get<stl_string>(
      Shader::kConfigModule, Shader::kConfigAttributeImplementation);
  if (implementation == GLSLShader::kImplementationName) {
    auto new_program = new GLSLShaderProgram(
        static_cast<GLSLShader*>(vertex_shader),
        static_cast<GLSLShader*>(fragment_shader));
    if (new_program->Create()) {
      return new_program;
    } else {
      delete new_program;
      LOG(ERROR) << "ShaderProgram Create() failed.";
    }
  }
  LOG(ERROR) << "Unable to create shader program for implementation: "
             << implementation;
  return nullptr;
}

}  // namespace ogle
