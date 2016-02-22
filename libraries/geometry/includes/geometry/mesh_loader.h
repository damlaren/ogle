/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file Defines MeshLoader.
 */

#ifndef LIBRARIES_GEOMETRY_INCLUDES_GEOMETRY_MESH_LOADER_H_
#define LIBRARIES_GEOMETRY_INCLUDES_GEOMETRY_MESH_LOADER_H_

#include <string>
#include <vector>
#include "math/vector.h"

namespace ogle {

class Mesh;
class MeshGraph;

/**
 * @brief Contains functions for loading Meshes.
 */
class MeshLoader {
 public:
  /**
   * @brief Wraps vectors containing mesh data.
   */
  struct MeshAttributes {
    std::vector<Vector3f> vertices;
    std::vector<Vector2f> tex_coords_uv;
    std::vector<Vector3f> tex_coords_uvw;
    std::vector<Vector3f> normals;
  };

  /**
   * @brief Creates a new Mesh constructed from parsing a file.
   *
   * The caller takes ownership of the Mesh.
   *
   * @param file_path Path to file to load. Extension determines file format.
   * @return Pointer to new Mesh, or nullptr if creation failed.
   */
  static Mesh* LoadMesh(const std::string& file_path);

 private:
  /**
   * @brief Supported formats for parsing Meshes.
   */
  enum class MeshFileFormat {
    UNKNOWN,  // Format could not be determined.
    OBJ  // Wavefront OBJ.
  };

  /**
   * @brief Determines format of Mesh stored in file.
   * @param file_path Path to file to inspect.
   * @return File format enum.
   */
  static const MeshFileFormat DetermineMeshFormat(const std::string& file_path);

  /**
   * @brief Loads a MeshGraph from an OBJ file.
   * @param file_path Path to file to load.
   * @param[out] mesh_graph Mesh graph built from file contents.
   * @return true if loading succeeded.
   */
  static bool LoadOBJ(const std::string& file_path, MeshGraph* mesh_graph);

  /**
   * @brief Creates a new Mesh from MeshGraph.
   * @param mesh_graph Graph to construct Mesh from.
   * @return New Mesh (or nullptr on failure). The caller is responsible for
   *     deallocation.
   */
  static Mesh* BuildMesh(const MeshGraph& mesh_graph);
};

}  // namespace ogle

#endif  // LIBRARIES_GEOMETRY_INCLUDES_GEOMETRY_MESH_LOADER_H_
