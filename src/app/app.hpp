#pragma once

#include "player/player.hpp"

#include <string>
#include <vector>
namespace app
{
class App
{
public:
  /**
   * @brief Constructor for the App class.
   */
  App() = default;

  /**
   * @brief Destructor for the App class.
   */
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
  /* Audio player */
  player::Player _player;

  /**
   * @brief Checks if the provided directory path is valid.
   *
   * @param path The directory path to check.
   * @return true if the directory path is valid, false otherwise.
   */
  bool is_directory_valid(const std::string& path) const;

  /**
   * @brief Retrieves a playable file from the provided list of files.
   *
   * @param files The list of files to choose from.
   * @param file_path The path of the selected file.
   * @return true if a playable file is found, false otherwise.
   */
  bool get_file(const std::vector<std::string>& files, std::string& file_path) const;
};
}
