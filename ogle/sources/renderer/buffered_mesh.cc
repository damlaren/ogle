/**
 * @file Implements buffered_mesh.h.
 */

#include "renderer/buffered_mesh.h"
#include "config/configuration.h"
#include "renderer/glfw_mesh_renderer.h"

namespace ogle {

BufferedMesh::BufferedMesh(const Mesh &mesh)
  : mesh_(mesh) {
}

std::unique_ptr<BufferedMesh> BufferedMesh::Load(
    const Configuration& configuration, const Mesh& mesh) {
  const stl_string implementation = configuration.Get<stl_string>(
      MeshRenderer::kConfigModule,
      MeshRenderer::kConfigAttributeImplementation).first;
  if (implementation == GLFWMeshRenderer::kConfigImplementationName) {
    auto new_object = AllocateUniqueObject<GLFWBufferedMesh>(mesh);
    if (new_object->Create()) {
      return std::move(new_object);
    } else {
      LOG(ERROR) << "GLFWBufferedMesh Create() failed.";
    }
  }
  LOG(ERROR) << "Unable to create BufferedMesh for implementation: "
             << implementation;
  return nullptr;
}

}  // namespace ogle
