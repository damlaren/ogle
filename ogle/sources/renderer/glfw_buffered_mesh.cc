/**
 * @file glfw_buffered_mesh.cc
 * @brief Implements glfw_buffered_mesh.h.
 */

#include "renderer/glfw_buffered_mesh.h"
#include "easylogging++.h"  // NOLINT
#include "geometry/mesh.h"

namespace ogle {

GLFWBufferedMesh::GLFWBufferedMesh(const Mesh& mesh) : BufferedMesh(mesh) {}

const VertexBuffer& GLFWBufferedMesh::vertices() const { return vertices_; }

const TexCoordUVBuffer& GLFWBufferedMesh::uvs() const { return uvs_; }

const NormalBuffer& GLFWBufferedMesh::normals() const { return normals_; }

const IndexBuffer& GLFWBufferedMesh::indices() const { return indices_; }

bool GLFWBufferedMesh::Create() {
  const auto& mesh_vertices = mesh_.mesh_vertices();
  const auto& mesh_faces = mesh_.mesh_faces();

  vertices_ = std::move(VertexBuffer(mesh_vertices.size()));
  uvs_ = std::move(TexCoordUVBuffer(mesh_vertices.size()));
  normals_ = std::move(NormalBuffer(mesh_vertices.size()));
  indices_ = std::move(IndexBuffer(mesh_faces.size() * Mesh::kVerticesPerFace));

  // TODO(damlaren): Some data is not always available.

  // Build per-vertex buffers.
  for (BufferIndex index = 0; index < mesh_vertices.size(); index++) {
    const auto& mesh_vertex = mesh_vertices[index];

    if (index < 0 || index >= mesh_vertices.size()) {
      LOG(ERROR) << "Invalid index assigned to vertex: " << index;
      return false;
    }

    vertices_.SetDataValue(index, mesh_vertex.vertex);
    uvs_.SetDataValue(index, mesh_vertex.uv);
    normals_.SetDataValue(index, mesh_vertex.vertex_normal);
  }

  // Build index buffer.
  BufferIndex num_indices_set = 0;
  for (const auto& mesh_face : mesh_faces) {
    for (const auto index : mesh_face.vertex_indices) {
      indices_.SetDataValue(num_indices_set++, index);
    }
  }

  return true;
}

}  // namespace ogle
