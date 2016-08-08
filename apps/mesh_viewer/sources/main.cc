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
      : Application(std::move(engine)) {}

  bool Create() override {
    if (!engine_->Create()) {
      LOG(ERROR) << "Engine creation failed.";
      return false;
    }

    CHECK(engine_->resource_manager_->LoadResources())
        << "Failed to load resources.";
    auto mesh = engine_->resource_manager_->GetResource<ogle::Mesh>("cube.obj");
    if (!mesh) {
      LOG(ERROR) << "Failed to load mesh in viewer.";
      return false;
    }
    auto shader_program =
        engine_->resource_manager_->GetResource<ogle::ShaderProgram>(
            "basic.glsl");
    if (!shader_program) {
      LOG(ERROR) << "Failed to load basic.glsl";
      return false;
    }
    auto material =
        engine_->resource_manager_->GetResource<ogle::Material>("default.mtl");
    if (!material) {
      LOG(ERROR) << "Failed to load default.mtl";
      return false;
    }

    // Create Mesh with renderable buffers.
    buffered_mesh_ = ogle::BufferedMesh::Load(engine_->configuration_, *mesh);

    // Create entity to render.
    rendered_entity_ = AllocateUniqueObject<ogle::Entity>(
        &engine_->scene_graph_->root_->transform_);
    rendered_entity_->transform_.set_world_position({0.f, 0.f, 0.f});
    if (!rendered_entity_->AddComponent(
            std::unique_ptr<ogle::MeshRenderer>(ogle::MeshRenderer::Load(
                engine_->configuration_, *buffered_mesh_.get(), material)))) {
      LOG(ERROR) << "Failed to add renderer component.";
      return false;
    }

    camera_entity_ = AllocateUniqueObject<ogle::Entity>(
        &engine_->scene_graph_->root_->transform_);
    if (!camera_entity_->AddComponent(
            AllocateUniqueObject<ogle::PerspectiveCamera>(
                0.01f, 100.f, ogle::Angle::FromDegrees(67.f),
                engine_->window_->aspect_ratio()))) {
      LOG(ERROR) << "Failed to add camera component.";
      return false;
    }
    camera_entity_->transform_.set_world_position({-3.f, 0.f, 0.f});
    return true;
  }

  bool ApplicationBody() {
    if (engine_->keyboard_->IsKeyDown(ogle::KeyCode::ESCAPE, false)) {
      return false;
    }

    // Update camera aspect ratio.
    // TODO(damlaren): Should be updated with an event system.
    ogle::Camera* camera = camera_entity_->GetComponent<ogle::Camera>();
    if (camera == nullptr) {
      LOG(ERROR) << "Failed to get camera.";
      return false;
    }
    camera->set_aspect_ratio(engine_->window_->aspect_ratio());

    // Move camera on input.
    constexpr float kMoveDelta = 1.0f;
    const ogle::Angle kAngleDelta = ogle::Angle::FromDegrees(60.0f);
    float translation = kMoveDelta * last_update_timestep_;
    ogle::Angle rotation = kAngleDelta * last_update_timestep_;
    if (engine_->keyboard_->IsKeyDown(ogle::KeyCode::W, true)) {
      camera_entity_->transform_.TranslateForward(translation);
    } else if (engine_->keyboard_->IsKeyDown(ogle::KeyCode::S, true)) {
      camera_entity_->transform_.TranslateForward(-translation);
    } else if (engine_->keyboard_->IsKeyDown(ogle::KeyCode::A, true)) {
      camera_entity_->transform_.TranslateRight(-translation);
    } else if (engine_->keyboard_->IsKeyDown(ogle::KeyCode::D, true)) {
      camera_entity_->transform_.TranslateRight(translation);
    } else if (engine_->keyboard_->IsKeyDown(ogle::KeyCode::Z, true)) {
      camera_entity_->transform_.TranslateUp(-translation);
    } else if (engine_->keyboard_->IsKeyDown(ogle::KeyCode::C, true)) {
      camera_entity_->transform_.TranslateUp(translation);
    } else if (engine_->keyboard_->IsKeyDown(ogle::KeyCode::Q, true)) {
      camera_entity_->transform_.RotateRoll(-rotation);
    } else if (engine_->keyboard_->IsKeyDown(ogle::KeyCode::E, true)) {
      camera_entity_->transform_.RotateRoll(rotation);
    } else if (engine_->keyboard_->IsKeyDown(ogle::KeyCode::Q, true)) {
      camera_entity_->transform_.RotateRoll(-rotation);
    } else if (engine_->keyboard_->IsKeyDown(ogle::KeyCode::UP_ARROW, true)) {
      camera_entity_->transform_.RotatePitch(rotation);
    } else if (engine_->keyboard_->IsKeyDown(ogle::KeyCode::DOWN_ARROW, true)) {
      camera_entity_->transform_.RotatePitch(-rotation);
    } else if (engine_->keyboard_->IsKeyDown(ogle::KeyCode::LEFT_ARROW, true)) {
      camera_entity_->transform_.RotateYaw(rotation);
    } else if (engine_->keyboard_->IsKeyDown(ogle::KeyCode::RIGHT_ARROW,
                                             true)) {
      camera_entity_->transform_.RotateYaw(-rotation);
    }
    engine_->keyboard_->Clear();

    engine_->Render(camera_entity_.get());

    return true;
  }

 private:
  /// Entity with camera in scene.
  std::unique_ptr<ogle::Entity> camera_entity_;

  /// Entity instantiated to render the mesh.
  std::unique_ptr<ogle::Entity> rendered_entity_;

  /// Mesh buffered for rendering.
  std::unique_ptr<ogle::BufferedMesh> buffered_mesh_;
};

/**
 * @brief Main entry point.
 * @return 0 on success, something else on failure.
 */
int main(const int argc, const char* argv[]) {
  if (argc < 2) {
    LOG(FATAL) << "usage: mesh_viewer <resource_dir>";
  }

  const auto config_file_path = ogle::FilePath(argv[1]);
  ogle::Configuration configuration;
  if (!configuration.Load(config_file_path)) {
    LOG(FATAL) << "Failed to load configuration.";
  }

  auto engine = AllocateUniqueObject<ogle::Engine>(configuration);
  auto app = AllocateUniqueObject<MeshViewerApplication>(std::move(engine));
  CHECK(app != nullptr) << "Failed to allocate app.";
  if (!app->Create()) {
    LOG(FATAL) << "Application failed to start.";
  }
  app->RunApplication();
  return 0;
}
