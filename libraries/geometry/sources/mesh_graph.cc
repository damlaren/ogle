/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file Implements MeshGraph.
 */

#include "geometry/mesh_graph.h"
#include "easylogging++.h"  // NOLINT

namespace ogle {

const bool operator<(const MeshGraph::MeshVertex& lhs,
                     const MeshGraph::MeshVertex& rhs) {
  if (lhs.vertex < rhs.vertex) {
    return true;
  } else if (lhs.vertex > rhs.vertex) {
    return false;
  }

  if (lhs.uv < rhs.uv) {
    return true;
  } else if (lhs.uv > rhs.uv) {
    return false;
  }

  if (lhs.vertex_normal < rhs.vertex_normal) {
    return true;
  } else {
    return false;
  }
}

const bool MeshGraph::AddFace(const std::vector<Vector3f>& vertices,
                              const std::vector<Vector2f>& uvs,
                              const std::vector<Vector3f>& vertex_normals) {
  if (vertices.empty()) {
    LOG(ERROR) << "Cannot add new face from empty vertices.";
    return false;
  }

  if ((!uvs.empty() && uvs.size() != vertices.size()) ||
      (!vertex_normals.empty() && vertex_normals.size() != vertices.size())) {
    LOG(ERROR) << "Vertex attributes must be same length as vertices vector.";
    return false;
  }

  std::vector<const MeshVertex*> face_vertices;
  for (std::vector<Vector3f>::size_type index = 0; index < vertices.size();
       index++) {
    MeshVertex mesh_vertex;
    mesh_vertex.vertex = vertices[index];
    mesh_vertex.uv = (!uvs.empty())? uvs[index] : Vector2f::Zero();
    mesh_vertex.vertex_normal = (!vertex_normals.empty())?
        vertex_normals[index] : Vector3f::Zero();

    auto insertion_result = mesh_vertices_.insert(
        {std::move(mesh_vertex), mesh_vertices_.size()});
    face_vertices.emplace_back(&insertion_result.first->first);
  }
  mesh_faces_.emplace_back(std::move(MeshFace{std::move(face_vertices)}));
  const MeshFace* new_mesh_face = &mesh_faces_.back();
  for (const MeshVertex* vertex_pointer : new_mesh_face->vertices) {
    vertex_pointer->adjoining_faces.emplace_back(new_mesh_face);
  }

  return true;
}

void MeshGraph::Clear() {
  mesh_vertices_.clear();
  mesh_faces_.clear();
}

const bool MeshGraph::BuildBuffers(VertexBuffer *vertex_buffer,
                                   TexCoordUVBuffer *uv_buffer,
                                   NormalBuffer *normal_buffer,
                                   IndexBuffer *index_buffer) const {
  if (vertex_buffer != nullptr) {
    *vertex_buffer = VertexBuffer(mesh_vertices_.size());
  }
  if (uv_buffer != nullptr) {
    *uv_buffer = TexCoordUVBuffer(mesh_vertices_.size());
  }
  if (normal_buffer != nullptr) {
    *normal_buffer = NormalBuffer(mesh_vertices_.size());
  }
  if (index_buffer != nullptr) {
    *index_buffer = IndexBuffer(mesh_faces_.size() * kVerticesPerFace);
  }

  // Build per-vertex buffers.
  for (const auto& vertex_index_pair : mesh_vertices_) {
    const MeshVertex& mesh_vertex = vertex_index_pair.first;
    const BufferIndex index = vertex_index_pair.second;

    if (index < 0 || index >= mesh_vertices_.size()) {
      LOG(ERROR) << "Invalid index assigned to vertex: " << index;
      return false;
    }

    if (vertex_buffer != nullptr) {
      vertex_buffer->SetDataValue(index, mesh_vertex.vertex);
    }
    if (uv_buffer != nullptr) {
      uv_buffer->SetDataValue(index, mesh_vertex.uv);
    }
    if (normal_buffer != nullptr) {
      normal_buffer->SetDataValue(index, mesh_vertex.vertex_normal);
    }
  }

  // Build index buffer.
  if (index_buffer == nullptr) {
    return true;
  }
  BufferIndex num_indices_set = 0;
  for (const auto& mesh_face : mesh_faces_) {
    for (const auto mesh_vertex : mesh_face.vertices) {
      const auto mesh_vertex_iterator = mesh_vertices_.find(*mesh_vertex);
      if (mesh_vertex_iterator != mesh_vertices_.end()) {
        const BufferIndex index = mesh_vertex_iterator->second;
        CHECK(index >= 0 && index < mesh_vertices_.size());  // Checked above.
        index_buffer->SetDataValue(num_indices_set++, index);
      } else {
        LOG(ERROR) << "Unknown vertex on face.";
        return false;
      }
    }
  }

  return true;
}

}  // namespace ogle
