/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file Defines Engine.
 */

#ifndef OGLE_INCLUDES_ENGINE_ENGINE_H_
#define OGLE_INCLUDES_ENGINE_ENGINE_H_

#include "std/ogle_std.inc"
#include "config/configuration.h"
#include "input/keyboard_input.h"
#include "window/window.h"
#include "renderer/scene_graph.h"
#include "renderer/scene_renderer.h"
#include "resource/resource_manager.h"

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
   */
  virtual void Render(Entity* camera_entity);

  // For now, all members are public to be accessed by applications.

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

#endif  // OGLE_INCLUDES_ENGINE_ENGINE_H_
