#include "file_selector.hpp"

#include <filesystem>
#include <iostream>
#include <time.h>

namespace fs = std::filesystem;

namespace utils
{
std::vector<std::string> FileSelector::get_files(const std::string& directory_path)
{
  std::vector<std::string> mp3_files;

  try
  {
    for(const auto& entry : fs::directory_iterator(directory_path))
    {
      if(entry.is_regular_file() && entry.path().extension() == ".mp3")
      {
        mp3_files.push_back(entry.path().string());
      }
    }
  }
  catch(const std::exception& e)
  {
    std::cerr << "Error reading directory: " << e.what() << std::endl;
  }

  return mp3_files;
}

std::string FileSelector::pick_file(const std::vector<std::string>& files)
{
  if(files.empty())
  {
    return "";
  }

  std::srand(static_cast<unsigned int>(time(nullptr)));
  int random_index = std::rand() % files.size();
  return files[random_index];
}

bool FileSelector::file_playable(const std::string& file_path)
{
  std::string extension = file_path.substr(file_path.find_last_of('.') + 1);
  return (extension == "mp3" || extension == "wav" || extension == "ogg" || extension == "flac");
}
} // namespace utils
