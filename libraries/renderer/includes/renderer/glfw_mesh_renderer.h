/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file Defines GLFWMeshRenderer.
 */

#ifndef LIBRARIES_RENDERER_INCLUDES_RENDERER_GLFW_MESH_RENDERER_H_
#define LIBRARIES_RENDERER_INCLUDES_RENDERER_GLFW_MESH_RENDERER_H_

#include "renderer/mesh_renderer.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"

namespace ogle {

class GLSLShaderProgram;

/**
 * @brief MeshRenderer implemented with GLFW & OpenGL.
 */
class GLFWMeshRenderer : public MeshRenderer {
 public:
  /**
   * @brief Constructor. Allocates OpenGL objects used for rendering.
   *
   * @param mesh Handle to Mesh to render.
   * @param shader_program Shader program to use in render pass.
   */
  GLFWMeshRenderer(std::shared_ptr<Mesh> mesh,
                   std::shared_ptr<GLSLShaderProgram> shader_program);

  /**
   * @brief Destructor. Deallocates OpenGL objects.
   */
  ~GLFWMeshRenderer() override;

  void Render(const Vector3f& position,
              const Camera &camera) override;

 private:
  /// Shader program to use in rendering pass.
  std::shared_ptr<GLSLShaderProgram> shader_program_;

  /// ID for OpenGL mesh vertex buffer.
  GLuint vertex_buffer_id_;

  /// ID for OpenGL mesh vertex array.
  GLuint vertex_array_id_;
};

}  // namespace ogle

#endif  // LIBRARIES_RENDERER_INCLUDES_RENDERER_GLFW_MESH_RENDERER_H_
