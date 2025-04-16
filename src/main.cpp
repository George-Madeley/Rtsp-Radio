#include "argparse/argparse.hpp"
#include "player/player.hpp"
#include "utils/file_selector.hpp"

#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

int main(int argc, char* argv[])
{
  argparse::ArgumentParser program("RTSP Radio");

  program.add_argument("-s", "--source").help("File path to the source files").required();

  try
  {
    program.parse_args(argc, argv);
  }
  catch(const std::exception& err)
  {
    std::cerr << err.what() << std::endl;
    std::cerr << program;
    return 1;
  }

  auto source = program.get<std::string>("--source");
  // Validate the file path
  if(!fs::exists(source))
  {
    std::cerr << "Error: The provided path does not exist: " << source << std::endl;
    return 1;
  }

  if(!fs::is_directory(source))
  {
    std::cerr << "Error: The provided path is not a directory: " << source << std::endl;
    return 1;
  }
  player::Player player;

  auto files = utils::FileSelector::get_files(source);
  if(files.empty())
  {
    std::cerr << "No playable files found in " << source << std::endl;
    return 1;
  }

  while(true)
  {
    auto file = utils::FileSelector::pick_file(files);
    if(file.empty())
    {
      std::cerr << "No playable files found in " << source << std::endl;
      break;
    }

    if(!utils::FileSelector::file_playable(file))
    {
      std::cerr << "File not playable: " << file << std::endl;
      continue;
    }

    player.play(file);

    // Simulate waiting for playback to finish
    std::this_thread::sleep_for(std::chrono::seconds(5));

    // In a real application, you would check if the playback is still active and wait accordingly.
    // For this example, we just wait for a fixed duration.
    // You can also implement a more sophisticated mechanism to check if the playback is still active.
    // For example, you could use a condition variable or a future/promise mechanism to wait for the playback to finish.
    player.stop(); // Uncomment this if you want to stop playback after the fixed duration.
  }

  return 0;
}
