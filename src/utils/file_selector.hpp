#pragma once

#include <string>
#include <vector>

namespace utils
{
class FileSelector
{
public:
  static std::vector<std::string> get_files(const std::string& directory_path);

  static std::string pick_file(const std::vector<std::string>& files);

  static bool file_playable(const std::string& file_path);
};
}
