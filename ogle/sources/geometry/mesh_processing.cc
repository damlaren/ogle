/**
 * @file mesh_processing.cc
 * @brief Implements mesh_processing.h.
 */

#include "geometry/mesh_processing.h"
#include "easylogging++.h"  // NOLINT
#include "math/vector.h"

namespace ogle {

void MeshProcessing::ComputeAveragedNormals(Mesh* mesh) {
  stl_vector<Vector3f> new_normals;
  for (const Mesh::MeshVertex& mesh_vertex : mesh->mesh_vertices_) {
    Vector3f new_vertex_normal = Vector3f::Zero();
    for (const Mesh::MeshFace* face : mesh_vertex.adjoining_faces) {
      CHECK(face->vertex_indices.size() == 3)
          << "Faces are assumed to have 3 vertices.";
      const auto& vertex_0 = mesh->mesh_vertices_[0];
      const auto& vertex_1 = mesh->mesh_vertices_[1];
      const auto& vertex_2 = mesh->mesh_vertices_[2];
      new_vertex_normal +=
          (vertex_1.vertex - vertex_0.vertex).Cross(
              vertex_2.vertex - vertex_0.vertex).NormalizedCopy();
    }
    new_normals.emplace_back(new_vertex_normal.NormalizedCopy());
  }

  // Swap normals.
  for (Mesh::VertexIndex index = 0; index < mesh->mesh_vertices_.size();
       index++) {
    mesh->mesh_vertices_[index].vertex_normal = new_normals[index];
  }
}

}  // namespace ogle
