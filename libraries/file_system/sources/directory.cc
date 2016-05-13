/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file Implementation of directory.h.
 */

#include "file_system/directory.h"
#include "easylogging++.h"  // NOLINT
#include "tinydir.h"  // NOLINT

namespace ogle {

const stl_string DirectoryEntry::kSameDirectoryName = ".";

const stl_string DirectoryEntry::kParentDirectoryName = "..";

std::pair<stl_vector<DirectoryEntry>, bool> DirectoryEntry::ListContents(
    const FilePath& directory_path) {
  stl_vector<DirectoryEntry> found_entries;
  tinydir_dir dir;
  if (tinydir_open(&dir, directory_path.str().c_str()) == -1) {
    LOG(ERROR) << "Failed to open directory path: " << directory_path;
    return {{}, false};
  }

  while (dir.has_next) {
    tinydir_file file;
    if (tinydir_readfile(&dir, &file) == -1) {
      LOG(ERROR) << "Failed to read directory entry in: " << directory_path;
      return {{}, false};
    }
    auto local_file_path = FilePath(file.name);
    auto directory_entry = DirectoryEntry(local_file_path, file.is_dir);
    if (!directory_entry.IsParentDirectoryLink() &&
        !directory_entry.IsSameDirectoryLink()) {
      found_entries.emplace_back(
          DirectoryEntry(directory_path + local_file_path, file.is_dir));
    }
    tinydir_next(&dir);
  }

  tinydir_close(&dir);
  return {found_entries, true};
}

const FilePath& DirectoryEntry::path() const {
  return path_;
}

const bool DirectoryEntry::is_directory() const {
  return is_directory_;
}

const bool DirectoryEntry::IsSameDirectoryLink() const {
  return path_.str() == kSameDirectoryName && is_directory_;
}

const bool DirectoryEntry::IsParentDirectoryLink() const {
  return path_.str() == kParentDirectoryName && is_directory_;
}

DirectoryEntry::DirectoryEntry(const FilePath& path, const bool is_directory)
  : path_(path), is_directory_(is_directory) {
}

}  // namespace ogle
