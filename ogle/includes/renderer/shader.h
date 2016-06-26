/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

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
  Shader(const ResourceMetadata& metadata, const stl_string& shader_text,
         const ShaderType type);

  /// Shader text.
  stl_string shader_text_;

  /// Shader type.
  ShaderType shader_type_;
};

}  // namespace ogle

#endif  // OGLE_INCLUDES_RENDERER_SHADER_H_
