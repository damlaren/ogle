/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file Defines an app to display a triangle on the screen.
 * Used to validate primitive drawing code.
 */

#include "ogle/ogle.h"

#include "GL/glew.h"
#include "GLFW/glfw3.h"

using GLFWApplication = ogle::GLFWApplication;

/**
 * @brief Application for drawing a triangle.
 */
class TriangleApplication : public GLFWApplication {
 public:
  TriangleApplication() : GLFWApplication() {
    // TODO(damlaren): Goal is to abstract this out in a separate layer.
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
  }
  ~TriangleApplication() override {
  }

  /**
   * @brief Renders mesh.
   * @param mesh Mesh to render.
   */
  void RenderMesh(const ogle::Mesh& mesh) const {
    // TODO(damlaren): move into Renderer.
      /*
    GLuint vbo = 0;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, mesh.GetVertexBuffer().SizeInBytes(),
                 mesh.GetVertexBuffer().data_, GL_STATIC_DRAW);

    GLuint vao = 0;
    glGenVertexArrays (1, &vao);
    glBindVertexArray (vao);
    glEnableVertexAttribArray (0);
    glBindBuffer (GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    const char* vertex_shader =
    "#version 400\n"
    "in vec3 vp;"
    "void main () {"
    "  gl_Position = vec4 (vp, 1.0);"
    "}";

    const char* fragment_shader =
    "#version 400\n"
    "out vec4 frag_colour;"
    "void main () {"
    "  frag_colour = vec4 (0.5, 0.0, 0.5, 1.0);"
    "}";

    GLuint vs = glCreateShader (GL_VERTEX_SHADER);
    glShaderSource (vs, 1, &vertex_shader, nullptr);
    glCompileShader (vs);
    GLuint fs = glCreateShader (GL_FRAGMENT_SHADER);
    glShaderSource (fs, 1, &fragment_shader, nullptr);
    glCompileShader (fs);

    GLuint shader_programme = glCreateProgram ();
    glAttachShader (shader_programme, fs);
    glAttachShader (shader_programme, vs);
    glLinkProgram (shader_programme);

    // TODO(damlaren): and in a loop...
    // wipe the drawing surface clear
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram (shader_programme);
    glBindVertexArray (vao);
    // draw points 0-3 from the currently bound VAO with current in-use shader
    glDrawArrays (GL_TRIANGLES, 0, 3);
    */
  }

  bool ApplicationBody() {
    ogle::VertexBuffer triangle_vertices(
        {{0.0f, 0.5f, 0.0f}, {0.5f, -0.5f, 0.0f}, {-0.5f, -0.5f, 0.0f}});
    ogle::Mesh mesh;
    mesh.TakeBuffers(std::move(triangle_vertices));

    // Do window stuff.
    return GLFWApplication::ApplicationBody();
  }
};

/**
 * @brief main Main entry point.
 * @return 0 on success, something else on failure.
 */
int main(const int argc, const char* argv[]) {
  auto app = std::make_unique<TriangleApplication>();
  app->RunApplication();
  return 0;
}
