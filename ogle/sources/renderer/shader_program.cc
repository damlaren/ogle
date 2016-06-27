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
 * @file Implementation of shader_program.h.
 */

#include "renderer/shader_program.h"
#include "config/configuration.h"
#include "file_system/text_file.h"
#include "renderer/glsl_shader.h"
#include "renderer/glsl_shader_program.h"
#include "resource/resource_manager.h"
#include "resource/resource_metadata.h"

namespace ogle {

const stl_string ShaderProgram::kModelMatrixArg = "model_matrix";
const stl_string ShaderProgram::kViewMatrixArg = "view_matrix";
const stl_string ShaderProgram::kProjectionMatrixArg = "projection_matrix";

const stl_string ShaderProgram::kVertexShaderField = "vertex_shader";
const stl_string ShaderProgram::kFragmentShaderField = "fragment_shader";

std::unique_ptr<ShaderProgram> ShaderProgram::Load(
    const ResourceMetadata& metadata, ResourceManager* resource_manager) {
  CHECK(resource_manager != nullptr) << "ResourceManager cannot be null.";

  if (metadata.type() != kResourceType) {
    LOG(ERROR) << "Attempt to load ShaderProgram from bad metadata type: "
               << metadata.type();
    return nullptr;
  }

  const auto vertex_shader_id =
      metadata.Get<ResourceID>(kVertexShaderField).first;
  const auto fragment_shader_id =
      metadata.Get<ResourceID>(kFragmentShaderField).first;
  Shader* vertex_shader_resource =
      resource_manager->GetResource<Shader>(vertex_shader_id);
  if (!vertex_shader_resource) {
    LOG(ERROR) << "Couldn't find vertex shader: " << vertex_shader_id;
    return nullptr;
  }
  if (vertex_shader_resource->type() != ResourceType::SHADER) {
    LOG(ERROR) << "Resource is not a shader: " << vertex_shader_id;
    return nullptr;
  }

  Shader* fragment_shader_resource =
      resource_manager->GetResource<Shader>(fragment_shader_id);
  if (!fragment_shader_resource) {
    LOG(ERROR) << "Couldn't find fragment shader: " << fragment_shader_id;
    return nullptr;
  }
  if (fragment_shader_resource->type() != ResourceType::SHADER) {
    LOG(ERROR) << "Resource is not a shader: " << fragment_shader_id;
    return nullptr;
  }

  Shader* vertex_shader = static_cast<Shader*>(vertex_shader_resource);
  Shader* fragment_shader = static_cast<Shader*>(fragment_shader_resource);
  return std::unique_ptr<ShaderProgram>(
      Link(metadata, vertex_shader, fragment_shader));
}

std::unique_ptr<ShaderProgram> ShaderProgram::Link(
    const ResourceMetadata& metadata, Shader* vertex_shader,
    Shader* fragment_shader) {
  const auto implementation = metadata.implementation();
  if (implementation == GLSLShaderProgram::kImplementationName) {
    if (vertex_shader->implementation() != GLSLShader::kImplementationName) {
      LOG(ERROR) << "Cannot link GLSLShaderProgram from non-GLSLShader: "
                 << vertex_shader->id();
      return nullptr;
    }
    if (fragment_shader->implementation() != GLSLShader::kImplementationName) {
      LOG(ERROR) << "Cannot link GLSLShaderProgram from non-GLSLShader: "
                 << fragment_shader->id();
      return nullptr;
    }
    auto new_program = AllocateUniqueObject<GLSLShaderProgram>(
        metadata, static_cast<GLSLShader*>(vertex_shader),
        static_cast<GLSLShader*>(fragment_shader));
    if (new_program->Create()) {
      return std::move(new_program);
    } else {
      LOG(ERROR) << "ShaderProgram Create() failed.";
    }
  }
  LOG(ERROR) << "Unable to create shader program for implementation: "
             << implementation;
  return nullptr;
}

ShaderProgram::ShaderProgram(const ResourceMetadata& metadata)
    : Resource(metadata) {}

}  // namespace ogle
