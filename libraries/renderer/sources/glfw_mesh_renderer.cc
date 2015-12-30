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
 * @file Implementation of glfw_renderer.h.
 */

#include "renderer/glfw_mesh_renderer.h"
#include "geometry/mesh.h"
#include "renderer/glsl_shader.h"

namespace ogle {

GLFWMeshRenderer::GLFWMeshRenderer(std::shared_ptr<Mesh> mesh) :
    MeshRenderer(mesh), vertex_buffer_id_(0), vertex_array_id_(0) {
}

void GLFWMeshRenderer::Render() {
  glGenBuffers(1, &vertex_buffer_id_);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id_);
  glBufferData(GL_ARRAY_BUFFER, mesh_->GetVertexBuffer().SizeInBytes(),
               mesh_->GetVertexBuffer().data_, GL_STATIC_DRAW);

  glGenVertexArrays(1, &vertex_array_id_);
  glBindVertexArray(vertex_array_id_);

  // TODO(damlaren): Parameterize. 1 for each vertex attribute in shader.
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id_);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

  // TODO(damlaren): Read from text files.
  const std::string vertex_shader_text =
      "#version 400\n"
      "in vec3 vp;"
      "void main () {"
      "  gl_Position = vec4 (vp, 1.0);"
      "}";
  const std::string fragment_shader_text =
      "#version 400\n"
      "out vec4 frag_colour;"
      "void main () {"
      "  frag_colour = vec4 (0.5, 0.0, 0.5, 1.0);"
      "}";

  // TODO(damlaren): Set shaders to use to draw the mesh, get from there.
  // But these could vary by mesh instance.
  std::shared_ptr<GLSLShader> vertex_shader =
      std::make_shared<GLSLShader>(vertex_shader_text, ShaderType::Vertex);
  std::shared_ptr<GLSLShader> fragment_shader =
      std::make_shared<GLSLShader>(fragment_shader_text, ShaderType::Fragment);
  GLSLShaderProgram shader_program(vertex_shader, fragment_shader);
  shader_program.UseProgram();

  glBindVertexArray(vertex_array_id_);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, mesh_->GetVertexBuffer().num_elements_);
}

}  // namespace ogle
