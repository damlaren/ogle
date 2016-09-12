/**
 * @file light.h
 * @brief Defines Light.
 */

#pragma once

#include "std/ogle_std.inc"
#include "entity/component.h"
#include "entity/property.h"
#include "math/vector.h"

namespace ogle {

/**
 * @brief A light source.
 */
class Light : public Component {
 public:
  /**
   * @brief Contains standardized names of common light properties.
   */
  class StandardPropertyName {
   public:
    /// Ambient color.
    static const stl_string kAmbientColor;

    /// Diffuse color.
    static const stl_string kDiffuseColor;

    /// Specular color.
    static const stl_string kSpecularColor;
  };

  /// Run-time type for all lights.
  static constexpr ComponentType kComponentType = ComponentType::LIGHT;

  /**
   * @brief Constructor.
   */
  Light();

  /**
   * @brief Sets color properties used in the common Phong lighting model.
   * @param ambient_color Ambient RGB, in range [0,1].
   * @param diffuse_color Diffuse RGB, in [0,1].
   * @param specular_color Specular RGB, in [0,1].
   */
  void SetPhongLightColors(const Vector3f& ambient_color,
                           const Vector3f& diffuse_color,
                           const Vector3f& specular_color);
};

}  // namespace ogle
