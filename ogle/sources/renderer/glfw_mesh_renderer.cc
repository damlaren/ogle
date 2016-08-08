/**
 * @file Implementation of glfw_mesh_renderer.h.
 */

#include "renderer/glfw_mesh_renderer.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "entity/entity.h"
#include "geometry/mesh.h"
#include "geometry/transform.h"
#include "geometry/transformation_matrix.h"
#include "renderer/camera.h"
#include "renderer/glsl_shader_program.h"
#include "renderer/material.h"
#include "renderer/shader_variable.h"

namespace ogle {

const stl_string GLFWMeshRenderer::kConfigImplementationName = "glfw";

GLFWMeshRenderer::GLFWMeshRenderer(const BufferedMesh& mesh, Material* material)
    : MeshRenderer(mesh),
      material_(material),
      vertex_buffer_id_(0),
      vertex_array_id_(0),
      index_buffer_id_(0) {}

GLFWMeshRenderer::~GLFWMeshRenderer() {
  glDeleteBuffers(1, &vertex_buffer_id_);
  glDeleteBuffers(1, &index_buffer_id_);
  glDeleteVertexArrays(1, &vertex_array_id_);
}

bool GLFWMeshRenderer::Create() {
  // Create vertex buffer and make it active array buffer.
  glGenBuffers(1, &vertex_buffer_id_);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id_);

  // Copy data to active array buffer. This may be in GPU memory, but
  // that's up to the graphics driver.
  glBufferData(GL_ARRAY_BUFFER, buffered_mesh_.vertices().SizeInBytes(),
               buffered_mesh_.vertices().data(), GL_STATIC_DRAW);

  // Create vertex array and bind it to be currently active.
  glGenVertexArrays(1, &vertex_array_id_);
  glBindVertexArray(vertex_array_id_);

  // Define vertex attribute data format and location, using
  // currently bound buffer & vertex array.
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

  // Do it all again for index buffer.
  glGenBuffers(1, &index_buffer_id_);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_id_);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, buffered_mesh_.indices().SizeInBytes(),
               buffered_mesh_.indices().data(), GL_STATIC_DRAW);

  return true;
}

void GLFWMeshRenderer::Render(const Transform& transform, Entity* camera) {
  material_->shader_program_->UseProgram();

  Matrix44f model_matrix = transform.TransformationMatrix3D();

  Camera* camera_component = camera->GetComponent<Camera>();
  if (camera_component == nullptr) {
    LOG(ERROR) << "Camera Entity needs Camera component.";
    return;
  }
  Matrix44f view_matrix = camera_component->GetViewMatrix(camera->transform_);
  Matrix44f projection_matrix = camera_component->GetProjectionMatrix();

  ShaderVariable variable = {ShaderProgram::kModelMatrixArg,
                             {4, 4},
                             ShaderVariableType::MATRIX,
                             ShaderScalarType::FLOAT,
                             model_matrix.data()};
  material_->shader_program_->SetVariable(variable);
  variable = {ShaderProgram::kViewMatrixArg,
              {4, 4},
              ShaderVariableType::MATRIX,
              ShaderScalarType::FLOAT,
              view_matrix.data()};
  material_->shader_program_->SetVariable(variable);
  variable = {ShaderProgram::kProjectionMatrixArg,
              {4, 4},
              ShaderVariableType::MATRIX,
              ShaderScalarType::FLOAT,
              projection_matrix.data()};
  material_->shader_program_->SetVariable(variable);

  // TODO(damlaren): bind other variables for surface properties, etc.

  // Enable vertex array attribute for rendering.
  glBindVertexArray(vertex_array_id_);
  glEnableVertexAttribArray(0);

  // Use index buffer to specify vertex order.
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_id_);

  // Draw.
  static_assert(std::is_same<BufferIndex, std::uint32_t>::value,
                "GLFWMeshRenderer assumes 32-bit unsigned BufferIndex.");
  glDrawElements(GL_TRIANGLES, buffered_mesh_.indices().num_elements(),
                 GL_UNSIGNED_INT, static_cast<void*>(0));
}

}  // namespace ogle
