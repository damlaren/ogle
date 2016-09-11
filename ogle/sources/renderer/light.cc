/**
 * @file light.cc
 * @brief Implements light.h.
 */

#include "renderer/light.h"

namespace ogle {

const stl_string Material::StandardPropertyName::kAmbientColor =
    "ambient_color";
const stl_string Material::StandardPropertyName::kDiffuseColor =
    "diffuse_color";
const stl_string Material::StandardPropertyName::kSpecularColor =
    "specular_color";

Light::Light()
  : Component(ComponentType::LIGHT) {
}

}  // namespace ogle
