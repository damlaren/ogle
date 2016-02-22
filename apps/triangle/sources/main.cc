/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file Defines an app to display a triangle on the screen.
 *
 * Used to validate primitive drawing code.
 */

#include "ogle/ogle.h"

/**
 * @brief Test application to draw a triangle.
 */
class TriangleApplication : public ogle::Application {
 public:
  explicit TriangleApplication(const std::string& resource_dir,
                               std::unique_ptr<ogle::Window> window,
                               std::unique_ptr<ogle::KeyboardInput> keyboard)
      : Application(
            std::make_unique<ogle::ResourceManager>(resource_dir),
            std::move(window), std::move(keyboard)) {
    const std::string kMeshDir = resource_manager_->resource_dir() + "/meshes";
    auto mesh = std::shared_ptr<ogle::Mesh>(
        ogle::Mesh::LoadMesh(kMeshDir + "/triangle.obj"));
    if (mesh == nullptr) {
      throw RuntimeException();
    }

    const std::string kShaderDir =
        resource_manager_->resource_dir() + "/shaders";
    std::string vertex_shader_text, fragment_shader_text;
    if (!(ogle::TextFile::ReadFile(kShaderDir + "/vertex/basic_vs.glsl",
                                   &vertex_shader_text) &&
          ogle::TextFile::ReadFile(kShaderDir + "/fragment/flat_fs.glsl",
                                   &fragment_shader_text))) {
      LOG(ERROR) << "Failed to read shader resources.";
      throw RuntimeException();
    }

    auto vertex_shader = std::make_shared<ogle::GLSLShader>(
        vertex_shader_text, ogle::ShaderType::Vertex);
    auto fragment_shader = std::make_shared<ogle::GLSLShader>(
        fragment_shader_text, ogle::ShaderType::Fragment);
    auto shader_program = std::make_shared<ogle::GLSLShaderProgram>(
        vertex_shader, fragment_shader);
    auto renderer =
        std::make_shared<ogle::GLFWMeshRenderer>(mesh, shader_program);

    scene_graph_ = std::make_unique<ogle::SceneGraph>();
    scene_renderer_ = std::make_unique<ogle::SceneRenderer>();
    triangle_ = std::make_unique<ogle::Entity>(
        &scene_graph_->root_->transform_, renderer, nullptr);
    auto camera_object = std::make_shared<ogle::PerspectiveCamera>(
        0.01f, 100.f, ogle::Angle::FromDegrees(67.f), window_->window_width(),
        window_->window_height());
    camera_ = std::make_unique<ogle::Entity>(
        &scene_graph_->root_->transform_, nullptr, camera_object);
    camera_->transform_.set_world_position({0.f, 0.f, 3.0f});
    camera_->transform_.set_world_orientation(
        ogle::Angle::FromDegrees(90.f), ogle::Angle(0.f), ogle::Angle(0.f));
  }

