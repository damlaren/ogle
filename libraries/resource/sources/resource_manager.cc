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
#include "file_system/directory.h"
#include "renderer/shader.h"
#include "resource/resource_metadata.h"
#include "util/string_utils.h"

namespace ogle {

void ResourceManager::AddResourceDirectory(const FilePath& directory_path) {
  resource_dirs_.emplace_back(directory_path);
}

const bool ResourceManager::LoadResource(const ResourceMetadata& metadata) {
  if (resources_.find(metadata.id()) != resources_.end()) {
    LOG(WARNING) << "Resource has already been loaded.";
    return true;
  }

  const auto& type = metadata.Get<stl_string>(Resource::kTypeField);
  if (type.empty()) {
    LOG(ERROR) << "Resource type not found: " << metadata;
    return false;
  }

  if (type == Shader::kResourceType) {
    auto resource = std::move(Shader::Load(metadata));
    if (resource != nullptr) {
      resources_[metadata.id()] = std::move(resource);
    }
  }

  LOG(ERROR) << "Failed to load resource: " << metadata;
  return false;
}

void ResourceManager::LoadResources() {
  stl_list<FilePath> directories_to_search;
  for (const auto& resource_dir : resource_dirs_) {
    directories_to_search.emplace_back(resource_dir);
  }

  while (!directories_to_search.empty()) {
    const auto& search_dir = directories_to_search.front();
    directories_to_search.pop_front();

    const auto contents = DirectoryEntry::ListContents(search_dir);
    if (!contents.second) {
      LOG(ERROR) << "Failed to read contents from: " << search_dir;
      continue;
    }

    for (const auto& directory_entry : contents.first) {
      const auto& entry_path = directory_entry.path();
      if (directory_entry.is_directory()) {
        directories_to_search.emplace_back(entry_path);
        continue;
      }

      if (entry_path.Extension() == ResourceMetadata::kFileExtension) {
        const auto metadata = ResourceMetadata::Load(entry_path);
        if (!metadata.loaded()) {
          LOG(ERROR) << "Failed to load metadata from: " << entry_path;
          continue;
        }

        if (!LoadResource(metadata)) {
          LOG(ERROR) << "Failed to load resource from metadata in: "
                     << entry_path;
        }
      }
    }
  }
}

}  // namespace ogle
