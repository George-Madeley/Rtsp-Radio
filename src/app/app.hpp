#pragma once

#include "player/player.hpp"

#include <string>
#include <vector>
namespace app
{
class App
{
public:
  App() = default;
  ~App() = default;

  /**
   * @brief Initializes the application.
   * @return true if initialization is successful, false otherwise.
   */
  bool init();

  /**
   * @brief Starts the application.
   */
  void start(const std::string& directory_path);

private:
  player::Player _player;

  bool is_directory_valid(const std::string& path) const;

  bool get_file(const std::vector<std::string>& files, std::string& file_path) const;
};
}
