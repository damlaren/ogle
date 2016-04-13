/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file An app for viewing meshes.
 */

#include "ogle/ogle.h"

/**
 * @brief Test application to draw a triangle.
 */
class MeshViewerApplication : public ogle::Application {
 public:
  explicit MeshViewerApplication(std::unique_ptr<ogle::Engine> engine)
    : Application(std::move(engine)) {
  }

  bool Create() override {
    if (!engine_->Create()) {
      LOG(ERROR) << "Engine creation failed.";
      return false;
    }

    const ogle::stl_string kMeshDir =
        ogle::file_system::JoinPaths(engine_->resource_manager_->resource_dir(),
                                     "meshes");
    if (!ogle::Mesh::LoadMesh(
             ogle::file_system::JoinPaths(kMeshDir, "cube.obj"), &mesh_)) {
      LOG(ERROR) << "Failed to load Mesh.";
      return false;
    }

    const ogle::stl_string kShaderDir =
        ogle::file_system::JoinPaths(engine_->resource_manager_->resource_dir(),
                                     "shaders");
    ogle::stl_string vertex_shader_text, fragment_shader_text;
    if (!(ogle::file_system::ReadTextFile(ogle::file_system::JoinPaths(
              kShaderDir, "/vertex/basic_vs.glsl"), &vertex_shader_text) &&
          ogle::file_system::ReadTextFile(ogle::file_system::JoinPaths(
              kShaderDir, "fragment/flat_fs.glsl"), &fragment_shader_text))) {
      LOG(ERROR) << "Failed to read shader text files.";
      return false;
    }

    vertex_shader_ = std::make_unique<ogle::GLSLShader>(
        vertex_shader_text, ogle::ShaderType::Vertex);
    if (!vertex_shader_->Create()) {
      return false;
    }
    fragment_shader_ = std::make_unique<ogle::GLSLShader>(
        fragment_shader_text, ogle::ShaderType::Fragment);
    if (!fragment_shader_->Create()) {
      return false;
    }
    shader_program_ = std::make_unique<ogle::GLSLShaderProgram>(
        vertex_shader_.get(), fragment_shader_.get());
    if (!shader_program_->Create()) {
      return false;
    }
    mesh_renderer_ =
        std::make_unique<ogle::GLFWMeshRenderer>(mesh_, shader_program_.get());
    if (!mesh_renderer_->Create()) {
      LOG(ERROR) << "MeshRenderer Create() failed.";
    }

    render_object_ = std::make_unique<ogle::Entity>(
        &engine_->scene_graph_->root_->transform_, mesh_renderer_.get(),
        nullptr);
    render_object_->transform_.set_world_position({0.f, 0.f, 0.f});
    camera_ = std::make_unique<ogle::PerspectiveCamera>(
        0.01f, 100.f, ogle::Angle::FromDegrees(67.f),
        engine_->window_->aspect_ratio());
    camera_entity_ = std::make_unique<ogle::Entity>(
        &engine_->scene_graph_->root_->transform_, nullptr, camera_.get());
    camera_entity_->transform_.set_world_position({-3.f, 0.f, 0.f});
    return true;
  }

  bool ApplicationBody() {
    if (engine_->keyboard_->IsKeyDown(ogle::KeyCode::ESCAPE, false)) {
      return false;
    }

    // Update camera aspect ratio.
    // TODO(damlaren): Should be done with an Update function on an Entity,
    // or some other interface.
    camera_->set_aspect_ratio(engine_->window_->aspect_ratio());

    // Move camera on input.
    constexpr float kMoveDelta = 0.03f;
    const ogle::Angle kAngleDelta = ogle::Angle::FromDegrees(2.0f);
    if (engine_->keyboard_->IsKeyDown(ogle::KeyCode::W, true)) {
      camera_entity_->transform_.TranslateForward(kMoveDelta);
    } else if (engine_->keyboard_->IsKeyDown(ogle::KeyCode::S, true)) {
      camera_entity_->transform_.TranslateForward(-kMoveDelta);
    } else if (engine_->keyboard_->IsKeyDown(ogle::KeyCode::A, true)) {
      camera_entity_->transform_.TranslateRight(-kMoveDelta);
    } else if (engine_->keyboard_->IsKeyDown(ogle::KeyCode::D, true)) {
      camera_entity_->transform_.TranslateRight(kMoveDelta);
    } else if (engine_->keyboard_->IsKeyDown(ogle::KeyCode::Z, true)) {
      camera_entity_->transform_.TranslateUp(-kMoveDelta);
    } else if (engine_->keyboard_->IsKeyDown(ogle::KeyCode::C, true)) {
      camera_entity_->transform_.TranslateUp(kMoveDelta);
    } else if (engine_->keyboard_->IsKeyDown(ogle::KeyCode::Q, true)) {
      camera_entity_->transform_.RotateRoll(-kAngleDelta);
    } else if (engine_->keyboard_->IsKeyDown(ogle::KeyCode::E, true)) {
      camera_entity_->transform_.RotateRoll(kAngleDelta);
    } else if (engine_->keyboard_->IsKeyDown(ogle::KeyCode::Q, true)) {
      camera_entity_->transform_.RotateRoll(-kAngleDelta);
    } else if (engine_->keyboard_->IsKeyDown(ogle::KeyCode::UP_ARROW, true)) {
      camera_entity_->transform_.RotatePitch(kAngleDelta);
    } else if (engine_->keyboard_->IsKeyDown(ogle::KeyCode::DOWN_ARROW, true)) {
      camera_entity_->transform_.RotatePitch(-kAngleDelta);
    } else if (engine_->keyboard_->IsKeyDown(ogle::KeyCode::LEFT_ARROW, true)) {
      camera_entity_->transform_.RotateYaw(kAngleDelta);
    } else if (engine_->keyboard_->IsKeyDown(ogle::KeyCode::RIGHT_ARROW,
                                             true)) {
      camera_entity_->transform_.RotateYaw(-kAngleDelta);
    }
    engine_->keyboard_->Clear();

    engine_->Render(camera_entity_.get());

    return true;
  }

 private:
  /// Camera Entity.
  std::unique_ptr<ogle::Entity> camera_entity_;

  /// Object instantiated to render the mesh.
  std::unique_ptr<ogle::Entity> render_object_;

  /// Mesh storage.
  ogle::Mesh mesh_;

  /// GLSL vertex shader.
  std::unique_ptr<ogle::GLSLShader> vertex_shader_;

  /// GLSL fragment shader.
  std::unique_ptr<ogle::GLSLShader> fragment_shader_;

  /// GLSL shader program.
  std::unique_ptr<ogle::GLSLShaderProgram> shader_program_;

  /// Mesh renderer.
  std::unique_ptr<ogle::GLFWMeshRenderer> mesh_renderer_;

  /// Camera to render from.
  std::unique_ptr<ogle::Camera> camera_;
};

/**
 * @brief Main entry point.
 * @return 0 on success, something else on failure.
 */
int main(const int argc, const char* argv[]) {
  if (argc < 2) {
    LOG(FATAL) << "usage: mesh_viewer <resource_dir>";
  }

  auto engine = std::make_unique<ogle::Engine>(argv[1]);
  auto app = std::make_unique<MeshViewerApplication>(std::move(engine));
  if (!app->Create()) {
    LOG(FATAL) << "Application failed to start.";
  }
  app->RunApplication();
  return 0;
}
