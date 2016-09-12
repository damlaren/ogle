/**
 * @file light.cc
 * @brief Implements light.h.
 */

#include "renderer/light.h"

namespace ogle {

const stl_string Light::StandardPropertyName::kAmbientColor = "ambient_color";
const stl_string Light::StandardPropertyName::kDiffuseColor = "diffuse_color";
const stl_string Light::StandardPropertyName::kSpecularColor = "specular_color";

Light::Light() : Component(ComponentType::LIGHT) {}

void Light::SetPhongLightColors(const Vector3f& ambient_color,
                                const Vector3f& diffuse_color,
                                const Vector3f& specular_color) {
  SetProperty(PropertyInstance<float>(StandardPropertyName::kAmbientColor, {3},
                                      ambient_color.data()));
  SetProperty(PropertyInstance<float>(StandardPropertyName::kDiffuseColor, {3},
                                      diffuse_color.data()));
  SetProperty(PropertyInstance<float>(StandardPropertyName::kSpecularColor, {3},
                                      specular_color.data()));
}

}  // namespace ogle
