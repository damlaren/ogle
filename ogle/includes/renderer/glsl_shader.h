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
