/**
 * @file Defines GLSLShader.
 */

#ifndef OGLE_INCLUDES_RENDERER_GLSL_SHADER_H_
#define OGLE_INCLUDES_RENDERER_GLSL_SHADER_H_

#include "std/ogle_std.inc"
#include "easylogging++.h"  // NOLINT
#include "renderer/opengl_primitive_types.h"
#include "renderer/shader.h"

namespace ogle {

class ResourceMetadata;

/**
 * @brief A shader written in GLSL.
 */
class GLSLShader : public Shader {
 public:
  friend class GLSLShaderProgram;

  /// String indicating that this implementation should be used.
  static const stl_string kImplementationName;

  GLSLShader(const ResourceMetadata& metadata, const stl_string& shader_text,
             const ShaderType type);

  ~GLSLShader() override;

  /**
   * @brief Builds Shader from loaded text.
   * @return Success/failure.
   */
  bool Create();

 protected:
  /// OpenGL-generated shader ID.
  ogle::GLuint shader_id_;
};

}  // namespace ogle

#endif  // OGLE_INCLUDES_RENDERER_GLSL_SHADER_H_
