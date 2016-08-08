/**
 * @file Defines ShaderProgram.
 */

#ifndef OGLE_INCLUDES_RENDERER_SHADER_PROGRAM_H_
#define OGLE_INCLUDES_RENDERER_SHADER_PROGRAM_H_

#include "std/ogle_std.inc"
#include <memory>
#include "math/matrix.h"
#include "resource/resource.h"

namespace ogle {

class ResourceManager;
class ResourceMetadata;
class Shader;
class ShaderVariable;

/**
 * @brief Base class for all ShaderPrograms.
 *
 * Shader programs link multiple shaders together and are the objects
 * used in rendering.
 */
class ShaderProgram : public Resource {
 public:
  ///@{
  /// Standardized names for common shader arguments.
  static const stl_string kModelMatrixArg;
  static const stl_string kViewMatrixArg;
  static const stl_string kProjectionMatrixArg;
  ///@}

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
   * @param variable Value to set.
   */
  virtual void SetVariable(const ShaderVariable& variable) = 0;

 protected:
  /**
   * @brief Constructor.
   * @param metadata Resource metadata.
   */
  explicit ShaderProgram(const ResourceMetadata& metadata);
};

}  // namespace ogle

#endif  // OGLE_INCLUDES_RENDERER_SHADER_PROGRAM_H_
