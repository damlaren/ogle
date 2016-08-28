/**
 * @file directory.cc
 * @brief Implementation of directory.h.
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
