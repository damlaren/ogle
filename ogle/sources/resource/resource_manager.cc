/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file Implementation of resource_manager.h.
 */

#include "resource/resource_manager.h"
#include "easylogging++.h"  // NOLINT
#include "algorithms/directed_graph.h"
#include "file_system/directory.h"
#include "geometry/mesh.h"
#include "renderer/shader.h"
#include "resource/resource_metadata.h"
#include "util/string_utils.h"

namespace ogle {

void ResourceManager::AddResourceDirectory(const FilePath& directory_path) {
  resource_dirs_.emplace_back(directory_path);
}

const bool ResourceManager::LoadResource(const ResourceMetadata& metadata) {
  if (resources_.find(metadata.id()) != resources_.end()) {
    LOG(ERROR) << "Resource has already been loaded: " << metadata.id();
    return true;
  }

  const auto type = metadata.type();
  std::unique_ptr<Resource> resource = nullptr;
  if (type == ResourceType::SHADER) {
    resource = std::move(Shader::Load(metadata));
  } else if (type == ResourceType::SHADER_PROGRAM) {
    resource = std::move(ShaderProgram::Load(metadata, this));
  } else if (type == ResourceType::MESH) {
    resource = std::move(Mesh::Load(metadata));
  }
  if (resource != nullptr) {
    resources_[metadata.id()] = std::move(resource);
    return true;
  }

  LOG(ERROR) << "Failed to load resource: " << metadata;
  return false;
}

bool ResourceManager::LoadResources() {
  stl_list<FilePath> directories_to_search;
  for (const auto& resource_dir : resource_dirs_) {
    directories_to_search.emplace_back(resource_dir);
  }

  using ResourceGraph = DirectedGraph<ResourceID, ResourceMetadata>;
  ResourceGraph resource_graph;
  while (!directories_to_search.empty()) {
    const auto search_dir = directories_to_search.front();
    directories_to_search.pop_front();

    const auto contents = DirectoryEntry::ListContents(search_dir);
    if (!contents.second) {
      LOG(ERROR) << "Failed to read contents from: " << search_dir;
      continue;
    }

    // Load all resource metadata upfront, so resource dependencies can be
    // tracked.
    for (const auto& directory_entry : contents.first) {
      const auto& entry_path = directory_entry.path();
      if (directory_entry.is_directory()) {
        directories_to_search.emplace_back(entry_path);
      } else if (StringUtils::Lower(entry_path.Extension()) ==
                 ResourceMetadata::kFileExtension) {
        auto metadata_result = ResourceMetadata::Load(entry_path);
        if (!metadata_result.second) {
          LOG(ERROR) << "Failed to load metadata from: " << entry_path;
        } else {
          const ResourceID& resource_id = metadata_result.first.id();
          if (!resource_graph.AddNode(resource_id, metadata_result.first)) {
            LOG(ERROR) << "Failed to track resource in dependency graph.";
          } else {
            const auto get_result = resource_graph.GetValue(resource_id);
            CHECK(get_result.second == true)
                << "Added resource not found in graph.";
            for (const auto& dependency_id : get_result.first.dependencies()) {
              if (!resource_graph.AddEdge(resource_id, dependency_id)) {
                LOG(ERROR) << "Failed to add edge to resource graph: "
                           << resource_id << " -> " << dependency_id;
              }
            }
          }
        }
      }
    }
  }

  // Load resources, being careful of dependencies.
  auto last_size = resource_graph.Size();
  while (!resource_graph.Empty()) {
    auto undependent_resources = resource_graph.GetMatches(
          [](const ResourceGraph::Node* node){
              return node->neighbors().empty(); });
    for (const auto& resource_data : undependent_resources) {
      if (!LoadResource(*resource_data.second)) {
        LOG(ERROR) << "Failed to load resource from metadata in: "
                   << resource_data.second->resource_path();
        return false;  // Can't load dependent resources.
      }
      CHECK(resource_graph.Remove(resource_data.first))
          << "Expected to remove node that is known to exist.";
    }

    auto curr_size = resource_graph.Size();
    if (last_size == curr_size) {
      LOG(ERROR) << "Cyclic dependency found in resources; bailing out.";
      return false;
    }
    last_size = curr_size;
  }

  return true;
}

Resource* ResourceManager::FindResource(const ResourceID& id) {
  const auto it = resources_.find(id);
  if (it == resources_.end()) {
    LOG(ERROR) << "Cannot find resource: " << id;
    return nullptr;
  }
  return it->second.get();
}

}  // namespace ogle
