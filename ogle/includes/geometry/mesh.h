/**
 * @file mesh.h
 * @brief Defines Mesh.
 */

#pragma once

#include "std/ogle_std.inc"
#include <memory>
#include "math/vector.h"
#include "memory/buffer.h"
#include "resource/resource.h"

namespace ogle {

/**
 * @brief A mesh representation with face-vertex connectivity information.
 *
 * Meshes contain detailed information about the mesh suitable for high-level
 * operations and algorithms. They are prepared for use on a rendering device by
 * constructing a BufferedMesh.
 */
class Mesh : public Resource {
 public:
  friend class MeshProcessing;

  struct MeshFace;

  /**
   * @brief Mesh vertex, associated attributes, and face connections.
   */
  struct MeshVertex {
    Vector3f vertex;  ///< Vertex location.
    Vector2f uv;  ///< 2D texture coordinate.
    Vector3f vertex_normal;  ///< Vertex normal.

    /// Faces connected to this Vertex.
    ogle::stl_vector<const MeshFace*> adjoining_faces;

    /**
     * @brief Less than operator. Compares vertex attributes in order.
     * @param lhs Left operand.
     * @param rhs Right operand.
     * @return true if lhs < rhs.
     */
    friend const bool operator<(const MeshVertex& lhs, const MeshVertex& rhs);
  };

  using VertexIndex = stl_vector<MeshVertex>::size_type;

  /**
   * @brief A single face of a mesh.
   */
  struct MeshFace {
    /// Indices of vertices making up this face.
    stl_vector<VertexIndex> vertex_indices;
  };

  /// Number of vertices per face. Only triangles are stored.
  static constexpr int kVerticesPerFace = 3;

  /// Type identifying mesh resources.
  static constexpr ResourceType kResourceType = ResourceType::MESH;

  explicit Mesh(const ResourceMetadata& metadata);

  /**
   * @brief Loads a new mesh from resource metadata.
   * @param metadata Metadata for mesh.
   * @return New mesh, or null on failure.
   */
  static std::unique_ptr<Mesh> Load(const ResourceMetadata& metadata);

  /**
   * @brief Adds a new face to this mesh.
   *
   * An empty argument is ignored; the corresponding vertex attribute is zeroed
   * out. All non-empty vectors passed to this function must be of equal
   * length.
   *
   * @param vertices Face vertices.
   * @param uvs 2D texture coordinates.
   * @param vertex_normals Normals for each vertex.
   * @return true if adding face succeeded, false on error.
   */
  const bool AddFace(const stl_vector<Vector3f>& vertices,
                     const stl_vector<Vector2f>& uvs,
                     const stl_vector<Vector3f>& vertex_normals);

  /**
   * @brief Clears all mesh representation data.
   */
  void Clear();

  /**
   * @brief Returns vertices.
   */
  const stl_vector<MeshVertex>& mesh_vertices() const;

  /**
   * @brief Returns faces.
   */
  const stl_vector<MeshFace>& mesh_faces() const;

 protected:
  /// Mesh vertices. Order determines indices for index buffers.
  stl_vector<MeshVertex> mesh_vertices_;

  /// Mesh faces.
  stl_vector<MeshFace> mesh_faces_;
};

}  // namespace ogle
