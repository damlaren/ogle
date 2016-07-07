/*
Copyright (c) 2016 damlaren

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
 * @file Defines Material.
 */

#ifndef OGLE_INCLUDES_RENDERER_MATERIAL_H_
#define OGLE_INCLUDES_RENDERER_MATERIAL_H_

#include "std/ogle_std.inc"
#include "renderer/shader_variable.h"

namespace ogle {

class ShaderProgram;

/**
 * @brief A material (shader program + variable bindings) to draw a surface.
 */
class Material {
 public:
  /**
   * @brief Constructor.
   * @param Shader program to set. Must be non-null.
   */
  explicit Material(ShaderProgram* program);

  /**
   * @brief Add a variable to bind to this shader program.
   * @param variable Variable binding to add.
   */
  void AddVariableBinding(ShaderVariable variable);

 private:
  /// Shader program to use for this material.
  ShaderProgram* shader_program_;

  /// Variable bindings.
  stl_vector<ShaderVariable> shader_variables_;
};

}  // namespace ogle

#endif  // OGLE_INCLUDES_RENDERER_MATERIAL_H_
