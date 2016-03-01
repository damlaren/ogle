/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file Defines GLFWBufferedMesh.
 */

#ifndef LIBRARIES_RENDERER_INCLUDES_RENDERER_GLFW_BUFFERED_MESH_H_
#define LIBRARIES_RENDERER_INCLUDES_RENDERER_GLFW_BUFFERED_MESH_H_

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

  //@{
  /**
   * @brief Mesh data buffer accessors.
   * @return Reference to buffer.
   */
  const VertexBuffer& vertices() const;
  const TexCoordUVBuffer& uvs() const;
  const NormalBuffer& normals() const;
  const IndexBuffer& indices() const;
  //@}

  bool Prepare() override;

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

#endif  // LIBRARIES_RENDERER_INCLUDES_RENDERER_GLFW_BUFFERED_MESH_H_
