/**
 * @file Defines Shader.
 */

#ifndef OGLE_INCLUDES_RENDERER_SHADER_H_
#define OGLE_INCLUDES_RENDERER_SHADER_H_

#include "std/ogle_std.inc"
#include <memory>
#include "resource/resource.h"

namespace ogle {

class Configuration;
class ResourceMetadata;

/**
 * @brief The type of a Shader.
 */
enum class ShaderType {
  Vertex,   ///< Vertex shader.
  Fragment  ///< Fragment, aka pixel shader.
};

/**
 * @brief Base class for all Shaders.
 *
 * Handles shader operations in an API-independent manner.
 * Subclassed Shaders are based on specific APIs.
 */
class Shader : public Resource {
 public:
  /// Type identifying shader resources.
  static constexpr ResourceType kResourceType = ResourceType::SHADER;

  ///@{
  /// A shader subtype specification in metadata.
  static const stl_string kVertexShaderSubType;
  static const stl_string kFragmentShaderSubType;
  ///@}

  /**
   * @brief Loads a shader from text.
   * @param metadata Metadata for shader file.
   * @return New shader.
   */
  static std::unique_ptr<Shader> Load(const ResourceMetadata& metadata);

  /**
   * @brief Accessor.
   * @return Shader text.
   */
  const stl_string& shader_text() const;

  /**
   * @brief Accessor.
   * @return Shader type.
   */
  const ShaderType shader_type() const;

 protected:
  /**
   * @brief Constructor.
   * @param metadata Metadata to use to infer Shader type and location.
   * @param shader_text Program text to copy.
   * @param type Type of this shader.
   */
  Shader(const ResourceMetadata& metadata, const stl_string& shader_text,
         const ShaderType type);

  /// Shader text.
  stl_string shader_text_;

  /// Shader type.
  ShaderType shader_type_;
};

}  // namespace ogle

#endif  // OGLE_INCLUDES_RENDERER_SHADER_H_
