/**
 * @file yaml_file.h
 * @brief Defines YAMLFile.
 */

#ifndef OGLE_INCLUDES_FILE_SYSTEM_YAML_FILE_H_
#define OGLE_INCLUDES_FILE_SYSTEM_YAML_FILE_H_

#include "std/ogle_std.inc"
#include <utility>

namespace ogle {

class FilePath;

class YAMLFile {
 public:
  /**
   * @brief Default constructor.
   */
  YAMLFile();

  /**
   * @brief Destructor.
   */
  ~YAMLFile();

  /**
   * @brief Copy constructor.
   * @param rhs Object to copy.
   */
  YAMLFile(const YAMLFile& rhs);

  /**
   * @brief Copy assignment operator.
   * @param Object to assign from.
   * @return Reference to this object.
   */
  YAMLFile& operator=(const YAMLFile& rhs);

  /**
   * @brief Output stream operator.
   * @param[in,out] os Output stream.
   * @param yaml_file File data to print.
   * @return Reference to #os.
   */
  friend std::ostream& operator<<(std::ostream& os,  // NOLINT
                                  const YAMLFile& yaml_file);

  /**
   * @brief Loads configuration from file.
   * @param file_path Name of file from which to load.
   * @return success/failure.
   */
  bool Load(const FilePath& file_path);

  /**
   * @brief Gets value from a YAML file.
   * @param keys Hierarchy of key names for which to look up a value.
   * @return Pair containing: (1) Retrieved value, or default-constructed object
   *         if nothing found; and (2) flag indicating whether value was found.
   */
  template <typename T>
  const std::pair<T, bool> Get(const stl_vector<stl_string>& keys) const;

 private:
  struct Data;

  /// Hidden implementation of yaml data.
  Data* data_;
};

}  // namespace ogle

#endif  // OGLE_INCLUDES_FILE_SYSTEM_YAML_FILE_H_
