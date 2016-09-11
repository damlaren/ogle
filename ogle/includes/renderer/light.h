/**
 * @file light.h
 * @brief Defines Light.
 */

#pragma once

#include "std/ogle_std.inc"
#include "entity/component.h"
#include "entity/property.h"

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
};

}  // namespace ogle
