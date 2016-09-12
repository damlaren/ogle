/**
 * @file shader_program.h
 * @brief Defines ShaderProgram.
 */

#pragma once

#include "std/ogle_std.inc"
#include <memory>
#include "math/matrix.h"
#include "resource/resource.h"

namespace ogle {

class Property;
class ResourceManager;
class ResourceMetadata;
class Shader;

/**
 * @brief Base class for all ShaderPrograms.
 *
 * Shader programs link multiple shaders together and are the objects
 * used in rendering.
 */
class ShaderProgram : public Resource {
 public:
  /// @brief Standardized names for common shader arguments.
  class StandardShaderArgumentNames {
   public:
    /// Model matrix.
    static const stl_string kModelMatrixArg;

    /// View matrix.
    static const stl_string kViewMatrixArg;

    /// Projection matrix.
    static const stl_string kProjectionMatrixArg;

    /// Light world position.
    static const stl_string kLightPosition;

    /// Light ambient color.
    static const stl_string kLightAmbientColor;

    /// Light diffuse color.
    static const stl_string kLightDiffuseColor;

    /// Light specular color.
    static const stl_string kLightSpecularColor;
  };

  /// Type identifying shader program resources.
  static constexpr ResourceType kResourceType = ResourceType::SHADER_PROGRAM;

  ///@{
  /// Fields identifying shader types to link together.
  static const stl_string kVertexShaderField;
  static const stl_string kFragmentShaderField;
  ///@}

  /**
   * @brief Default destructor.
   */
  virtual ~ShaderProgram() = default;

  /**
   * @brief Load shader program.
   * @param metadata Metadata for program.
   * @param[in] resource_manager Resource manager for application.
   * @return Linked shader program.
   */
  static std::unique_ptr<ShaderProgram> Load(const ResourceMetadata& metadata,
                                             ResourceManager* resource_manager);

  /**
   * @brief Links shaders into a program.
   * @param metadata Metadata for shader program resource.
   * @param[in, out] vertex_shader Vertex shader.
   * @param[in, out] fragment_shader Fragment shader.
   * @return Linked ShaderProgram, or nullptr if linking failed.
   */
  static std::unique_ptr<ShaderProgram> Link(const ResourceMetadata& metadata,
                                             Shader* vertex_shader,
                                             Shader* fragment_shader);

  /**
   * @brief Sets this shader program up to be used in rendering pass.
   */
  virtual void UseProgram() = 0;

  /**
   * @brief Sets variable on shader program.
   * @param variable_name Name of variable to set in shader program.
   * @param value Value to set.
   */
  virtual void SetVariable(const stl_string& variable_name,
                           const Property& value) = 0;

 protected:
  /**
   * @brief Constructor.
   * @param metadata Resource metadata.
   */
  explicit ShaderProgram(const ResourceMetadata& metadata);
};

}  // namespace ogle
