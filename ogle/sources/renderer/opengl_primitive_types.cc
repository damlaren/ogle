/**
 * @file Implementation of opengl_primitive_types.h.
 */

#include "renderer/opengl_primitive_types.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"

static_assert(sizeof(ogle::GLuint) == sizeof(GLuint), "GLuint size mismatch.");
static_assert(sizeof(ogle::GLint) == sizeof(GLint), "GLint size mismatch.");
static_assert(sizeof(ogle::GLfloat) == sizeof(GLfloat),
              "GLfloat size mismatch.");
static_assert(sizeof(ogle::GLdouble) == sizeof(GLdouble),
              "GLdouble size mismatch.");
