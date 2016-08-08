/**
 * @file Implementation of mesh_renderer.h.
 */

#include "renderer/mesh_renderer.h"
#include "config/configuration.h"
#include "renderer/glfw_mesh_renderer.h"
#include "renderer/glsl_shader_program.h"
#include "renderer/material.h"

namespace ogle {

MeshRenderer* MeshRenderer::Load(const Configuration& configuration,
                                 const BufferedMesh& mesh, Material* material) {
  const stl_string implementation =
      configuration.Get<stl_string>(kConfigModule,
                                    kConfigAttributeImplementation)
          .first;
  if (implementation == GLFWMeshRenderer::kConfigImplementationName) {
    if (material->shader_program_->implementation() !=
        GLSLShaderProgram::kImplementationName) {
      LOG(ERROR) << "GLFWMeshRenderer requires GLSLShaderProgram.";
      return nullptr;
    }
    auto new_object = AllocateObject<GLFWMeshRenderer>(mesh, material);
    if (new_object->Create()) {
      return new_object;
    } else {
      delete new_object;
      LOG(ERROR) << "GLFWMeshRenderer Create() failed.";
    }
  }
  LOG(ERROR) << "Unable to create MeshRenderer for implementation: "
             << implementation;
  return nullptr;
}

MeshRenderer::MeshRenderer(const BufferedMesh& mesh)
    : Renderer(), buffered_mesh_(mesh) {}

}  // namespace ogle
