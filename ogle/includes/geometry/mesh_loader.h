/**
 * @file Defines MeshLoader.
 */

#ifndef OGLE_INCLUDES_GEOMETRY_MESH_LOADER_H_
#define OGLE_INCLUDES_GEOMETRY_MESH_LOADER_H_

#include "std/ogle_std.inc"
#include <memory>
#include "geometry/mesh.h"
#include "math/vector.h"

namespace ogle {

class FilePath;
class ResourceMetadata;

/**
 * @brief Contains functions for loading Meshes.
 */
class MeshLoader {
 public:
  /**
   * @brief Creates a Mesh from parsing a file.
   * @param metadata Metadata for mesh to load.
   * @return New mesh, or null on failure.
   */
  static std::unique_ptr<Mesh> LoadMesh(const ResourceMetadata& metadata);

 private:
  /**
   * @brief Wraps vectors containing mesh data.
   */
  struct MeshAttributes {
    stl_vector<Vector3f> vertices;
    stl_vector<Vector2f> tex_coords_uv;
    stl_vector<Vector3f> tex_coords_uvw;
    stl_vector<Vector3f> normals;
  };

  /**
   * @brief Supported formats for parsing Meshes.
   */
  enum class MeshFileFormat {
    UNKNOWN,  // Format could not be determined.
    OBJ       // Wavefront OBJ.
  };

  /**
   * @brief Determines format of Mesh stored in file.
   * @param metadata Metadata for mesh.
   * @return File format enum.
   */
  static const MeshFileFormat DetermineMeshFormat(
      const ResourceMetadata& metadata);

  /**
   * @brief Loads a mesh from an OBJ file.
   * @param metadata Metadata for mesh to load.
   * @return New mesh, or null on failure.
   */
  static std::unique_ptr<Mesh> LoadOBJ(const ResourceMetadata& metadata);
};

}  // namespace ogle

#endif  // OGLE_INCLUDES_GEOMETRY_MESH_LOADER_H_
