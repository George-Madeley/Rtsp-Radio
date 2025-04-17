#include "app.hpp"
#include "utils/file_selector.hpp"

#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

namespace app
{
bool App::init()
{
  if(!_player.init())
  {
    std::cerr << "Failed to initialize player." << std::endl;
    return false;
  }
  return true;
}

void App::start(const std::string& directory_path)
{
  if(!is_directory_valid(directory_path))
  {
    std::cerr << "Invalid directory path: " << directory_path << std::endl;
    return;
  }

  std::vector<std::string> files;
  while(utils::FileSelector::get_files(directory_path, files))
  {
    std::string file_path;
    if(!get_file(files, file_path))
    {
      std::cerr << "No playable file found in the directory." << std::endl;
      break;
    }

    _player.play(file_path);

    // Simulate waiting for playback to finish
    std::this_thread::sleep_for(std::chrono::seconds(5));

    // In a real application, you would check if the playback is still active and wait accordingly.
    // For this example, we just wait for a fixed duration.
    // You can also implement a more sophisticated mechanism to check if the playback is still active.
    // For example, you could use a condition variable or a future/promise mechanism to wait for the playback to finish.
    _player.stop(); // Uncomment this if you want to stop playback after the fixed duration.
  }
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
