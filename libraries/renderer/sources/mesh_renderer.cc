/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file Implementation of mesh_renderer.h.
 */

#include "renderer/mesh_renderer.h"
#include "config/configuration.h"
#include "renderer/glfw_mesh_renderer.h"

namespace ogle {

MeshRenderer* MeshRenderer::Load(const Configuration& configuration,
                                 const Mesh& mesh,
                                 ShaderProgram *shader_program) {
  const stl_string implementation = configuration.Get<stl_string>(
      kConfigModule, kConfigAttributeImplementation);
  if (implementation == GLFWMeshRenderer::kConfigImplementationName) {
    auto new_object = new GLFWMeshRenderer(mesh, shader_program);
    if (new_object->Create()) {
      return new_object;
    } else {
      delete new_object;
      LOG(ERROR) << "MeshRenderer Create() failed.";
    }
  }
  LOG(ERROR) << "Unable to create MeshRenderer for implementation: "
             << implementation;
  return nullptr;
}

MeshRenderer::MeshRenderer(const Mesh& mesh)
  : Renderer(), mesh_(mesh) {
}

}  // namespace ogle
