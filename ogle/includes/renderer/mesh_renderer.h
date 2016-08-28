/**
 * @file mesh_renderer.h
 * @brief Defines MeshRenderer.
 */

#pragma once

#include "std/ogle_std.inc"
#include "renderer/renderer.h"

namespace ogle {

class BufferedMesh;
class Configuration;
class Material;

/**
 * @brief Base class for all MeshRenderers.
 *
 * Subclasses handle different APIs.
 */
class MeshRenderer : public Renderer {
 public:
  /**
   * @brief Creates a new MeshRenderer.
   * @param configuration Renderer configuration.
   * @param mesh Mesh to create renderer for.
   * @param material Material to use for rendering.
   * @return New renderer, or nullptr on failure.
   */
  static MeshRenderer* Load(const Configuration& configuration,
                            const BufferedMesh& mesh, Material* material);

 protected:
  /**
   * @brief Constructor.
   * @param mesh Mesh to render.
   */
  explicit MeshRenderer(const BufferedMesh& mesh);

  /// Reference to mesh to render. Memory is managed elsewhere.
  const BufferedMesh& buffered_mesh_;
};

}  // namespace ogle

