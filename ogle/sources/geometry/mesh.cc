/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file Implements MeshGraph.
 */

#include "geometry/mesh.h"
#include "easylogging++.h"  // NOLINT
#include "file_system/file_path.h"
#include "geometry/mesh_loader.h"

namespace ogle {

const bool operator<(const Mesh::MeshVertex& lhs, const Mesh::MeshVertex& rhs) {
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

const stl_string Mesh::kResourceType = "mesh";

Mesh::Mesh(const ResourceMetadata& metadata)
  : Resource(metadata) {
}

std::unique_ptr<Mesh> Mesh::Load(const ResourceMetadata& metadata) {
  return std::move(MeshLoader::LoadMesh(metadata));
}

const bool Mesh::AddFace(const stl_vector<Vector3f>& vertices,
                         const stl_vector<Vector2f>& uvs,
                         const stl_vector<Vector3f>& vertex_normals) {
  if (vertices.empty()) {
    LOG(ERROR) << "Cannot add new face from empty vertices.";
    return false;
  }

  if ((!uvs.empty() && uvs.size() != vertices.size()) ||
      (!vertex_normals.empty() && vertex_normals.size() != vertices.size())) {
    LOG(ERROR) << "Vertex attributes must be same length as vertices vector.";
    return false;
  }

  stl_vector<const MeshVertex*> face_vertices;
  for (stl_vector<Vector3f>::size_type index = 0; index < vertices.size();
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

void Mesh::Clear() {
  mesh_vertices_.clear();
  mesh_faces_.clear();
}

const stl_map<Mesh::MeshVertex, BufferIndex>& Mesh::mesh_vertices() const {
  return mesh_vertices_;
}

const stl_vector<Mesh::MeshFace>& Mesh::mesh_faces() const {
  return mesh_faces_;
}

}  // namespace ogle