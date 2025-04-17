#pragma once

#include <string>
#include <vector>

namespace utils
{
class FileSelector
{
public:
  /**
   * @brief Retrieves all playable files from the specified directory.
   *
   * @param directory_path The path to the directory to search for files.
   * @param files A vector to store the paths of the playable files found.
   * @return true if playable files are found, false otherwise.
   */
  static bool get_files(const std::string& directory_path, std::vector<std::string>& files);

  /**
   * @brief Picks a random file from the provided list of files.
   *
   * @param files A vector containing the paths of files to choose from.
   * @return A string representing the path of the randomly selected file.
   */
  static std::string pick_file(const std::vector<std::string>& files);

  /**
   * @brief Checks if a file is playable based on its extension.
   *
   * @param file_path The path to the file to check.
   * @return true if the file is playable, false otherwise.
   */
  static bool file_playable(const std::string& file_path);
};
}
