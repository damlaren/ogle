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
 * @file Implementation of shader.h.
 */

#include "renderer/shader.h"
#include "file_system/text_file.h"
#include "renderer/glsl_shader.h"
#include "resource/resource_metadata.h"

namespace ogle {

const stl_string Shader::kVertexShaderSubType = "vertex";
const stl_string Shader::kFragmentShaderSubType = "fragment";

std::unique_ptr<Shader> Shader::Load(const ResourceMetadata& metadata) {
  if (metadata.type() != ResourceType::SHADER) {
    LOG(ERROR) << "Attempt to load Shader from incorrect metadata type: "
               << metadata.type();
    return nullptr;
  }

  const auto& shader_type_string = metadata.subtype(1);
  ShaderType type;
  if (shader_type_string == kVertexShaderSubType) {
    type = ShaderType::Vertex;
  } else if (shader_type_string == kFragmentShaderSubType) {
    type = ShaderType::Fragment;
  } else {
    LOG(ERROR) << "Unrecognized shader type: " << shader_type_string;
    return nullptr;
  }

  stl_string text;
  if (!ogle::TextFile::ReadTextFile(metadata.resource_path(), &text)) {
    LOG(ERROR) << "Failed to read shader text from: "
               << metadata.resource_path();
    return nullptr;
  }

  const auto implementation =
      metadata.Get<stl_string>(Resource::kImplementationField).first;
  if (implementation == GLSLShader::kImplementationName) {
    auto new_object = AllocateUniqueObject<GLSLShader>(metadata, text, type);
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

const stl_string& Shader::shader_text() const { return shader_text_; }

const ShaderType Shader::shader_type() const { return shader_type_; }

Shader::Shader(const ResourceMetadata& metadata, const stl_string& shader_text,
               const ShaderType type)
    : Resource(metadata), shader_text_{shader_text}, shader_type_{type} {}

}  // namespace ogle
