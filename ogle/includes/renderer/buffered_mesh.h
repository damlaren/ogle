/**
 * @file buffered_mesh.h
 * @brief Defines BufferedMesh.
 */

#pragma once

#include "std/ogle_std.inc"
#include "math/vector.h"
#include "memory/buffer.h"

namespace ogle {

class Configuration;
class Mesh;

/// 3D vertex buffer type.
using VertexBuffer = Buffer<Vector3f>;

/// 2D texture coordinate buffer.
using TexCoordUVBuffer = Buffer<Vector2f>;

/// 3D texture coordinate buffer.
using TexCoordUVWBuffer = Buffer<Vector3f>;

/// 3D normal vector buffer.
using NormalBuffer = Buffer<Vector3f>;

/// Index buffer type.
using IndexBuffer = Buffer<std::uint32_t>;

/**
 * @brief A 3D geometry mesh that has been prepared for rendering.
 *
 * It is subclassed to implement meshes that are ready to be rendered by
 * specific graphics APIs and hardware. It is meant to prepare raw data buffers,
 * not to provide more functionality for the Mesh.
 */
class BufferedMesh {
 public:
  /**
   * @brief Constructor.
   * @param mesh Const reference to mesh to prepare for rendering.
   */
  explicit BufferedMesh(const Mesh& mesh);

  /**
   * @brief Destructor.
   */
  virtual ~BufferedMesh() = default;

  /**
   * @brief Creates a BufferedMesh.
   * @param configuration Rendering configuration.
   * @param mesh Mesh to create render buffers for.
   * @return new mesh.
   */
  static std::unique_ptr<BufferedMesh> Load(const Configuration& configuration,
                                            const Mesh& mesh);

  //@{
  /**
   * @brief Mesh data buffer accessors.
   * @return Reference to buffer.
   */
  virtual const VertexBuffer& vertices() const = 0;
  virtual const TexCoordUVBuffer& uvs() const = 0;
  virtual const NormalBuffer& normals() const = 0;
  virtual const IndexBuffer& indices() const = 0;
  //@}

 protected:
  /**
   * @brief Prepares buffers for rendering the Mesh.
   * @return success or failure.
   */
  virtual bool Create() = 0;

  /// Reference to Mesh to prepare buffers for.
  const Mesh& mesh_;
};

}  // namespace ogle

