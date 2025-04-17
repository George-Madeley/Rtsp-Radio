#pragma once

#include <string>
#include <vector>

namespace utils
{
class FileSelector
{
public:
  static bool get_files(const std::string& directory_path, std::vector<std::string>& files);

  static std::string pick_file(const std::vector<std::string>& files);

  static bool file_playable(const std::string& file_path);
};
}
