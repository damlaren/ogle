/**
 * @file engine.h
 * @brief Defines Engine.
 */

#pragma once

#include "std/ogle_std.inc"
#include "config/configuration.h"
#include "input/keyboard_input.h"
#include "window/window.h"
#include "renderer/scene_graph.h"
#include "renderer/scene_renderer.h"
#include "resource/resource_manager.h"
#include "time/timer.h"

namespace ogle {

class Entity;

/**
 * @brief The core object tieing together everything in ogle.
 *
 * The Engine manages every other subsystem in ogle. It is ultimately
 * responsible for all memory allocations, behavior, and control flow,
 * and is the container by which applications access ogle.
 */
class Engine {
 public:
  /// Indicates a feature implemented using GLFW.
  static const stl_string kGLFWImpl;

  /**
   * @brief Constructor.
   * @param configuration Engine configuration.
   */
  explicit Engine(const Configuration& configuration);

  /**
   * @brief Destructor.
   */
  virtual ~Engine() = default;

  /**
   * @brief Creates engine from configuration.
   * @return Success/failure.
   */
  virtual bool Create();

  /**
   * @brief Renders all objects in scene.
   * @param camera_entity Entity with attached Camera.
   * @param light_entities Entities with attached lights.
   */
  virtual void Render(const Entity& camera_entity,
                      const stl_vector<const Entity*> light_entities);

  // For now, all members are public to be accessible by applications.

  /// Engine configuration.
  Configuration configuration_;

  /// ResourceManager handle.
  std::unique_ptr<ResourceManager> resource_manager_;

  /// Window handle. (Later, will be replaced by a Window Manager class,
  /// because apps might want multiple windows.)
  std::unique_ptr<Window> window_;

  /// Keyboard handle.
  std::unique_ptr<KeyboardInput> keyboard_;

  /// Scene graph.
  std::unique_ptr<ogle::SceneGraph> scene_graph_;

  /// Scene renderer.
  std::unique_ptr<ogle::SceneRenderer> scene_renderer_;
};

}  // namespace ogle

