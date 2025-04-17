#ifndef PLAYER_HPP
#define PLAYER_HPP

#pragma once

#include <string>

namespace player
{
class Player
{
public:
  /**
   * @brief Constructor for the Player class.
   */
  Player();

  /**
   * @brief Destructor for the Player class.
   */
  ~Player();

  /**
   * @brief Initializes the audio player.
   */
  bool init();

  /**
   * @brief Plays the specified audio file.
   *
   * @param file_path The path to the audio file to play.
   * @return true if the file is played successfully, false otherwise.
   */
  bool play(const std::string& file_path);

private:
};
} // namespace player

#endif // PLAYER_HPP
