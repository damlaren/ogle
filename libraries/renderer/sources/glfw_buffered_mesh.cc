/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

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

bool GLFWBufferedMesh::Prepare() {
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
        CHECK(index >= 0 && index < mesh_vertices.size());
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
