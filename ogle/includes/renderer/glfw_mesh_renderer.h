/**
 * @file glfw_mesh_renderer.h
 * @brief Defines GLFWMeshRenderer.
 */

#pragma once

#include "std/ogle_std.inc"
#include "renderer/glfw_buffered_mesh.h"
#include "renderer/mesh_renderer.h"
#include "renderer/opengl_primitive_types.h"

namespace ogle {

class GLSLShaderProgram;

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
   * @param material Material to use in render pass.
   */
  GLFWMeshRenderer(const BufferedMesh& mesh, Material* material);

  /**
   * @brief Destructor. Deallocates OpenGL objects.
   */
  ~GLFWMeshRenderer() override;

  /**
   * @brief Allocates OpenGL objects used for rendering.
   * @return success/failure.
   */
  bool Create();

  void Render(const Transform& transform, const Entity& camera,
              const stl_vector<const Entity*>& lights) override;

 private:
  struct Data;

  /// Material to use to render mesh.
  Material* material_;

  /// OpenGL ID for vertex buffer.
  ogle::GLuint vertex_buffer_id_;

  /// OpenGL ID for normal buffer.
  ogle::GLuint normal_buffer_id_;

  /// OpenGL ID for vertex buffer array object.
  ogle::GLuint vertex_array_id_;

  /// OpenGL ID for index buffer.
  ogle::GLuint index_buffer_id_;
};

}  // namespace ogle

