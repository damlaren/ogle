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

using GLFWApplication = ogle::GLFWApplication;

/**
 * @brief Test application to draw a triangle.
 */
class TriangleApplication : public GLFWApplication {
 public:
  static constexpr int kWindowWidth = 1024;
  static constexpr int kWindowHeight = 768;

  explicit TriangleApplication(const std::string& resource_dir)
      : GLFWApplication(
            std::make_unique<ogle::GLFWWindow>(kWindowWidth, kWindowHeight,
                                               "Triangle App", 4, 0, 4),
            std::make_unique<ogle::GLFWKeyboardInput>(),
            resource_dir) {
    ogle::VertexBuffer triangle_vertices(
        {{0.0f, 0.5f, 0.0f}, {0.5f, -0.5f, 0.0f}, {-0.5f, -0.5f, 0.0f}});
    auto mesh = std::make_shared<ogle::Mesh>();
    mesh->StealBuffers(std::move(triangle_vertices));

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

    auto vertex_shader =
      std::make_shared<ogle::GLSLShader>(vertex_shader_text,
                                         ogle::ShaderType::Vertex);
    auto fragment_shader =
      std::make_shared<ogle::GLSLShader>(fragment_shader_text,
                                         ogle::ShaderType::Fragment);
    auto shader_program =
      std::make_shared<ogle::GLSLShaderProgram>(vertex_shader,
                                                fragment_shader);
    auto renderer =
      std::make_shared<ogle::GLFWMeshRenderer>(mesh, shader_program);

    triangle_ = std::make_unique<ogle::Entity>(renderer);
    camera_ = std::make_unique<ogle::PerspectiveCamera>(
        0.01f, 100.f, ogle::Angle::FromDegrees(67.f),
        static_cast<float>(kWindowWidth) / kWindowHeight);
    camera_->transform_.set_world_position({0.f, 0.f, 3.0f});
  }

  ~TriangleApplication() override {
  }

  bool ApplicationBody() {
    if (!window_->HandleWindowEvents() ||
        keyboard_->IsKeyDown(ogle::KeyCode::ESCAPE, false)) {
      return false;
    }

    // Move camera.
    constexpr float kDelta = 0.01f;
    ogle::Vector3f move_dir(0.f, 0.f, 0.f);
    if (keyboard_->IsKeyDown(ogle::KeyCode::W, true)) {
      move_dir += ogle::Vector3f(0.f, 0.f, -kDelta);
    } else if (keyboard_->IsKeyDown(ogle::KeyCode::S, true)) {
      move_dir += ogle::Vector3f(0.f, 0.f, kDelta);
    } else if (keyboard_->IsKeyDown(ogle::KeyCode::A, true)) {
      move_dir += ogle::Vector3f(-kDelta, 0.f, 0.f);
    } else if (keyboard_->IsKeyDown(ogle::KeyCode::D, true)) {
      move_dir += ogle::Vector3f(kDelta, 0.f, 0.f);
    }
    camera_->transform_.set_world_position(
        camera_->transform_.world_position() + move_dir);

    // Move triangle.
    float t = static_cast<float>(loop_count_) / kMoveCycleTicks;
    triangle_->position_ = ogle::Vector3f(kXRange * static_cast<float>(cos(t)),
                                          0.f, 0.f);
    window_->ClearWindow();
    triangle_->Render(*camera_.get());
    window_->SwapBuffers();

    // Cleanup.
    keyboard_->Clear();

    ++loop_count_;
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

  /// Camera.
  std::unique_ptr<ogle::Camera> camera_;
};

constexpr int TriangleApplication::kWindowWidth;
constexpr int TriangleApplication::kWindowHeight;

/**
 * @brief Main entry point.
 * @return 0 on success, something else on failure.
 */
int main(const int argc, const char* argv[]) {
  if (argc < 2) {
    LOG(FATAL) << "usage: triangle <resource_dir>";
  }

  auto app = std::make_unique<TriangleApplication>(argv[1]);
  app->RunApplication();
  return 0;
}
