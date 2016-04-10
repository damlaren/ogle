/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file Implementation of engine.h.
 */

#include "engine/engine.h"

namespace ogle {

Engine::Engine(std::unique_ptr<ResourceManager> resource_manager,
               std::unique_ptr<Window> window,
               std::unique_ptr<KeyboardInput> keyboard)
  : resource_manager_(std::move(resource_manager)), window_(std::move(window)),
    keyboard_(std::move(keyboard)),
    scene_graph_(std::make_unique<ogle::SceneGraph>()),
    scene_renderer_(std::make_unique<ogle::SceneRenderer>()) {
}

void Engine::Render(Entity* camera_entity) {
  window_->ClearWindow();
  scene_renderer_->RenderScene(camera_entity, scene_graph_.get());
  window_->SwapBuffers();
}

}  // namespace ogle