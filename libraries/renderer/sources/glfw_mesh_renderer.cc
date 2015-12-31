/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file Implementation of glfw_mesh_renderer.h.
 */

#include "renderer/glfw_mesh_renderer.h"
#include "geometry/mesh.h"
#include "renderer/glsl_shader.h"

namespace ogle {

GLFWMeshRenderer::GLFWMeshRenderer(
    std::shared_ptr<Mesh> mesh,
    std::shared_ptr<GLSLShaderProgram> shader_program) :
    MeshRenderer(mesh), shader_program_(shader_program) {
  // Create vertex buffer and make it active array buffer.
  glGenBuffers(1, &vertex_buffer_id_);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id_);

  // Copy data to active array buffer. This may be in GPU memory, but
  // that's up to the graphics driver.
  glBufferData(GL_ARRAY_BUFFER, mesh_->vertices().SizeInBytes(),
               mesh_->vertices().data_, GL_STATIC_DRAW);

  // Create vertex array.
  glGenVertexArrays(1, &vertex_array_id_);
}

GLFWMeshRenderer::~GLFWMeshRenderer() {
  glDeleteBuffers(1, &vertex_buffer_id_);
  glDeleteVertexArrays(1, &vertex_array_id_);
}

void GLFWMeshRenderer::Render() {
  // Set active vertex array and array buffer.
  glBindVertexArray(vertex_array_id_);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id_);

  // Define vertex attribute data format and location, using
  // currently bound buffer & vertex array.
  // TODO(damlaren): # components per vertex & type are hard-coded.
  const int kVertexArrayIndex = 0;
  glVertexAttribPointer(kVertexArrayIndex, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

  shader_program_->UseProgram();

  // Enable vertex array attribute for rendering.
  glEnableVertexAttribArray(kVertexArrayIndex);

  // Draw vertices.
  // TODO(damlaren): triangle strip vs. quad vs. other may vary.
  glDrawArrays(GL_TRIANGLE_STRIP, 0, mesh_->vertices().num_elements_);
}

}  // namespace ogle
