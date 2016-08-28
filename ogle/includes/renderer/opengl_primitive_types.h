/**
 * @file opengl_primitive_types.h
 * @brief Defines replacements for OpenGL primitive types.
 *
 * Equivalents are chosen based on: https://www.opengl.org/wiki/OpenGL_Type
 */

#pragma once

#include <cstdint>

namespace ogle {

using GLint = std::int32_t;
using GLuint = std::uint32_t;
using GLfloat = float;
using GLdouble = double;

}  // namespace ogle

