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
#include "file_system/file_path.h"
#include "resource/resource.h"

namespace ogle {

/**
 * @brief Class to manage and load resources.
 *
 * Right now it just provides the location of the resource directory.
 */
class ResourceManager {
 public:
  /**
   * @brief Registers a loader function to construct resource.
   * @param type Type of resource to construct.
   * @param implementation Implementation created by loader.
   * @param loader Factory function.
   */
  static void RegisterLoader(
      const stl_string& type, const stl_string& implementation,
      Resource::LoadFunction loader);

  /**
   * @brief Add directory to list to search for Resources.
   * @param directory_path Path to add.
   */
  void AddResourceDirectory(const FilePath& directory_path);

  /**
   * @brief Load resources under a directory.
   *
   * TODO(damlaren): This is a temporary solution that wouldn't scale well.
   *
   * @param root_directory Directory under which to search.
   * @return success/failure.
   */
  const bool LoadResources(const FilePath& root_directory);

 private:
  /// Directories under which to search for resources.
  stl_vector<FilePath> resource_dirs_;
};

}  // namespace ogle

#endif  // LIBRARIES_RESOURCE_INCLUDES_RESOURCE_RESOURCE_MANAGER_H_
