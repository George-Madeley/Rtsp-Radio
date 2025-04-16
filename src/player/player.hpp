#ifndef PLAYER_HPP
#define PLAYER_HPP

#pragma once

#include <atomic>
#include <string>
#include <thread>

namespace player
{
class Player
{
public:
  Player();
  ~Player();

  void play(const std::string& file_path);
  void stop();

private:
  std::atomic<bool> is_playing;
  std::thread playback_thread;

  void playback(const std::string& file_path);
};
} // namespace player

#endif // PLAYER_HPP
