/**
 * @file mesh.cc
 * @brief Implements mesh.h.
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

  stl_vector<VertexIndex> face_vertices;
  for (stl_vector<Vector3f>::size_type index = 0; index < vertices.size();
       index++) {
    MeshVertex mesh_vertex;
    mesh_vertex.vertex = vertices[index];
    mesh_vertex.uv = (!uvs.empty())? uvs[index] : Vector2f::Zero();
    mesh_vertex.vertex_normal = (!vertex_normals.empty())?
        vertex_normals[index] : Vector3f::Zero();

    mesh_vertices_.emplace_back(std::move(mesh_vertex));
    face_vertices.emplace_back(mesh_vertices_.size() - 1);
  }
  mesh_faces_.emplace_back(std::move(MeshFace{std::move(face_vertices)}));
  const MeshFace* new_mesh_face = &mesh_faces_.back();
  for (const VertexIndex index : new_mesh_face->vertex_indices) {
    mesh_vertices_[index].adjoining_faces.emplace_back(new_mesh_face);
  }

  return true;
}

void Mesh::Clear() {
  mesh_vertices_.clear();
  mesh_faces_.clear();
}

const stl_vector<Mesh::MeshVertex>& Mesh::mesh_vertices() const {
  return mesh_vertices_;
}

const stl_vector<Mesh::MeshFace>& Mesh::mesh_faces() const {
  return mesh_faces_;
}

}  // namespace ogle
