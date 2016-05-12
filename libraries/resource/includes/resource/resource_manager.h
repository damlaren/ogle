/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file Defines ResourceManager.
 */

#ifndef LIBRARIES_RESOURCE_INCLUDES_RESOURCE_RESOURCE_MANAGER_H_
#define LIBRARIES_RESOURCE_INCLUDES_RESOURCE_RESOURCE_MANAGER_H_

#include "std/ogle_std.inc"
#include <utility>
#include "file_system/file_path.h"
#include "resource/resource.h"

namespace ogle {

class ResourceMetadata;

/**
 * @brief Class to manage and load resources.
 *
 * Right now it just provides the location of the resource directory.
 */
class ResourceManager {
 public:
  /**
   * @brief Adds directory to list to search for Resources.
   * @param directory_path Path to add.
   */
  void AddResourceDirectory(const FilePath& directory_path);

  /**
   * @brief Loads a single resource from metadata.
   * @param metadata Resource metadata.
   * @return true if resource is available.
   */
  const bool LoadResource(const ResourceMetadata& metadata);

  /**
   * @brief Loads all resources from configured directories.
   */
  void LoadResources();

  /**
   * @brief Finds a resource.
   * @param id Unique ID of resource to retrieve.
   * @return Pointer to resource, or null if not found.
   */
  Resource* GetResource(const ResourceID& id);

 private:
  /// All tracked resources.
  stl_map<ResourceID, std::unique_ptr<Resource>> resources_;

  /// Directories under which to search for resources.
  stl_vector<FilePath> resource_dirs_;
};

}  // namespace ogle

#endif  // LIBRARIES_RESOURCE_INCLUDES_RESOURCE_RESOURCE_MANAGER_H_
