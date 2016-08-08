/**
 * @file Implements glfw_buffered_mesh.h.
 */

#include "renderer/glfw_buffered_mesh.h"
#include "easylogging++.h"  // NOLINT
#include "geometry/mesh.h"

namespace ogle {

GLFWBufferedMesh::GLFWBufferedMesh(const Mesh& mesh)
  : BufferedMesh(mesh) {
}

const VertexBuffer& GLFWBufferedMesh::vertices() const {
  return vertices_;
}

const TexCoordUVBuffer& GLFWBufferedMesh::uvs() const {
  return uvs_;
}

const NormalBuffer& GLFWBufferedMesh::normals() const {
  return normals_;
}

const IndexBuffer& GLFWBufferedMesh::indices() const {
  return indices_;
}

bool GLFWBufferedMesh::Create() {
  const auto& mesh_vertices = mesh_.mesh_vertices();
  const auto& mesh_faces = mesh_.mesh_faces();

  vertices_ = std::move(VertexBuffer(mesh_vertices.size()));
  uvs_ = std::move(TexCoordUVBuffer(mesh_vertices.size()));
  normals_ = std::move(NormalBuffer(mesh_vertices.size()));
  indices_ = std::move(IndexBuffer(mesh_faces.size() * Mesh::kVerticesPerFace));

  // TODO(damlaren): Some data is not always available.

  // Build per-vertex buffers.
  for (const auto& vertex_index_pair : mesh_vertices) {
    const auto& mesh_vertex = vertex_index_pair.first;
    const BufferIndex index = vertex_index_pair.second;

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
    for (const auto mesh_vertex : mesh_face.vertices) {
      const auto mesh_vertex_iterator = mesh_vertices.find(*mesh_vertex);
      if (mesh_vertex_iterator != mesh_vertices.end()) {
        const BufferIndex index = mesh_vertex_iterator->second;
        if (index < 0 || index >= mesh_vertices.size()) {
          LOG(ERROR) << "Vertex index out of bounds.";
          return false;
        }
        indices_.SetDataValue(num_indices_set++, index);
      } else {
        LOG(ERROR) << "Unknown vertex on face.";
        return false;
      }
    }
  }

  return true;
}

}  // namespace ogle
