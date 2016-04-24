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

#include "std/ogle_std.inc"
#include "math/vector.h"

namespace ogle {

class FilePath;
class Mesh;

/**
 * @brief Contains functions for loading Meshes.
 */
class MeshLoader {
 public:
  /**
   * @brief Creates a Mesh from parsing a file.
   * @param file_path Path to file to load. Extension determines file format.
   * @param[out] mesh Storage for Mesh built from file contents.
   * @return success or failure.
   */
  static const bool LoadMesh(const FilePath& file_path, Mesh* mesh);

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
    OBJ  // Wavefront OBJ.
  };

  /**
   * @brief Determines format of Mesh stored in file.
   * @param file_path Path to file to inspect.
   * @return File format enum.
   */
  static const MeshFileFormat DetermineMeshFormat(const FilePath& file_path);

  /**
   * @brief Loads a MeshGraph from an OBJ file.
   * @param file_path Path to file to load.
   * @param[out] mesh Storage for Mesh built from file contents.
   * @return true if loading succeeded.
   */
  static const bool LoadOBJ(const FilePath& file_path, Mesh* mesh);
};

}  // namespace ogle

#endif  // LIBRARIES_GEOMETRY_INCLUDES_GEOMETRY_MESH_LOADER_H_