  bool ApplicationBody() {
    if (keyboard_->IsKeyDown(ogle::KeyCode::ESCAPE, false)) {
      return false;
    }

    // Update camera aspect ratio.
    // TODO(damlaren): Should be done with an Update function on an Entity,
    // or a messaging interface.
    ogle::PerspectiveCamera* camera =
        dynamic_cast<ogle::PerspectiveCamera*>(camera_->camera());
    camera->set_aspect_ratio(window_->window_width(), window_->window_height());

    // Move camera on input.
    constexpr float kMoveDelta = 0.03f;
    const ogle::Angle kAngleDelta = ogle::Angle::FromDegrees(2.0f);
    if (keyboard_->IsKeyDown(ogle::KeyCode::W, true)) {
      camera_->transform_.TranslateForward(kMoveDelta);
    } else if (keyboard_->IsKeyDown(ogle::KeyCode::S, true)) {
      camera_->transform_.TranslateForward(-kMoveDelta);
    } else if (keyboard_->IsKeyDown(ogle::KeyCode::A, true)) {
      camera_->transform_.TranslateRight(-kMoveDelta);
    } else if (keyboard_->IsKeyDown(ogle::KeyCode::D, true)) {
      camera_->transform_.TranslateRight(kMoveDelta);
    } else if (keyboard_->IsKeyDown(ogle::KeyCode::Z, true)) {
      camera_->transform_.TranslateUp(-kMoveDelta);
    } else if (keyboard_->IsKeyDown(ogle::KeyCode::C, true)) {
      camera_->transform_.TranslateUp(kMoveDelta);
    } else if (keyboard_->IsKeyDown(ogle::KeyCode::Q, true)) {
      camera_->transform_.RotateRoll(-kAngleDelta);
    } else if (keyboard_->IsKeyDown(ogle::KeyCode::E, true)) {
      camera_->transform_.RotateRoll(kAngleDelta);
    } else if (keyboard_->IsKeyDown(ogle::KeyCode::Q, true)) {
      camera_->transform_.RotateRoll(-kAngleDelta);
    } else if (keyboard_->IsKeyDown(ogle::KeyCode::UP_ARROW, true)) {
      camera_->transform_.RotatePitch(kAngleDelta);
    } else if (keyboard_->IsKeyDown(ogle::KeyCode::DOWN_ARROW, true)) {
      camera_->transform_.RotatePitch(-kAngleDelta);
    } else if (keyboard_->IsKeyDown(ogle::KeyCode::LEFT_ARROW, true)) {
      camera_->transform_.RotateYaw(kAngleDelta);
    } else if (keyboard_->IsKeyDown(ogle::KeyCode::RIGHT_ARROW, true)) {
      camera_->transform_.RotateYaw(-kAngleDelta);
    }
    keyboard_->Clear();

    // Move triangle.
    const float t = static_cast<float>(loop_count_) / kMoveCycleTicks;
    triangle_->transform_.set_world_position(
        {kXRange * static_cast<float>(cos(t)), 0.f, 0.f});

    // TODO(damlaren): Move rendering code out.
    window_->ClearWindow();
    scene_renderer_->RenderScene(camera_.get(), scene_graph_.get());
    window_->SwapBuffers();

    return true;
  }

 private:
  //@{
  /// Move triangle between these coordinates (+/-).
  static constexpr float kXRange = 0.3f;
  //@}

  // TODO(damlaren): Need timers, frame time, etc. & standardized tick type.
  /// How many ticks it takes to complete full cycle of triangle motion.
  static constexpr std::uint64_t kMoveCycleTicks = 200;

  /// Object instantiated to render triangle mesh.
  std::unique_ptr<ogle::Entity> triangle_;

  /// Camera Entity.
  std::unique_ptr<ogle::Entity> camera_;

  /// Scene graph.
  std::unique_ptr<ogle::SceneGraph> scene_graph_;

  /// Scene renderer.
  std::unique_ptr<ogle::SceneRenderer> scene_renderer_;
};

/**
 * @brief Main entry point.
 * @return 0 on success, something else on failure.
 */
int main(const int argc, const char* argv[]) {
  if (argc < 2) {
    LOG(FATAL) << "usage: triangle <resource_dir>";
  }

  static constexpr int kWindowWidth = 1024;
  static constexpr int kWindowHeight = 768;
  auto window = std::make_unique<ogle::GLFWWindow>(kWindowWidth, kWindowHeight,
                                                   "Triangle App", 4, 0, 4);
  auto keyboard = std::make_unique<ogle::GLFWKeyboardInput>();

  // TODO(damlaren): This is a quirk specific to GLFW, can move it once engine
  // is "packed up."
  window->AttachKeyboard(keyboard.get());

  auto app = std::make_unique<TriangleApplication>(argv[1], std::move(window),
      std::move(keyboard));
  app->RunApplication();
  return 0;
}
