/**
 * @file glfw_mesh_renderer.cc
 * @brief Implementation of glfw_mesh_renderer.h.
 */

#include "renderer/glfw_mesh_renderer.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "entity/entity.h"
#include "entity/property.h"
#include "geometry/mesh.h"
#include "geometry/transform.h"
#include "geometry/transformation_matrix.h"
#include "renderer/camera.h"
#include "renderer/glsl_shader_program.h"
#include "renderer/light.h"
#include "renderer/material.h"

namespace ogle {

const stl_string GLFWMeshRenderer::kConfigImplementationName = "glfw";

GLFWMeshRenderer::GLFWMeshRenderer(const BufferedMesh& mesh, Material* material)
    : MeshRenderer(mesh),
      material_(material),
      vertex_buffer_id_(0),
      normal_buffer_id_(0),
      vertex_array_id_(0),
      index_buffer_id_(0) {}

GLFWMeshRenderer::~GLFWMeshRenderer() {
  glDeleteBuffers(1, &vertex_buffer_id_);
  glDeleteBuffers(1, &normal_buffer_id_);
  glDeleteBuffers(1, &index_buffer_id_);
  glDeleteVertexArrays(1, &vertex_array_id_);
}

bool GLFWMeshRenderer::Create() {
  // Create vertex array and bind it to be currently active.
  glGenVertexArrays(1, &vertex_array_id_);
  glBindVertexArray(vertex_array_id_);

  // Create vertex buffer and make it active array buffer.
  glGenBuffers(1, &vertex_buffer_id_);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id_);

  // Copy data to active array buffer. This may be in GPU memory, but
  // that's up to the graphics driver.
  glBufferData(GL_ARRAY_BUFFER, buffered_mesh_.vertices().SizeInBytes(),
               buffered_mesh_.vertices().data(), GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

  // Do the same stuff again for normal buffer.
  glGenBuffers(1, &normal_buffer_id_);
  glBindBuffer(GL_ARRAY_BUFFER, normal_buffer_id_);
  glBufferData(GL_ARRAY_BUFFER, buffered_mesh_.normals().SizeInBytes(),
               buffered_mesh_.normals().data(), GL_STATIC_DRAW);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

  // Do it all again for index buffer.
  glGenBuffers(1, &index_buffer_id_);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_id_);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, buffered_mesh_.indices().SizeInBytes(),
               buffered_mesh_.indices().data(), GL_STATIC_DRAW);

  return true;
}

void GLFWMeshRenderer::Render(const Transform& transform, const Entity& camera,
                              const stl_vector<const Entity*>& lights) {
  material_->UseProgram();

  Matrix44f model_matrix = transform.TransformationMatrix3D();

  Camera* camera_component = camera.GetComponent<Camera>();
  if (camera_component == nullptr) {
    LOG(ERROR) << "Camera Entity needs Camera component.";
    return;
  }
  Matrix44f view_matrix = camera_component->GetViewMatrix(camera.transform_);
  Matrix44f projection_matrix = camera_component->GetProjectionMatrix();

  // Set camera uniforms in shader.
  material_->SetVariable(PropertyInstance<float>(
      ShaderProgram::StandardShaderArgumentNames::kModelMatrixArg, {4, 4},
      model_matrix.data()));
  material_->SetVariable(PropertyInstance<float>(
      ShaderProgram::StandardShaderArgumentNames::kViewMatrixArg, {4, 4},
      view_matrix.data()));
  material_->SetVariable(PropertyInstance<float>(
      ShaderProgram::StandardShaderArgumentNames::kProjectionMatrixArg, {4, 4},
      projection_matrix.data()));

  // Set light uniforms in shader.
  if (!lights.empty()) {
    if (!lights[0]) {
      LOG(ERROR) << "Attempted to compute lighting from null light";
      goto end_lighting;
    }
    const Entity& light_entity_0 = *lights[0];
    const auto light_position = light_entity_0.transform_.world_position();
    material_->SetVariable(PropertyInstance<float>(
        ShaderProgram::StandardShaderArgumentNames::kLightPosition, {3},
        light_position.data()));

    Light* light = light_entity_0.GetComponent<Light>();
    if (!light) {
      LOG(ERROR) << "Entity does not have light attached.";
      goto end_lighting;
    }
    const Property* ambient_color_property =
        light->GetProperty(Light::StandardPropertyName::kAmbientColor);
    if (ambient_color_property) {
      material_->SetVariable(
          ShaderProgram::StandardShaderArgumentNames::kLightAmbientColor,
          *ambient_color_property);
    }
    const Property* diffuse_color_property =
        light->GetProperty(Light::StandardPropertyName::kDiffuseColor);
    if (diffuse_color_property) {
      material_->SetVariable(
          ShaderProgram::StandardShaderArgumentNames::kLightDiffuseColor,
          *diffuse_color_property);
    }
    const Property* specular_color_property =
        light->GetProperty(Light::StandardPropertyName::kSpecularColor);
    if (specular_color_property) {
      material_->SetVariable(
          ShaderProgram::StandardShaderArgumentNames::kLightSpecularColor,
          *specular_color_property);
    }
  }
end_lighting:

  // Set material properties on shader.
  material_->SetBoundVariables();

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
