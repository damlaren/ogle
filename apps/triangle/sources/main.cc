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

using GLFWApplication = ogle::GLFWApplication;

/**
 * @brief Test application to draw a triangle.
 */
class TriangleApplication : public GLFWApplication {
 public:
  TriangleApplication() : GLFWApplication() {
  }
  ~TriangleApplication() override {
  }

  bool ApplicationBody() {
    window_->ClearWindow();

    ogle::VertexBuffer triangle_vertices(
        {{0.0f, 0.5f, 0.0f}, {0.5f, -0.5f, 0.0f}, {-0.5f, -0.5f, 0.0f}});
    auto mesh = std::make_shared<ogle::Mesh>();
    mesh->StealBuffers(std::move(triangle_vertices));

    const std::string vertex_shader_text =
        "#version 400\n"
        "in vec3 vp;"
        "void main () {"
        "  gl_Position = vec4 (vp, 1.0);"
        "}";
    const std::string fragment_shader_text =
        "#version 400\n"
        "out vec4 frag_color;"
        "void main () {"
        "  frag_color = vec4 (0.5, 0.0, 0.5, 1.0);"
        "}";
    auto vertex_shader =
        std::make_shared<ogle::GLSLShader>(vertex_shader_text,
                                           ogle::ShaderType::Vertex);
    auto fragment_shader =
        std::make_shared<ogle::GLSLShader>(fragment_shader_text,
                                           ogle::ShaderType::Fragment);
    auto shader_program =
        std::make_shared<ogle::GLSLShaderProgram>(vertex_shader,
                                                  fragment_shader);

    ogle::GLFWMeshRenderer renderer(mesh, shader_program);
    renderer.Render();

    window_->SwapBuffers();
    return window_->HandleWindowEvents();
  }
};

/**
 * @brief Main entry point.
 * @return 0 on success, something else on failure.
 */
int main(const int argc, const char* argv[]) {
  auto app = std::make_unique<TriangleApplication>();
  app->RunApplication();
  return 0;
}
