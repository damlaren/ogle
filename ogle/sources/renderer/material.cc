/**
 * @file material.cc
 * @brief Implements material.h.
 */

#include "renderer/material.h"
#include "file_system/text_file.h"
#include "renderer/shader_program.h"
#include "resource/resource_manager.h"
#include "util/string_utils.h"

namespace ogle {

const stl_string Material::StandardPropertyName::kAmbientReflectance =
    "ambient_reflectance";
const stl_string Material::StandardPropertyName::kDiffuseReflectance =
    "diffuse_reflectance";
const stl_string Material::StandardPropertyName::kSpecularReflectance =
    "specular_reflectance";
const stl_string Material::StandardPropertyName::kSpecularExponent =
    "specular_exponent";

const stl_string Material::kMTLImplementation = "mtl";

Material::Material(const ResourceMetadata& metadata) : Resource(metadata) {}

const stl_string Material::implementation() const {
  return shader_program_->implementation();
}

std::unique_ptr<Material> Material::Load(const ResourceMetadata& metadata,
                                         ResourceManager* resource_manager) {
  if (metadata.type() != ResourceType::MATERIAL) {
    LOG(ERROR) << "Attempt to load Material from incorrect metadata type: "
               << metadata.type();
    return nullptr;
  }

  stl_string text;
  if (!ogle::TextFile::ReadTextFile(metadata.resource_path(), &text)) {
    LOG(ERROR) << "Failed to read material text from: "
               << metadata.resource_path();
    return nullptr;
  }

  auto new_object = AllocateUniqueObject<Material>(metadata);
  const auto implementation =
      metadata.Get<stl_string>(Resource::kImplementationField).first;
  if (implementation == Material::kMTLImplementation) {
    if (!new_object->LoadMTL(text)) {
      LOG(ERROR) << "Material Create() failed.";
      return nullptr;
    }
  } else {
    LOG(ERROR) << "Unable to create Material for implementation: "
               << implementation;
    return nullptr;
  }

  const auto shader_program_id =
      metadata.Get<stl_string>("shader_program").first;
  new_object->shader_program_ =
      resource_manager->GetResource<ShaderProgram>(shader_program_id);
  return std::move(new_object);
}

bool Material::LoadMTL(const stl_string& text) {
  int newmtl_count = 0;
  for (const auto& line : StringUtils::Split(text, '\n')) {
    const auto trimmed_line = StringUtils::Trim(line, " \t\n\r");
    auto tokens = StringUtils::Split(trimmed_line, ' ');
    if (tokens.empty()) {
      continue;
    }
    const auto line_type = tokens[0];

    auto read_float3 = [&](const stl_string& name) {
      if (tokens.size() < 4) {
        LOG(ERROR) << "Not enough tokens to read Vector3f.";
        return false;
      }
      std::vector<float> values = {std::stof(tokens[1]), std::stof(tokens[2]),
                                   std::stof(tokens[3])};
      variable_bindings_.emplace_back(
          AllocateObject<PropertyInstance<float>>(
              name, std::vector<PropertyDimIndex>({3}), values.data()));
      return true;
    };

    bool ok = true;
    if (line_type == "newmtl") {
      if (newmtl_count > 0) {
        LOG(ERROR) << "Only one material is supported per MTL file.";
        return false;
      }
      newmtl_count++;
    } else if (line_type == "Ka") {
      ok = read_float3(StandardPropertyName::kAmbientReflectance);
    } else if (line_type == "Kd") {
      ok = read_float3(StandardPropertyName::kDiffuseReflectance);
    } else if (line_type == "Ks") {
      ok = read_float3(StandardPropertyName::kSpecularReflectance);
    } else if (line_type == "Ns") {
      if (tokens.size() != 2) {
        ok = false;
      } else {
        float float_val = std::stof(tokens[1]);
        variable_bindings_.emplace_back(AllocateObject<PropertyInstance<float>>(
            stl_string(StandardPropertyName::kSpecularExponent),
            std::vector<PropertyDimIndex>(), &float_val));
      }
    }
    if (!ok) {
      LOG(ERROR) << "Not enough tokens to finish reading MTL: " << trimmed_line;
      return false;
    }
  }
  return true;
}

void Material::UseProgram() { shader_program_->UseProgram(); }

void Material::SetVariable(const Property &variable) {
  shader_program_->SetVariable(variable.name(), variable);
}

void Material::SetVariable(const stl_string& name, const Property& variable) {
  shader_program_->SetVariable(name, variable);
}

void Material::SetBoundVariables() {
  for (const auto& variable : variable_bindings_) {
    SetVariable(*variable.get());
  }
}

}  // namespace ogle
