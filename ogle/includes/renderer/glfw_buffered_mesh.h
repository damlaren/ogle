/**
 * @file Defines GLFWBufferedMesh.
 */

#ifndef OGLE_INCLUDES_RENDERER_GLFW_BUFFERED_MESH_H_
#define OGLE_INCLUDES_RENDERER_GLFW_BUFFERED_MESH_H_

#include "std/ogle_std.inc"
#include "renderer/buffered_mesh.h"

namespace ogle {

/**
 * @brief A BufferedMesh implementation for OpenGL, GLSL, and GLFW.
 */
class GLFWBufferedMesh : public BufferedMesh {
 public:
  /**
   * @brief Constructor.
   * @param mesh Mesh to prepare buffers for.
   */
  explicit GLFWBufferedMesh(const Mesh& mesh);

  const VertexBuffer& vertices() const override;
  const TexCoordUVBuffer& uvs() const override;
  const NormalBuffer& normals() const override;
  const IndexBuffer& indices() const override;

  bool Create() override;

 protected:
  /// Vertex buffer.
  VertexBuffer vertices_;

  /// 2D texture coordinate buffer.
  TexCoordUVBuffer uvs_;

  /// Vertex normals.
  NormalBuffer normals_;

  /// Index buffer.
  IndexBuffer indices_;
};

}  // namespace ogle

#endif  // OGLE_INCLUDES_RENDERER_GLFW_BUFFERED_MESH_H_
