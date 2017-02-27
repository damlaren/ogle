/**
 * @file mesh_processing.cc
 * @brief Defines MeshProcessing.
 */

#pragma once

#include "std/ogle_std.inc"
#include "geometry/mesh.h"

namespace ogle {

class MeshProcessing {
 public:
  /**
   * @brief Computes vertex normals as average of surrounding face normals.
   *
   * It's assumed each face is triangular.
   *
   * @param[in,out] mesh Mesh to compute normals for.
   */
  static void ComputeAveragedNormals(Mesh* mesh);
};

}  // namespace ogle
