/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file Defines ShaderProgram.
 */
 
#ifndef LIBRARIES_RENDERER_INCLUDES_RENDERER_SHADER_PROGRAM_H_
#define LIBRARIES_RENDERER_INCLUDES_RENDERER_SHADER_PROGRAM_H_

#include "renderer/shader.h"

namespace ogle{

/**
 * @brief Base class for all ShaderPrograms.
 *
 * Shader programs link multiple shaders together and are the objects
 * used in rendering.
 */
class ShaderProgram {
 public:
  /// Use shader program in rendering pass.
  virtual void UseProgram() = 0;

 protected:
  /// Error that can be thrown if ShaderProgram creation fails.
  class ShaderProgramLinkError : public std::exception {
  };

  /// Default constructor. Not used.
  ShaderProgram() = default;

  /// Destructor.
  virtual ~ShaderProgram() = default;
};

}  // namespace ogle

#endif  // LIBRARIES_RENDERER_INCLUDES_RENDERER_SHADER_PROGRAM_H_
