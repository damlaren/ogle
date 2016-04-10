/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file Defines Engine.
 */

#ifndef LIBRARIES_ENGINE_INCLUDES_ENGINE_ENGINE_H_
#define LIBRARIES_ENGINE_INCLUDES_ENGINE_ENGINE_H_

#include "std/ogle_std.inc"
#include "input/keyboard_input.h"
#include "renderer/window.h"
#include "resource/resource_manager.h"

namespace ogle {

/**
 * @brief The core object tieing together everything in ogle.
 *
 * The Engine manages every other subsystem in ogle. It is ultimately
 * responsible for all memory allocations, behavior, and control flow,
 * and is the container by which applications access ogle.
 */
class Engine {
 public:
  /**
   * @brief Constructor. Takes over passed objects.
   *
   * All unique_ptr parameters are moved and invalid after calling this
   * constructor.
   *
   * TODO(damlaren): This is a temporary interface. Soon, the Engine itself
   * will take over constructing these objects.
   *
   * @param resource_manager ResourceManager implementation.
   * @param window Window implementation.
   * @param keyboard Keyboard implementation.
   */
  Engine(std::unique_ptr<ResourceManager> resource_manager,
         std::unique_ptr<Window> window,
         std::unique_ptr<KeyboardInput> keyboard);

  /**
   * @brief Destructor.
   */
  virtual ~Engine() = default;

  // For now, all members are public to be accessed by applications.

  /// ResourceManager handle.
  std::unique_ptr<ResourceManager> resource_manager_;

  /// Window handle. (Later, will be replaced by a Window Manager class,
  /// because apps might want multiple windows.)
  std::unique_ptr<Window> window_;

  /// Keyboard handle.
  std::unique_ptr<KeyboardInput> keyboard_;
};

}  // namespace ogle

#endif  // LIBRARIES_ENGINE_INCLUDES_ENGINE_ENGINE_H_
