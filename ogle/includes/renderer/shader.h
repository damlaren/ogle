/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file Defines Shader and ShaderProgram.
 */

#ifndef OGLE_INCLUDES_RENDERER_SHADER_H_
#define OGLE_INCLUDES_RENDERER_SHADER_H_

#include "std/ogle_std.inc"
#include <memory>
#include "math/matrix.h"
#include "resource/resource.h"

namespace ogle {

class Configuration;
class ResourceManager;
class ResourceMetadata;

/**
 * @brief The type of a Shader.
 */
enum class ShaderType {
  Vertex,  ///< Vertex shader.
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
  static const stl_string kResourceType;

  ///@{
  /// A shader subtype specification in metadata.
  static const stl_string kVertexShaderSubType;
  static const stl_string kFragmentShaderSubType;
  ///@}

  /**
   * @brief Default destructor.
   */
  virtual ~Shader() = default;

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
  Shader(const ResourceMetadata& metadata, const stl_string &shader_text,
         const ShaderType type);

  /// Shader text.
  stl_string shader_text_;

  /// Shader type.
  ShaderType shader_type_;
};

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
  static const stl_string kResourceType;

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
  static std::unique_ptr<ShaderProgram> Load(
      const ResourceMetadata& metadata, ResourceManager* resource_manager);

  /**
   * @brief Links shaders into a program.
   * @param metadata Metadata for shader program resource.
   * @param[in, out] vertex_shader Vertex shader.
   * @param[in, out] fragment_shader Fragment shader.
   * @return Linked ShaderProgram, or nullptr if linking failed.
   */
  static std::unique_ptr<ShaderProgram> Link(
      const ResourceMetadata& metadata, Shader* vertex_shader,
      Shader* fragment_shader);

  /**
   * @brief Sets this shader program up to be used in rendering pass.
   */
  virtual void UseProgram() = 0;

  // TODO(damlaren): API with having to call all these different uniform
  //     functions kind of sucks.

  ///@{
  /**
   * @brief Sets a uniform matrix value in shader program.
   * @param variable Name of uniform variable.
   * @param mat Matrix to set values.
   */
  virtual void SetUniformMatrix22f(const stl_string& variable,
                                   const Matrix22f& mat) = 0;
  virtual void SetUniformMatrix33f(const stl_string& variable,
                                   const Matrix33f& mat) = 0;
  virtual void SetUniformMatrix44f(const stl_string& variable,
                                   const Matrix44f& mat) = 0;
  ///@}

 protected:
  /**
   * @brief Constructor.
   * @param metadata Resource metadata.
   */
  explicit ShaderProgram(const ResourceMetadata& metadata);
};

}  // namespace ogle

#endif  // OGLE_INCLUDES_RENDERER_SHADER_H_