/**
 * @file mesh_processing.cc
 * @brief Defines MeshProcessing.
 */

#pragma once

#include "geometry/mesh.h"

namespace ogle {

class MeshProcessing {
 public:
  /**
   * @brief Computes vertex normals as average of surrounding face normals.
   * @param[in,out] mesh Mesh to compute normals for.
   */
  void ComputeAveragedNormals(Mesh* mesh);
};

}  // namespace ogle
