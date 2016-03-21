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
#include "entity/entity.h"
#include "geometry/mesh.h"
#include "geometry/transform.h"
#include "geometry/transformation_matrix.h"
#include "renderer/camera.h"
#include "renderer/glsl_shader.h"

namespace ogle {

GLFWMeshRenderer::GLFWMeshRenderer(
    const Mesh &mesh, GLSLShaderProgram* shader_program)
  : MeshRenderer(mesh), shader_program_(shader_program) {
}

GLFWMeshRenderer::~GLFWMeshRenderer() {
  if (created_) {
    glDeleteBuffers(1, &vertex_buffer_id_);
    glDeleteBuffers(1, &index_buffer_id_);
    glDeleteVertexArrays(1, &vertex_array_id_);
  }
}

bool GLFWMeshRenderer::Create() {
  // Create Mesh with renderable buffers.
  buffered_mesh_ = std::move(std::make_unique<GLFWBufferedMesh>(mesh_));
  if (!buffered_mesh_->Create()) {
    return false;
  }

  // Create vertex buffer and make it active array buffer.
  glGenBuffers(1, &vertex_buffer_id_);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id_);

  // Copy data to active array buffer. This may be in GPU memory, but
  // that's up to the graphics driver.
  glBufferData(GL_ARRAY_BUFFER, buffered_mesh_->vertices().SizeInBytes(),
               buffered_mesh_->vertices().data(), GL_STATIC_DRAW);

  // Create vertex array and bind it to be currently active.
  glGenVertexArrays(1, &vertex_array_id_);
  glBindVertexArray(vertex_array_id_);

  // Define vertex attribute data format and location, using
  // currently bound buffer & vertex array.
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

  // Do it all again for index buffer.
  glGenBuffers(1, &index_buffer_id_);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_id_);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, buffered_mesh_->indices().SizeInBytes(),
               buffered_mesh_->indices().data(), GL_STATIC_DRAW);

  created_ = true;
  return true;
}

void GLFWMeshRenderer::Render(const Transform& transform,
                              Entity *camera) {
  shader_program_->UseProgram();

  Matrix44f model_matrix = transform.TransformationMatrix3D();

  auto camera_component = camera->camera();
  if (camera_component == nullptr) {
    LOG(ERROR) << "Camera Entity needs Camera component.";
    return;
  }
  Matrix44f view_matrix = camera_component->GetViewMatrix(camera->transform_);
  Matrix44f projection_matrix = camera_component->GetProjectionMatrix();

  shader_program_->SetUniformMatrix44f(ShaderProgram::kModelMatrixArg,
                                       model_matrix);
  shader_program_->SetUniformMatrix44f(ShaderProgram::kViewMatrixArg,
                                       view_matrix);
  shader_program_->SetUniformMatrix44f(ShaderProgram::kProjectionMatrixArg,
                                       projection_matrix);

  // Enable vertex array attribute for rendering.
  glBindVertexArray(vertex_array_id_);
  glEnableVertexAttribArray(0);

  // Use index buffer to specify vertex order.
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_id_);

  // Draw.
  static_assert(std::is_same<BufferIndex, std::uint32_t>::value,
                "GLFWMeshRenderer assumes 32-bit unsigned BufferIndex.");
  glDrawElements(GL_TRIANGLES, buffered_mesh_->indices().num_elements(),
                 GL_UNSIGNED_INT, static_cast<void*>(0));
}

}  // namespace ogle
