/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file Defines GLFWMeshRenderer.
 */

#ifndef OGLE_INCLUDES_RENDERER_GLFW_MESH_RENDERER_H_
#define OGLE_INCLUDES_RENDERER_GLFW_MESH_RENDERER_H_

#include "std/ogle_std.inc"
#include "renderer/glfw_buffered_mesh.h"
#include "renderer/mesh_renderer.h"
#include "renderer/opengl_primitive_types.h"

namespace ogle {

class ShaderProgram;

/**
 * @brief MeshRenderer implemented with GLFW & OpenGL.
 */
class GLFWMeshRenderer : public MeshRenderer {
 public:
  /// String to specify use of this implementation in configuration file.
  static const stl_string kConfigImplementationName;

  /**
   * @brief Constructor. Call Create() to complete object construction.
   *
   * @param mesh Mesh to render.
   * @param shader_program Shader program to use in render pass.
   */
  GLFWMeshRenderer(const Mesh& mesh, ShaderProgram *shader_program);

  /**
   * @brief Destructor. Deallocates OpenGL objects.
   */
  ~GLFWMeshRenderer() override;

  /**
   * @brief Allocates OpenGL objects used for rendering.
   * @return success/failure.
   */
  bool Create();

  void Render(const Transform& transform, Entity *camera) override;

 private:
  struct Data;

  // TODO(damlaren): Don't duplicate this for each MeshRenderer.
  /// Mesh prepared for rendering.
  std::unique_ptr<GLFWBufferedMesh> buffered_mesh_;

  /// Shader program to use in rendering pass.
  ShaderProgram* shader_program_;

  /// OpenGL ID for vertex buffer.
  ogle::GLuint vertex_buffer_id_;

  /// OpenGL ID for vertex buffer array object.
  ogle::GLuint vertex_array_id_;

  /// OpenGL ID for index buffer.
  ogle::GLuint index_buffer_id_;
};

}  // namespace ogle

#endif  // OGLE_INCLUDES_RENDERER_GLFW_MESH_RENDERER_H_
