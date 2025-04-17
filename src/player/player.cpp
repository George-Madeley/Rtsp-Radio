#include "player.hpp"
#include "portaudio.h"

#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>

namespace player
{
Player::Player()
{
}

Player::~Player()
{
  Pa_Terminate();
}

bool Player::init()
{
  return Pa_Initialize() == paNoError;
}

bool Player::play(const std::string& file_path)
{
  std::cout << "Playing: " << file_path << std::endl;

  // Open the WAV file
  std::ifstream wav_file(file_path, std::ios::binary);
  if(!wav_file)
  {
    std::cerr << "Failed to open WAV file: " << file_path << std::endl;
    return false;
  }

  // Read the WAV header
  char header[44];
  wav_file.read(header, sizeof(header));
  if(wav_file.gcount() < sizeof(header))
  {
    std::cerr << "Invalid WAV file: " << file_path << std::endl;
    return false;
  }

  // Extract audio format information from the header
  int sample_rate = *reinterpret_cast<int*>(header + 24);
  short channels = *reinterpret_cast<short*>(header + 22);
  short bits_per_sample = *reinterpret_cast<short*>(header + 34);

  if(std::strncmp(header, "RIFF", 4) != 0 || std::strncmp(header + 8, "WAVE", 4) != 0)
  {
    std::cerr << "Invalid WAV file format: " << file_path << std::endl;
    return false;
  }

  if(bits_per_sample != 16)
  {
    std::cerr << "Only 16-bit WAV files are supported." << std::endl;
    return false;
  }

  // Configure PortAudio
  PaStream* stream;
  PaStreamParameters output_params;
  output_params.device = Pa_GetDefaultOutputDevice();
  output_params.channelCount = channels;
  output_params.sampleFormat = paInt16;

  if(output_params.device == paNoDevice)
  {
    std::cerr << "No default output device available." << std::endl;
    return false;
  }

  if(Pa_GetDeviceInfo(output_params.device) == nullptr)
  {
    std::cerr << "Failed to get device info." << std::endl;
    return false;
  }
  output_params.suggestedLatency = Pa_GetDeviceInfo(output_params.device)->defaultLowOutputLatency;
  output_params.hostApiSpecificStreamInfo = nullptr;

  if(Pa_OpenStream(&stream, nullptr, &output_params, sample_rate, paFramesPerBufferUnspecified, paClipOff, nullptr,
         nullptr) != paNoError)
  {
    std::cerr << "Failed to open PortAudio stream." << std::endl;
    return false;
  }

  if(Pa_StartStream(stream) != paNoError)
  {
    std::cerr << "Failed to start PortAudio stream." << std::endl;
    Pa_CloseStream(stream);
    return false;
  }

  // Read and play audio data
  const size_t buffer_size = 4096;
  std::vector<char> buffer(buffer_size);

  while(wav_file.read(buffer.data(), buffer_size))
  {
    std::streamsize frames_read = wav_file.gcount() / (bits_per_sample / 8 * channels);
    if(Pa_WriteStream(stream, buffer.data(), (unsigned long)frames_read) != paNoError)
    {
      std::cerr << "Error writing to PortAudio stream." << std::endl;
      break;
    }
  }

  // Handle any remaining data in the buffer
  if(wav_file.gcount() > 0)
  {
    std::streamsize frames_read = wav_file.gcount() / (bits_per_sample / 8 * channels);
    Pa_WriteStream(stream, buffer.data(), (unsigned long)frames_read);
  }

  // Clean up
  Pa_StopStream(stream);
  Pa_CloseStream(stream);
  wav_file.close();

  std::cout << "Finished playing: " << file_path << std::endl;

  return true;
}
} // namespace player
