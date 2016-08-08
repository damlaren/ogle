/**
 * @file Defines replacements for OpenGL primitive types.
 *
 * Equivalents are chosen based on: https://www.opengl.org/wiki/OpenGL_Type
 */

#ifndef OGLE_INCLUDES_RENDERER_OPENGL_PRIMITIVE_TYPES_H_
#define OGLE_INCLUDES_RENDERER_OPENGL_PRIMITIVE_TYPES_H_

#include <cstdint>

namespace ogle {

using GLint = std::int32_t;
using GLuint = std::uint32_t;
using GLfloat = float;
using GLdouble = double;

}  // namespace ogle

#endif  // OGLE_INCLUDES_RENDERER_OPENGL_PRIMITIVE_TYPES_H_
