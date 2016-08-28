/**
 * @file renderer.cc
 * @brief Implementation of renderer.h.
 */

#include "renderer/renderer.h"

namespace ogle {

const stl_string Renderer::kConfigModule = "render";

const stl_string Renderer::kConfigAttributeImplementation = "implementation";

Renderer::Renderer()
  : Component(ComponentType::RENDERER) {
}

}  // namespace ogle
