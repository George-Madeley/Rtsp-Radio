#ifndef PLAYER_HPP
#define PLAYER_HPP

#pragma once

#include <string>

namespace player
{
class Player
{
public:
  Player();
  ~Player();

  /**
   * @brief Initializes the audio player.
   */
  bool init();

  bool play(const std::string& file_path);

private:
};
} // namespace player

#endif // PLAYER_HPP
