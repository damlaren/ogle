/**
 * @file resource_manager.h
 * @brief Defines ResourceManager.
 */

#ifndef OGLE_INCLUDES_RESOURCE_RESOURCE_MANAGER_H_
#define OGLE_INCLUDES_RESOURCE_RESOURCE_MANAGER_H_

#include "std/ogle_std.inc"
#include <utility>
#include "file_system/file_path.h"
#include "geometry/mesh.h"
#include "renderer/shader.h"
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
   * @return true if all resources were loaded, else false.
   */
  const bool LoadResources();

  /**
   * @brief Gets a resource of requested type.
   *
   * Only types named in ResourceType can be retrieved.
   *
   * @param id Unique ID of resource to retrieve.
   * @return Pointer to resource, or null if not found.
   */
  template <typename T>
  T* GetResource(const ResourceID& id) {
    auto resource = FindResource(id);
    if (resource && resource->metadata().type() == T::kResourceType) {
      return static_cast<T*>(resource);
    }
    return nullptr;
  }

 private:
  /**
   * @brief Finds a resource.
   * @param id Unique ID of resource to retrieve.
   * @return Pointer to resource, or null if not found.
   */
  Resource* FindResource(const ResourceID& id);

  /// All tracked resources.
  stl_map<ResourceID, std::unique_ptr<Resource>> resources_;

  /// Directories under which to search for resources.
  stl_vector<FilePath> resource_dirs_;
};

}  // namespace ogle

#endif  // OGLE_INCLUDES_RESOURCE_RESOURCE_MANAGER_H_
