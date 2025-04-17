#include "app.hpp"
#include "utils/file_selector.hpp"

#include <filesystem>
#include <loguru.hpp>

namespace fs = std::filesystem;

namespace app
{
bool App::init()
{
  if(!_player.init())
  {
    LOG_S(ERROR) << "Failed to initialize player.";
    return false;
  }
  return true;
}

void App::start(const std::string& directory_path)
{
  if(!is_directory_valid(directory_path))
  {
    LOG_S(WARNING) << "Invalid directory path: " << directory_path;
    return;
  }

  std::vector<std::string> files;
  while(utils::FileSelector::get_files(directory_path, files))
  {
    std::string file_path;
    if(!get_file(files, file_path))
    {
      LOG_S(WARNING) << "No playable file found in the directory.";
      break;
    }

    if(!_player.play(file_path))
    {
      LOG_S(ERROR) << "Failed to play file: " << file_path;
      break;
    }
  }

  LOG_S(INFO) << "Playback finished.";
}

bool App::is_directory_valid(const std::string& path) const
{
  return fs::exists(path) && fs::is_directory(path);
}

bool App::get_file(const std::vector<std::string>& files, std::string& file_path) const
{
  file_path = utils::FileSelector::pick_file(files);
  return !file_path.empty() && utils::FileSelector::file_playable(file_path);
}
} // namespace app
