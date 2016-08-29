/**
 * @file material.h
 * @brief Defines Material.
 */

#pragma once

#include "std/ogle_std.inc"
#include "entity/property.h"
#include "math/vector.h"
#include "resource/resource.h"

namespace ogle {

class ResourceManager;
class ShaderProgram;

/**
 * @brief A material (shader program + variable bindings) to draw a surface
 */
class Material : public Resource {
 public:
  /// Type identifying material resources.
  static constexpr ResourceType kResourceType = ResourceType::MATERIAL;

  /// Identifies Wavefront OBJ/MTL implementation.
  static const stl_string kMTLImplementation;

  /**
   * @brief Constructor.
   * @param metadata Metadata to use for loading material.
   */
  explicit Material(const ResourceMetadata& metadata);

  /**
   * @brief Identifies underlying shader implementation used.
   * @return Implementation string.
   */
  const stl_string implementation() const;

  /**
   * @brief Loads a material from metadata.
   * @param metadata Metadata for loading.
   * @param[in] resource_manager Resource manager for application.
   * @return New material.
   */
  static std::unique_ptr<Material> Load(const ResourceMetadata& metadata,
                                        ResourceManager* resource_manager);

  /**
   * @brief Parses material data from an MTL file.
   * @param text Full text of MTL file to parse.
   * @return Success/failure.
   */
  bool LoadMTL(const stl_string& text);

  /**
   * @brief Use shader program for rendering.
   */
  void UseProgram();

  /**
   * @brief Set variable on shader program.
   * @param variable Value to set.
   */
  void SetVariable(const Property& variable);

 private:
  /// Shader program to use for this material.
  ShaderProgram* shader_program_;

  // TODO(damlaren): Remove these in favor of loading properties instead.
  Vector3f ambient_reflectivity_;  ///< Response to ambient light.
  Vector3f diffuse_reflectivity_;  ///< Response to diffuse light.
  Vector3f specular_reflectivity_;  ///< Response to specular light.
  float specular_exponent_;  ///< Exponent for specular reflectivity.

  /// Variables to set for the shader program.
  stl_vector<Property> variable_bindings_;
};

}  // namespace ogle
