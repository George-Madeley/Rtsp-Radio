#include "player.hpp"

#include <chrono>
#include <iostream>
#include <thread>

namespace player
{
Player::Player():
    is_playing(false)
{
}

Player::~Player()
{
  stop();
}

void Player::play(const std::string& file_path)
{
  if(is_playing)
  {
    std::cerr << "A song is already playing. Stop it first before playing a new one." << std::endl;
    return;
  }

  is_playing = true;
  playback_thread = std::thread(&Player::playback, this, file_path);
}

void Player::stop()
{
  if(is_playing)
  {
    is_playing = false;
    if(playback_thread.joinable())
    {
      playback_thread.join();
    }
  }
}

void Player::playback(const std::string& file_path)
{
  std::cout << "Playing: " << file_path << std::endl;

  // Simulate playback by sleeping for a fixed duration (e.g., 5 seconds for testing)
  // Replace this with actual audio playback logic using a library like PortAudio or FFmpeg.
  for(int i = 0; i < 5 && is_playing; ++i)
  {
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }

  if(is_playing)
  {
    std::cout << "Finished playing: " << file_path << std::endl;
  }
  else
  {
    std::cout << "Playback stopped: " << file_path << std::endl;
  }

  is_playing = false;
}
} // namespace player
